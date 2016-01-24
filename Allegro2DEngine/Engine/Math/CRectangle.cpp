/**************************************************************************************************
// file:	Engine\Math\CRectangle.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the rectangle class
 **************************************************************************************************/
#define NOMINMAX

#include "CRectangle.h"

#include <utility>
#include <algorithm>

#include "CPoint.h"
#include "CLine.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"
#include "CVector2D.h"

#include "CMiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Rectangle::Rectangle(const Vector2D& position, const Vector2D& half_extents)
    : Shape(position, half_extents) {
    _type = Shape::ShapeType::Rectangle;
    _verts.resize(6);
    CalculateVerts();
}

Rectangle::Rectangle(const Rectangle& rect) : Shape(rect) {
    CalculateArea();
}

Rectangle::~Rectangle() {

}
Line Rectangle::GetTop() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {{ p.GetX() - e.GetX(), p.GetY() - e.GetY() }, { p.GetX() + e.GetX(), p.GetY() + e.GetY() }};
}
Line Rectangle::GetLeft() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {{p.GetX() - e.GetX(), p.GetY() + e.GetY()}, {p.GetX() - e.GetX(), p.GetY() - e.GetY()}};
}
Line Rectangle::GetBottom() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {{p.GetX() - e.GetX(), p.GetY() + e.GetY()}, {p.GetX() + e.GetX(), p.GetY() + e.GetY()}};
}
Line Rectangle::GetRight() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {{p.GetX() + e.GetX(), p.GetY() - e.GetY()}, {p.GetX() + e.GetX(), p.GetY() + e.GetY()}};
}
Vector2D Rectangle::GetTopLeft() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {p.GetX() - e.GetX(), p.GetY() - e.GetY()};
}
Vector2D Rectangle::GetTopRight() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {p.GetX() + e.GetX(), p.GetY() - e.GetY()};
}
Vector2D Rectangle::GetBottomLeft() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {p.GetX() - e.GetX(), p.GetY() + e.GetY()};
}
Vector2D Rectangle::GetBottomRight() const {
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    return {p.GetX() + e.GetX(), p.GetY() + e.GetY()};
}

void Rectangle::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
    CalculateVerts();
}

void Rectangle::SetHalfExtents(const Vector2D& half_extents) {
    Shape::SetHalfExtents(half_extents);
    CalculateArea();
    CalculateVerts();
}

//void Rectangle::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) {
//
//    auto p = this->_transform.GetPosition();
//    auto e = this->_half_extents;
//
//    double x1 = a2de::Math::ToScreenScale(p.GetX() - e.GetX());
//    double y1 = a2de::Math::ToScreenScale(p.GetY() - e.GetY());
//    double x2 = a2de::Math::ToScreenScale(p.GetX() + e.GetX());
//    double y2 = a2de::Math::ToScreenScale(p.GetY() + e.GetY());
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//
//    filled ? al_draw_filled_rectangle(x1, y1, x2, y2, color) : al_draw_rectangle(x1, y1, x2, y2, color, 0.0);
//
//    al_set_target_bitmap(old_target);
//
//}

bool Rectangle::Intersects(const Polygon& polygon) const {
    return polygon.Intersects(*this);
}

