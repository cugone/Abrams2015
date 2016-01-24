/**************************************************************************************************
// file:	Engine\Math\CSpline.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the spline class
 **************************************************************************************************/
#ifndef A2DE_CSPLINE_H
#define A2DE_CSPLINE_H

#include "../a2de_vals.h"
#include "CShape.h"
#include "CPoint.h"

#include <vector>

A2DE_BEGIN

class Line;
class Rectangle;
class Circle;
class Ellipse;
class Triangle;
class Arc;
class Polygon;
class Sector;

class Spline : public Shape {
public:

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    Spline();

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="controlPoints">The control points.</param>
     * <param name="color">        The color.</param>
     **************************************************************************************************/
    Spline(const std::vector<Vector2D>& controlPoints);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="other">The other.</param>
     **************************************************************************************************/
    Spline(const Spline& other);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Spline();

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
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) override;

    /**************************************************************************************************
     * <summary>Gets the control point one.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point one.</returns>
     **************************************************************************************************/
    const Vector2D& GetControlPointOne() const;

    /**************************************************************************************************
     * <summary>Gets the control point one.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point one.</returns>
     **************************************************************************************************/
    Vector2D& GetControlPointOne();
    
    /**************************************************************************************************
     * <summary>Gets the control point two.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point two.</returns>
     **************************************************************************************************/
    const Vector2D& GetControlPointTwo() const;

    /**************************************************************************************************
     * <summary>Gets the control point two.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point two.</returns>
     **************************************************************************************************/
    Vector2D& GetControlPointTwo();
    
    /**************************************************************************************************
     * <summary>Gets the control point three.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point three.</returns>
     **************************************************************************************************/
    const Vector2D& GetControlPointThree() const;

    /**************************************************************************************************
     * <summary>Gets the control point three.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point three.</returns>
     **************************************************************************************************/
    Vector2D& GetControlPointThree();
    
    /**************************************************************************************************
     * <summary>Gets the control point four.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point four.</returns>
     **************************************************************************************************/
    const Vector2D& GetControlPointFour() const;

    /**************************************************************************************************
     * <summary>Gets the control point four.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the control point four.</returns>
     **************************************************************************************************/
    Vector2D& GetControlPointFour();
    
    /**************************************************************************************************
     * <summary>Gets the result points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the result points.</returns>
     **************************************************************************************************/
    const std::vector<Vector2D>& GetResultPoints() const;

    /**************************************************************************************************
     * <summary>Gets the result points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else the result points.</returns>
     **************************************************************************************************/
    std::vector<Vector2D>& GetResultPoints();

    /**************************************************************************************************
     * <summary>Adjust control point.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="number">Number of.</param>
     * <param name="value"> The value.</param>
     **************************************************************************************************/
    void AdjustControlPoint(std::size_t number, Vector2D value);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    Spline& operator=(const Spline& rhs);

    /**************************************************************************************************
     * <summary>Equality operator.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>true if the parameters are considered equivalent.</returns>
     **************************************************************************************************/
    bool operator==(const Spline& rhs);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="rhs">The right hand side.</param>
     **************************************************************************************************/
    bool operator!=(const Spline& rhs);

protected:

    /**************************************************************************************************
     * <summary>Calculates the result points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateResultPoints();

    /**************************************************************************************************
     * <summary>Iterate result points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="object">The object.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    template<class T>
    bool IterateResultPoints(const T& object) const;
private:
    /// <summary> The control points </summary>
    std::vector<Vector2D> _control_points;
    /// <summary> The result points </summary>
    std::vector<Vector2D> _result_points;

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;
    
    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector2D GetPosition() const;

    /**************************************************************************************************
     * <summary>Gets the position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The position.</returns>
     **************************************************************************************************/
    Vector2D GetPosition();

    /**************************************************************************************************
     * <summary>Gets the center.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The center.</returns>
     **************************************************************************************************/
    Vector2D GetCenter() const;

    /**************************************************************************************************
     * <summary>Gets the center.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The center.</returns>
     **************************************************************************************************/
    Vector2D GetCenter();

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
     * <summary>Query if this object is filled.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if filled, false if not.</returns>
     **************************************************************************************************/
    bool IsFilled() const;

    /**************************************************************************************************
     * <summary>Query if this object is filled.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>true if filled, false if not.</returns>
     **************************************************************************************************/
    bool IsFilled();

    /**************************************************************************************************
     * <summary>Sets a fill.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    void SetFill(bool filled);
    
    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX() const;

    /**************************************************************************************************
     * <summary>Get x coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The x coordinate.</returns>
     **************************************************************************************************/
    double GetX();
    
    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY() const;
    
    /**************************************************************************************************
     * <summary>Get y coordinate.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The y coordinate.</returns>
     **************************************************************************************************/
    double GetY();
    
    /**************************************************************************************************
     * <summary>Gets the width.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The width.</returns>
     **************************************************************************************************/
    double GetHalfWidth() const;

    /**************************************************************************************************
     * <summary>Gets the width.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The width.</returns>
     **************************************************************************************************/
    double GetHalfWidth();
    
    /**************************************************************************************************
     * <summary>Gets the height.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The height.</returns>
     **************************************************************************************************/
    double GetHalfHeight() const;

    /**************************************************************************************************
     * <summary>Gets the height.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The height.</returns>
     **************************************************************************************************/
    double GetHalfHeight();

    /**************************************************************************************************
     * <summary>Sets a position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="position">The position.</param>
     **************************************************************************************************/
    virtual void SetPosition(const Vector2D& position) override;

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The dimensions.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& dimensions) override;

};

/**************************************************************************************************
 * <summary>Checks intersection among all points.</summary>
 * <remarks>Casey Ugone, 5/8/2013.</remarks>
 * <param name="object">The object.</param>
 * <returns>true if it succeeds, false if it fails.</returns>
 **************************************************************************************************/
template<class T>
bool Spline::IterateResultPoints(const T& object) const {
    std::size_t sz = _result_points.size();
    for(std::size_t i = 0; i < (sz / 2); ++i) {
        if(object.Intersects(_result_points.at(i))) return true;
        if(object.Intersects(_result_points.at(sz - 1 - i))) return true;
    }
    return false;
}

A2DE_END

#endif