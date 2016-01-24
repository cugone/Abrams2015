/**************************************************************************************************
// file:	Engine\Physics\CWorld.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the world class
 **************************************************************************************************/
#define NOMINMAX

#include "CWorld.h"

#include "../a2de_exceptions.h"
#include "../a2de_math.h"
#include "../a2de_graphics.h"
#include "CRigidBody.h"

#include <utility>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "../GFX/CSprite.h"
#include "../Objects/ADTEntity.h"
#include "CRigidBody.h"
#include "CContactPair.h"
#include "CContactData.h"

#include "../Objects/ADTEntity.h"

#include "../GFX/CRenderManager.h"

#include <set>

A2DE_BEGIN

World::World(const a2de::WorldDef& world_definition) throw(...) : _dimensions(Vector2D(world_definition.width, world_definition.height)), _cameras(MapCams()), _objects(Objects()), _gh(nullptr), _dh(nullptr), _render_context(nullptr), _grid(), _max_velocity_solve_count(world_definition.max_velocity_solve_count), _max_position_solve_count(world_definition.max_position_solve_count), _cur_vsc(0), _cur_psc(0) {
    a2de::Math::SetWorldScale(world_definition.scale);
    
    try {
        //Don't bother allocating gravity and drag forces if the gravity and drag will not affect physics!
        if(a2de::Math::IsEqual(world_definition.gravity_x, 0.0) == false || a2de::Math::IsEqual(world_definition.gravity_y, 0.0) == false) {
            _gh = new GravityForceGenerator(world_definition.gravity_x, world_definition.gravity_y);
        }
        if(a2de::Math::IsEqual(world_definition.drag_linear, 0.0) == false || a2de::Math::IsEqual(world_definition.drag_quadratic, 0.0) == false) {
            _dh = new DragForceGenerator(world_definition.drag_linear, world_definition.drag_quadratic);
        }
        _render_context = new a2de::RenderManager(*al_get_current_display());

        _grid = new QuadTree<a2de::Vector2D>(a2de::Rectangle(Vector2D(world_definition.width, world_definition.height) / 2.0, Vector2D(world_definition.width, world_definition.height) / 2.0, al_map_rgb(0, 255, 0), false));

    } catch(...) {
        DeallocateWorld();
        throw;
    }
}

World::~World() {
    DeallocateWorld();
}

bool World::AddCamera(const Camera& camera) {
    MapCams::size_type msize = _cameras.max_size();
    MapCams::size_type s = _cameras.size();
    if(msize == s) return false;
    std::pair<MapCamsIter, bool> result = _cameras.insert(std::make_pair(s, camera));
    return result.second;
}

bool World::RemoveCamera(const unsigned char camera_index) {
    MapCamsIter result = _cameras.find(camera_index);
    MapCamsIter e = _cameras.end();
    if(result == e) return false;
    return (_cameras.erase(result) == e);
}

bool World::RemoveCamera(const Camera& camera) {

    MapCamsIter b = _cameras.begin();
    MapCamsIter e = _cameras.end();
    for(MapCamsIter _iter = b; _iter != e; /* DO NOTHING */) {
        if(&_iter->second != &camera) {
            _iter++;
            continue;
        } else {
            _cameras.erase(_iter++);
        }
    }

    return true;
}

void World::CameraToObject(Camera& cam, const Entity& obj) {
    if(obj.GetBody() == nullptr) return;
    cam.SetPosition(obj.GetBody()->GetPosition() - cam.GetHalfExtents());
}

void World::ObjectToCamera(Entity& obj, const Camera& cam) {
    if(obj.GetBody() == nullptr) return;
    obj.GetBody()->SetPosition(cam.GetPosition() + cam.GetHalfExtents());
}

bool World::AddObject(Entity* obj) {
    if(obj == nullptr) return false;
    if(std::find(_objects.begin(), _objects.end(), obj) != _objects.end()) return false;

    if(this->_gh) this->_gh->RegisterBody(obj);
    if(this->_dh) this->_dh->RegisterBody(obj);
    if(obj->GetBody()) this->_grid->Add(obj->GetBody()->GetPosition());

    this->_objects.push_back(obj);
    return true;
}