bool Rectangle::Intersects(const Rectangle& rectangle) const {
    
    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;
    
    double myX = p.GetX();
    double myY = p.GetY();
    double myWidth = e.GetX();
    double myHeight = e.GetY();
    
    double myTop = myY - myHeight;
    double myLeft = myX - myWidth;
    double myRight = myX + myWidth;
    double myBottom = myY + myHeight;

    auto rp = rectangle._transform.GetPosition();
    auto re = rectangle._half_extents;

    double rX = rp.GetX();
    double rY = rp.GetY();
    double rWidth = re.GetX();
    double rHeight = re.GetY();

    double rTop = rY - rHeight;
    double rLeft = rX - rWidth;
    double rRight = rX + rWidth;
    double rBottom = rY + rHeight;

    if(myTop > rBottom) return false;
    if(myBottom < rTop) return false;
    if(myLeft > rRight) return false;
    if(myRight < rLeft) return false;

    return true;
}
bool Rectangle::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //bool resultTop = GetTop().Intersects(triangle.GetLineAB()) ||
    //    GetTop().Intersects(triangle.GetLineBC()) ||
    //    GetTop().Intersects(triangle.GetLineCA());
    //bool resultLeft = GetLeft().Intersects(triangle.GetLineAB()) ||
    //    GetLeft().Intersects(triangle.GetLineBC()) ||
    //    GetLeft().Intersects(triangle.GetLineCA());
    //bool resultRight = GetRight().Intersects(triangle.GetLineAB()) ||
    //    GetRight().Intersects(triangle.GetLineBC()) ||
    //    GetRight().Intersects(triangle.GetLineCA());
    //bool resultBottom = GetBottom().Intersects(triangle.GetLineAB()) ||
    //    GetBottom().Intersects(triangle.GetLineBC()) ||
    //    GetBottom().Intersects(triangle.GetLineCA());
    //bool isInside = Intersects(Point(triangle.GetCenter(), triangle.GetColor()));
    //return (isInside || resultTop || resultLeft || resultRight || resultBottom);
}
bool Rectangle::Intersects(const Ellipse& ellipse) const {

    auto eeh = ellipse.GetHalfExtents();
    double ellipseResultWidth = eeh.GetX();
    double ellipseResultHeight = eeh.GetY();

    auto ep = ellipse.GetPosition();

    auto t = GetTop();
    double distTop = Math::GetDistance(ep, t.GetPointOne(), t.GetPointTwo());

    auto l = GetLeft();
    double distLeft = Math::GetDistance(ep, l.GetPointOne(), l.GetPointTwo());

    auto r = GetRight();
    double distRight = Math::GetDistance(ep, r.GetPointOne(), r.GetPointTwo());

    auto b = GetBottom();
    double distBottom = Math::GetDistance(ep, b.GetPointOne(), b.GetPointTwo());

    bool resultTop = (distTop <= ellipseResultWidth) || (distTop <= ellipseResultHeight);
    bool resultLeft = (distLeft <= ellipseResultWidth) || (distLeft <= ellipseResultHeight);
    bool resultRight = (distRight <= ellipseResultWidth) || (distRight <= ellipseResultHeight);
    bool resultBottom = (distBottom <= ellipseResultWidth) || (distBottom <= ellipseResultHeight);

    return (resultTop || resultLeft || resultRight || resultBottom);
}
bool Rectangle::Intersects(const Circle& circle) const {

    double radius = circle.GetRadius();

    auto cp = circle.GetPosition();

    auto t = GetTop();
    double distTop = Math::GetDistance(cp, t.GetPointOne(), t.GetPointTwo());

    auto l = GetLeft();
    double distLeft = Math::GetDistance(cp, l.GetPointOne(), l.GetPointTwo());

    auto r = GetRight();
    double distRight = Math::GetDistance(cp, r.GetPointOne(), r.GetPointTwo());

    auto b = GetBottom();
    double distBottom = Math::GetDistance(cp, b.GetPointOne(), b.GetPointTwo());

    bool resultTop = distTop <= radius;
    bool resultLeft = distLeft <= radius;
    bool resultRight = distRight <= radius;
    bool resultBottom = distBottom <= radius;
    bool isInside = Intersects(Point(circle.GetPosition()));
    return (isInside || resultTop || resultLeft || resultRight || resultBottom);
}

bool Rectangle::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Rectangle::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Rectangle::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Rectangle::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Rectangle::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Rectangle::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Rectangle::Intersects(const Vector2D& position) const {

    auto p = this->_transform.GetPosition();
    auto e = this->_half_extents;

    double rX = p.GetX();
    double rHalfWidth = e.GetX();
    double rLeft = rX - rHalfWidth;
    double rRight = rX + rHalfWidth;

    double rY = p.GetY();
    double rHalfHeight = e.GetY();
    double rTop = rY - rHalfHeight;
    double rBottom = rY + rHalfHeight;

    double pX = position.GetX();
    double pY = position.GetY();

    if(rLeft > pX) return false;
    if(rRight < pX) return false;
    if(rTop > pY) return false;
    if(rBottom < pY) return false;

    return true;
}

