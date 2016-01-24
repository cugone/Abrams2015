/**************************************************************************************************
// file:	Engine\Math\CLine.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the line class
 **************************************************************************************************/
#ifndef A2DE_CLINE_H
#define A2DE_CLINE_H

#include <tuple>
#include <utility>

#include "../a2de_vals.h"
#include "CShape.h"
#include "CPoint.h"
#include "CVector2D.h"

A2DE_BEGIN

class Rectangle;
class Circle;
class Ellipse;
class Triangle;
class Arc;
class Polygon;
class Spline;
class Sector;

class Line : public Shape {

public:
    
    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    Line();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="one">The one.</param>
     * <param name="two">The two.</param>
     **************************************************************************************************/
    Line(const Vector2D& one, const Vector2D& two);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="one">  The one.</param>
     * <param name="two">  The two.</param>
     * <param name="color">The color.</param>
     **************************************************************************************************/
    //Line(const Vector2D& one, const Vector2D& two, const ALLEGRO_COLOR& color);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     **************************************************************************************************/
    Line(const Line& line);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Line();

    /**************************************************************************************************
     * <summary>Gets the point one.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point one.</returns>
     **************************************************************************************************/
    Vector2D GetPointOne() const;

    /**************************************************************************************************
     * <summary>Gets the point one.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point one.</returns>
     **************************************************************************************************/
    Vector2D GetPointOne();

    /**************************************************************************************************
     * <summary>Gets the point two.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point two.</returns>
     **************************************************************************************************/
    Vector2D GetPointTwo() const;

    /**************************************************************************************************
     * <summary>Gets the point two.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The point two.</returns>
     **************************************************************************************************/
    Vector2D GetPointTwo();


    /**************************************************************************************************
     * <summary>Gets the length.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length.</returns>
     **************************************************************************************************/
    double GetLength() const;

    /**************************************************************************************************
     * <summary>Gets the length.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The length.</returns>
     **************************************************************************************************/
    double GetLength();

    /**************************************************************************************************
     * <summary>Gets length squared.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The length squared.</returns>
     **************************************************************************************************/
    double GetLengthSquared() const;

    /**************************************************************************************************
     * <summary>Gets length squared.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The length squared.</returns>
     **************************************************************************************************/
    double GetLengthSquared();
    
    /**************************************************************************************************
     * <summary>Gets the slope.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The slope.</returns>
     **************************************************************************************************/
    const Vector2D& GetSlope() const;

    /**************************************************************************************************
     * <summary>Gets the slope.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The slope.</returns>
     **************************************************************************************************/
    Vector2D& GetSlope();
    
    /**************************************************************************************************
     * <summary>Gets the perpendicular slope.</summary>
     * <remarks>Casey Ugone, 9/15/2012.</remarks>
     * <returns>The perpendicular slope.</returns>
     **************************************************************************************************/
    Vector2D GetPerpendicularSlope() const;

    /**************************************************************************************************
     * <summary>Gets the perpendicular slope.</summary>
     * <remarks>Casey Ugone, 9/15/2012.</remarks>
     * <returns>The perpendicular slope.</returns>
     **************************************************************************************************/
    Vector2D GetPerpendicularSlope();

    /**************************************************************************************************
     * <summary>Gets the normal.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The normal.</returns>
     **************************************************************************************************/
    Vector2D GetNormal() const;

    /**************************************************************************************************
     * <summary>Gets the normal.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The normal.</returns>
     **************************************************************************************************/
    Vector2D GetNormal();

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Line& operator=(const Line& rhs);

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     **************************************************************************************************/
    bool operator!=(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than the second.</returns>
     **************************************************************************************************/
    bool operator<(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than to the second.</returns>
     **************************************************************************************************/
    bool operator>(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Less-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is less than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator<=(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Greater-than-or-equal comparison operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the first parameter is greater than or equal to the second.</returns>
     **************************************************************************************************/
    bool operator>=(const Line& rhs) const;

    /**************************************************************************************************
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled);
    
    /**************************************************************************************************
     * <summary>Query if this object is vertical.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if vertical, false if not.</returns>
     **************************************************************************************************/
    bool IsVertical() const;

    /**************************************************************************************************
     * <summary>Query if this object is horizontal.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if horizontal, false if not.</returns>
     **************************************************************************************************/
    bool IsHorizontal() const;
    
    /**************************************************************************************************
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Vector2D& position) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given shape.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="shape">The shape.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Shape& shape) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="point">The point.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Point& point) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given line.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Line& line) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Rectangle& rectangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Circle& circle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Ellipse& ellipse) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Triangle& triangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given arc.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="arc">The arc.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Arc& arc) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given polygon.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Polygon& polygon) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given spline.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="spline">The spline.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Spline& spline) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given sector.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
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
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position) override;

protected:

    /// <summary> The slope </summary>
    Vector2D _slope;
    /// <summary> The length </summary>
    double _length_squared;

private:

    /**************************************************************************************************
     * <summary>Calculates the slope.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateSlope();
        
    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;
    
    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The half_extents.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& half_extents) override;

};

A2DE_END

#endif