bool World::RemoveObject(Entity* obj) {
    if(obj == nullptr) return false;
    if(obj->GetBody() == nullptr) return false;

    ObjectsIter b = _objects.begin();

    for(ObjectsIter _iter = b; _iter != _objects.end(); ++_iter) {
        if(*_iter != obj) continue;
        _objects.erase(_iter);
        if(_gh) _gh->UnregisterBody(obj);
        if(_dh) _dh->UnregisterBody(obj);
        _grid->Remove(obj->GetBody()->GetPosition());
        return true;
    }
    return false;
}

double World::GetWidth() const {
    return _dimensions.GetX();
}

double World::GetWidth() {
    return static_cast<const World&>(*this).GetWidth();
}

double World::GetHeight() const {
    return _dimensions.GetY();
}

double World::GetHeight() {
    return static_cast<const World&>(*this).GetHeight();
}

Vector2D World::GetDimensions() const {
    return _dimensions;
}

Vector2D World::GetDimensions() {
    return static_cast<const World&>(*this).GetDimensions();
}

void World::SetDimensions(double width, double height) {

    bool width_less_equal_zero = a2de::Math::IsEqual(width, 0.0) || width < 0.0;
    bool height_less_equal_zero = a2de::Math::IsEqual(height, 0.0) || height < 0.0;
    bool width_not_changed = a2de::Math::IsEqual(width, _dimensions.GetX());
    bool height_not_changed = a2de::Math::IsEqual(height, _dimensions.GetY());
    bool dimensions_not_changed = width_not_changed && height_not_changed;

    bool invalid_dimensions = dimensions_not_changed || width_less_equal_zero || height_less_equal_zero;

    if(invalid_dimensions) return;

    _dimensions = Vector2D(width, height);

}

World::MapCamsIter World::GetCamera(unsigned char index) throw(...) {
    MapCamsIter result = _cameras.find(index);
    if(result == _cameras.end()) throw a2de::IndexOutOfBoundsException("index", "0", "_cameras.size() - 1");
    return result;
}

a2de::Vector2D World::CameraToWorldPosition(const Camera& cam, const Vector2D& screen_position) {
    return Camera::CameraToWorldPosition(cam, screen_position);
}

a2de::Vector2D World::WorldToCameraPosition(const Camera& cam, const Vector2D& world_position) {
    return Camera::WorldToCameraPosition(cam, world_position);
}

unsigned char World::GetCameraCount() const {
    return _cameras.size();
}

unsigned char World::GetCameraCount() {
    return static_cast<const World&>(*this).GetCameraCount();
}

World::MapCams World::GetCameras() const {
    return _cameras;
}

World::MapCams World::GetCameras() {
    return static_cast<const World&>(*this).GetCameras();
}

const World::Objects& World::GetObjects() const {
    return _objects;
}

World::Objects& World::GetObjects() {
    return const_cast<World::Objects&>(static_cast<const World&>(*this).GetObjects());
}

void World::SetGravity(const Vector2D& gravity) {
    if(a2de::Math::IsEqual(gravity.GetX(), 0.0) && a2de::Math::IsEqual(gravity.GetY(), 0.0)) {
        delete _gh;
        _gh = nullptr;
        return;
    }

    if(_gh == nullptr) {
        if(a2de::Math::IsEqual(gravity.GetX(), 0.0) == false || a2de::Math::IsEqual(gravity.GetY(), 0.0) == false) {
            _gh = new GravityForceGenerator(gravity);
        }
    }
    if(_gh) _gh->SetGravity(gravity);
}

const GravityForceGenerator* World::GetGravityHandler() const {
    return _gh;
}

