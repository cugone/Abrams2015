#include "ADTAnimationHandler.h"

#include <algorithm>

#include <allegro5/display.h>
#include <allegro5/bitmap_draw.h>

#include "CAnimationFrameSet.h"
#include "CAnimatedSprite.h"
#include "CSprite.h"


A2DE_BEGIN

ADTAnimationHandler::ADTAnimationHandler(Sprite& observed) : _animations(), _curSet(), _curFrame(), _observed(observed), _curName() {
    /* DO NOTHING: Empty destructor required for virtual calls. */
}


ADTAnimationHandler::~ADTAnimationHandler() {
    /* DO NOTHING: Empty destructor required for virtual calls. */
}


bool ADTAnimationHandler::AddAnimation(const std::string& name) {
    return _animations.insert_or_assign(name, a2de::AnimationFrameSet()).second;
}

bool ADTAnimationHandler::AddAnimation(const std::string& name, const AnimationFrameSet& frames) {
    return _animations.insert_or_assign(name, frames).second;
}

bool ADTAnimationHandler::RemoveAnimation(const std::string& name) {
    return _animations.erase(name) > 0;
}

std::map<std::string, AnimationFrameSet>::const_iterator ADTAnimationHandler::begin() const {
    return this->_animations.begin();
}

std::map<std::string, AnimationFrameSet>::iterator ADTAnimationHandler::begin() {
    return this->_animations.begin();
}

std::map<std::string, AnimationFrameSet>::const_iterator ADTAnimationHandler::end() const {
    return this->_animations.end();
}

std::map<std::string, AnimationFrameSet>::iterator ADTAnimationHandler::end() {
    return this->_animations.end();
}

bool ADTAnimationHandler::empty() const {
    return this->_animations.empty();
}

bool ADTAnimationHandler::empty() {
    return this->_animations.empty();
}

std::size_t ADTAnimationHandler::size() const {
    return this->_animations.size();
}

std::size_t ADTAnimationHandler::size() {
    return this->_animations.size();
}

std::size_t ADTAnimationHandler::size(const std::string& name) const {
    return this->_animations.at(name).size();
}

std::size_t ADTAnimationHandler::size(const std::string& name) {
    return this->_animations.at(name).size();
}

std::map<std::string, AnimationFrameSet>::const_iterator ADTAnimationHandler::find(const std::string& name) const {
    return this->_animations.find(name);
}

std::map<std::string, AnimationFrameSet>::iterator ADTAnimationHandler::find(const std::string& name) {
    return this->_animations.find(name);
}

void ADTAnimationHandler::Play(const std::string& name, bool rewindOnCompletion) {
    if(rewindOnCompletion) {
        this->Animate(name, ADTAnimationHandler::Direction::Forward_Looping);
    } else {
        this->Animate(name, ADTAnimationHandler::Direction::Forward_Nonlooping);
    }
}

void ADTAnimationHandler::Reverse(const std::string& name, bool rewindOnCompletion) {
    if(rewindOnCompletion) {
        this->Animate(name, ADTAnimationHandler::Direction::Reverse_Looping);
    } else {
        this->Animate(name, ADTAnimationHandler::Direction::Reverse_Nonlooping);
    }
}

void ADTAnimationHandler::Animate(const std::string& name, ADTAnimationHandler::Direction dir) {

    const auto iter = _animations.find(name);
    if(iter == _animations.cend()) return;
    
    if(_curName != name) {
        _curName = name;

        switch(dir) {
            case ADTAnimationHandler::Direction::Forward_Looping: /* Fall through to DIR_FORWARD_NONLOOPING */
            case ADTAnimationHandler::Direction::Forward_Nonlooping:
                _curFrame = iter->second.cbegin();
                break;
            case ADTAnimationHandler::Direction::Reverse_Looping: /* Fall through to DIR_REVERSE_NONLOOPING */
            case ADTAnimationHandler::Direction::Reverse_Nonlooping:
                _curFrame = iter->second.cend();
                break;
        }
    } else {

        switch(dir) {
            case ADTAnimationHandler::Direction::Forward_Looping:
                if(_curFrame != iter->second.cend()) {
                    ++_curFrame;
                } else {
                    _curFrame = iter->second.cbegin();
                }
                break;
            case ADTAnimationHandler::Direction::Forward_Nonlooping:
                if(_curFrame != iter->second.cend()) {
                    ++_curFrame;
                } else {
                    _curFrame = iter->second.cend() - 1;
                }
                break;
            case ADTAnimationHandler::Direction::Reverse_Looping:
                if(_curFrame != iter->second.cbegin()) {
                    --_curFrame;
                } else {
                    _curFrame = iter->second.cend() - 1;
                }
                break;
            case ADTAnimationHandler::Direction::Reverse_Nonlooping:
                if(_curFrame != iter->second.cbegin()) {
                    --_curFrame;
                } else {
                    _curFrame = iter->second.cbegin();
                }
                break;
        }
    }

    if(_curFrame == iter->second.cend()) {
        switch(dir) {
            case ADTAnimationHandler::Direction::Forward_Looping:
                _curFrame = iter->second.cbegin();
                break;
            case ADTAnimationHandler::Direction::Forward_Nonlooping:
                _curFrame = iter->second.cend() - 1;
                break;
            case ADTAnimationHandler::Direction::Reverse_Looping:
                _curFrame = iter->second.cend() - 1;
                break;
            case ADTAnimationHandler::Direction::Reverse_Nonlooping:
                _curFrame = iter->second.cend() - 1;
                break;
        }
    }

    CopyCurrentFrameToImageFrame(_curFrame);
}

void ADTAnimationHandler::CopyCurrentFrameToImageFrame(AnimationFrameSet::const_iterator iter) {

    double curFrameWidth = iter->GetWidth();
    double curFrameHeight = iter->GetHeight();
    double curFrameX = iter->GetX();
    double curFrameY = iter->GetY();

    _observed.ResizeFrame(curFrameWidth, curFrameHeight);

    if(_observed.GetSheet().expired()) return;
    if(_observed.GetImage().expired()) return;
    
    auto sp_observed_sheet = _observed.GetSheet().lock();
    auto sp_observed_frame = _observed.GetImage().lock();

    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
    al_set_target_bitmap(sp_observed_frame.get());
    al_clear_to_color(al_map_rgba(0, 0, 0, 255));
    al_draw_bitmap_region(sp_observed_sheet.get(), curFrameX, curFrameY, curFrameWidth, curFrameHeight, 0, 0, 0);

    al_set_target_bitmap(old_target);
}

A2DE_END