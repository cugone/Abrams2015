/**************************************************************************************************
// file:	Engine\Math\CPolygon.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the polygon class
 **************************************************************************************************/
#ifndef A2DE_CPOLYGON_H
#define A2DE_CPOLYGON_H

#include "../a2de_vals.h"
#include "CShape.h"
#include "CPoint.h"
#include "CRectangle.h"

#include <vector>

struct ALLEGRO_BITMAP;

A2DE_BEGIN

class Line;
class Circle;
class Ellipse;
class Triangle;
class Arc;
class Spline;
class Sector;

class Polygon : public Shape {

public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="points">The points.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    Polygon(const std::vector<Vector2D>& points);

    /**************************************************************************************************
     * <summary>Copy constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="polygon">The polygon.</param>
     **************************************************************************************************/
    Polygon(const Polygon& polygon);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Polygon();

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
     * <summary>Draws.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dest">  [in,out] If non-null, destination for the.</param>
     * <param name="color"> The color.</param>
     * <param name="filled">true to filled.</param>
     **************************************************************************************************/
    //virtual void Render(ALLEGRO_BITMAP* dest, const ALLEGRO_COLOR& color, bool filled) override;

    /**************************************************************************************************
     * <summary>Gets a smallest coordinates.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">[in,out] The x coordinate.</param>
     * <param name="y">[in,out] The y coordinate.</param>
     **************************************************************************************************/
    Vector2D GetSmallestCoordinates() const;

    /**************************************************************************************************
     * <summary>Gets a smallest coordinates.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">[in,out] The x coordinate.</param>
     * <param name="y">[in,out] The y coordinate.</param>
     **************************************************************************************************/
    Vector2D GetSmallestCoordinates();

    /**************************************************************************************************
     * <summary>Gets a largest coordinates.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">[in,out] The x coordinate.</param>
     * <param name="y">[in,out] The y coordinate.</param>
     **************************************************************************************************/
    Vector2D GetLargestCoordinates() const;

    /**************************************************************************************************
     * <summary>Gets a largest coordinates.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="x">[in,out] The x coordinate.</param>
     * <param name="y">[in,out] The y coordinate.</param>
     **************************************************************************************************/
    Vector2D GetLargestCoordinates();

    /**************************************************************************************************
     * <summary>Gets the number sides.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The number sides.</returns>
     **************************************************************************************************/
    auto GetNumSides() const;

    /**************************************************************************************************
     * <summary>Gets the number sides.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The number sides.</returns>
     **************************************************************************************************/
    auto GetNumSides();

    /**************************************************************************************************
     * <summary>Gets the number vertices.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The number vertices.</returns>
     **************************************************************************************************/
    auto GetNumVertices() const;

    /**************************************************************************************************
     * <summary>Gets the number vertices.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The number vertices.</returns>
     **************************************************************************************************/
    auto GetNumVertices();

    /**************************************************************************************************
     * <summary>Gets the vertices.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The vertices.</returns>
     **************************************************************************************************/
    const auto& GetVertices() const;

    /**************************************************************************************************
     * <summary>Gets the vertices.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The vertices.</returns>
     **************************************************************************************************/
    auto& GetVertices();

    /**************************************************************************************************
     * <summary>Creates the vertices array.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>null if it fails, else.</returns>
     **************************************************************************************************/
    int* CreateVerticesArray();

    /**************************************************************************************************
     * <summary>Releases the vertices array described by points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="points">[in,out] If non-null, the points.</param>
     **************************************************************************************************/
    void ReleaseVerticesArray(int* points);

    /**************************************************************************************************
     * <summary>Gets the sides.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The sides.</returns>
     **************************************************************************************************/
    auto GetSides() const;

    /**************************************************************************************************
     * <summary>Gets the sides.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The sides.</returns>
     **************************************************************************************************/
    auto GetSides();

    /**************************************************************************************************
     * <summary>Sets a vertex position.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="vertexNum">The vertex number.</param>
     * <param name="x">        The x coordinate.</param>
     * <param name="y">        The y coordinate.</param>
     **************************************************************************************************/
    void SetVertexPosition(std::size_t vertexNum, double x, double y);

    /**************************************************************************************************
     * <summary>Assignment operator.</summary>
     * <remarks>Casey Ugone, 5/8/2013.</remarks>
     * <param name="rhs">The right hand side.</param>
     * <returns>A deep copy of this object.</returns>
     **************************************************************************************************/
    Polygon& operator=(const Polygon& rhs);

protected:

    /**************************************************************************************************
     * <summary>Calculates the area.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual void CalculateArea() override;

    /**************************************************************************************************
     * <summary>Calculates the center.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    void CalculateCenter();

    /**************************************************************************************************
     * <summary>Calculates the points.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="deltaX">The delta x coordinate.</param>
     * <param name="deltaY">The delta y coordinate.</param>
     **************************************************************************************************/
    void CalculatePoints(double deltaX, double deltaY);

    /**************************************************************************************************
     * <summary>Gets the bounding box.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <returns>The bounding box.</returns>
     **************************************************************************************************/
    Rectangle GetBoundingBox() const;

    /// <summary> The points </summary>
    std::vector<Vector2D> _points;

private:

    /**************************************************************************************************
     * <summary>Sets the dimensions.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="dimensions">The half extents.</param>
     **************************************************************************************************/
    virtual void SetHalfExtents(const Vector2D& dimensions) override;

};

A2DE_END

#endif