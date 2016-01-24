/**************************************************************************************************
// file:	Engine\GFX\CAnimatedSprite.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the animated sprite class
 **************************************************************************************************/
#ifndef A2DE_CANIMATEDSPRITE_H
#define A2DE_CANIMATEDSPRITE_H

#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include <allegro5/bitmap.h>

#include "../a2de_vals.h"
#include "CSprite.h"

A2DE_BEGIN

class DefaultAnimationHandler;

/**************************************************************************************************
 * <summary>Animated sprite.</summary>
 * <remarks>Casey Ugone, 8/1/2011.</remarks>
 * <seealso cref="Sprite"/>
 **************************************************************************************************/
class AnimatedSprite : public Sprite {
public:

    /**************************************************************************************************
    * <summary>Constructor.</summary>
    * <remarks>Casey Ugone, 11/22/2011.</remarks>
    * <param name="file">     The file.</param>
    * <param name="frameRate">The frame rate.</param>
    **************************************************************************************************/
    AnimatedSprite(const std::string& file, std::chrono::duration<double> frameRate);

    /**************************************************************************************************
    * <summary>Initializes a new instance of the AnimatedSprite class.</summary>
    * <remarks>Casey Ugone, 8/2/2011.</remarks>
    * <param name="animSprite">The animated sprite.</param>
    **************************************************************************************************/
    AnimatedSprite(const AnimatedSprite& animSprite);

    /**************************************************************************************************
    * <summary>Assignment operator.</summary>
    * <remarks>Casey Ugone, 8/2/2011.</remarks>
    * <param name="rhs">The right hand side.</param>
    * <returns>A deep copy of this object.</returns>
    **************************************************************************************************/
    AnimatedSprite& operator=(const AnimatedSprite& rhs);

    /**************************************************************************************************
     * <summary>Destructor</summary>
     * <remarks>Casey Ugone, 8/1/2011.</remarks>
     **************************************************************************************************/
    virtual ~AnimatedSprite() = default;

    /**************************************************************************************************
     * <summary>Gets the current frame.</summary>
     * <remarks>Casey Ugone, 8/1/2011.</remarks>
     * <returns>null if it fails, else the current frame.</returns>
     **************************************************************************************************/
    virtual std::weak_ptr<ALLEGRO_BITMAP> GetImage() const override;

    /**************************************************************************************************
     * <summary>Gets the current frame.</summary>
     * <remarks>Casey Ugone, 6/30/2012.</remarks>
     * <returns>null if it fails, else the image.</returns>
     **************************************************************************************************/
    virtual std::weak_ptr<ALLEGRO_BITMAP> GetImage() override;

    /**************************************************************************************************
     * <summary>Gets the entire BITMAP sheet.</summary>
     * <remarks>Casey Ugone, 10/31/2011.</remarks>
     * <returns>null if it fails, else the sheet.</returns>
     **************************************************************************************************/
    virtual std::weak_ptr<ALLEGRO_BITMAP> GetSheet() const override;

    /**************************************************************************************************
     * <summary>Gets the entire BITMAP sheet.</summary>
     * <remarks>Casey Ugone, 6/30/2012.</remarks>
     * <returns>null if it fails, else the sheet.</returns>
     **************************************************************************************************/
    virtual std::weak_ptr<ALLEGRO_BITMAP> GetSheet() override;

    /**************************************************************************************************
     * <summary>Animates an animated sprite.</summary>
     * <remarks>Casey Ugone, 11/8/2011.</remarks>
     * <param name="name">     The name of the animation.</param>
     * <param name="dir">      The direction to animate.</param>
     * <param name="deltaTime">The current time between frames.</param>
     **************************************************************************************************/
    virtual void Animate(const std::string& name, ADTAnimationHandler::Direction dir, std::chrono::duration<double> deltaTime) override;

