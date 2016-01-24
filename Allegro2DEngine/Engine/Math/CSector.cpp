/**************************************************************************************************
// file:	Engine\Math\CSector.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the sector class
 **************************************************************************************************/
#include "CSector.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"

#include "MathConstants.h"
#include "CMiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

Sector::Sector(const Vector2D& position, double startAngle, double endAngle, double radius) : Shape(position, {(radius < 0.0 ? 0.0 : radius * 2), (radius < 0.0 ? 0.0 : radius * 2)}), _arc(position, startAngle, endAngle, (radius < 0.0 ? 0.0 : radius)) {
    _type = Shape::ShapeType::Sector;
}

Sector::Sector(const Sector& sector) : Shape(sector), _arc(sector._arc) {
    _type = Shape::ShapeType::Sector;
}

Sector::~Sector() {
    /* DO NOTHING. ALL DE-INITIALIZATION DONE IN BASE CLASS */
}

void Sector::SetPosition(const Vector2D& position) {
    this->SetPosition(position);
    _arc.SetPosition(position);
}

void Sector::SetHalfExtents(const Vector2D& half_extents) {
    _arc.SetHalfExtents(_half_extents);
}

void Sector::SetRadius(double radius) {
    if(radius < 0.0) radius = 0.0;
    SetHalfExtents(Vector2D(radius, radius));
}

void Sector::SetAngles(double startAngle, double endAngle) {
    _arc.SetAngles(startAngle, endAngle);
    CalculateArea();
}

double Sector::GetLength() const {
    return _arc.GetLength();
}
double Sector::GetLength(){
    return static_cast<const Sector&>(*this).GetLength();
}

double Sector::GetRadius() const {
    return _arc.GetRadius();
}
double Sector::GetRadius(){
    return static_cast<const Sector&>(*this).GetRadius();
}

double Sector::GetTheta() const {
    return _arc.GetTheta();
}
double Sector::GetTheta(){
    return static_cast<const Sector&>(*this).GetTheta();
}

double Sector::GetStartAngle() const {
    return _arc.GetStartAngle();
}
double Sector::GetStartAngle() {
    return static_cast<const Sector&>(*this).GetStartAngle();
}

double Sector::GetEndAngle() const {
    return _arc.GetEndAngle();
}
double Sector::GetEndAngle() {
    return static_cast<const Sector&>(*this).GetEndAngle();
}

Vector2D Sector::GetStartPoint() const {
    return _arc.GetStartPoint();
}
Vector2D Sector::GetEndPoint() const {
    return _arc.GetEndPoint();
}

Vector2D Sector::GetArcCenterPoint() const {
    return _arc.GetCenterPoint();
}
Vector2D Sector::GetArcCenterPoint() {
    return static_cast<const Sector&>(*this).GetArcCenterPoint();
}


//void Sector::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) {
//
//    auto p = this->GetPosition();
//    Line initial(GetPosition(), GetStartPoint(), color);
//    Line terminal(GetPosition(), GetEndPoint(), color);
//
//    initial.Render(dest, initial.GetColor(), false);
//    terminal.Render(dest, terminal.GetColor(), false);
//
//    _arc.Render(dest, color, filled);
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//
//    filled ? al_draw_filled_pieslice(a2de::Math::ToScreenScale(p.GetX()), a2de::Math::ToScreenScale(p.GetY()), a2de::Math::ToScreenScale(GetRadius()), GetStartAngle(), GetEndAngle() - GetStartAngle(), color) :
//             al_draw_pieslice(a2de::Math::ToScreenScale(p.GetX()), a2de::Math::ToScreenScale(p.GetY()), a2de::Math::ToScreenScale(GetRadius()), GetStartAngle(), GetEndAngle() - GetStartAngle(), color, 0.0);
//
//    al_set_target_bitmap(old_target);
//
//}

void Sector::CalculateArea() {
    auto r2 = GetRadius();
    r2 *= r2;
    auto theta = GetTheta();
    _area = 0.5 * (r2 * theta);
}

bool Sector::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Sector::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}

bool Sector::Intersects(const Line& line) const {
    if(this->Intersects(Point(line.GetPointOne()))) return true;
    if(this->Intersects(Point(line.GetPointTwo()))) return true;

    Line initial(GetPosition(), GetStartPoint());
    Line terminal(GetPosition(), GetEndPoint());

    if(initial.Intersects(line)) return true;
    if(terminal.Intersects(line)) return true;

    return false;
}

