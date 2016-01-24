/**************************************************************************************************
// file:	Engine\Math\CSpline.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the spline class
 **************************************************************************************************/
#include "CSpline.h"

#include <algorithm>

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSector.h"

#include "CMiscMath.h"

A2DE_BEGIN

Spline::Spline()
      : Shape(),
        _control_points(4),
        _result_points()
      {
        _type = Shape::ShapeType::Spline;
}

Spline::Spline(const std::vector<Vector2D>& controlPoints)
    : Shape({ 0, 0 }, { 0, 0 }),
        _control_points(controlPoints),
        _result_points() {
            _type = Shape::ShapeType::Spline;
            _control_points = controlPoints;
        CalculateResultPoints();
}

Spline::Spline(const Spline& other)
      : Shape(other), _control_points(other._control_points), _result_points(other._result_points) {
          _type = Shape::ShapeType::Spline;
}

Spline::~Spline() {
    _result_points.clear();
    _control_points.clear();
}

const Vector2D& Spline::GetControlPointOne() const {
    return _control_points.at(0);
}

Vector2D& Spline::GetControlPointOne() {
    return const_cast<Vector2D&>(static_cast<const Spline&>(*this).GetControlPointOne());
}

const Vector2D& Spline::GetControlPointTwo() const {
    return _control_points.at(1);
}

Vector2D& Spline::GetControlPointTwo() {
    return const_cast<Vector2D&>(static_cast<const Spline&>(*this).GetControlPointTwo());
}

const Vector2D& Spline::GetControlPointThree() const {
    return _control_points.at(2);
}

Vector2D& Spline::GetControlPointThree() {
    return const_cast<Vector2D&>(static_cast<const Spline&>(*this).GetControlPointThree());
}

const Vector2D& Spline::GetControlPointFour() const {
    return _control_points.at(3);
}

Vector2D& Spline::GetControlPointFour() {
    return const_cast<Vector2D&>(static_cast<const Spline&>(*this).GetControlPointFour());
}

const std::vector<Vector2D>& Spline::GetResultPoints() const {
    return _result_points;
}

std::vector<Vector2D>& Spline::GetResultPoints() {
    return const_cast<decltype(_result_points)&>(static_cast<const Spline&>(*this).GetResultPoints());
}

void Spline::AdjustControlPoint(std::size_t number, Vector2D value) {
    if(number > 3) number = 3;
    _control_points[number] = value;
    CalculateResultPoints();
}

//void Spline::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool /*filled*/) {
//    if(dest == nullptr) return;
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//    float points[8] = { //Horrible API. No choice but to use floats!
//        static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(0).GetX())), static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(0).GetY())),
//        static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(1).GetX())), static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(1).GetY())),
//        static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(2).GetX())), static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(2).GetY())),
//        static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(3).GetX())), static_cast<float>(a2de::Math::ToScreenScale(_control_points.at(3).GetY())),
//        };
//    al_draw_spline(points, color, 0.0);
//    al_set_target_bitmap(old_target);
//}

bool Spline::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}
bool Spline::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Spline::Intersects(const Line& line) const {
    
    //Perform fast searches first:
    Point point_one(line.GetPointOne());
    bool isOnPointOne = this->Intersects(point_one);
    if(isOnPointOne) return true;

    Point point_two(line.GetPointTwo());
    bool isOnPointTwo = this->Intersects(point_two);
    if(isOnPointTwo) return true;

    //Perform slow O(n) point search:
    for(std::size_t i = 0; i < _result_points.size(); ++i) {
        if(line.Intersects(_result_points.at(i))) return true;
    }

    //Perform agonizingly slow O(n^2) line search.
    for(std::size_t i = 0; i < _result_points.size() - 1; ++i) {
        Line current_line(_result_points.at(i), _result_points.at(i+1));
        if(current_line.Intersects(line)) return true;
    }
    return false;
}

