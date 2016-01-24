/**************************************************************************************************
// file:	Engine\Math\CPoint.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the point class
 **************************************************************************************************/
#include "CPoint.h"

#include <cassert>
#include <cmath>

#include <allegro5/color.h>

#include "CMiscMath.h"

#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"
#include "CVector2D.h"
#include "CVertex.h"

#include "../a2de_exceptions.h"

A2DE_BEGIN

Point::Point(const Vector2D& position) : Shape(position) {
    _type = Shape::ShapeType::Point;
    _verts.resize(1);
    _verts[0] = Vertex(Vector3D(position.GetX(), position.GetY(), 0.0), Vector2D(), al_map_rgb_f(0.0, 0.0, 0.0));
    CalculateArea();
}

Point::Point(const Point& point) : Shape(point) {
    _type = Shape::ShapeType::Point;
    _verts = point._verts;
    CalculateArea();
}


Point::~Point() { }


void Point::SetPosition(const Vector2D& position) {
    Shape::SetPosition(position);
}

bool Point::IsPartOf(const Line& line) const {
    return (Math::GetDistance(this->GetPosition(), line.GetPointOne(), line.GetPointTwo()) <= 0.0001);
}

Point& Point::operator=(const Point& rhs) {
    if(this == &rhs) return *this;
    Shape::operator=(rhs);
    return *this;
}

bool Point::operator==(const Point& rhs) const {
    auto lhs_pos = this->GetPosition();
    auto rhs_pos = rhs.GetPosition();
    return (Math::IsEqual(lhs_pos.GetX(), rhs_pos.GetX()) && Math::IsEqual(lhs_pos.GetY(), rhs_pos.GetY()));
}

bool Point::operator!=(const Point& rhs) const {
    return !(*this == rhs);
}

Point Point::operator+(const Point& rhs) {
    auto p1 = this->GetPosition();
    auto p2 = rhs.GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();
    double xR = p2.GetX();
    double yR = p2.GetY();

    return Point(Vector2D(xP + xR, yP + yR));
}
Point Point::operator-(const Point& rhs) {
    auto p1 = this->GetPosition();
    auto p2 = rhs.GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();
    double xR = p2.GetX();
    double yR = p2.GetY();

    return Point(Vector2D(xP - xR, yP - yR));
}
Point Point::operator*(const Point& rhs) {
    auto p1 = this->GetPosition();
    auto p2 = rhs.GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();
    double xR = p2.GetX();
    double yR = p2.GetY();

    return Point(Vector2D(xP * xR, yP * yR));
}
Point Point::operator/(const Point& rhs) {
    auto p1 = this->GetPosition();
    auto p2 = rhs.GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();
    double xR = p2.GetX();
    double yR = p2.GetY();

    assert(a2de::Math::IsEqual(xR, 0.0) == false || a2de::Math::IsEqual(yR,0.0) == false);
    return Point(Vector2D(xP / xR, yP / yR));
}
Point Point::operator+(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    return Point(Vector2D(xP + scalar, yP + scalar));
}
Point Point::operator-(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    return Point(Vector2D(xP - scalar, yP - scalar));
}
Point Point::operator*(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    return Point(Vector2D(xP * scalar, yP * scalar));
}
Point Point::operator/(double scalar) {
    assert(a2de::Math::IsEqual(scalar, 0.0) == false);

    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    return Point(Vector2D(xP / scalar, yP / scalar));
}

Point& Point::operator+=(const Point& rhs) {    
    this->SetPosition(this->GetPosition() + rhs.GetPosition());
    return *this;
}
Point& Point::operator-=(const Point& rhs) {
    this->SetPosition(this->GetPosition() - rhs.GetPosition());
    return *this;
}
Point& Point::operator*=(const Point& rhs) {
    this->SetPosition(this->GetPosition() * rhs.GetPosition());
    return *this;
}
Point& Point::operator/=(const Point& rhs) {

    auto p2 = rhs.GetPosition();
    double xR = p2.GetX();
    double yR = p2.GetY();

    assert(a2de::Math::IsEqual(xR, 0.0) == false || a2de::Math::IsEqual(yR, 0.0) == false);

    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();
    
    double x = xP / xR;
    double y = yP / yR;

    this->SetPosition(Vector2D(x, y));
    return *this;
}

Point& Point::operator+=(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    double x = xP + scalar;
    double y = yP + scalar;

    this->SetPosition(Vector2D(x, y));
    return *this;
}
Point& Point::operator-=(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    double x = xP - scalar;
    double y = yP - scalar;

    this->SetPosition(Vector2D(x, y));
    return *this;
}
Point& Point::operator*=(double scalar) {
    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    double x = xP * scalar;
    double y = yP * scalar;

    this->SetPosition(Vector2D(x, y));
    return *this;
}
Point& Point::operator/=(double scalar) {
    assert(a2de::Math::IsEqual(scalar, 0.0) == false);

    auto p1 = this->GetPosition();
    double xP = p1.GetX();
    double yP = p1.GetY();

    double x = xP / scalar;
    double y = yP / scalar;

    this->SetPosition(Vector2D(x, y));
    return *this;
}