    /**************************************************************************************************
     * <summary>Sets the frame rate of the animated sprite.</summary>
     * <remarks>Casey Ugone, 8/2/2011.</remarks>
     * <remarks>If deltaTime is zero or less, the animation plays as fast as possible.</remarks>
     * <param name="deltaTime">The time between each frame in seconds.</param>
     **************************************************************************************************/
    virtual void SetFrameRate(std::chrono::duration<double> frameRate) override;

    /**************************************************************************************************
     * <summary>Gets the width of the frame.</summary>
     * <remarks>Casey Ugone, 7/4/2012.</remarks>
     * <returns>The width of the frame in pixels.</returns>
     **************************************************************************************************/
    virtual int GetWidth() const override;

    /**************************************************************************************************
     * <summary>Gets the width of the frame.</summary>
     * <remarks>Casey Ugone, 7/4/2012.</remarks>
     * <returns>The width of the frame in pixels.</returns>
     **************************************************************************************************/
    virtual int GetWidth() override;

    /**************************************************************************************************
     * <summary>Gets the height of the frame.</summary>
     * <remarks>Casey Ugone, 7/4/2012.</remarks>
     * <returns>The height of the frame in pixels.</returns>
     **************************************************************************************************/
    virtual int GetHeight() const override;

    /**************************************************************************************************
     * <summary>Gets the height of the frame.</summary>
     * <remarks>Casey Ugone, 7/4/2012.</remarks>
     * <returns>The height of the frame in pixels.</returns>
     **************************************************************************************************/
    virtual int GetHeight() override;

    /**************************************************************************************************
     * <summary>Gets the frame rate.</summary>
     * <remarks>Casey Ugone, 8/2/2011.</remarks>
     * <returns>The frame rate in seconds.</returns>
     **************************************************************************************************/
    virtual std::chrono::duration<double> GetFrameRate() const override;

    /**************************************************************************************************
     * <summary>Gets the frame rate.</summary>
     * <remarks>Casey Ugone, 6/30/2012.</remarks>
     * <returns>The frame rate.</returns>
     **************************************************************************************************/
    virtual std::chrono::duration<double> GetFrameRate() override;

    /**************************************************************************************************
     * <summary>Gets the animation handler.</summary>
     * <remarks>Casey Ugone, 12/3/2011.</remarks>
     * <returns>null if it fails, else the animation handler.</returns>
     **************************************************************************************************/
    virtual const ADTAnimationHandler* GetAnimationHandler() const override;

    /**************************************************************************************************
     * <summary>Gets the animation handler.</summary>
     * <remarks>Casey Ugone, 6/30/2012.</remarks>
     * <returns>null if it fails, else the animation handler.</returns>
     **************************************************************************************************/
    virtual ADTAnimationHandler* GetAnimationHandler() override;

protected:

    /**************************************************************************************************
     * <summary>Resize frame image.</summary>
     * <remarks>Casey Ugone, 12/3/2011.</remarks>
     * <remarks>Does nothing if width and height are unchanged from previous width and height.</remarks>
     * <remarks>Does nothing if called on a Sprite object.</remarks>
     * <param name="width"> The new width.</param>
     * <param name="height">The new height.</param>
     **************************************************************************************************/
    virtual void ResizeFrame(unsigned int width, unsigned int height) override;

private:
    /// <summary> The current frame image </summary>
    std::shared_ptr<ALLEGRO_BITMAP> _frameImage;
    /// <summary> The weak pointer to frame image </summary>
    std::weak_ptr<ALLEGRO_BITMAP> _wp_frameImage;
    /// <summary> The frame rate </summary>
    std::chrono::duration<double> _frameRate;
    /// <summary> The animation handler.</summary>
    std::unique_ptr<ADTAnimationHandler> _animation;
    /// <summary> The framerate accumulator to determine if a frame should advance.</summary>
    std::chrono::duration<double> _accumulator;

    friend ADTAnimationHandler;
};

A2DE_END

#endif