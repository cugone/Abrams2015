/**************************************************************************************************
// file:	Engine\GFX\CAnimationFrame.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the animation frame class
 **************************************************************************************************/
#include "CAnimationFrame.h"

#include <iostream>
#include <fstream>

A2DE_BEGIN

AnimationFrame::AnimationFrame() : AnimationFrame(0.0, 0.0, 1.0, 1.0) { }

AnimationFrame::AnimationFrame(double xOffset, double yOffset, double width, double height)
:
_position(std::make_pair(xOffset, yOffset)),
_dimensions(std::make_pair(width, height))
{ /* DO NOTHING: Not required */ }

AnimationFrame::AnimationFrame(const AnimationFrame& other)
    :
    _position(other._position),
    _dimensions(other._dimensions) { /* DO NOTHING: Not required */
}

AnimationFrame::AnimationFrame(AnimationFrame&& other)
:
_position(std::move(other._position)),
_dimensions(std::move(other._dimensions))
{ /* DO NOTHING: Not required */ }

AnimationFrame& AnimationFrame::operator=(AnimationFrame rhs) {
    this->swap(rhs);
    return *this;
}

bool AnimationFrame::operator==(const AnimationFrame& rhs) const {
    return (this->_position == rhs._position && this->_dimensions == rhs._dimensions);
}

bool AnimationFrame::operator!=(const AnimationFrame& rhs) const {
    return !(*this == rhs);
}

bool AnimationFrame::operator==(const AnimationFrame& rhs) {
    return static_cast<const AnimationFrame&>(*this).operator==(rhs);
}

bool AnimationFrame::operator!=(const AnimationFrame& rhs) {
    return static_cast<const AnimationFrame&>(*this).operator!=(rhs);
}

double AnimationFrame::GetWidth() const {
    return this->_dimensions.first;
}

double AnimationFrame::GetWidth() {
    return static_cast<const AnimationFrame&>(*this).GetWidth();
}

double AnimationFrame::GetHeight() const {
    return this->_dimensions.second;
}

double AnimationFrame::GetHeight() {
    return static_cast<const AnimationFrame&>(*this).GetHeight();
}

auto AnimationFrame::GetDimensions() const {
    return _dimensions;
}

auto AnimationFrame::GetDimensions() {
    return static_cast<const AnimationFrame&>(*this).GetDimensions();
}

double AnimationFrame::GetX() const {
    return this->_position.first;
}

double AnimationFrame::GetX() {
    return static_cast<const AnimationFrame&>(*this).GetX();
}

double AnimationFrame::GetY() const {
    return this->_position.second;
}

double AnimationFrame::GetY() {
    return static_cast<const AnimationFrame&>(*this).GetY();
}

auto AnimationFrame::GetPosition() const {
    return _position;
}

auto AnimationFrame::GetPosition() {
    return static_cast<const AnimationFrame&>(*this).GetPosition();
}

void AnimationFrame::swap(AnimationFrame& rhs) {
    std::swap(this->_dimensions, rhs._dimensions);
    std::swap(this->_position, rhs._position);
}


A2DE_END
