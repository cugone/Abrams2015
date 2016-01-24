/**************************************************************************************************
// file:	Engine\Math\CPolygon.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the polygon class
 **************************************************************************************************/
#include "CPolygon.h"


#include "CPoint.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CArc.h"
#include "CSpline.h"
#include "CSector.h"


#include "MathConstants.h"
#include "CMiscMath.h"
#include <algorithm>
#include <cfloat>
#include "../a2de_exceptions.h"

#include <iostream>

A2DE_BEGIN

Polygon::Polygon(const std::vector<Vector2D>& points) : Shape(Vector2D(), Vector2D()), _points(points) {

    _type = Shape::ShapeType::Polygon;

    double width = 0.0;
    double height = 0.0;
    auto large_coords = GetLargestCoordinates();
    auto small_coords = GetSmallestCoordinates();
    width = large_coords.GetX() - small_coords.GetX();
    height = large_coords.GetY() - small_coords.GetY();
    _half_extents = Vector2D(width, height) / 2.0;
    CalculateArea();
    CalculateCenter();
}
Polygon::Polygon(const Polygon& polygon) : Shape(polygon), _points(polygon._points) {
    _type = Shape::ShapeType::Polygon;
    CalculateArea();
    CalculateCenter();
}
Polygon::~Polygon() {

}


auto Polygon::GetNumSides() const {
    return _points.size() - 1;
}

auto Polygon::GetNumSides() {
    return static_cast<const Polygon&>(*this).GetNumSides();
}

auto Polygon::GetNumVertices() const {
    return _points.size();
}

auto Polygon::GetNumVertices() {
    return static_cast<const Polygon&>(*this).GetNumVertices();
}

auto Polygon::GetSides() const {
    std::vector<Line> sides(GetNumSides());
    for(size_t i = 0; i < _points.size() - 1; ++i) {
        auto p1 = Vector2D(_points[i].GetX(), _points[i].GetY());
        auto p2 = Vector2D(_points[i + 1].GetX(), _points[i + 1].GetY());
        sides[i] = Line(p1, p2);
    }
    return sides;
}

auto Polygon::GetSides() {
    return static_cast<const Polygon&>(*this).GetSides();
}

const auto& Polygon::GetVertices() const {
    return _points;
}

auto& Polygon::GetVertices() {
    return const_cast<decltype(_points)&>(static_cast<const Polygon&>(*this).GetVertices());
}


void Polygon::SetPosition(const Vector2D& position) {
    auto p = position - this->GetPosition();
    auto t = this->_transform.GetLocalTransform();
    for(auto iter = _points.begin(), end = _points.end(); iter != end; ++iter) {
        *iter = t * p.GetHomogeneous();
    }
    CalculateCenter();
}

void Polygon::SetVertexPosition(std::size_t vertexNum, double x, double y) {
    _points[vertexNum] = Vector2D(x, y);
    CalculateArea();
    CalculateCenter();
}

bool Polygon::Intersects(const Shape& shape) const {
    return shape.Intersects(*this);
}

bool Polygon::Intersects(const Point& point) const {
    return (GetBoundingBox().Intersects(point.GetPosition()));
}
bool Polygon::Intersects(const Line& line) const {
    return line.Intersects(*this);
}
bool Polygon::Intersects(const Rectangle& rectangle) const {
    if(rectangle.Intersects(GetBoundingBox()) == false) return false;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(rectangle.Intersects(_points[i]) == true) {
            return true;
        }
    }
    return false;
}
bool Polygon::Intersects(const Circle& circle) const {
    if(circle.Intersects(GetBoundingBox()) == false) return false;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(circle.Intersects(_points[i]) == true) {
            return true;
        }
    }
    return false;
}
bool Polygon::Intersects(const Ellipse& ellipse) const {
    if(ellipse.Intersects(GetBoundingBox()) == false) return false;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(ellipse.Intersects(_points[i]) == true) {
            return true;
        }
    }
    return false;
}
bool Polygon::Intersects(const Triangle& triangle) const {
    if(triangle.Intersects(GetBoundingBox()) == false) return false;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(triangle.Intersects(_points[i]) == true) {
            return true;
        }
    }
    return false;
}
bool Polygon::Intersects(const Polygon& polygon) const {
    if(polygon.Intersects(this->GetBoundingBox()) == false) return false;
    auto mySides = this->GetSides();
    auto yourSides = polygon.GetSides();
    for(size_t i = 0; i < mySides.size(); ++i) {
        for(size_t j = 0; j < yourSides.size(); ++j) {
            if(mySides[i].Intersects(yourSides[j]) == true) {
                return true;
            }
        }
    }
    return false;
}

//void Polygon::Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& /*color*/, bool /*filled*/) {
//    if(dest == nullptr) return;
//
//    std::cout << "Polygon drawing not supported in Allegro 5.0.10" << std::endl;
//
//}

bool Polygon::Intersects(const Arc& /*arc*/) const {
    return false;
}

bool Polygon::Intersects(const Spline& /*spline*/) const {
    return false;
}

bool Polygon::Intersects(const Sector& /*sector*/) const {
    return false;
}

bool Polygon::Intersects(const Vector2D& position) const {
    return (GetBoundingBox().Intersects(position));
}

