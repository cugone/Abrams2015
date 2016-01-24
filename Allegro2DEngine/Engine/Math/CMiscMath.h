/**************************************************************************************************
// file:	Engine\Math\CMiscMath.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the misc mathematics class
 **************************************************************************************************/
#ifndef A2DE_CMATH_H
#define A2DE_CMATH_H

#include "../a2de_vals.h"
#include "MathConstants.h"

#include <cmath>
#include <utility>

A2DE_BEGIN

class Line;
class Vector2D;
class Vector3D;

namespace Math {


/**************************************************************************************************
* <summary>Values that represent LINEINTERSECTIONTYPE. </summary>
* <remarks>Casey Ugone, 9/3/2012.</remarks>
**************************************************************************************************/
enum class LINEINTERSECTIONTYPE : int {
    PARALLEL = -1,
    NONE = 0,
    ONE = 1,
    COLINEAR = 2,
};

struct PolarCoordinate {
    double mag;
    double angle;

};

struct CartesianCoordinate {
    double x;
    double y;
};

    /**************************************************************************************************
     * <summary>Converts Degrees to Radians.</summary>
     * <remarks>Casey Ugone, 2/10/2012.</remarks>
     * <param name="degree">The degree value to convert.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    double DegreeToRadian(double degree);

    /**************************************************************************************************
     * <summary>Converts Radians to Degrees.</summary>
     * <remarks>Casey Ugone, 7/8/2012.</remarks>
     * <param name="radian">The radian value to convert.</param>
     * <returns>A double describing the value of the radian input in degrees.</returns>
     **************************************************************************************************/
    double RadianToDegree(double radian);

    /**************************************************************************************************
     * <summary>Converts a Cartesian coordinate to a Polar coordinate.</summary>
     * <remarks>Casey Ugone, 7/13/2012.</remarks>
     * <param name="value">The coordinate.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    PolarCoordinate CartesianToPolar(const CartesianCoordinate& coordinate);

    /**************************************************************************************************
     * <summary>Converts a Polar coordinate to a Cartesian coordinate.</summary>
     * <remarks>Casey Ugone, 7/13/2012.</remarks>
     * <param name="coordinate">The coordinate.</param>
     * <returns>.</returns>
     **************************************************************************************************/
    CartesianCoordinate PolarToCartesian(const PolarCoordinate& coordinate);

    /**************************************************************************************************
     * <summary>Query if 'a' is equal to 'b'.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="a">The first double.</param>
     * <param name="b">The second double.</param>
     * <returns>true if equal, false if not.</returns>
     **************************************************************************************************/
    bool IsEqual(double a, double b);

    /**************************************************************************************************
     * <summary>Sets the world scale.</summary>
     * <remarks>Casey Ugone, 5/2/2013.</remarks>
     * <param name="scale">The scale.</param>
     **************************************************************************************************/
    void SetWorldScale(double scale);

    /**************************************************************************************************
     * <summary>Sets spline buffer size.</summary>
     * <remarks>Casey Ugone, 11/4/2015.</remarks>
     * <param name="size">The size.</param>
     **************************************************************************************************/
    void SetSplineBufferSize(std::size_t size);

    /**************************************************************************************************
     * <summary>Gets spline buffer size.</summary>
     * <remarks>Casey Ugone, 11/4/2015.</remarks>
     * <returns>The spline buffer size.</returns>
     **************************************************************************************************/
    std::size_t GetSplineBufferSize();

    /**************************************************************************************************
     * <summary>Converts a pixel to a world scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="pixel">The pixel.</param>
     * <returns>This object as a double.</returns>
     **************************************************************************************************/
    double ToWorldScale(double pixel);

    /**************************************************************************************************
     * <summary>Converts a meter to a screen scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="meter">The meter.</param>
     * <returns>This object as a double.</returns>
     **************************************************************************************************/
    double ToScreenScale(double meter);

    /**************************************************************************************************
     * <summary>Converts the meters to a screen scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="meters">The meters.</param>
     * <returns>This object as an a2de::Vector2D.</returns>
     **************************************************************************************************/
    a2de::Vector2D ToScreenScale(const a2de::Vector2D& meters);

    /**************************************************************************************************
     * <summary>Converts the pixels to a world scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="pixels">The pixels.</param>
     * <returns>This object as an a2de::Vector2D.</returns>
     **************************************************************************************************/
    a2de::Vector2D ToWorldScale(const a2de::Vector2D& pixels);

    /**************************************************************************************************
     * <summary>Converts the meters to a screen scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="meters">The meters.</param>
     * <returns>This object as an a2de::Vector3D.</returns>
     **************************************************************************************************/
    a2de::Vector3D ToScreenScale(const a2de::Vector3D& meters);

    /**************************************************************************************************
     * <summary>Converts the pixels to a world scale.</summary>
     * <remarks>Casey Ugone, 5/6/2013.</remarks>
     * <param name="pixels">The pixels.</param>
     * <returns>This object as an a2de::Vector3D.</returns>
     **************************************************************************************************/
    a2de::Vector3D ToWorldScale(const a2de::Vector3D& pixels);


    /**************************************************************************************************
    * <summary>Query if one line intersects another and determines at what point.</summary>
    * <remarks>Casey Ugone, 11/2/2015.</remarks>
    * <remarks>The first element of the pair is the type of intersection, the second where.</remarks>
    * <remarks>If the first element is not LINEINTERSECTIONTYPE::ONE, the second has no meaning and should not be used.</remarks>
    * <param name="line">The line.</param>
    * <returns>A std::pair&lt;Line::LINEINTERSECTIONTYPE,Vector2D&gt;</returns>
    **************************************************************************************************/
    std::pair<Math::LINEINTERSECTIONTYPE, Vector2D> IntersectsAt(const Line& lineA, const Line& lineB);

    /**************************************************************************************************
    * <summary>Gets the distance between two points.</summary>
    * <remarks>Casey Ugone, 10/25/2014.</remarks>
    * <param name="one">The first point.</param>
    * <param name="two">The second point.</param>
    * <returns>The distance.</returns>
    **************************************************************************************************/
    double GetDistance(const Vector2D& one, const Vector2D& two);

    /**************************************************************************************************
    * <summary>Gets distance squared between two points.</summary>
    * <remarks>Casey Ugone, 10/25/2014.</remarks>
    * <param name="one">The first point.</param>
    * <param name="two">The second point.</param>
    * <returns>The distance squared.</returns>
    **************************************************************************************************/
    double GetDistanceSquared(const Vector2D& one, const Vector2D& two);

    /**************************************************************************************************
     * <summary>Gets the distance between a point and a line.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="p">  The single point.</param>
     * <param name="one">The first point of the line.</param>
     * <param name="two">The second point of the line.</param>
     * <returns>The distance.</returns>
     **************************************************************************************************/
    double GetDistance(const Vector2D& p, const Vector2D& one, const Vector2D& two);

    /**************************************************************************************************
     * <summary>Gets distance squared between two points.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="p">  The single point.</param>
     * <param name="one">The first point of the line.</param>
     * <param name="two">The second point of the line.</param>
     * <returns>The distance squared.</returns>
     **************************************************************************************************/
    double GetDistanceSquared(const Vector2D& p, const Vector2D& one, const Vector2D& two);

}

A2DE_END

#endif