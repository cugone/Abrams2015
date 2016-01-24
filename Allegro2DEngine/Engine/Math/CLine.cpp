/**************************************************************************************************
// file:	Engine\Math\CLine.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the line class
 **************************************************************************************************/
#include "CLine.h"

#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"


#include <cmath>
#include <algorithm>
#include "../Math/CMiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Line::Line()
    : Shape(),
     _slope(),
    _length_squared(0.0) {
    _type = Shape::ShapeType::Line;
    _verts.resize(2);
    CalculateSlope();
}

Line::Line(const Line& line)
    : Shape(line),
    _slope(),
    _length_squared(line._length_squared) {
    _type = Shape::ShapeType::Line;
    _verts = line._verts;
    CalculateSlope();
}

Line::Line(const Vector2D& one, const Vector2D& two)
    : Shape((one + two) / 2.0, (two - one) / 2.0),
    _slope(),
    _length_squared(((_transform.GetPosition() + _half_extents) - (_transform.GetPosition() - _half_extents)).GetLengthSquared()) {
    _type = Shape::ShapeType::Line;
    _verts.resize(2);
    _verts[0] = Vertex{ one };
    _verts[1] = Vertex{ two };
    CalculateSlope();
}

//Line::Line(const Vector2D& one, const Vector2D& two, const ALLEGRO_COLOR& color)
//    : Shape((one + two) / 2.0, (two - one) / 2.0, color, false),
//    _slope(),
//    _length_squared(((_transform.GetPosition() + _half_extents) - (_transform.GetPosition() - _half_extents)).GetLengthSquared()) {
//    _type = Shape::ShapeType::Line;
//    CalculateSlope();
//}

Line::~Line() {

}

Vector2D Line::GetPointOne() const {
    return _transform.GetPosition() - _half_extents;
}

Vector2D Line::GetPointOne() {
    return static_cast<const Line&>(*this).GetPointOne();
}

Vector2D Line::GetPointTwo() const {
    return _transform.GetPosition() + _half_extents;
}

Vector2D Line::GetPointTwo() {
    return static_cast<const Line&>(*this).GetPointTwo();
}

double Line::GetLength() const {
    return std::sqrt(_length_squared);
}

double Line::GetLength() {
    return static_cast<const Line&>(*this).GetLength();
}

double Line::GetLengthSquared() const {
    return _length_squared;
}

double Line::GetLengthSquared() {
    return static_cast<const Line&>(*this).GetLengthSquared();
}
const Vector2D& Line::GetSlope() const {
    return _slope;
}

Vector2D& Line::GetSlope() {
    return const_cast<Vector2D&>(static_cast<const Line&>(*this).GetSlope());
}

Line& Line::operator=(const Line& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    this->_slope = rhs._slope;
    this->_length_squared = rhs._length_squared;
    return *this;
}

bool Line::operator==(const Line& rhs) const {
    if(this == &rhs) return true;
    //A line is equal to another if:
    //the both first points are equal AND
    //the both second points are equal.
    return (
            (this->_transform.GetPosition() == rhs._transform.GetPosition()) &&
            (this->_half_extents == rhs._half_extents)
           );
}

bool Line::operator!=(const Line& rhs) const {
    return !(*this == rhs);
}
bool Line::operator<(const Line& rhs) const {
    return ((*this) != rhs) && (this->GetLengthSquared() < rhs.GetLengthSquared());
}
bool Line::operator>(const Line& rhs) const {
    return (rhs < *this);
}
bool Line::operator<=(const Line& rhs) const {
    return !(rhs < *this);
}
bool Line::operator>=(const Line& rhs) const {
    return !(*this < rhs);
}

//void Line::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool /*filled*/) {
//    if(dest == nullptr) return;
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//    a2de::Vector2D p1 = GetPointOne();
//    a2de::Vector2D p2 = GetPointTwo();
//    al_draw_line(a2de::Math::ToScreenScale(p1.GetX()), a2de::Math::ToScreenScale(p1.GetY()), a2de::Math::ToScreenScale(p2.GetX()), a2de::Math::ToScreenScale(p2.GetY()), color, 0.0);
//    al_set_target_bitmap(old_target);
//
//}

bool Line::IsVertical() const {
    return Math::IsEqual(_slope.GetX(), 0.0);
}

bool Line::IsHorizontal() const {
    if(IsVertical()) return false;
    return Math::IsEqual(_slope.GetY(), 0.0);
}

bool Line::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Line::Intersects(const Point& point) const {
    return this->Contains(point);
}

bool Line::Intersects(const Line& line) const {
    auto r = a2de::Math::IntersectsAt(*this, line);
    switch(r.first) {
        case Math::LINEINTERSECTIONTYPE::NONE: /* fall through */
        case Math::LINEINTERSECTIONTYPE::PARALLEL:
            return false;
        case Math::LINEINTERSECTIONTYPE::ONE: /* fall through */
        case Math::LINEINTERSECTIONTYPE::COLINEAR:
            return true;
    }
    return false;
}

