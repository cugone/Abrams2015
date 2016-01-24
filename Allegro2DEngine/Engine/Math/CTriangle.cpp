/**************************************************************************************************
// file:	Engine\Math\CTriangle.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the triangle class
 **************************************************************************************************/
#include "CTriangle.h"

#include <cassert>

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"

#include "CVector2D.h"
#include "CVector3D.h"

#include "MathConstants.h"
#include "CMiscMath.h"

#include "../a2de_exceptions.h"

A2DE_BEGIN


Triangle::Triangle(const Vector2D& pointOne, const Vector2D& pointTwo, const Vector2D& pointThree) : Shape(), _pointA(pointOne), _pointB(pointTwo), _pointC(pointThree) {
    if(_pointA == _pointB || _pointA == _pointC || _pointB == _pointC) throw Exception("Points do not describe a triangle.");
    _type = Shape::ShapeType::Triangle;
    _verts.resize(3);
    _verts[0] = Vertex{ _pointA };
    _verts[1] = Vertex{ _pointB };
    _verts[2] = Vertex{ _pointC };
    CalculateDimensions();
    CalculateArea();
}

Triangle::Triangle(const Triangle& triangle) : Shape(triangle), _pointA(triangle._pointA), _pointB(triangle._pointB), _pointC(triangle._pointC) {
    _type = Shape::ShapeType::Triangle;
    _verts.resize(3);
    _verts[0] = Vertex{ _pointA };
    _verts[1] = Vertex{ _pointB };
    _verts[2] = Vertex{ _pointC };
    CalculateDimensions();
    CalculateArea();
}

Triangle::~Triangle() {

}

void Triangle::SetPosition(const Vector2D& position) {
    a2de::Vector2D delta = position - _transform.GetPosition();

    a2de::Vector2D new_a = _pointA + delta;
    a2de::Vector2D new_b = _pointB + delta;
    a2de::Vector2D new_c = _pointC + delta;

    SetPoints(new_a, new_b, new_c);
    _transform.SetPosition(_transform.GetPosition() + delta);

}

bool Triangle::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Triangle::Intersects(const Point& point) const {
    return Intersects(point.GetPosition());
}
bool Triangle::Intersects(const Line& line) const {
    return line.Intersects(*this);
}

bool Triangle::Intersects(const Rectangle& /*rectangle*/) const {
    return false;
    //bool resultAB = GetLineAB().Intersects(rectangle);
    //bool resultBC = GetLineBC().Intersects(rectangle);
    //bool resultCA = GetLineCA().Intersects(rectangle);

    //bool resultA = GetPointA().Intersects(rectangle);
    //bool resultB = GetPointB().Intersects(rectangle);
    //bool resultC = GetPointC().Intersects(rectangle);
    //return (resultAB || resultBC || resultCA || resultA || resultB || resultC);
}
bool Triangle::Intersects(const Circle& /*circle*/) const {
    return false;
    //bool resultAB = GetLineAB().Intersects(circle);
    //bool resultBC = GetLineBC().Intersects(circle);
    //bool resultCA = GetLineCA().Intersects(circle);

    //bool resultA = GetPointA().Intersects(circle);
    //bool resultB = GetPointB().Intersects(circle);
    //bool resultC = GetPointC().Intersects(circle);
    //bool resultCircleCenter = this->Intersects(Point(circle.GetPosition()));
    //return (resultAB || resultBC || resultCA || resultA || resultB || resultC || resultCircleCenter);
}
bool Triangle::Intersects(const Ellipse& /*ellipse*/) const {
    return false;
    //bool resultAB = GetLineAB().Intersects(ellipse);
    //bool resultBC = GetLineBC().Intersects(ellipse);
    //bool resultCA = GetLineCA().Intersects(ellipse);

    //bool resultA = GetPointA().Intersects(ellipse);
    //bool resultB = GetPointB().Intersects(ellipse);
    //bool resultC = GetPointC().Intersects(ellipse);
    //return (resultAB || resultBC || resultCA || resultA || resultB || resultC);
}
bool Triangle::Intersects(const Triangle& /*triangle*/) const {
    return false;
    //bool resultAB = this->GetLineAB().Intersects(triangle.GetLineAB()) ||
    //                this->GetLineAB().Intersects(triangle.GetLineBC()) ||
    //                this->GetLineAB().Intersects(triangle.GetLineCA());

    //bool resultBC = this->GetLineBC().Intersects(triangle.GetLineAB()) ||
    //    this->GetLineBC().Intersects(triangle.GetLineBC()) ||
    //    this->GetLineBC().Intersects(triangle.GetLineCA());

    //bool resultCA = this->GetLineCA().Intersects(triangle.GetLineAB()) ||
    //    this->GetLineCA().Intersects(triangle.GetLineBC()) ||
    //    this->GetLineCA().Intersects(triangle.GetLineCA());

    //bool resultA = this->GetPointA().Intersects(triangle);
    //bool resultB = this->GetPointB().Intersects(triangle);
    //bool resultC = this->GetPointC().Intersects(triangle);

    //return (resultAB || resultBC || resultCA || resultA || resultB || resultC);
}

