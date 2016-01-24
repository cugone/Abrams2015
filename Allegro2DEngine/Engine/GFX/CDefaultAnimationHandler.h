/**************************************************************************************************
// file:	Engine\GFX\CAnimationHandler.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the animation handler class
 **************************************************************************************************/
#ifndef A2DE_CANIMATIONHANDLER_H
#define A2DE_CANIMATIONHANDLER_H

#include "../a2de_vals.h"

#include "ADTAnimationHandler.h"

A2DE_BEGIN

class Sprite;
class AnimatedSprite;

class DefaultAnimationHandler : public ADTAnimationHandler {
public:
    explicit DefaultAnimationHandler(Sprite& observed);
    DefaultAnimationHandler(const DefaultAnimationHandler&) = default;
    DefaultAnimationHandler(DefaultAnimationHandler&&) = default;
    DefaultAnimationHandler& operator=(const DefaultAnimationHandler&) = default;
    DefaultAnimationHandler& operator=(DefaultAnimationHandler&&) = default;
    virtual ~DefaultAnimationHandler() = default;
protected:

private:

};

A2DE_END

#endif