bool Sector::Intersects(const Rectangle& rectangle) const {

    Circle s(this->GetPosition(), this->GetRadius());

    if(rectangle.Intersects(s) == false) return false;
    if(rectangle.Intersects(Point(this->GetPosition()))) return true;

    if(this->Intersects(rectangle.GetTopLeft())) return true;
    if(this->Intersects(rectangle.GetTopRight())) return true;
    if(this->Intersects(rectangle.GetBottomLeft())) return true;
    if(this->Intersects(rectangle.GetBottomRight())) return true;

    if(this->Intersects(rectangle.GetTop())) return true;
    if(this->Intersects(rectangle.GetLeft())) return true;
    if(this->Intersects(rectangle.GetBottom())) return true;
    if(this->Intersects(rectangle.GetRight())) return true;

    return false;
}

bool Sector::Intersects(const Circle& circle) const {

    //Intersections performed fast to slow.
    //FAST:
    //If bounding circle and argument circle do not intersect: no.
    //If initial point intersects circle: yes.
    //If terminal point intersects circle: yes.
    //If central point intersects circle: yes.
    //SLOW:
    //If the angle between the circle and the sector is in-between the start and end angles (mapped to [0, 2pi]): yes.
    //If the circle intersects the initial line: yes.
    //If the circle intersects the terminal line: yes.
    //Otherwise: no.

    auto my_p = this->GetPosition();
    auto your_p = circle.GetPosition();
    double radius_sum = this->GetRadius() + circle.GetRadius();
    if(a2de::Math::GetDistance(my_p, your_p) > radius_sum) return false;

    auto sp = this->GetStartPoint();
    if(circle.Intersects(sp)) return true;

    auto ep = this->GetEndPoint();
    if(circle.Intersects(ep)) return true;

    if(circle.Intersects(my_p)) return true;
    
    double angle = Vector2D::GetFacingAngle(your_p, my_p);

    //Map return values to [0, 360]
    double sA = this->GetStartAngle();
    while(sA > Math::A2DE_PI) {
        sA -= Math::A2DE_2PI;
    }
    double eA = this->GetEndAngle();
    while(eA > Math::A2DE_PI) {
        eA -= Math::A2DE_2PI;
    }
    bool within_sector = ((sA < angle || Math::IsEqual(sA, angle)) && (angle < eA || Math::IsEqual(angle, eA)));
    if(within_sector) return true;

    Line sl(my_p, sp);
    Line tl(my_p, ep);

    if(sl.Intersects(circle)) return true;
    if(tl.Intersects(circle)) return true;

    return false;
}

bool Sector::Intersects(const Ellipse& /*ellipse*/) const {
    return false;
}

bool Sector::Intersects(const Triangle& triangle) const {

    auto p = this->GetPosition();
    auto sp = this->GetStartPoint();
    auto ep = this->GetEndPoint();
    Line il(p, sp);
    Line tl(p, ep);
    Circle s(p, this->GetRadius());

    bool circle_intersect = triangle.Intersects(s);
    if(circle_intersect == false) return false;

    bool il_intersect = triangle.Intersects(il);
    if(il_intersect) return true;

    bool tl_intersect = triangle.Intersects(tl);
    if(tl_intersect) return true;

    bool c_intersect = triangle.Intersects(p);
    if(c_intersect) return true;

    return false;
}

bool Sector::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Sector::Intersects(const Polygon& /*polygon*/) const {
    return false;
}

bool Sector::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Sector::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Sector::Intersects(const Vector2D& position) const {
    Vector2D l(this->GetPosition() - position);
    if(l.GetLength() > GetRadius()) return false;
    if(Math::IsEqual(l.GetLength(), 0.0)) return true;

    Vector2D sF = Vector2D::GetFacingVector(this->GetArcCenterPoint(), this->GetPosition());
    Vector2D sF_n(sF.Normalize());
    Vector2D P_to_S(l.Normalize());

    double angle = std::acos(Vector2D::DotProduct(sF_n, P_to_S));
    double half_angle = GetTheta() / 2.0;

    bool angle_less = angle < half_angle;
    bool angle_equal = Math::IsEqual(angle, half_angle);

    return angle_less || angle_equal;
}

void Sector::SetAnglesDegrees(double startAngle, double endAngle) {
    SetAngles(a2de::Math::DegreeToRadian(startAngle), a2de::Math::DegreeToRadian(endAngle));
}

Sector& Sector::operator=(const Sector& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    SetAngles(rhs._arc.GetStartAngle(), rhs._arc.GetEndAngle());
    CalculateArea();

    return *this;
}


A2DE_END