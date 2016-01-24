/**************************************************************************************************
// file:	Engine\Math\CEllipse.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the ellipse class
 **************************************************************************************************/
#include "CEllipse.h"

#include <cassert>
#include "MathConstants.h"
#include "CMiscMath.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"


A2DE_BEGIN

Ellipse::Ellipse(const Vector2D& center, const Vector2D& half_extents)
    : Shape(center, {((half_extents.GetX() < 0.0) ? 0.0 : half_extents.GetX()), ((half_extents.GetY() < 0.0) ? 0.0 : half_extents.GetY())}) {
        _type = Shape::ShapeType::Ellipse;
        _radii = _half_extents;
        CalculateFoci();
        CalculateArea();
        CalculateCircumference();
}

Ellipse::Ellipse(const Ellipse& ellipse) : Shape(ellipse) {
    _type = Shape::ShapeType::Ellipse;
    _radii = ellipse._half_extents;
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}

Ellipse::~Ellipse() {

}

void Ellipse::SetHalfExtents(const Vector2D& half_extents) {
    Shape::SetHalfExtents(half_extents);
    _radii = half_extents;
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
}

double Ellipse::GetCircumference() const {
    return _circumference;
}

void Ellipse::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

bool Ellipse::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Ellipse::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //Line tlAB(triangle.GetLineAB());
    //Line tlBC(triangle.GetLineBC());
    //Line tlCA(triangle.GetLineCA());
    //bool resultAB = tlAB.Intersects(*this);
    //bool resultBC = tlBC.Intersects(*this);
    //bool resultCA = tlCA.Intersects(*this);
    //bool isInside = Intersects(Point(triangle.GetCenter()));
    //return (isInside || resultAB || resultBC || resultCA);
}
bool Ellipse::Intersects(const Ellipse& ellipse) const {
    auto p = this->GetPosition();
    auto ep = ellipse.GetPosition();
    auto rx_sum = this->_radii.GetX() + ellipse._radii.GetX();
    auto ry_sum = this->_radii.GetY() + ellipse._radii.GetY();
    auto d = Math::GetDistance(p, ep);

    return (d < rx_sum || Math::IsEqual(d, rx_sum)) && (d < ry_sum || Math::IsEqual(d, ry_sum));
}

bool Ellipse::Intersects(const Circle& circle) const {
    auto r = circle.GetRadius();
    auto rx_sum = this->_radii.GetX() + r;
    auto ry_sum = this->_radii.GetY() + r;
    auto p = this->GetPosition();
    auto cp = circle.GetPosition();
    auto d = Math::GetDistance(p, cp);
    return (d < rx_sum || Math::IsEqual(d, rx_sum)) && (d < ry_sum || Math::IsEqual(d, ry_sum));
}

bool Ellipse::Intersects(const Rectangle& rectangle) const {

    auto p = this->GetPosition();

    auto t = rectangle.GetTop();
    double distTop = Math::GetDistance(p, t.GetPointOne(), t.GetPointTwo());

    auto l = rectangle.GetLeft();
    double distLeft = Math::GetDistance(p, l.GetPointOne(), l.GetPointTwo());

    auto r = rectangle.GetRight();
    double distRight = Math::GetDistance(p, r.GetPointOne(), r.GetPointTwo());

    auto b = rectangle.GetBottom();
    double distBottom = Math::GetDistance(p, b.GetPointOne(), b.GetPointTwo());

    double radiusWidth = _half_extents.GetX();
    double radiusHeight = _half_extents.GetY();

    bool resultTop = (distTop < radiusWidth && distTop < radiusHeight);
    bool resultBottom = (distBottom < radiusWidth && distBottom < radiusHeight);
    bool resultLeft = (distLeft < radiusWidth && distLeft < radiusHeight);
    bool resultRight = (distRight < radiusWidth && distRight < radiusHeight);
    bool isInside = rectangle.Intersects(p);

    return (isInside || resultTop || resultBottom || resultLeft || resultRight);
}
bool Ellipse::Intersects(const Point& point) const {

    auto ep = this->GetPosition();
    auto p = point.GetPosition();
    auto rx2 = _radii.GetX();
    rx2 *= rx2;

    auto ry2 = _radii.GetY();
    ry2 *= ry2;

    auto d2 = Math::GetDistanceSquared(ep, p);

    return  (d2 < rx2 || Math::IsEqual(d2, rx2)) &&
            (d2 < ry2 || Math::IsEqual(d2,ry2));
}
bool Ellipse::Intersects(const Line& line) const {
    auto p = this->GetPosition();
    auto p1 = line.GetPointOne();
    auto p2 = line.GetPointTwo();
    return (Math::GetDistance(p, p1, p2) < this->GetMinimumDistance()) || this->IsTangent(line);
}

