/**************************************************************************************************
// file:	Engine\GFX\CRenderManager.h
// A2DE
// Copyright (c) 2014 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the Render Manager class.
 **************************************************************************************************/
#ifndef A2DE_CRENDERMANAGER_H
#define A2DE_CRENDERMANAGER_H

#include "../a2de_vals.h"

#include "../Math/CVector2D.h"

#include <allegro5/display.h>

A2DE_BEGIN

class Entity;
class Sprite;
class Shape;
class IBoundingBox;
class IRenderable;

//TODO: Uncomment RenderManager functions after testing window.
/**************************************************************************************************
 * <summary>Class for managing the render operations of objects.</summary>
 * <remarks>Casey Ugone, 10/25/2014.</remarks>
 **************************************************************************************************/
class RenderManager {
public:


    /**************************************************************************************************
    * <summary>Constructor.</summary>
    * <remarks>Casey Ugone, 10/25/2014.</remarks>
    * <param name="display">[in,out] The display.</param>
    **************************************************************************************************/
    RenderManager(ALLEGRO_DISPLAY& display);

    ~RenderManager();

//    /**************************************************************************************************
//     * <summary>Renders the object described by object.</summary>
//     * <remarks>Casey Ugone, 10/25/2014.</remarks>
//     * <param name="object">[in,out] If non-null, the object.</param>
//     **************************************************************************************************/
//    void RenderObject(Entity* object);

    /**************************************************************************************************
     * <summary>Renders the object described by sprite.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="sprite">[in,out] If non-null, the sprite.</param>
     **************************************************************************************************/
    void RenderObject(const Sprite& sprite);

    /**************************************************************************************************
     * <summary>Renders the object described by shape.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="shape"> The shape.</param>
     * <param name="filled">true if filled.</param>
     **************************************************************************************************/
    void RenderObject(const Shape& shape, bool filled = false, ALLEGRO_BITMAP* texture = nullptr);
//
//    /**************************************************************************************************
//     * <summary>Renders the object described by bounding_box.</summary>
//     * <remarks>Casey Ugone, 10/25/2014.</remarks>
//     * <param name="bounding_box">[in,out] If non-null, the bounding box.</param>
//     **************************************************************************************************/
//    void RenderObject(IBoundingBox* bounding_box);

    /**************************************************************************************************
     * <summary>Renders the object described by drawable.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="renderable">[in,out] If non-null, the renderable object.</param>
     **************************************************************************************************/
    void RenderObject(IRenderable& renderable);
//
//    /**************************************************************************************************
//     * <summary>Renders the object at the specified location.</summary>
//     * <remarks>Casey Ugone, 10/25/2014.</remarks>
//     * <param name="object">         [in,out] If non-null, the object.</param>
//     * <param name="screen_position">The screen position.</param>
//     **************************************************************************************************/
//    void RenderObjectAt(Entity* object, const a2de::Vector2D& screen_position);

    /**************************************************************************************************
     * <summary>Renders the sprite at the specified location.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="sprite">         [in,out] If non-null, the sprite.</param>
     * <param name="screen_position">The screen position.</param>
     **************************************************************************************************/
    void RenderObjectAt(Sprite& sprite, const a2de::Vector2D& screen_position);

    /**************************************************************************************************
     * <summary>Renders the shpae at the specified location.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="shape">          [in,out] If non-null, the shape.</param>
     * <param name="screen_position">The screen position.</param>
     * <param name="filled">         true if filled.</param>
     **************************************************************************************************/
    void RenderObjectAt(Shape& shape, const a2de::Vector2D& screen_position, bool filled = false);

//    /**************************************************************************************************
//     * <summary>Renders the bounding box at the specified location.</summary>
//     * <remarks>Casey Ugone, 10/25/2014.</remarks>
//     * <param name="bounding_box">   [in,out] If non-null, the bounding box.</param>
//     * <param name="screen_position">The screen position.</param>
//     **************************************************************************************************/
//    void RenderObjectAt(IBoundingBox* bounding_box, const a2de::Vector2D& screen_position);
//
protected:

private:

    /**************************************************************************************************
     * <summary>The display to draw to.</summary>
     **************************************************************************************************/
    ALLEGRO_DISPLAY* _display_context;
};

A2DE_END

#endif