void World::SetDragCoefficients(const Vector2D& k1k2) {
    if(a2de::Math::IsEqual(k1k2.GetX(), 0.0) && a2de::Math::IsEqual(k1k2.GetY(), 0.0)) {
        delete _dh;
        _dh = nullptr;
        return;
    }

    if(_dh == nullptr) {
        if(a2de::Math::IsEqual(k1k2.GetX(), 0.0) == false || a2de::Math::IsEqual(k1k2.GetY(), 0.0) == false) {
            _dh = new DragForceGenerator();
        }
    }
    if(_dh) _dh->SetLinearCoefficient(k1k2.GetX());
    if(_dh) _dh->SetQuadraticCoefficient(k1k2.GetY());
}

const DragForceGenerator* World::GetDragHandler() const {
    return _dh;
}

void World::Render() {


    for(auto& c : contacts) {
        auto f_pos = c.GetFirstBody()->GetPosition();
        auto s_pos = c.GetSecondBody()->GetPosition();
        auto x1 = (f_pos.GetX());
        auto y1 = (f_pos.GetY());
        auto x2 = (s_pos.GetX());
        auto y2 = (s_pos.GetY());
        auto color = al_map_rgb(255, 0, 0);

        a2de::Line l(x1, y1, x2, y2, color);
        this->_render_context->RenderObjectAt(&l, a2de::Math::ToScreenScale(a2de::World::WorldToCameraPosition(this->GetCamera(0)->second, l.GetPosition())));

    }


    for(auto& cur_camera : _cameras)
    {
        for(auto& cur_object : _objects) {

            if(cur_object == nullptr) return;

            RigidBody* b = cur_object->GetBody();
            if(b == nullptr) return;
            
            a2de::Shape* s = b->GetCollisionShape();
            if(s == nullptr) return;

            a2de::Vector2D pos = s->GetPosition();
            a2de::Vector2D he = s->GetHalfExtents();
            a2de::Rectangle bbr(pos, he);

            if(bbr.Intersects(cur_camera.second.GetArea()) == false) return;

            a2de::Vector2D draw_pos = a2de::World::WorldToCameraPosition(cur_camera.second, b->GetPosition());
            _render_context->RenderObjectAt(cur_object, a2de::Math::ToScreenScale(draw_pos));

        }
    }

}

void World::Update(double deltaTime) {

    _objects.sort([&](const a2de::Entity* elem_objectA, const a2de::Entity* elem_objectB) ->bool {
        return elem_objectA->GetZOrder() < elem_objectB->GetZOrder();
    });

    UpdateObjectsInWorld(deltaTime);
    ResolveCollisions(deltaTime);

}

void World::UpdateObjectsInWorld(double deltaTime) {

    if(_gh) _gh->Update(deltaTime);
    if(_dh) _dh->Update(deltaTime);

    if(_objects.empty()) return;
    for(auto& elem : _objects) {
        elem->Update(deltaTime);
    }

}

void World::ResolveCollisions(double deltaTime) {
    //BroadPhase: Check if Bounding Boxes are colliding.
    //NarrowPhase: Check if Collision Shapes are colliding and handle shape-specific resolution.
    contacts = BroadPhaseCollision();

    if(contacts.empty()) return;

    NarrowPhaseCollision(contacts, deltaTime);
}

