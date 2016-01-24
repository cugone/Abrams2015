/**************************************************************************************************
// file:	Engine\Math\CCircle.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the circle class
 **************************************************************************************************/
#include "CCircle.h"

#include <cassert>
#include "MathConstants.h"
#include "CMiscMath.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"
#include "CVector2D.h"


A2DE_BEGIN


Circle::Circle(const Vector2D& center, double radius) : Shape(center, { (radius < 0.0 ? 0.0 : radius), (radius < 0.0 ? 0.0 : radius) }) {
    _type = Shape::ShapeType::Circle;
    _radius = radius;
    CalculateArea();
    CalculateCircumference();
}

Circle::Circle(const Circle& circle) : Shape(circle) {
    _type = Shape::ShapeType::Circle;
    _radius = circle._radius;
    CalculateArea();
    CalculateCircumference();
}

Circle::~Circle() {
    /* DO NOTHING. ALL DE-INITIALIZATION IS DONE IN BASE CLASS */
}

Circle& Circle::operator=(const Circle& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    this->_half_extents = rhs._half_extents;
    this->_radius = rhs._radius;
    CalculateCircumference();
    CalculateArea();

    return *this;
}

bool Circle::operator==(const Circle& rhs) const {
    if(this == &rhs) return true;
    return (this->_radius == rhs._radius);
}

bool Circle::operator!=(const Circle& rhs) const {
    return !(*this == rhs);
}

bool Circle::operator<(const Circle& rhs) const {
    if(this == &rhs) return false;
    return (this->_radius < rhs._radius);
}

bool Circle::operator>(const Circle& rhs) const {
    if(this == &rhs) return false;
    return (this->_radius > rhs._radius);
}

bool Circle::operator<=(const Circle& rhs) const {
    return (!(*this > rhs));
}

bool Circle::operator>=(const Circle& rhs) const {
    return (!(*this < rhs));
}

double Circle::GetRadius() const {
    return _radius;
}
double Circle::GetRadius() {
    return static_cast<const Circle&>(*this).GetRadius();
}

double Circle::GetDiameter() const {
    return _radius * 2;
}
double Circle::GetDiameter() {
    return static_cast<const Circle&>(*this).GetDiameter();
}

double Circle::GetCircumference() const {
    return _circumference;
}
double Circle::GetCircumference() {
    return static_cast<const Circle&>(*this).GetCircumference();
}

void Circle::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

void Circle::SetHalfExtents(const Vector2D& half_extents) {
    Shape::SetHalfExtents(half_extents);
}

void Circle::SetRadius(double radius) {
    _radius = radius;
    CalculateArea();
    CalculateCircumference();
}

bool Circle::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Circle::Intersects(const Rectangle& rectangle) const {

    auto cp = GetPosition();
    
    auto t = rectangle.GetTop();
    auto td = Math::GetDistance(cp, t.GetPointOne(), t.GetPointTwo());
    bool resultTop = td < _radius || Math::IsEqual(td, _radius);

    auto l = rectangle.GetLeft();
    auto ld = Math::GetDistance(cp, l.GetPointOne(), l.GetPointTwo());
    bool resultLeft = ld < _radius || Math::IsEqual(ld, _radius);

    auto r = rectangle.GetRight();
    auto rd = Math::GetDistance(cp, r.GetPointOne(), r.GetPointTwo());
    bool resultRight = rd < _radius || Math::IsEqual(rd, _radius);

    auto b = rectangle.GetBottom();
    auto bd = Math::GetDistance(cp, b.GetPointOne(), b.GetPointTwo());
    bool resultBottom = bd < _radius || Math::IsEqual(bd, _radius);

    bool isInside = rectangle.Intersects(cp);

    return (isInside || resultTop || resultLeft || resultRight || resultBottom);
}
bool Circle::Intersects(const Ellipse& ellipse) const {

    auto cp = this->GetPosition();
    auto ep = ellipse.GetPosition();
    auto ee = ellipse.GetHalfExtents();
    auto r = this->GetRadius();

    bool resultX = Math::GetDistance(cp, ep) <= ee.GetX() + r;
    bool resultY = Math::GetDistance(cp, ep) <= ee.GetY() + r;
    return (resultX && resultY);
}
bool Circle::Intersects(const Triangle& triangle) const {

    auto cp = this->GetPosition();
    auto a = triangle.GetPointA();
    auto b = triangle.GetPointB();
    auto c = triangle.GetPointC();

    auto td = Math::GetDistance(cp, a, b);
    bool resultTop = td < _radius || Math::IsEqual(td, _radius);

    auto ld = Math::GetDistance(cp, b, c);
    bool resultLeft = ld < _radius || Math::IsEqual(ld, _radius);
    
    auto rd = Math::GetDistance(cp, c, a);
    bool resultRight = rd < _radius || Math::IsEqual(rd, _radius);

    bool isInside = triangle.Intersects(cp);

    return (isInside || resultTop || resultLeft || resultRight);
}
bool Circle::Intersects(const Circle& circle) const {
    auto rd = Math::GetDistance(this->GetPosition(), circle.GetPosition());
    auto radii_sum = this->GetRadius() + circle.GetRadius();
    return rd < radii_sum || Math::IsEqual(rd, radii_sum);
}
bool Circle::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}
bool Circle::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Circle::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Circle::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Circle::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Circle::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Circle::Intersects(const Vector2D& position) const {
    auto ds = Math::GetDistanceSquared(this->GetPosition(), position);
    auto r2 = _radius * _radius;
    return ds < r2 || Math::IsEqual(ds, r2);
}

bool Circle::IsTangent(const Line& line) {
    auto cp = this->GetPosition();
    auto p1 = line.GetPointOne();
    auto p2 = line.GetPointTwo();
    return Math::IsEqual(Math::GetDistanceSquared(cp, p1, p2), _radius * _radius);
}

//void Circle::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) {
//
//    auto p = this->GetPosition();
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//
//    filled ? al_draw_filled_circle(a2de::Math::ToScreenScale(p.GetX()), a2de::Math::ToScreenScale(p.GetY()), a2de::Math::ToScreenScale(_radius), color) :
//             al_draw_circle(a2de::Math::ToScreenScale(p.GetX()), a2de::Math::ToScreenScale(p.GetY()), a2de::Math::ToScreenScale(_radius), color, 0.0);
//
//    al_set_target_bitmap(old_target);
//
//}

void Circle::CalculateArea() {
    _area = (Math::A2DE_PI * _radius * _radius);
}

void Circle::CalculateCircumference() {
    _circumference = 2 * Math::A2DE_PI * _radius;
}

bool Circle::Contains(const Circle& circle) const {
    if(((this->GetPosition().GetX() == circle.GetPosition().GetX()) && (this->GetPosition().GetY() == circle.GetPosition().GetY())) && circle.GetRadius() <= this->GetRadius()) return true;
    return this->Intersects(Point(circle.GetPosition())) && circle.GetDiameter() <= this->GetRadius();
}


A2DE_END