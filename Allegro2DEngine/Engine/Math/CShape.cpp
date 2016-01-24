/**************************************************************************************************
// file:	Engine\Math\CShape.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the shape class
 **************************************************************************************************/
#include "CShape.h"

#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CPolygon.h"
#include "CSpline.h"
#include "CSector.h"


A2DE_BEGIN


const std::vector<Vertex>& a2de::Shape::GetVerticies() const {
    return _verts;
}

std::vector<Vertex>& a2de::Shape::GetVerticies() {
    return const_cast<decltype(_verts)&>(static_cast<const Shape&>(*this).GetVerticies());
}

Shape::Shape(const Vector2D& position, const Vector2D& half_extents) :
_transform(),
_half_extents(half_extents),
_area(0.0),
_type(Shape::ShapeType::None),
_verts()
{
    _transform.SetPosition(position);
}


Shape::Shape(const Shape& shape) :
_transform(shape._transform),
_half_extents(shape._half_extents),
_area(shape._area),
_type(shape._type),
_verts()
{ }

Shape& Shape::operator=(const Shape& rhs) {
    if(this == &rhs) return *this;
    this->_transform = rhs._transform;
    this->_half_extents = rhs._half_extents;
    this->_area = rhs._area;
    this->_type = rhs._type;
    this->_verts = rhs._verts;
    return *this;
}

Shape::~Shape() {

}

void a2de::Shape::CalculateVerts() {
    /* DO NOTHING: Not required */
}

const Vector2D& Shape::GetHalfExtents() const {
    return _half_extents;
}

Vector2D& Shape::GetHalfExtents() {
    return const_cast<a2de::Vector2D&>(static_cast<const Shape&>(*this).GetHalfExtents());
}

const Vector2D& Shape::GetPosition() const {
    return _transform.GetPosition();
}

Vector2D& Shape::GetPosition() {
    return const_cast<a2de::Vector2D&>(static_cast<const Shape&>(*this).GetPosition());
}

double Shape::GetArea() const {
    return _area;
}

double Shape::GetArea() {
    return static_cast<const Shape&>(*this).GetArea();
}

void Shape::SetPosition(const Vector2D& position) {
    _transform.SetPosition(position);
    CalculateVerts();
}

void Shape::SetHalfExtents(const Vector2D& dimensions) {
    _half_extents = dimensions;
}

const Shape::ShapeType& Shape::GetShapeType() const {
    return _type;
}

Shape::ShapeType& Shape::GetShapeType() {
    return const_cast<Shape::ShapeType&>(static_cast<const Shape&>(*this).GetShapeType());
}

bool Shape::Contains(const Shape& shape) const {

    Shape::ShapeType type = shape.GetShapeType();
    switch(type) {
    case Shape::ShapeType::Point:
        return this->Contains(dynamic_cast<const Point&>(shape));
    case Shape::ShapeType::Line:
        return this->Contains(dynamic_cast<const Line&>(shape));
    case Shape::ShapeType::Rectangle:
        return this->Contains(dynamic_cast<const Rectangle&>(shape));
    case Shape::ShapeType::Circle:
        return this->Contains(dynamic_cast<const Circle&>(shape));
    case Shape::ShapeType::Ellipse:
        return this->Contains(dynamic_cast<const Ellipse&>(shape));
    case Shape::ShapeType::Triangle:
        return this->Contains(dynamic_cast<const Triangle&>(shape));
    case Shape::ShapeType::Arc:
        return this->Contains(dynamic_cast<const Arc&>(shape));
    case Shape::ShapeType::Polygon:
        return this->Contains(dynamic_cast<const Polygon&>(shape));
    case Shape::ShapeType::Spline:
        return this->Contains(dynamic_cast<const Spline&>(shape));
    case Shape::ShapeType::Sector:
        return this->Contains(dynamic_cast<const Sector&>(shape));
    default:
        return false;
    }

}

bool Shape::Contains(const Point& point) const {
    return this->Intersects(point);
}