World::ContactPairs World::BroadPhaseCollision() {

    //Update the QuadTree Grid.
    //For each Camera: Query any visible Objects.
    //For each visible Object in all Cameras: generate a unique Contact Pair.
    //Return the set of Contact Pairs.

    UpdateGrid();

    ContactPairs cps;
    if(_objects.empty()) return cps; //returns empty cps

    for(ObjectsIter objects_iter = _objects.begin(); objects_iter != _objects.end(); ++objects_iter) {
        if((*objects_iter)->GetBody() == nullptr) continue;
        std::vector<a2de::QuadTree<a2de::Vector2D>* > p = this->_grid->GetNodesByLocation((*objects_iter)->GetBody()->GetPosition());
        if(p.empty()) continue;

        std::size_t ps = p.size();
        std::vector<a2de::Vector2D> v;
        for(std::size_t i = 0; i < ps; ++i) {
            std::vector<a2de::Vector2D> current_element_vec(p[i]->GetAllElements());
            std::size_t cs = current_element_vec.size();
            if(i == 0) {
                v = current_element_vec;
                continue;
            }
            v.reserve(cs + v.size());
            v.insert(v.end(), current_element_vec.begin(), current_element_vec.end());
        }

        ContactPairs current_cps_pairs = GenerateContactPairs(v);

        //Remove any false positives. FP = non-colliding bounding boxes.
        for(World::ContactPairsIter contacts_iter = current_cps_pairs.begin(); contacts_iter != current_cps_pairs.end(); /* DO NOTHING */ ) {
            a2de::RigidBody* first_body = const_cast<a2de::RigidBody*>((*contacts_iter).GetFirstBody());
            a2de::RigidBody* second_body = const_cast<a2de::RigidBody*>((*contacts_iter).GetSecondBody());

            IBoundingBox* fBB = first_body->GetBoundingRectangle();
            IBoundingBox* sBB = second_body->GetBoundingRectangle();
            if(fBB == nullptr && sBB == nullptr) {
                current_cps_pairs.erase(contacts_iter++);
                continue;
            }
            a2de::Rectangle fR(fBB->GetTransform().GetPosition(), fBB->GetHalfExtents());
            a2de::Rectangle sR(sBB->GetTransform().GetPosition(), sBB->GetHalfExtents());
            if(fR.Intersects(sR) == false) {
                current_cps_pairs.erase(contacts_iter++);
                continue;
            }
            ++contacts_iter;
        }
        cps.insert(current_cps_pairs.begin(), current_cps_pairs.end());
    }
    return cps;
}

void World::NarrowPhaseCollision(ContactPairs& contact_pairs, double deltaTime) {

    //For Each contact pair, update the post-collision physics.
    for(World::ContactPairsIter _iter = contact_pairs.begin(); _iter != contact_pairs.end(); ++_iter) {
        a2de::RigidBody* first_body = const_cast<a2de::RigidBody*>((*_iter).GetFirstBody());
        a2de::RigidBody* second_body = const_cast<a2de::RigidBody*>((*_iter).GetSecondBody());

        first_body->Wake();
        second_body->Wake();

        //Process contact: Adjust Velocity. Adjust Position.
        if(_cur_vsc < _max_velocity_solve_count) {
            VelocitySolver(first_body, second_body);
        } else {
            _cur_vsc = 0;
        }
        if(_cur_psc < _max_position_solve_count) {
            PositionSolver(first_body, second_body, deltaTime);
        } else {
            _cur_psc = 0;
        }
    }

}

void World::UpdateGrid() {

    std::vector<a2de::Vector2D> objs;
    for(auto _iter = this->_objects.begin(); _iter != this->_objects.end(); ++_iter ) {
        if((*_iter)->GetBody() == nullptr) continue;
        a2de::Vector2D collision_position = (*_iter)->GetBody()->GetPosition();
        objs.push_back(collision_position);
    }
    _grid->Clear();
    _grid->Add(objs);
}

void World::QueryAllCameras(std::vector<a2de::Vector2D>& queried_elems) {
    std::size_t max_cameras = _cameras.size();
    for(std::size_t i = 0; i < max_cameras; ++i) {
        std::vector<a2de::Vector2D> temp_queried_elems(_grid->Query(a2de::Rectangle(_cameras.at(i).GetPosition(), _cameras.at(i).GetHalfExtents())));
        queried_elems.insert(queried_elems.end(), temp_queried_elems.begin(), temp_queried_elems.end());
    }
}

