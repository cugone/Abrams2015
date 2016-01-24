/**************************************************************************************************
// file:	Engine\Math\CSector.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the sector class
 **************************************************************************************************/
#ifndef A2DE_CSECTOR_H
#define A2DE_CSECTOR_H

#include "../a2de_vals.h"
#include "CArc.h"

struct ALLEGRO_BITMAP;

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
class Vector2D;

class Sector : public Shape {

public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">  The position.</param>
     * <param name="startAngle">The start angle.</param>
     * <param name="endAngle">  The end angle.</param>
     * <param name="radius">    The radius.</param>
     * <param name="color">     The color.</param>
     * <param name="filled">    true to filled.</param>
     **************************************************************************************************/
    Sector(const Vector2D& position, double startAngle, double endAngle, double radius);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="sector">The sector.</param>
     **************************************************************************************************/
    Sector(const Sector& sector);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Sector();

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
     * <summary>Gets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The radius.</returns>
     **************************************************************************************************/
    double GetRadius() const;

    /**************************************************************************************************
     * <summary>Gets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The radius.</returns>
     **************************************************************************************************/
    double GetRadius();
    
    /**************************************************************************************************
     * <summary>Gets the theta.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The theta.</returns>
     **************************************************************************************************/
    double GetTheta() const;

    /**************************************************************************************************
     * <summary>Gets the theta.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The theta.</returns>
     **************************************************************************************************/
    double GetTheta();

    /**************************************************************************************************
     * <summary>Sets the radius.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="radius">The radius.</param>
     **************************************************************************************************/
    void SetRadius(double radius);

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position) override;
    
    /**************************************************************************************************
     * <summary>Gets the start angle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The start angle.</returns>
     **************************************************************************************************/
    double GetStartAngle() const;

    /**************************************************************************************************
     * <summary>Gets the start angle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The start angle.</returns>
     **************************************************************************************************/
    double GetStartAngle();
    
    /**************************************************************************************************
     * <summary>Gets the end angle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The end angle.</returns>
     **************************************************************************************************/
    double GetEndAngle() const;

    /**************************************************************************************************
     * <summary>Gets the end angle.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The end angle.</returns>
     **************************************************************************************************/
    double GetEndAngle();

    /**************************************************************************************************
     * <summary>Gets the start point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The start point.</returns>
     **************************************************************************************************/
    Vector2D GetStartPoint() const;

    /**************************************************************************************************
     * <summary>Gets the end point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The end point.</returns>
     **************************************************************************************************/
    Vector2D GetEndPoint() const;

    /**************************************************************************************************
     * <summary>Gets the center point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The center point.</returns>
     **************************************************************************************************/
    Vector2D GetCenterPoint() const;

    /**************************************************************************************************
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) override;

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
     * <summary>Query if this object intersects the given position.</summary>
     * <remarks>Casey Ugone, 8/23/2013.</remarks>
     * <param name="position">The position.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool Intersects(const Vector2D& position) const override;

    /**************************************************************************************************
     * <summary>Gets the arc center point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The arc center point.</returns>
     **************************************************************************************************/
    Vector2D GetArcCenterPoint() const;

    /**************************************************************************************************
     * <summary>Gets the arc center point.</summary>
     * <remarks>Casey Ugone, 11/4/2015.</remarks>
     * <returns>The arc center point.</returns>
     **************************************************************************************************/
    Vector2D GetArcCenterPoint();

    /**************************************************************************************************
     * <summary>Sets the angles degrees.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="startAngle">The start angle.</param>
     * <param name="endAngle">  The end angle.</param>
     **************************************************************************************************/
    void SetAnglesDegrees(double startAngle, double endAngle);

    /**************************************************************************************************
     * <summary>Sets the angles.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="startAngle">The start angle.</param>
     * <param name="endAngle">  The end angle.</param>
     **************************************************************************************************/
    void SetAngles(double startAngle, double endAngle);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    Sector& operator=(const Sector& rhs);

protected:

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The dimensions.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& half_extents) override;

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;


private:
    /// <summary> The arc </summary>
    Arc _arc;

};

A2DE_END

#endif