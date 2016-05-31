/**************************************************************************************************
// file:	Engine\Physics\CFluidPhysicsArea.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the fluid physics area class
 **************************************************************************************************/
#include "CFluidPhysicsArea.h"

#include "../Math/CRectangle.h"
#include "../Math/CVector2D.h"
#include "../Math/CMiscMath.h"

#include "../a2de_objects.h"
#include "a2de_force_generators.h"

A2DE_BEGIN


    FluidPhysicsArea::FluidPhysicsArea(double density, const a2de::Vector2D& gravity) : PhysicsArea(), _density(density) {
        SetGravity(gravity);
}

FluidPhysicsArea::~FluidPhysicsArea() {
    /* DO NOTHING */
}

void FluidPhysicsArea::Update(double deltaTime) {
    a2de::PhysicsArea::Update(deltaTime);
}

void FluidPhysicsArea::OnEnter(Entity* entered_object) {
    a2de::PhysicsArea::RegisterObject(entered_object);
}

void FluidPhysicsArea::OnTick(Entity* object) {

    if(_gravity == nullptr) return;
    if(object == nullptr) return;

    a2de::Rectangle bounding_box(object->GetComponent<TransformComponent>().transform.GetPosition(), object->GetComponent<DimensionsComponent>().dimensions);

    a2de::Rectangle area_bounding_box(_area->GetCollisionShape()->GetPosition(), _area->GetCollisionShape()->GetHalfExtents());

    if(bounding_box.Intersects(area_bounding_box) == false) return;

    bool is_in_fluid = false;
    auto result = bounding_box.Overlap(area_bounding_box);
    if(result.first == false) return;

    double current_area = result.second.GetArea();
	double mass = object->GetComponent<PhysicsComponent>().body.GetMass();
    a2de::Vector2D gravityValue = _gravity->GetGravityValue();

    a2de::Vector2D current_weight(mass * gravityValue);
    a2de::Vector2D buoyancy(current_area * (_density / 1000.0) * -gravityValue);

	object->GetComponent<PhysicsComponent>().body.ApplyImpulse(buoyancy + current_weight);
}

void FluidPhysicsArea::OnExit(Entity* exited_object) {
    a2de::PhysicsArea::UnregisterObject(exited_object);
}


A2DE_END