bool Triangle::Intersects(const Arc& /*arc*/) const {
    return false;
}
bool Triangle::Intersects(const Polygon& /*polygon*/) const {
    return false;
}
bool Triangle::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Triangle::Intersects(const Sector& sector) const {
    return sector.Intersects(*this);
}

bool Triangle::Intersects(const a2de::Vector2D& position) const {

    Vector3D A(GetPointA().GetX(), GetPointA().GetY());
    Vector3D B(GetPointB().GetX(), GetPointB().GetY());
    Vector3D C(GetPointC().GetX(), GetPointC().GetY());

    Vector3D AB(A - B);
    Vector3D BC(B - C);
    Vector3D CA(C - A);

    Vector3D AP(A - position);
    Vector3D BP(B - position);
    Vector3D CP(C - position);

    Vector3D resultABAP(Vector3D::CrossProduct(AB, AP));
    Vector3D resultBCBP(Vector3D::CrossProduct(BC, BP));
    Vector3D resultCACP(Vector3D::CrossProduct(CA, CP));

    bool resultPos = (resultABAP.GetZ() > 0.0) && (resultBCBP.GetZ() > 0.0) && (resultCACP.GetZ() > 0.0);
    bool resultZero = (Math::IsEqual(resultABAP.GetZ(), 0.0) && Math::IsEqual(resultBCBP.GetZ(), 0.0) && Math::IsEqual(resultCACP.GetZ(), 0.0));
    bool resultNeg = (resultABAP.GetZ() < 0.0) && (resultBCBP.GetZ() < 0.0) && (resultCACP.GetZ() < 0.0);
    //bool isOn = point.IsOnLine(GetLineAB()) || point.IsOnLine(GetLineBC()) || point.IsOnLine(GetLineCA());
    return (/*isOn ||*/ resultPos || resultZero || resultNeg);
}

//void Triangle::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) {
//    double ax = a2de::Math::ToScreenScale(_pointA.GetX());
//    double ay = a2de::Math::ToScreenScale(_pointA.GetY());
//    double bx = a2de::Math::ToScreenScale(_pointB.GetX());
//    double by = a2de::Math::ToScreenScale(_pointB.GetY());
//    double cx = a2de::Math::ToScreenScale(_pointC.GetX());
//    double cy = a2de::Math::ToScreenScale(_pointC.GetY());
//
//
//    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
//    al_set_target_bitmap(dest);
//    
//    filled ? al_draw_filled_triangle(ax, ay, bx, by, cx, cy, color) : al_draw_triangle(ax, ay, bx, by, cx, cy, color, 0.0);
//    
//    al_set_target_bitmap(old_target);
//
//}

void Triangle::CalculateArea() {
    _area = (0.5 * GetSideA() * GetSideB() * std::sin(GetAngleC()));
}