bool Ellipse::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Ellipse::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Ellipse::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Ellipse::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Ellipse::Intersects(const Vector2D& position) const {

    auto p = this->GetPosition();
    double d2 = Math::GetDistanceSquared(p, position);
    double rX_squared = _radii.GetX();
    rX_squared *= rX_squared;
    double rY_squared = _radii.GetY();
    rY_squared *= rY_squared;

    return (d2 < rX_squared || Math::IsEqual(d2, rX_squared)) && (d2 < rY_squared || Math::IsEqual(d2, rY_squared));

}

double Ellipse::GetMinimumDistance() const {
    double a = _half_extents.GetX();
    double b = _half_extents.GetY();
    double distance_sq_cubed = (a * a + b * b) * (a * a + b * b) * (a * a + b * b);
    return (3.0 * std::sqrt(3.0) * a * a * b * b) / std::sqrt(distance_sq_cubed);
}

double Ellipse::GetMinimumDistance() {
    return static_cast<const Ellipse&>(*this).GetMinimumDistance();
}


bool Ellipse::IsTangent(const Line& line) const {
    auto p = this->GetPosition();
    auto p1 = line.GetPointOne();
    auto p2 = line.GetPointTwo();
    auto min_distance = this->GetMinimumDistance();
    auto distance = Math::GetDistance(p, p1, p2);
    return a2de::Math::IsEqual(distance, min_distance);
}

bool Ellipse::IsTangent(const Line& line) {
    return static_cast<const Ellipse&>(*this).IsTangent(line);
}

const Vector2D& Ellipse::GetFocusA() const {
    return _focusA;
}
Vector2D& Ellipse::GetFocusA() {
    return const_cast<Vector2D&>(static_cast<const Ellipse&>(*this).GetFocusA());
}

const Vector2D& Ellipse::GetFocusB() const {
    return _focusB;
}

Vector2D& Ellipse::GetFocusB() {
    return const_cast<Vector2D&>(static_cast<const Ellipse&>(*this).GetFocusB());
}

void Ellipse::CalculateArea() {
    _area = Math::A2DE_PI * _radii.GetX() * _radii.GetY();
}

void Ellipse::CalculateCircumference() {

    //C = 2 * pi * (sqrt(0.5 * (a^2 + b^2)) / 2.0 )
    double a = _half_extents.GetX();
    double b = _half_extents.GetY();
    _circumference = 2 * Math::A2DE_PI * (std::sqrt(0.5 * ((a * a) + (b * b))) / 2.0);

}

void Ellipse::CalculateFoci() {
    auto p = this->GetPosition();
    double x = p.GetX();
    double y = p.GetY();
    Vector2D half_radii = _radii / 2.0;
    double hrx = half_radii.GetX();
    double hry = half_radii.GetY();
    if(IsVertical()) {
        _focusA = Vector2D(x, y + hry);
        _focusB = Vector2D(x, y - hry);
    } else if(IsHorizontal()) {
        _focusA = Vector2D(x - hrx, y);
        _focusB = Vector2D(x + hrx, y);
    }
}

//void Ellipse::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) {
//
//    if(dest == nullptr) return;
//
//    auto p = this->GetPosition();
//    auto he = this->GetHalfExtents();
//    auto x = p.GetX();
//    auto y = p.GetY();
//    auto hx = he.GetX();
//    auto hy = he.GetY();
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//
//    filled ? al_draw_filled_ellipse(a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(hx), a2de::Math::ToScreenScale(hy), color) :
//             al_draw_ellipse(a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), a2de::Math::ToScreenScale(hx), a2de::Math::ToScreenScale(hy), color, 0.0);
//
//    al_set_target_bitmap(old_target);
//
//}

bool Ellipse::IsHorizontal() const {
    return (_radii.GetX() > _radii.GetY());
}

bool Ellipse::IsHorizontal() {
    return static_cast<const Ellipse&>(*this).IsHorizontal();
}

bool Ellipse::IsVertical() const {
    return (_radii.GetX() < _radii.GetY());
}

bool Ellipse::IsVertical() {
    return static_cast<const Ellipse&>(*this).IsVertical();
}

Ellipse& Ellipse::operator=(const Ellipse& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    this->_radii = Vector2D(rhs._half_extents.GetX() / 2, rhs._half_extents.GetY() / 2);
    CalculateFoci();
    CalculateArea();
    CalculateCircumference();
    return *this;
}


A2DE_END