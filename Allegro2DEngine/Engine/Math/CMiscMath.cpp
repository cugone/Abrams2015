/**************************************************************************************************
// file:	Engine\Math\CMiscMath.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the misc mathematics class
 **************************************************************************************************/
#include "CMiscMath.h"

#include "CLine.h"
#include "CVector2D.h"
#include "CVector3D.h"

A2DE_BEGIN

namespace Math {

    namespace {
        /// <summary> The meter to pixel scale ratio </summary>
        double WORLD_SCALE = 0.01;
        unsigned int SPLINE_BUFFER_SIZE = 100;
    }

double a2de::Math::DegreeToRadian(double degree) {
    return degree * A2DE_RADIAN;
}

double RadianToDegree(double radian) {
    return radian * A2DE_DEGREE;
}

PolarCoordinate CartesianToPolar(const CartesianCoordinate& coordinate) {
    PolarCoordinate polar;
    polar.mag = std::sqrt((coordinate.x * coordinate.x) + (coordinate.y * coordinate.y));
    polar.angle = std::atan2(coordinate.y, coordinate.x);
    return polar;
}

CartesianCoordinate PolarToCartesian(const PolarCoordinate& coordinate) {
    CartesianCoordinate cartesian;
    cartesian.x = coordinate.mag * std::cos(coordinate.angle);
    cartesian.y = coordinate.mag * std::sin(coordinate.angle);
    return cartesian;
}

bool IsEqual(double a, double b) {
    double ZERO_EPSILON = 0.0001;
    return std::fabs(a - b) < ZERO_EPSILON;
}

void SetWorldScale(double scale) {
    WORLD_SCALE = scale;
}

void SetSplineBufferSize(std::size_t size) {
    SPLINE_BUFFER_SIZE = size;
}

std::size_t GetSplineBufferSize() {
    return SPLINE_BUFFER_SIZE;
}

double ToWorldScale(double pixel) {
    return pixel * WORLD_SCALE;
}

double ToScreenScale(double meter) {
    return meter / WORLD_SCALE;
}

a2de::Vector2D ToWorldScale(const a2de::Vector2D& pixel) {
    return pixel * WORLD_SCALE;
}

a2de::Vector2D ToScreenScale(const a2de::Vector2D& meter) {
    return meter / WORLD_SCALE;
}

a2de::Vector3D ToWorldScale(const a2de::Vector3D& pixel) {
    return pixel * WORLD_SCALE;
}

a2de::Vector3D ToScreenScale(const a2de::Vector3D& meter) {
    return meter / WORLD_SCALE;
}


std::pair<Math::LINEINTERSECTIONTYPE, Vector2D> IntersectsAt(const Line& lineA, const Line& lineB) {
    //Points to the same lineB.
    if(lineA == lineB) {
        return std::make_pair(Math::LINEINTERSECTIONTYPE::COLINEAR, Vector2D());
    }

    auto lineAp1 = lineA.GetPointOne();
    auto lineAp2 = lineA.GetPointTwo();
    auto lineBp1 = lineB.GetPointOne();
    auto lineBp2 = lineB.GetPointTwo();

    Math::LINEINTERSECTIONTYPE result = Math::LINEINTERSECTIONTYPE::NONE;
    double ua_t = (lineBp2.GetX() - lineBp1.GetX()) * (lineAp1.GetY() - lineBp1.GetY()) - (lineBp2.GetY() - lineBp1.GetY()) * (lineAp1.GetX() - lineBp1.GetX());

    double ub_t = (lineAp2.GetX() - lineAp1.GetX()) *
        (lineAp1.GetY() - lineBp1.GetY()) -
        (lineAp2.GetY() - lineAp1.GetY()) *
        (lineAp1.GetX() - lineBp1.GetX());

    double u_b = (lineBp2.GetY() - lineBp1.GetY()) * (lineAp2.GetX() - lineAp1.GetX()) - (lineBp2.GetX() - lineBp1.GetX()) * (lineAp2.GetY() - lineAp1.GetY());

    if(u_b != 0.0) {
        double ua = ua_t / u_b;
        double ub = ub_t / u_b;

        if(0.0 <= ua && ua <= 1.0 && 0.0 <= ub && ub <= 1.0) {
            Vector2D at(lineAp1.GetX() + ua * (lineAp2.GetX() - lineAp1.GetX()),
                        lineAp1.GetY() + ua * (lineAp2.GetY() - lineAp1.GetY()));
            return std::make_pair(Math::LINEINTERSECTIONTYPE::ONE, at);
        } else {
            return std::make_pair(Math::LINEINTERSECTIONTYPE::NONE, Vector2D());
        }
    } else {
        if(ua_t == 0.0 || ub_t == 0.0) {
            return std::make_pair(Math::LINEINTERSECTIONTYPE::COLINEAR, Vector2D());
        } else {
            return std::make_pair(Math::LINEINTERSECTIONTYPE::PARALLEL, Vector2D());
        }
    }

    return std::make_pair(result, Vector2D());

}

double GetDistance(const Vector2D& one, const Vector2D& two) {
    return std::sqrt(GetDistanceSquared(one, two));
}

double GetDistanceSquared(const Vector2D& one, const Vector2D& two) {
    return (two - one).GetLengthSquared();
}

double GetDistance(const Vector2D& p, const Vector2D& one, const Vector2D& two) {
    return std::sqrt(GetDistanceSquared(p, one, two));
}

double GetDistanceSquared(const Vector2D& p, const Vector2D& one, const Vector2D& two) {

    //Taken from http://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Vector_formulation
    //(a - p) - (dot((a - p), n)n)

    Vector2D a = one;
    Vector2D n = (two - one).Normalize();

    double distance = ((a - p) - (a2de::Vector2D::DotProduct((a - p), n)) * n).GetLengthSquared();
    return distance;

}

} //End namespace Math

A2DE_END