//void Point::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool /*filled*/) {
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//    auto p = this->GetPosition();
//    auto x = p.GetX();
//    auto y = p.GetY();
//    al_draw_pixel(a2de::Math::ToScreenScale(x), a2de::Math::ToScreenScale(y), color);
//    al_set_target_bitmap(old_target);
//}

void Point::CalculateArea() { /* DO NOTHING */ }
void Point::SetHalfExtents(const Vector2D& /*half_extents*/) { /* DO NOTHING */ }

bool Point::Intersects(const Vector2D& position) const {
    return (this->GetPosition() == position);
}

bool Point::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Point::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Point::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Point::Intersects(const Rectangle& rectangle) const {

    auto rp = rectangle.GetPosition();
    double rLeft = rp.GetX();

    auto tp = this->GetPosition();
    auto te = this->GetHalfExtents();
    double pWidth = te.GetX();
    double pRight = tp.GetX() + pWidth;
    if(rLeft > pRight) return false;

    auto re = rectangle.GetHalfExtents();
    double rWidth = re.GetX();
    double rRight = rLeft + rWidth;
    double pLeft = pRight - pWidth;
    if(rRight < pLeft) return false;

    double rTop = rp.GetY() - re.GetY();
    double pHeight = te.GetY();
    double pBottom = tp.GetY() + pHeight;
    if(rTop > pBottom) return false;

    double rHeight = re.GetY();
    double rBottom = rTop + rHeight;
    double pTop = pBottom - pHeight;
    if(rBottom < pTop) return false;

    return true;
}
bool Point::Intersects(const Circle& circle) const {
    auto p = this->GetPosition();
    auto c = circle.GetPosition();
    return (Math::GetDistance(p, c) <= circle.GetRadius());
}
bool Point::Intersects(const Ellipse& ellipse) const {
    auto p = this->GetPosition();
    auto ep = ellipse.GetPosition();
    auto eeh = ellipse.GetHalfExtents();
    auto eehx = eeh.GetX();
    auto eehy = eeh.GetY();
    auto d = Math::GetDistance(p, ep);

    bool resultX = (d < eehx || Math::IsEqual(d, eehx));
    bool resultY = (d < eehy || Math::IsEqual(d, eehy));
    return (resultX && resultY);
}
bool Point::Intersects(const Triangle& triangle) const {

    auto p = this->GetPosition();
    //Distance: this from center
    auto trp = triangle.GetPosition();
    Vector2D tCenter(trp.GetX(), trp.GetY());
    double distCtoP = Math::GetDistance(p, tCenter);

    //Distance: center to sides
    double distCtoAB = Math::GetDistance(tCenter, triangle.GetLineAB());
    double distCtoBC = Math::GetDistance(tCenter, triangle.GetLineBC());
    double distCtoCA = Math::GetDistance(tCenter, triangle.GetLineCA());

    //Distance: this from points
    double distPtoA = Math::GetDistance(p, triangle.GetPointA());
    double distPtoB = Math::GetDistance(p, triangle.GetPointB());
    double distPtoC = Math::GetDistance(p, triangle.GetPointC());

    bool resultAB = (distCtoP <= distCtoAB);
    bool resultBC = (distCtoP <= distCtoBC);
    bool resultCA = (distCtoP <= distCtoCA);
    bool resultA = (distPtoA <= distCtoP);
    bool resultB = (distPtoB <= distCtoP);
    bool resultC = (distPtoC <= distCtoP);

    return (resultAB && resultBC && resultCA && resultA && resultB && resultC);
}

bool Point::Intersects(const Arc& /*arc*/) const {
    return false;
}
bool Point::Intersects(const Polygon& /*polygon*/) const {
    return false;
}
bool Point::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Point::Intersects(const Sector& sector) const {
    return sector.Intersects(*this);
}


bool Point::Contains(const Shape& shape) const {
    return this->Contains(shape);
}

bool Point::Contains(const Point& point) const {
    return (*this) == point;
}

bool Point::Contains(const Line& /*line*/) const {
    return false;
}

bool Point::Contains(const Rectangle& /*rectangle*/) const {
    return false;
}

bool Point::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Point::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Point::Contains(const Triangle& /*triangle*/) const {
    return false;
}

bool Point::Contains(const Arc& /*arc*/) const {
    return false;
}

bool Point::Contains(const Polygon& /*polygon*/) const {
    return false;
}

bool Point::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Point::Contains(const Sector& /*sector*/) const {
    return false;
}


A2DE_END