void Triangle::CalculateDimensions() {

    //double longestSide = 0.0;
    //double ls_ba = (_pointB - _pointA).GetLengthSquared();
    //double ls_bc = (_pointC - _pointA).GetLengthSquared();
    //double ls_ac = (_pointA - _pointC).GetLengthSquared();

    //longestSide = std::max(std::max(ls_ba, ls_bc), ls_ac);
    //longestSide = std::sqrt(longestSide);
    //double x2 = std::max(longestSide * std::cos(), longestSide.GetPointTwo().GetX());
    //double x1 = std::min(longestSide.GetPointOne().GetX(), longestSide.GetPointTwo().GetX());

    //int w = (x2 - x1);
    //int h = (GetSideA() * std::sin(GetAngleC()));
    //_dimensions = Vector2D(w, h);
}

const Vector2D& Triangle::GetPointA() const {
    return _pointA;
}

Vector2D& Triangle::GetPointA() {
    return const_cast<Vector2D&>(static_cast<const Triangle&>(*this).GetPointA());
}

const Vector2D& Triangle::GetPointB() const {
    return _pointB;
}

Vector2D& Triangle::GetPointB() {
    return const_cast<Vector2D&>(static_cast<const Triangle&>(*this).GetPointB());
}

const Vector2D& Triangle::GetPointC() const {
    return _pointC;
}

Vector2D& Triangle::GetPointC() {
    return const_cast<Vector2D&>(static_cast<const Triangle&>(*this).GetPointC());
}

Vector2D Triangle::GetLineAB() const {
    return (_pointB - _pointA);
}
Vector2D Triangle::GetLineBC() const {
    return (_pointC - _pointB);
}
Vector2D Triangle::GetLineCA() const {
    return (_pointC - _pointA);
}

double Triangle::GetSideA() const {
    return (GetLineBC()).GetLength();
}
double Triangle::GetSideB() const {
    return (GetLineCA()).GetLength();
}
double Triangle::GetSideC() const {
    return (GetLineAB()).GetLength();
}
double Triangle::GetAngleA() const {
    double sA = GetSideA();
    double sB = GetSideB();
    double sC = GetSideC();
    //arccosine(b^2 + c^2 - a^2 / 2bc)
    return std::acos((sB * sB + sC * sC - sA * sA) / (2 * sB * sC));
}
double Triangle::GetAngleB() const {
    double sA = GetSideA();
    double sB = GetSideB();
    double sC = GetSideC();
    //arccosine(a^2 + c^2 - b^2 / 2ac)
    return std::acos((sA * sA + sC * sC - sB * sB) / (2 * sA * sC));
}
double Triangle::GetAngleC() const {
    double sA = GetSideA();
    double sB = GetSideB();
    double sC = GetSideC();
    //arccosine(a^2 + b^2 - c^2 / 2ab)
    double result = (sA * sA + sB * sB - sC * sC) / (2 * sA * sB);
    return std::acos(result);
}

bool Triangle::IsRightTriangle() const {
    double AC = Math::GetDistanceSquared(GetPointA(), GetPointC());
    double CB = Math::GetDistanceSquared(GetPointC(), GetPointB());
    double AB = Math::GetDistanceSquared(GetPointA(), GetPointB());
    return (Math::IsEqual(AC + CB, AB));
}

void Triangle::SetHalfExtents(const Vector2D& /*half_extents*/) { /* DO NOTHING */ }

void Triangle::SetPointA(const Vector2D& position) {
    SetPoints(position, GetPointB(), GetPointC());
}

void Triangle::SetPointB(const Vector2D& position) {
    SetPoints(GetPointA(), position, GetPointC());
}

void Triangle::SetPointC(const Vector2D& position) {
    SetPoints(GetPointA(), GetPointB(), position);
}

void Triangle::SetPoints(const Vector2D& pointA, const Vector2D& pointB, const Vector2D& pointC) {

    this->_pointA = pointA;
    this->_pointB = pointB;
    this->_pointC = pointC;

}

bool Triangle::Contains(const Circle& /*circle*/) const {
    return false;
}

bool Triangle::Contains(const Ellipse& /*ellipse*/) const {
    return false;
}

Triangle& Triangle::operator=(const Triangle& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    this->_pointA = rhs._pointA;
    this->_pointB = rhs._pointB;
    this->_pointC = rhs._pointC;
    CalculateDimensions();
    CalculateArea();

    return *this;
}

A2DE_END