bool Line::Intersects(const Rectangle& rectangle) const {

    auto rect_p = rectangle.GetPosition();
    auto rect_ex = rectangle.GetHalfExtents();

    if(this->IsVertical()) {
        double Xr = rect_p.GetX();
        double Xrw = rect_ex.GetX();
        double Xl = _half_extents.GetX();
        if(Xr > Xl) return false;
        double Xrb = Xr + Xrw;
        if(Xrb < Xl) return false;
        return true;
    } else if(this->IsHorizontal()) {
        double Yr = rect_p.GetY();
        double Yrh = rect_ex.GetY();
        double Yl = _half_extents.GetY();
        if(Yr > Yl) return false;
        double Yrb = Yr + Yrh;
        if(Yrb < Yl) return false;
        return true;
    }

    double eOne_x = GetPointOne().GetX();
    double eOne_y = GetPointOne().GetY();
    double eTwo_x = GetPointTwo().GetX();
    double eTwo_y = GetPointTwo().GetY();
    double rTop = rect_p.GetY() - rect_ex.GetY();
    double rLeft = rect_p.GetX() - rect_ex.GetX();
    double rRight = rect_p.GetX() + rect_ex.GetX();
    double rBottom = rect_p.GetY() + rect_ex.GetY();

    bool point_one_result = eOne_x > rLeft && eOne_x < rRight && eOne_y > rTop && eOne_y < rBottom;
    bool point_two_result = eTwo_x > rLeft && eTwo_x < rRight && eTwo_y > rTop && eTwo_y < rBottom;
    if(point_one_result || point_two_result) return true;

    bool result = Intersects(rectangle.GetTop()) ||
                  Intersects(rectangle.GetLeft()) ||
                  Intersects(rectangle.GetRight()) ||
                  Intersects(rectangle.GetBottom());
    return result;
}

bool Line::Intersects(const Circle& circle) const {
    auto p1 = this->GetPointOne();
    auto p2 = this->GetPointTwo();
    auto cp = circle.GetPosition();
    auto r = circle.GetRadius();
    auto r2 = r * r;

    bool eOne_result = ((p1 - cp).GetLengthSquared() < r2);
    bool eTwo_result = ((p2 - cp).GetLengthSquared() < r2);
    
    if(eOne_result) return true;
    if(eTwo_result) return true;
    
    return Math::GetDistance(cp, p1, p2) <= r;
}

bool Line::Intersects(const Ellipse& ellipse) const {
    auto p1 = this->GetPointOne();
    auto p2 = this->GetPointTwo();
    auto ep = ellipse.GetPosition();
    auto eh = ellipse.GetHalfExtents();
    auto erw = eh.GetX();
    auto erh = eh.GetY();
    bool resultX = Math::GetDistance(ep, p1, p2) <= erw;
    bool resultY = Math::GetDistance(ep, p1, p2) <= erh;
    return (resultX && resultY);
}

bool Line::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //bool resultAB = Intersects(triangle.GetLineAB());
    //bool resultBC = Intersects(triangle.GetLineBC());
    //bool resultCA = Intersects(triangle.GetLineCA());
    //bool isInside = Point(GetPointOne()).Intersects(triangle) || Point(GetPointTwo()).Intersects(triangle);
    //return (isInside || resultAB || resultBC || resultCA);
}

bool Line::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Line::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Line::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Line::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Line::Intersects(const Vector2D& position) const {
    return Math::GetDistance(position, this->GetPointOne(), this->GetPointTwo()) <= 0.0001;
}

void Line::CalculateSlope() {
    //(y2 - y1) / (x2 - x1)
    _slope = GetPointTwo() - GetPointOne();
}

void Line::CalculateArea() {
    _area = 0.0;
}

void Line::SetPosition(const Vector2D& position) {
    _transform.SetPosition(position);
}

void Line::SetHalfExtents(const Vector2D& /*half_extents*/) { /* DO NOTHING */ }

a2de::Vector2D Line::GetPerpendicularSlope() const {
    return Vector2D(-_slope.GetY(), _slope.GetX());
}

a2de::Vector2D Line::GetPerpendicularSlope() {
    return static_cast<const a2de::Line&>(*this).GetPerpendicularSlope();
}

a2de::Vector2D Line::GetNormal() const {
    a2de::Vector2D v(GetPointTwo() - GetPointOne());
    return v.GetNormal();
}

a2de::Vector2D Line::GetNormal() {
    return static_cast<const a2de::Line&>(*this).GetNormal();
}


bool Line::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Line::Contains(const Point& point) const {
    auto d = Math::GetDistance(point.GetPosition(), this->GetPointOne(), this->GetPointTwo());
    return Math::IsEqual(d, 0.0);
}

bool Line::Contains(const Line& line) const {
    return (*this) == line;
}

bool Line::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Line::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Line::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Line::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Line::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Line::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Line::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Line::Contains(const Sector& /*sector*/) const {
    return false;
}


A2DE_END