bool Spline::Intersects(const Rectangle& rectangle) const {
    return IterateResultPoints<Rectangle>(rectangle);
}
bool Spline::Intersects(const Circle& circle) const {
    return IterateResultPoints<Circle>(circle);
}
bool Spline::Intersects(const Ellipse& ellipse) const {
    return IterateResultPoints<Ellipse>(ellipse);
}
bool Spline::Intersects(const Triangle& triangle) const {
    return IterateResultPoints<Triangle>(triangle);
}
bool Spline::Intersects(const Arc& arc) const {
    return IterateResultPoints<Arc>(arc);
}
bool Spline::Intersects(const Polygon& polygon) const {
    return IterateResultPoints<Polygon>(polygon);
}
bool Spline::Intersects(const Spline& spline) const {
    return IterateResultPoints<Spline>(spline);
}

bool Spline::Intersects(const Sector& sector) const {
    return IterateResultPoints<Sector>(sector);
}

bool Spline::Intersects(const Vector2D& position) const {
    auto b = _result_points.begin();
    auto e = _result_points.end();
    for(auto p : _result_points) {
        if(p == position) return true;
    }
    return false;
}

void Spline::CalculateResultPoints() {

    float points[8] = {
        static_cast<float>(_control_points[0].GetX()), static_cast<float>(_control_points[0].GetY()),
        static_cast<float>(_control_points[1].GetX()), static_cast<float>(_control_points[1].GetY()),
        static_cast<float>(_control_points[2].GetX()), static_cast<float>(_control_points[2].GetY()),
        static_cast<float>(_control_points[3].GetX()), static_cast<float>(_control_points[3].GetY()),
    };

    std::vector<float> dest(Math::GetSplineBufferSize() * 2);
    auto num_points = dest.size();
    al_calculate_spline(dest.data(), sizeof(decltype(dest)::value_type), points, 0.0, num_points);
    for(std::size_t i = 0; i < num_points / 2 - 1; ++i) {
        _result_points[i] = Vector2D(dest[i], dest[i+1]);
    }
}

Spline& Spline::operator=(const Spline& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    _control_points = rhs._control_points;
    _result_points = rhs._result_points;
    return *this;
}

bool Spline::operator==(const Spline& rhs) {
    if(this == &rhs) return true;

    for(std::size_t i = 0; i < 4; ++i) {
        if(this->_control_points[i] != rhs._control_points[i]) return false;
    }
    return true;
}

bool Spline::operator!=(const Spline& rhs) {
    return !(*this == rhs);
}

void Spline::CalculateArea() { /* DO NOTHING */ }
Vector2D Spline::GetPosition() const { return Vector2D(); }
Vector2D Spline::GetPosition() { return Vector2D(); }
Vector2D Spline::GetCenter() const { return Vector2D(); }
Vector2D Spline::GetCenter() { return Vector2D(); }
double Spline::GetArea() const { return 0.0; }
double Spline::GetArea() { return static_cast<const Spline&>(*this).GetArea(); }
bool Spline::IsFilled() const { return false; }
bool Spline::IsFilled() { return static_cast<const Spline&>(*this).IsFilled(); }
void Spline::SetFill(bool /*filled*/) { /* DO NOTHING*/ }
double Spline::GetX() const { return 0.0; }
double Spline::GetX() { return static_cast<const Spline&>(*this).GetX(); }
double Spline::GetY() const { return 0.0; }
double Spline::GetY() { return static_cast<const Spline&>(*this).GetY(); }
double Spline::GetHalfWidth() const { return 0; }
double Spline::GetHalfWidth() { return static_cast<const Spline&>(*this).GetHalfWidth(); }
double Spline::GetHalfHeight() const { return 0; }
double Spline::GetHalfHeight() { return static_cast<const Spline&>(*this).GetHalfHeight(); }

void Spline::SetPosition(const Vector2D& position) { this->_transform.SetPosition(position); }

void Spline::SetHalfExtents(const Vector2D& dimensions) { this->_half_extents = dimensions; }

bool Spline::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Spline::Contains(const Point& /*point*/) const {
    return false;
}

bool Spline::Contains(const Line& /*line*/) const {
    return false;
}

bool Spline::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Spline::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Spline::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Spline::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Spline::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Spline::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Spline::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Spline::Contains(const Sector& /*sector*/) const {
    return false;
}

A2DE_END