a2de::World::ContactPairs World::GenerateContactPairs(std::vector<a2de::Vector2D>& queried_elems) {

    a2de::World::ContactPairs contact_pairs;

    std::size_t max_elems = queried_elems.size();
    if(max_elems == 0) return contact_pairs;

    for(std::size_t i = 0; i < max_elems - 1; ++i) {
        for(std::size_t j = i + 1; j < max_elems; ++j) {

            if(queried_elems[i] == queried_elems[j]) continue;
            ObjectsIter left_iter = std::find_if(_objects.begin(), _objects.end(), [&](a2de::Entity* elem) {
                if(elem == nullptr) return false;

                a2de::RigidBody* b = elem->GetBody();
                if(b == nullptr) return false;

                return b->GetPosition() == queried_elems[i];
            });
            if(left_iter == _objects.end()) continue;

            if((*left_iter)->GetBody() == nullptr) continue;
            a2de::RigidBody* left_body = (*left_iter)->GetBody();

            ObjectsIter right_iter = std::find_if(_objects.begin(), _objects.end(), [&](a2de::Entity* elem) {
                if(elem == nullptr) return false;

                a2de::RigidBody* b = elem->GetBody();
                if(b == nullptr) return false;

                return b->GetPosition() == queried_elems[j];
            });
            if(right_iter == _objects.end()) continue;

            if((*right_iter)->GetBody() == nullptr) continue;
            a2de::RigidBody* right_body = (*right_iter)->GetBody();

            if(left_body == right_body) continue;

            //The result doesn't matter. Inserted or not, the loop will continue.
            contact_pairs.insert(a2de::ContactPair(left_body, right_body));

        }
    }
    return contact_pairs;
}

void World::VelocitySolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Vector2D first_position = first_body->GetPosition();
    a2de::Vector2D second_position = second_body->GetPosition();
    a2de::Vector2D first_contact_normal;
    a2de::Vector2D relPosFirst = first_position - second_position;
    if(relPosFirst != a2de::Vector2D(0.0, 0.0)) {
        first_contact_normal = relPosFirst.Normalize();
    }
    a2de::Vector2D second_contact_normal;
    a2de::Vector2D relPosSecond = second_position - first_position;
    if(relPosSecond != a2de::Vector2D(0.0, 0.0)) {
        second_contact_normal = relPosSecond.Normalize();
    }

    double m1 = first_body->GetMass();
    double m2 = second_body->GetMass();
    double mass_sum = m1 + m2;
    double mass1_mass2_diff = m1 - m2;
    double mass2_mass1_diff = m2 - m1;
    double v1 = first_body->GetVelocity().GetLength();
    double v2 = second_body->GetVelocity().GetLength();
    double theta1 = first_body->GetVelocity().GetAngle();
    double theta2 = second_body->GetVelocity().GetAngle();
    double phi1 = first_contact_normal.GetAngle();
    double phi2 = second_contact_normal.GetAngle();
    double cos_theta1_phi1 = std::cos(theta1 - phi1);
    double cos_theta2_phi1 = std::cos(theta2 - phi1);
    double sin_theta1_phi1 = std::sin(theta1 - phi1);
    double cos_theta1_phi2 = std::cos(theta1 - phi2);
    double cos_theta2_phi2 = std::cos(theta2 - phi2);
    double sin_theta2_phi2 = std::sin(theta2 - phi2);
    double cos_phi1_pi_2 = std::cos(phi1 + (a2de::Math::A2DE_1PI_2));
    double sin_phi1_pi_2 = std::sin(phi1 + (a2de::Math::A2DE_1PI_2));
    double cos_phi2_pi_2 = std::cos(phi2 + (a2de::Math::A2DE_1PI_2));
    double sin_phi2_pi_2 = std::sin(phi2 + (a2de::Math::A2DE_1PI_2));
    double twice_m1v1 = 2.0 * m1 * v1;
    double twice_m2v2 = 2.0 * m2 * v2;
    double cos_phi1 = std::cos(phi1);
    double sin_phi1 = std::sin(phi1);
    double cos_phi2 = std::cos(phi2);
    double sin_phi2 = std::sin(phi2);

    double v1_ratio = ((v1 * cos_theta1_phi1 * mass1_mass2_diff) + (twice_m2v2 * cos_theta2_phi1)) / mass_sum;

    double v1x = (v1_ratio * cos_phi1) + (v1 * sin_theta1_phi1 * cos_phi1_pi_2);
    double v1y = (v1_ratio * sin_phi1) + (v1 * sin_theta1_phi1 * sin_phi1_pi_2);

    a2de::Vector2D v1prime(v1x, v1y);

    double v2_ratio = ((v2 * cos_theta2_phi2 * mass2_mass1_diff) + (twice_m1v1 * cos_theta1_phi2)) / mass_sum;

    double v2x = (v2_ratio * cos_phi2) + (v2 * sin_theta2_phi2 * cos_phi2_pi_2);
    double v2y = (v2_ratio * sin_phi2) + (v2 * sin_theta2_phi2 * sin_phi2_pi_2);

    a2de::Vector2D v2prime(v2x, v2y);

    first_body->SetVelocity(v1prime);
    second_body->SetVelocity(v2prime);

}

