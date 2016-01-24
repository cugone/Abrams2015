/**************************************************************************************************
// file:	Engine\Math\CEllipse.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the ellipse class
 **************************************************************************************************/
#ifndef A2DE_CELLIPSE_H
#define A2DE_CELLIPSE_H

#include "../a2de_vals.h"
#include "CShape.h"

#include <tuple>
#include <utility>

#include "CPoint.h"
#include "CVector2D.h"

struct ALLEGRO_BITMAP;

A2DE_BEGIN

class Line;
class Rectangle;
class Circle;
class Triangle;
class Arc;
class Polygon;
class Spline;
class Sector;

class Ellipse : public Shape {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 10/10/2014.</remarks>
     * <param name="center">     The center.</param>
     * <param name="half_width"> Width of the half.</param>
     * <param name="half_height">Height of the half.</param>
     * <param name="color">      The color.</param>
     * <param name="filled">     true if filled.</param>
     **************************************************************************************************/
    Ellipse(const Vector2D& center, const Vector2D& half_extents);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     **************************************************************************************************/
    Ellipse(const Ellipse& ellipse);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Ellipse();
    
    /**************************************************************************************************
     * <summary>Sets the half extents.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="half_extents">The half extents.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& half_extents) override;

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position) override;

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
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination to draw to.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) override;

    /**************************************************************************************************
     * <summary>Gets the focus a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The focus a.</returns>
     **************************************************************************************************/
    const Vector2D& GetFocusA() const;

    /**************************************************************************************************
     * <summary>Gets the focus a.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The focus a.</returns>
     **************************************************************************************************/
    Vector2D& GetFocusA();
    
    /**************************************************************************************************
     * <summary>Gets the focus b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The focus b.</returns>
     **************************************************************************************************/
    const Vector2D& GetFocusB() const;

    /**************************************************************************************************
     * <summary>Gets the focus b.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The focus b.</returns>
     **************************************************************************************************/
    Vector2D& GetFocusB();

    /**************************************************************************************************
     * <summary>Gets the minimum distance required to be tangent to the ellipse.</summary>
     * <remarks>Casey Ugone, 10/10/2014.</remarks>
     * <returns>The minimum distance.</returns>
     **************************************************************************************************/
    double GetMinimumDistance() const;

    /**************************************************************************************************
     * <summary>Gets the minimum distance required to be tangent to the ellipse.</summary>
     * <remarks>Casey Ugone, 10/10/2014.</remarks>
     * <returns>The minimum distance.</returns>
     **************************************************************************************************/
    double GetMinimumDistance();

    /**************************************************************************************************
     * <summary>Query if 'line' is tangent.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if tangent, false if not.</returns>
     **************************************************************************************************/
    bool IsTangent(const Line& line) const;

    /**************************************************************************************************
     * <summary>Query if 'line' is tangent.</summary>
     * <remarks>Casey Ugone, 10/10/2014.</remarks>
     * <param name="line">The line.</param>
     * <returns>true if tangent, false if not.</returns>
     **************************************************************************************************/
    bool IsTangent(const Line& line);
    
    /**************************************************************************************************
     * <summary>Query if this object intersects the given triangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="triangle">The triangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Triangle& triangle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given ellipse.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="ellipse">The ellipse.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Ellipse& ellipse) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given circle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="circle">The circle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Circle& circle) const override;

    /**************************************************************************************************
     * <summary>Query if this object intersects the given rectangle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rectangle">The rectangle.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Rectangle& rectangle) const override;
    
    /**************************************************************************************************
     * <summary>Gets the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The circumference.</returns>
     **************************************************************************************************/
    double GetCircumference() const;

    /**************************************************************************************************
     * <summary>Gets the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The circumference.</returns>
     **************************************************************************************************/
    double GetCircumference();

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A shallow copy of this object.</returns>
     **************************************************************************************************/
    Ellipse& operator=(const Ellipse& rhs);

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Ellipse& rhs);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     **************************************************************************************************/
    bool operator!=(const Ellipse& rhs);

protected:

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;

    /**************************************************************************************************
     * <summary>Calculates the circumference.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateCircumference();

    /**************************************************************************************************
     * <summary>Calculates the foci.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateFoci();
    
    /**************************************************************************************************
     * <summary>Query if this object is vertical.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if vertical, false if not.</returns>
     **************************************************************************************************/
    bool IsVertical() const;

    /**************************************************************************************************
     * <summary>Query if this object is vertical.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if vertical, false if not.</returns>
     **************************************************************************************************/
    bool IsVertical();
    
    /**************************************************************************************************
     * <summary>Query if this object is horizontal.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if horizontal, false if not.</returns>
     **************************************************************************************************/
    bool IsHorizontal() const;

    /**************************************************************************************************
     * <summary>Query if this object is horizontal.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if horizontal, false if not.</returns>
     **************************************************************************************************/
    bool IsHorizontal();
    
    /// <summary> The radii </summary>
    Vector2D _radii;
    /// <summary> The foci </summary>
    Vector2D _focusA;
    Vector2D _focusB;
    /// <summary> The circumference </summary>
    double _circumference;

};

A2DE_END

#endif