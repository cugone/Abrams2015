/**************************************************************************************************
// file:	Engine\GFX\CAnimatedSprite.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the animated sprite class
 **************************************************************************************************/
#include "CAnimatedSprite.h"

#include <functional>
#include <string>

#include <allegro5/drawing.h>
#include <allegro5/color.h>
#include <allegro5/display.h>

#include "../a2de_exceptions.h"

#include "CDefaultAnimationHandler.h"

A2DE_BEGIN

AnimatedSprite::AnimatedSprite(const std::string& file, std::chrono::duration<double> frameRate)
    : Sprite(file), _frameImage(nullptr, al_destroy_bitmap), _wp_frameImage(), _frameRate(frameRate), _animation(nullptr), _accumulator(0) {
        _frameDimensions = _dimensions;
        _animation = std::make_unique<DefaultAnimationHandler>(*this);
        auto default_frameset = a2de::AnimationFrameSet{ };
        for(auto y = 0.0; y < _dimensions.GetY(); y += _frameDimensions.GetY()) {
            for(auto x = 0.0; x < _dimensions.GetX(); x += _frameDimensions.GetX()) {
                default_frameset.AddFrame(a2de::AnimationFrame{ x, y, _frameDimensions.GetX(), _frameDimensions.GetY() });
            }
        }
        _animation->AddAnimation("default", default_frameset);
        _frameImage = std::shared_ptr<ALLEGRO_BITMAP>(al_create_bitmap(default_frameset.at(0).GetWidth(), default_frameset.at(0).GetHeight()), al_destroy_bitmap);
        _wp_frameImage = _frameImage;
}

AnimatedSprite::AnimatedSprite(const AnimatedSprite& animatedSprite)
 : Sprite(animatedSprite), _frameImage(nullptr, al_destroy_bitmap), _wp_frameImage(), _frameRate(animatedSprite._frameRate), _animation(nullptr), _accumulator(0) {
    this->_frameImage = std::shared_ptr<ALLEGRO_BITMAP>(al_create_bitmap(al_get_bitmap_width(animatedSprite._frameImage.get()), al_get_bitmap_height(animatedSprite._frameImage.get())), al_destroy_bitmap);
    this->_wp_frameImage = _frameImage;
    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
    al_set_target_bitmap(this->_frameImage.get());
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_set_target_bitmap(old_target);

    this->_frameDimensions = animatedSprite._frameDimensions;
    _animation = std::make_unique<DefaultAnimationHandler>(*this);
    if(animatedSprite._animation->empty() == false) {
        for(auto anims : *(animatedSprite.GetAnimationHandler())) {
            this->_animation->AddAnimation(anims.first, anims.second);
        }
    }

}

std::weak_ptr<ALLEGRO_BITMAP> AnimatedSprite::GetImage() const {
    return _wp_frameImage;
}
std::weak_ptr<ALLEGRO_BITMAP> AnimatedSprite::GetImage() {
    return static_cast<const AnimatedSprite&>(*this).GetImage();
}

std::weak_ptr<ALLEGRO_BITMAP> AnimatedSprite::GetSheet() const {
    return Sprite::GetSheet();
}
std::weak_ptr<ALLEGRO_BITMAP> AnimatedSprite::GetSheet() {
    return static_cast<const AnimatedSprite&>(*this).GetSheet();
}

void AnimatedSprite::Animate(const std::string& name, ADTAnimationHandler::Direction dir, std::chrono::duration<double> deltaTime) {
    
    //Plays the animation from beginning to end.
    std::function<void(const std::string&, bool)> play = [=](const std::string& name, bool rewind) {
        this->_animation->Play(name, rewind);
    };

    //Plays the animation from end to beginning.
    std::function<void(const std::string&, bool)> reverse = [=](const std::string& name, bool rewind) {
        this->_animation->Reverse(name, rewind);
    };

    _accumulator += deltaTime;
    while(_accumulator >= _frameRate * deltaTime.count()) {

        //Defaults to Forward_Looping
        auto animation_function = play;
        bool rewindOnCompletion = true;

        if(dir == ADTAnimationHandler::Direction::Forward_Nonlooping || dir == ADTAnimationHandler::Direction::Reverse_Nonlooping) {
            rewindOnCompletion = false;
        } else if(dir == ADTAnimationHandler::Direction::Reverse_Looping || dir == ADTAnimationHandler::Direction::Reverse_Nonlooping) {
            animation_function = reverse;
        } else {
            /* default case handled */
        }

        animation_function(name, rewindOnCompletion);

        //if(_frameRate.count() == 0) {
        //    _accumulator = decltype(_accumulator)::zero();
        //    break;
        //}

        _accumulator = decltype(_accumulator)::zero();

        //_accumulator -= _frameRate;
    }

}

void AnimatedSprite::SetFrameRate(std::chrono::duration<double> deltaTime) {
    _frameRate = deltaTime;
}

std::chrono::duration<double> AnimatedSprite::GetFrameRate() const {
    return _frameRate;
}

std::chrono::duration<double> AnimatedSprite::GetFrameRate() {
    return static_cast<const AnimatedSprite&>(*this).GetFrameRate();
}

const ADTAnimationHandler* AnimatedSprite::GetAnimationHandler() const {
    return _animation.get();
}

ADTAnimationHandler* AnimatedSprite::GetAnimationHandler() {
    return const_cast<ADTAnimationHandler*>(static_cast<const AnimatedSprite&>(*this).GetAnimationHandler());
}

void AnimatedSprite::ResizeFrame(unsigned int width, unsigned int height) {

    double fdX = this->_frameDimensions.GetX();
    double fdY = this->_frameDimensions.GetY();
    if(static_cast<unsigned int>(fdX) == width && static_cast<unsigned int>(fdY) == height) return;

    this->_frameDimensions = Vector2D(width, height);
    CalcCenterFrame();
    _frameImage.reset(al_create_bitmap(width, height), al_destroy_bitmap);
    _wp_frameImage = _frameImage;
    ALLEGRO_BITMAP* old_target = al_get_target_bitmap();
    al_set_target_bitmap(_wp_frameImage.lock().get());
    al_clear_to_color(al_map_rgba(0, 0, 0, 255));
    al_set_target_bitmap(old_target);

}

int AnimatedSprite::GetWidth() const {
    return _frameDimensions.GetX();
}

int AnimatedSprite::GetWidth() {
    return static_cast<const AnimatedSprite&>(*this).GetWidth();
}

int AnimatedSprite::GetHeight() const {
    return _frameDimensions.GetY();
}

int AnimatedSprite::GetHeight() {
    return static_cast<const AnimatedSprite&>(*this).GetHeight();
}

A2DE_END