void World::PositionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body, double /*deltaTime*/) {

    double first_mass = first_body->GetMass();
    double second_mass = second_body->GetMass();

    //If both are zero or infinite mass, do nothing.
    if(a2de::Math::IsEqual(first_mass, 0.0) && a2de::Math::IsEqual(second_mass, 0.0)) return;
    if(a2de::Math::IsEqual(first_mass, a2de::Math::A2DE_INFINITY) && a2de::Math::IsEqual(second_mass, a2de::Math::A2DE_INFINITY)) return;

    a2de::Shape* first_collision_shape = first_body->GetCollisionShape();
    a2de::Shape* second_collision_shape = second_body->GetCollisionShape();

    if(first_collision_shape == nullptr && second_collision_shape == nullptr) return;

    std::vector<ContactData> collision_results(ShapeCollisionSolver(first_body, second_body));

    if(collision_results.empty() || collision_results.size() < 2) return;

    double mass_sum = first_mass + second_mass;

    a2de::Vector2D first_position = first_body->GetPosition();
    a2de::Vector2D second_position = second_body->GetPosition();

    a2de::Vector2D first_contact_normal = collision_results[0].GetContactNormal();
    a2de::Vector2D second_contact_normal = collision_results[1].GetContactNormal();

    double first_penetration_amount = collision_results[0].GetPenetrationAmount();
    double second_penetration_amount = collision_results[1].GetPenetrationAmount();

    a2de::Vector2D first_interpenetration = (first_mass / mass_sum) * first_contact_normal * first_penetration_amount;
    a2de::Vector2D second_interpenetration = (second_mass / mass_sum) * second_contact_normal * second_penetration_amount;
    
    first_body->SetPosition((first_position + first_interpenetration));
    second_body->SetPosition((second_position + second_interpenetration));
}

std::vector<ContactData> World::ShapeCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Shape* first_collision_shape = first_body->GetCollisionShape();
    a2de::Shape* second_collision_shape = second_body->GetCollisionShape();
    if(first_collision_shape == nullptr || second_collision_shape == nullptr) return std::vector<ContactData>();

    a2de::Shape::SHAPE_TYPE first_shape_type = first_collision_shape->GetShapeType();
    a2de::Shape::SHAPE_TYPE second_shape_type = second_collision_shape->GetShapeType();

    bool isCircleCircle = first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE;
    bool isCircleLine = (first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_LINE) || (first_shape_type == a2de::Shape::SHAPETYPE_LINE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE);
    bool isCircleRectangle = (first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE) || (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_CIRCLE);
    bool isRectangleLine = (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_LINE) || (first_shape_type == a2de::Shape::SHAPETYPE_LINE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE);
    bool isRectangleRectangle = (first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE && second_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE);

    std::vector<ContactData> collision_result;
    if(isCircleCircle) {
        collision_result = CircleCircleCollisionSolver(first_body, second_body);
    } else if(isCircleLine) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE) {
            collision_result = CircleLineCollisionSolver(first_body, second_body);
        } else {
            collision_result = CircleLineCollisionSolver(second_body, first_body);
        }
    } else if(isCircleRectangle) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_CIRCLE) {
            collision_result = CircleRectangleCollisionSolver(first_body, second_body);
        } else {
            collision_result = CircleRectangleCollisionSolver(second_body, first_body);
        }
    } else if(isRectangleLine) {
        if(first_shape_type == a2de::Shape::SHAPETYPE_RECTANGLE) {
            collision_result = RectangleLineCollisionSolver(first_body, second_body);
        } else {
            collision_result = RectangleLineCollisionSolver(second_body, first_body);
        }
    } else if (isRectangleRectangle) {
        collision_result = RectangleRectangleCollisionSolver(first_body, second_body);
    } else {
        /* DO NOTHING */
    }
    return collision_result;
}