bool Shape::Contains(const Line& line) const {
    return this->Intersects(line.GetPointOne()) && this->Intersects(line.GetPointTwo());
}

bool Shape::Contains(const Rectangle& rectangle) const {
    auto r_pos = rectangle.GetPosition();
    auto r_dim = rectangle.GetHalfExtents();
    
    double rleft = r_pos.GetX() - r_dim.GetX();
    double rtop = r_pos.GetY() - r_dim.GetY();
    double rright = r_pos.GetX() + r_dim.GetX();
    double rbottom = r_pos.GetY() + r_dim.GetY();

    auto t_pos = this->GetPosition();
    auto t_dim = this->GetHalfExtents();

    double tleft = t_pos.GetX() - t_dim.GetX();
    double ttop = t_pos.GetY() - t_dim.GetY();
    double tright = t_pos.GetX() + t_dim.GetX();
    double tbottom = t_pos.GetY() + t_dim.GetY();

    bool is_exact = a2de::Math::IsEqual(rtop, ttop) && a2de::Math::IsEqual(rleft, tleft) && a2de::Math::IsEqual(rbottom, tbottom) && a2de::Math::IsEqual(rright, tright);
    bool is_smaller = (rtop > ttop && rleft > tleft && rbottom < tbottom && rright < tright);
    return (is_exact || is_smaller);
}

bool Shape::Contains(const Circle& circle) const {
    double cdiameter = circle.GetDiameter();
    double twidth = this->GetHalfExtents().GetX() * 2.0;
    double theight = this->GetHalfExtents().GetY() * 2.0;

    bool diameter_equal_to_width = a2de::Math::IsEqual(cdiameter, twidth);
    bool diameter_equal_to_height = a2de::Math::IsEqual(cdiameter, theight);
    bool diameter_less_than_width = cdiameter < twidth;
    bool diameter_less_than_height = cdiameter < theight;
    
    bool diameter_less_equal_width = diameter_less_than_width || diameter_equal_to_width;
    bool diameter_less_equal_height = diameter_less_than_height || diameter_equal_to_height;

    bool center_inside_shape = this->Intersects(circle.GetPosition());

    bool contains = center_inside_shape && diameter_less_equal_width && diameter_less_equal_height;

    return contains;
}

bool Shape::Contains(const Ellipse& ellipse) const {
    return false;//this->Intersects(ellipse.GetPosition()) && ellipse.GetHalfWidth() <= this->GetHalfWidth() && ellipse.GetHalfHeight() <= this->GetHalfHeight();
}

bool Shape::Contains(const Triangle& triangle) const {
    return this->Intersects(triangle.GetPointA()) && this->Intersects(triangle.GetPointB()) && this->Intersects(triangle.GetPointC());
}

bool Shape::Contains(const Arc& arc) const {
    return this->Intersects(arc.GetStartPoint()) && this->Intersects(arc.GetEndPoint()) && this->Intersects(arc.GetCenterPoint());
}

bool Shape::Contains(const Polygon& polygon) const {

    a2de::Vector2D upper_left = polygon.GetSmallestCoordinates();
    a2de::Vector2D lower_right = polygon.GetLargestCoordinates();
    a2de::Vector2D half_extents = (lower_right - upper_left) / 2.0;
    a2de::Vector2D position = upper_left + half_extents;
    a2de::Rectangle bounds(position, half_extents);

    return this->Contains(bounds);
}

bool Shape::Contains(const Spline& /*spline*/) const {
    return false;
}

bool Shape::Contains(const Sector& sector) const {
    
    a2de::Circle bounds(sector.GetPosition(), sector.GetRadius());
    if(this->Contains(bounds)) return true;

    return (this->Intersects(sector.GetPosition()) &&
            this->Intersects(sector.GetStartPoint()) &&
            this->Intersects(sector.GetEndPoint()) &&
            this->Intersects(sector.GetArcCenterPoint()));
}

A2DE_END