int* Polygon::CreateVerticesArray() {
    int* points = new int[GetNumVertices() * 2];
    for(size_t i = 0; i < _points.size(); ++i) {
        int x = i * 2;
        points[x] = a2de::Math::ToScreenScale(_points[i].GetX());
        points[x+1] = a2de::Math::ToScreenScale(_points[i].GetY());
    }
    return points;
}
void Polygon::ReleaseVerticesArray(int* points) {
    delete[] points;
    points = nullptr;
}
void Polygon::CalculateArea() {
    double area = 0.0;
    //A = 1/2(sum of ((X[i] * Y[i+1]) - (X[i+1] * Y[i])) where i = 0 to n - 1
    if(_points.size() < 3) _area = area;
    for(size_t i = 0; i < _points.size() - 1; ++i) {
        double Xi = _points[i].GetX();
        double Yi = _points[i].GetY();
        double Xi1 = _points[i+1].GetX();
        double Yi1 = _points[i+1].GetY();
        area += ((Xi * Yi1) - (Xi1 * Yi));
    }
    area = (0.5) * area;
    _area = area;
}
void Polygon::CalculateCenter() {
    if(_area == 0.0) {
        this->SetPosition(Vector2D(0.0, 0.0));
        return;
    }
    //Cx = (1/6A)(sum of(X[i] + X[i+1])((X[i] * Y[i+1]) - (X[i+1] * Y[i]))) where A = Area, i = 0 to n - 1
    double Cx = 0.0;
    for(size_t i = 0; i < _points.size() - 1; ++i) {
        double Xi = _points[i].GetX();
        double Yi = _points[i].GetY();
        double Xi1 = _points[i+1].GetX();
        double Yi1 = _points[i+1].GetY();
        Cx += ((Xi + Xi1) * ((Xi * Yi1) - (Xi1 * Yi)));
    }
    double A = _area;
    Cx = ((1.0 / 6.0) * A) * Cx;

    //Cy = (1/6A)(sum of(Y[i] + Y[i+1])((X[i] * Y[i+1]) - (X[i+1] * Y[i]))) where A = Area, i = 0 to n - 1
    double Cy = 0.0;
    for(size_t i = 0; i < _points.size() - 1; ++i) {
        double Xi = _points[i].GetX();
        double Yi = _points[i].GetY();
        double Xi1 = _points[i+1].GetX();
        double Yi1 = _points[i+1].GetY();
        Cy += ((Yi + Yi1) * ((Xi * Yi1) - (Xi1 * Yi)));
    }
    Cy = ((1.0 / 6.0) * A) * Cy;
    this->SetPosition(Vector2D(Cx, Cy));
}

void Polygon::CalculatePoints(double deltaX, double deltaY) {
    for(size_t i = 0; i <_points.size(); ++i) {
        _points[i] = Vector2D(_points[i].GetX() + deltaX, _points[i].GetY() + deltaY);
    }
}

Vector2D Polygon::GetSmallestCoordinates() const {

    double smallestX = DBL_MAX;
    double largestX = DBL_MIN;
    double smallestY = DBL_MAX;
    double largestY = DBL_MIN;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(_points[i].GetX() < smallestX) {
            smallestX = _points[i].GetX();
        }
        if(_points[i].GetX() > largestX) {
            largestX = _points[i].GetX();
        }
        if(_points[i].GetY() < smallestY) {
            smallestY = _points[i].GetY();
        }
        if(_points[i].GetY() > largestY) {
            largestY = _points[i].GetY();
        }
    }
    double x = smallestX;
    double y = smallestY;

    return Vector2D(x, y);
}

Vector2D Polygon::GetSmallestCoordinates() {
    return static_cast<const Polygon&>(*this).GetSmallestCoordinates();
}

Vector2D Polygon::GetLargestCoordinates() const {
    double smallestX = DBL_MAX;
    double largestX = DBL_MIN;
    double smallestY = DBL_MAX;
    double largestY = DBL_MIN;
    for(size_t i = 0; i < _points.size(); ++i) {
        if(_points[i].GetX() < smallestX) {
            smallestX = _points[i].GetX();
        }
        if(_points[i].GetX() > largestX) {
            largestX = _points[i].GetX();
        }
        if(_points[i].GetY() < smallestY) {
            smallestY = _points[i].GetY();
        }
        if(_points[i].GetY() > largestY) {
            largestY = _points[i].GetY();
        }
    }
    double x = largestX;
    double y = largestY;

    return Vector2D(x, y);
}

Vector2D Polygon::GetLargestCoordinates() {
    return static_cast<const Polygon&>(*this).GetLargestCoordinates();
}

Rectangle Polygon::GetBoundingBox() const {
    Vector2D smallest(GetSmallestCoordinates());
    Vector2D largest(GetLargestCoordinates());
    auto p = (largest - smallest) / 2.0;
    Rectangle bb(p, p);
    return bb;
}

void Polygon::SetHalfExtents(const Vector2D& /*dimensions*/) { /* DO NOTHING */ }

Polygon& Polygon::operator=(const Polygon& rhs) {
    if(this == &rhs) return *this;

    Shape::operator=(rhs);
    this->_points = rhs._points;
    CalculateArea();
    CalculateCenter();

    return *this;
}


A2DE_END