std::vector<ContactData> World::CircleCircleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Circle second_shape(*dynamic_cast<a2de::Circle*>(second_body->GetCollisionShape()));

    if(first_shape.Intersects(second_shape) == false) return std::vector<ContactData>();

    a2de::Vector2D direction_of_first = second_shape.GetPosition() - first_shape.GetPosition();
    a2de::Vector2D direction_of_second = first_shape.GetPosition() - second_shape.GetPosition();

    a2de::Vector2D first_collision_normal = direction_of_second.Normalize();
    a2de::Vector2D second_collision_normal = direction_of_first.Normalize();

    double distance_apart = direction_of_first.GetLength();
    double r1 = first_shape.GetRadius();
    double r2 = second_shape.GetRadius();
    double interpenetration_distance = -distance_apart + r1 + r2;

    a2de::Vector2D first_contact_point = interpenetration_distance * first_collision_normal;
    a2de::Vector2D second_contact_point = interpenetration_distance * second_collision_normal;

    std::vector<ContactData> contact_result;
    contact_result.push_back(ContactData(first_contact_point, first_collision_normal, interpenetration_distance, *first_body, *second_body));
    contact_result.push_back(ContactData(second_contact_point, second_collision_normal, interpenetration_distance, *second_body, *first_body));
    return contact_result;
}

std::vector<ContactData> World::CircleLineCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Line second_shape(*dynamic_cast<a2de::Line*>(second_body->GetCollisionShape()));

    if(first_shape.Intersects(second_shape) == false) return std::vector<ContactData>();

    double distance_s = a2de::Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetPointOne(), second_shape.GetPointTwo());
    double r_s = first_shape.GetRadius();
    r_s *= r_s;

    std::vector<ContactData> contact_result;
    if(distance_s < r_s || a2de::Math::IsEqual(distance_s, r_s)) {
        double distance = std::sqrt(distance_s);
        double r = std::sqrt(r_s);
        a2de::Vector2D collision_normal(second_shape.GetNormal());
        a2de::Vector2D collision_normal_distance(collision_normal.Normalize() * distance);
        a2de::Vector2D collision_point(std::cos(collision_normal_distance.GetAngle()) * r, std::sin(collision_normal_distance.GetAngle()) * r);
        double interpenetration_distance = r - distance;

        contact_result.push_back(ContactData(collision_point, collision_normal, interpenetration_distance, *first_body, *second_body));
    }

    return contact_result;
}

std::vector<ContactData> World::CircleRectangleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Circle first_shape(*dynamic_cast<a2de::Circle*>(first_body->GetCollisionShape()));
    a2de::Rectangle second_shape(*dynamic_cast<a2de::Rectangle*>(second_body->GetCollisionShape()));

    
    if(first_shape.Intersects(second_shape) == false) return std::vector<ContactData>();

    double resultTop = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetTop().GetPointOne(), second_shape.GetTop().GetPointTwo());
    double resultLeft = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetLeft().GetPointOne(), second_shape.GetLeft().GetPointTwo());
    double resultRight = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetRight().GetPointOne(), second_shape.GetRight().GetPointTwo());
    double resultBottom = Point(first_shape.GetPosition()).GetDistanceSquared(second_shape.GetBottom().GetPointOne(), second_shape.GetBottom().GetPointTwo());

    a2de::Vector2D contact_normal(second_shape.GetPosition() - first_shape.GetPosition().Normalize());
    a2de::Vector2D contact_point(contact_normal * first_shape.GetRadius());
    double interpenetraction_depth_s = std::min(std::min(resultTop, resultBottom), std::min(resultLeft, resultRight));

    double interpenetraction_depth = std::sqrt(interpenetraction_depth_s);

    std::vector<ContactData> contact_result;
    contact_result.push_back(ContactData(contact_point, contact_normal, interpenetraction_depth, *first_body, *second_body));

    return contact_result;
}

