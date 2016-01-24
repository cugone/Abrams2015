/**************************************************************************************************
// file:	Engine\Math\CPoint.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the point class
 **************************************************************************************************/
#ifndef A2DE_CPOINT_H
#define A2DE_CPOINT_H

#include "../a2de_vals.h"
#include <tuple>
#include "CShape.h"

A2DE_BEGIN

class Line;
class Rectangle;
class Circle;
class Ellipse;
class Triangle;
class Arc;
class Polygon;
class Spline;
class Sector;
class Vector2D;

/**************************************************************************************************
 * <summary>Represents a point in 2D space.</summary>
 * <remarks>Casey Ugone, 7/15/2012.</remarks>
 * <seealso cref="Shape"/>
 **************************************************************************************************/
class Point : public Shape {

public:

    /**************************************************************************************************
    * <summary>Constructor.</summary>
    * <remarks>Casey Ugone, 7/15/2012.</remarks>
    * <param name="position">The position.</param>
    **************************************************************************************************/
    explicit Point(const Vector2D& position = Vector2D());

    /**************************************************************************************************
    * <summary>Copy constructor.</summary>
    * <remarks>Casey Ugone, 7/15/2012.</remarks>
    * <param name="point">The point.</param>
    **************************************************************************************************/
    Point(const Point& point);

    /**************************************************************************************************
    * <summary>Destructor.</summary>
    * <remarks>Casey Ugone, 7/15/2012.</remarks>
    **************************************************************************************************/
    virtual ~Point();


    /**************************************************************************************************
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Vector2D& position) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given shape.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Shape& shape) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given point.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Point& point) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given line.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Line& line) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given rectangle.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Rectangle& rectangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given circle.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Circle& circle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given ellipse.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Ellipse& ellipse) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given triangle.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Triangle& triangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given arc.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Arc& arc) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given polygon.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Polygon& polygon) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given spline.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Spline& spline) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given sector.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="sector">The sector.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Sector& sector) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Shape& shape) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Point& point) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given line.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Line& line) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Rectangle& rectangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Circle& circle) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Ellipse& ellipse) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Triangle& triangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given arc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Arc& arc) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given polygon.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Polygon& polygon) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given spline.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Spline& spline) const override;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given sector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="sector">The sector.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Sector& sector) const override;

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position) override;

    /**************************************************************************************************
     * <summary>Query if this point is on Line 'line'.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if on line, false if not.</returns>
     **************************************************************************************************/
    bool IsPartOf(const Line& line) const;

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    Point& operator=(const Point& rhs);
    
    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Point& rhs) const;

    /**************************************************************************************************
     * <summary>Inequality operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <returns>true if the parameters are not considered equivalent.</returns>
     **************************************************************************************************/
    bool operator!=(const Point& rhs) const;

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator+(const Point& rhs);

    /**************************************************************************************************
     * <summary>Negation operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator-(const Point& rhs);

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator*(const Point& rhs);

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator/(const Point& rhs);

    /**************************************************************************************************
     * <summary>Addition operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator+(double scalar);

    /**************************************************************************************************
     * <summary>Subtraction operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator-(double scalar);

    /**************************************************************************************************
     * <summary>Multiplication operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator*(double scalar);

    /**************************************************************************************************
     * <summary>Division operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point operator/(double scalar);

    /**************************************************************************************************
     * <summary>Addition assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator+=(const Point& rhs);

    /**************************************************************************************************
     * <summary>Subtraction assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator-=(const Point& rhs);

    /**************************************************************************************************
     * <summary>Multiplication assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator*=(const Point& rhs);

    /**************************************************************************************************
     * <summary>Division assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator/=(const Point& rhs);

    /**************************************************************************************************
     * <summary>Addition assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator+=(double scalar);

    /**************************************************************************************************
     * <summary>Subtraction assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator-=(double scalar);

    /**************************************************************************************************
     * <summary>Multiplication assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator*=(double scalar);

    /**************************************************************************************************
     * <summary>Division assignment operator.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="scalar">The scalar.</param>
     * <returns>The result of the operation.</returns>
     **************************************************************************************************/
    Point& operator/=(double scalar);

    /**************************************************************************************************
     * <summary>Draws a point on the destination bitmap with the color specified. Value of filled is ignored.</summary>
     * <remarks>Casey Ugone, 7/15/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination BITMAP.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">ignored.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) override;

protected:

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The dimensions.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& half_extents) override;

};

A2DE_END

#endif