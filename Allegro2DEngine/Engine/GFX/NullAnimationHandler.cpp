#include "NullAnimationHandler.h"

#include "../a2de_vals.h"
#include "CSprite.h"

A2DE_BEGIN

NullAnimationHandler::NullAnimationHandler(Sprite& observed) : ADTAnimationHandler(observed) {
    /* DO NOTHING: Not required */
}

bool NullAnimationHandler::AddAnimation(const std::string& /*name*/) {
    return false;
}

bool NullAnimationHandler::AddAnimation(const std::string& /*name*/, const AnimationFrameSet& /*frames*/) {
    return false;
}

bool NullAnimationHandler::RemoveAnimation(const std::string& /*name*/) {
    return false;
}

A2DE_END