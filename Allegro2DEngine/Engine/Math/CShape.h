/**************************************************************************************************
// file:	Engine\Math\CShape.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the shape class
 **************************************************************************************************/
#ifndef A2DE_CSHAPE_H
#define A2DE_CSHAPE_H

#include "../a2de_vals.h"

#include "CVertex.h"
#include "CVector2D.h"
#include "CTransform2D.h"

#include <string>
#include <tuple>
#include <utility>

A2DE_BEGIN

class Point;
class Line;
class Rectangle;
class Circle;
class Ellipse;
class Triangle;
class Arc;
class Polygon;
class Spline;
class Sector;

class Shape {

public:
    enum class ShapeType : int {
        None = -1,
        Point,
        Line,
        Rectangle,
        Circle,
        Ellipse,
        Triangle,
        Arc,
        Polygon,
        Spline,
        Sector,
        max,
    };

    /**************************************************************************************************
     * <summary>Gets the verticies.</summary>
     * <remarks>Casey Ugone, 11/4/2015.</remarks>
     * <returns>The verticies.</returns>
     **************************************************************************************************/
    const std::vector<Vertex>& GetVerticies() const;

    /**************************************************************************************************
     * <summary>Gets the verticies.</summary>
     * <remarks>Casey Ugone, 11/4/2015.</remarks>
     * <returns>The verticies.</returns>
     **************************************************************************************************/
    std::vector<Vertex>& GetVerticies();

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    const Vector2D& GetPosition() const;

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector2D& GetPosition();

    /**************************************************************************************************
     * <summary>Gets the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The area.</returns>
     **************************************************************************************************/
    double GetArea() const;

    /**************************************************************************************************
     * <summary>Gets the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The area.</returns>
     **************************************************************************************************/
    double GetArea();
    
    /**************************************************************************************************
     * <summary>Gets the dimensions.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The dimensions.</returns>
     **************************************************************************************************/
    const Vector2D& GetHalfExtents() const;

    /**************************************************************************************************
     * <summary>Gets the dimensions.</summary>
     * <remarks>Casey Ugone, 5/3/2013.</remarks>
     * <returns>The dimensions.</returns>
     **************************************************************************************************/
    Vector2D& GetHalfExtents();
    
    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position)=0;

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The dimensions.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& half_extents)=0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const a2de::Vector2D& position) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Shape& shape) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Point& point) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given line.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Line& line) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Rectangle& rectangle) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Circle& circle) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Ellipse& ellipse) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Triangle& triangle) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given arc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Arc& arc) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given polygon.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Polygon& polygon) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given spline.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Spline& spline) const =0;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given sector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="sector">The sector.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Sector& sector) const =0;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Shape& shape) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Point& point) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given line.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Line& line) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Rectangle& rectangle) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Circle& circle) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Ellipse& ellipse) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Triangle& triangle) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given arc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Arc& arc) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given polygon.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Polygon& polygon) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given spline.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Spline& spline) const;

    /**************************************************************************************************
     * <summary>Query if this object fully contains the given sector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="sector">The sector.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Contains(const Sector& sector) const;
    
    /**************************************************************************************************
     * <summary>Gets the shape type.</summary>
     * <remarks>Casey Ugone, 3/28/2013.</remarks>
     * <returns>The shape type.</returns>
     **************************************************************************************************/
    virtual const Shape::ShapeType& GetShapeType() const;

    /**************************************************************************************************
     * <summary>Gets the shape type.</summary>
     * <remarks>Casey Ugone, 3/28/2013.</remarks>
     * <returns>The shape type.</returns>
     **************************************************************************************************/
    virtual Shape::ShapeType& GetShapeType();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">  The position.</param>
     * <param name="dimensions">The dimensions.</param>
     * <param name="color">     The color.</param>
     * <param name="filled">    true to filled.</param>
     **************************************************************************************************/
    Shape(const Vector2D& position = Vector2D(), const Vector2D& half_extents = Vector2D());

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     **************************************************************************************************/
    Shape(const Shape& shape);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Shape& operator=(const Shape& rhs);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Shape();

protected:

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea()=0;

    /**************************************************************************************************
     * <summary>Calculates the vertices.</summary>
     * <remarks>Casey Ugone, 11/15/2015.</remarks>
     **************************************************************************************************/
    virtual void CalculateVerts();

    /// <summary>The transform.</summary>
    Transform2D _transform;
    /// <summary> The dimensions </summary>
    Vector2D _half_extents;
    /// <summary> The area </summary>
    double _area;
    /// <summary> The shape type </summary>
    Shape::ShapeType _type;
    /// <summary> The verticies describing the shape </summary>
    std::vector<Vertex> _verts;

};

A2DE_END

#endif