std::pair<bool, a2de::Rectangle> Rectangle::Overlap(const Rectangle& rectangle) {
    if(this->Intersects(rectangle) == false) {
        bool result = false;
        return std::make_pair(result, Rectangle());
    }

    auto p = this->_transform.GetPosition();

    a2de::Vector2D my_TL(p - this->_half_extents);
    a2de::Vector2D my_BR(p + this->_half_extents);

    auto rp = rectangle._transform.GetPosition();

    a2de::Vector2D your_TL(rp - rectangle._half_extents);
    a2de::Vector2D your_BR(rp + rectangle._half_extents);

    a2de::Vector2D topLeft(std::max(my_TL.GetX(), your_TL.GetX()), std::max(my_TL.GetY(), your_TL.GetY()));
    a2de::Vector2D bottomRight(std::min(my_BR.GetX(), your_BR.GetX()), std::min(my_BR.GetY(), your_BR.GetY()));

    return std::make_pair(true, Rectangle(topLeft, bottomRight));
}

Rectangle& Rectangle::operator=(const Rectangle& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    CalculateArea();

    return *this;
}

bool Rectangle::operator==(const Rectangle& rhs) {
    if(this == &rhs) return true;
    return (this->GetArea() == rhs.GetArea());
}
bool operator==(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return true;
    return (lhs.GetArea() == rhs.GetArea());
}
bool Rectangle::operator!=(const Rectangle& rhs) {
    return !(*this == rhs);
}
bool operator!=(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() != rhs.GetArea());
}
bool Rectangle::operator<(const Rectangle& rhs) {
    if(this == &rhs) return false;
    return (this->GetArea() < rhs.GetArea());
}
bool operator<(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() < rhs.GetArea());
}
bool Rectangle::operator>(const Rectangle& rhs) {
    if(this == &rhs) return false;
    return (this->GetArea() > rhs.GetArea());
}
bool operator>(const Rectangle& lhs, const Rectangle& rhs) {
    if(&lhs == &rhs) return false;
    return (lhs.GetArea() > rhs.GetArea());
}
bool Rectangle::operator<=(const Rectangle& rhs) {
    return !(*this > rhs);
}
bool operator<=(const Rectangle& lhs, const Rectangle& rhs) {
    return !(lhs.GetArea() < rhs.GetArea());
}

bool Rectangle::operator>=(const Rectangle& rhs) {
    return !(*this < rhs);
}
bool operator>=(const Rectangle& lhs, const Rectangle& rhs) {
    return !(lhs.GetArea() > rhs.GetArea());
}

void Rectangle::CalculateArea() {
    _area = (4.0) * (_half_extents.GetX() * _half_extents.GetY());
}

void a2de::Rectangle::CalculateVerts() {
    auto p = this->GetPosition();
    auto he = this->GetHalfExtents();
    _verts[0] = Vertex{ Vector3D(p.GetX() - he.GetX(), p.GetY() + he.GetY(), 0.0) };
    _verts[1] = Vertex{ Vector3D(p.GetX() - he.GetX(), p.GetY() - he.GetY(), 0.0) };
    _verts[2] = Vertex{ Vector3D(p.GetX() + he.GetX(), p.GetY() - he.GetY(), 0.0) };
    _verts[3] = Vertex{ Vector3D(p.GetX() - he.GetX(), p.GetY() + he.GetY(), 0.0) };
    _verts[4] = Vertex{ Vector3D(p.GetX() + he.GetX(), p.GetY() - he.GetY(), 0.0) };
    _verts[5] = Vertex{ Vector3D(p.GetX() + he.GetX(), p.GetY() + he.GetY(), 0.0) };

}

A2DE_END