std::vector<ContactData> World::RectangleLineCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Rectangle first_shape(*dynamic_cast<a2de::Rectangle*>(first_body->GetCollisionShape()));
    a2de::Line second_shape(*dynamic_cast<a2de::Line*>(second_body->GetCollisionShape()));

    if(first_shape.Intersects(second_shape) == false) return std::vector<ContactData>();

    //return contact_result;
    return std::vector<ContactData>();
}

std::vector<ContactData> World::RectangleRectangleCollisionSolver(a2de::RigidBody* first_body, a2de::RigidBody* second_body) {
    a2de::Rectangle first_shape(*dynamic_cast<a2de::Rectangle*>(first_body->GetCollisionShape()));
    a2de::Rectangle second_shape(*dynamic_cast<a2de::Rectangle*>(second_body->GetCollisionShape()));


    if(first_shape.Intersects(second_shape) == false) return std::vector<ContactData>();



    a2de::Vector2D p1 = first_shape.GetPosition();
    a2de::Vector2D p2 = second_shape.GetPosition();

    a2de::Vector2D p1_to_p2_direction = (p2 - p1).Normalize();
    a2de::Vector2D p2_to_p1_direction = (p1 - p2).Normalize();

    double p1hw = first_shape.GetHalfWidth();
    double p1hh = first_shape.GetHalfHeight();

    a2de::Vector2D p1_horizontal_projection = a2de::Vector2D::GetProjection(p1_to_p2_direction, a2de::Vector2D(p1hw, 0.0));
    a2de::Vector2D p1_vertical_projection = a2de::Vector2D::GetProjection(p1_to_p2_direction, a2de::Vector2D(0.0, p1hh));

    double p2hw = second_shape.GetHalfWidth();
    double p2hh = second_shape.GetHalfHeight();

    a2de::Vector2D p2_horizontal_projection = a2de::Vector2D::GetProjection(p2_to_p1_direction, a2de::Vector2D(p2hw, 0.0));
    a2de::Vector2D p2_vertical_projection = a2de::Vector2D::GetProjection(p2_to_p1_direction, a2de::Vector2D(0.0, p2hh));

    double p1pax = (p1_horizontal_projection * p1hw).GetLength();
    double p1pay = (p1_vertical_projection * p1hh).GetLength();

    double p2pax = (p2_horizontal_projection * p2hw).GetLength();
    double p2pay = (p2_vertical_projection * p2hh).GetLength();

    std::vector<ContactData> contact_result;
    contact_result.push_back(ContactData(p1_horizontal_projection, p1_to_p2_direction, p1pax, *first_body, *second_body));
    contact_result.push_back(ContactData(p1_vertical_projection, p1_to_p2_direction, p1pay, *first_body, *second_body));

    contact_result.push_back(ContactData(p2_horizontal_projection, p2_to_p1_direction, p2pax, *second_body, *first_body));
    contact_result.push_back(ContactData(p2_vertical_projection, p2_to_p1_direction, p2pay, *second_body, *first_body));

    return contact_result;
}

const a2de::QuadTree<a2de::Vector2D>* World::GetGrid() const {
    return _grid;
}

a2de::QuadTree<a2de::Vector2D>* World::GetGrid() {
    return const_cast<a2de::QuadTree<a2de::Vector2D>*>(static_cast<const World&>(*this).GetGrid());
}

void World::DeallocateWorld() {

    delete _grid;
    _grid = nullptr;

    delete _render_context;
    _render_context = nullptr;

    delete _gh;
    _gh = nullptr;

    delete _dh;
    _dh = nullptr;

    _objects.clear();
    _cameras.clear();
}


A2DE_END