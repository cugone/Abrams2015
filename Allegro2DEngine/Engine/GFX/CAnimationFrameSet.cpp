/**************************************************************************************************
// file:	Engine\GFX\CAnimationFrameSet.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the animation frame set class
 **************************************************************************************************/
#include "CAnimationFrameSet.h"

#include "CSprite.h"
#include <algorithm>

A2DE_BEGIN


AnimationFrameSet::const_iterator AnimationFrameSet::begin() const {
    return _frameStrip.begin();
}

AnimationFrameSet::const_iterator AnimationFrameSet::cbegin() const {
    return _frameStrip.cbegin();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::rbegin() const {
    return _frameStrip.rbegin();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::crbegin() const {
    return _frameStrip.crbegin();
}

AnimationFrameSet::iterator AnimationFrameSet::begin() {
    return _frameStrip.begin();
}

AnimationFrameSet::const_iterator AnimationFrameSet::cbegin() {
    return _frameStrip.cbegin();
}

AnimationFrameSet::reverse_iterator AnimationFrameSet::rbegin() {
    return _frameStrip.rbegin();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::crbegin() {
    return _frameStrip.crbegin();
}

AnimationFrameSet::const_iterator AnimationFrameSet::end() const {
    return _frameStrip.end();
}

AnimationFrameSet::const_iterator AnimationFrameSet::cend() const {
    return _frameStrip.cend();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::rend() const {
    return _frameStrip.rend();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::crend() const {
    return _frameStrip.crend();
}

AnimationFrameSet::iterator AnimationFrameSet::end() {
    return _frameStrip.end();
}

AnimationFrameSet::const_iterator AnimationFrameSet::cend() {
    return _frameStrip.cend();
}

AnimationFrameSet::reverse_iterator AnimationFrameSet::rend() {
    return _frameStrip.rend();
}

AnimationFrameSet::const_reverse_iterator AnimationFrameSet::crend() {
    return _frameStrip.crend();
}

bool AnimationFrameSet::operator==(const AnimationFrameSet& rhs) {
    if(this == &rhs) return true;
    if(this->_frameStrip.size() != rhs._frameStrip.size()) return false;

    AnimationFrameSet::const_iterator _rhsIter = rhs._frameStrip.cbegin();
    AnimationFrameSet::const_iterator _thisIter = this->_frameStrip.cbegin();
    AnimationFrameSet::const_iterator _myEnd = _frameStrip.cend();

    for(const auto& my_frame : _frameStrip) {
        for(const auto& your_frame : rhs._frameStrip) {
            if(my_frame != your_frame) return false;
        }
    }
    return true;
}


bool AnimationFrameSet::operator!=(const AnimationFrameSet& rhs) {
    return !(*this == rhs);
}

void AnimationFrameSet::AddFrame(const AnimationFrame& frame) {
    _frameStrip.push_back(frame);
    _curFrame = _frameStrip.cbegin();
}

std::size_t AnimationFrameSet::size() const {
    return _frameStrip.size();
}

std::size_t AnimationFrameSet::size() {
    return static_cast<const AnimationFrameSet&>(*this).size();
}

bool AnimationFrameSet::IsAtFirst() const {
    return _curFrame == _frameStrip.cbegin();
}

bool AnimationFrameSet::IsAtFirst() {
    return static_cast<const AnimationFrameSet&>(*this).IsAtFirst();
}

bool a2de::AnimationFrameSet::IsAtLast() const {
    return _curFrame == _frameStrip.cend() - 1;
}

bool a2de::AnimationFrameSet::IsAtLast() {
    return static_cast<const AnimationFrameSet&>(*this).IsAtLast();
}

bool AnimationFrameSet::IsAtEnd() const {
    return IsComplete();
}

bool AnimationFrameSet::IsAtEnd() {
    return static_cast<const AnimationFrameSet&>(*this).IsAtEnd();
}

bool AnimationFrameSet::IsAt(const std::vector<AnimationFrame>::const_iterator& position) const {
    return _curFrame == position;
}

bool AnimationFrameSet::IsAt(const std::vector<AnimationFrame>::const_iterator& position) {
    return static_cast<const AnimationFrameSet&>(*this).IsAt(position);
}

bool a2de::AnimationFrameSet::IsAtFront() const {
    return _curFrame == _frameStrip.cbegin();
}

bool a2de::AnimationFrameSet::IsAtFront() {
    return static_cast<const AnimationFrameSet&>(*this).IsAtFront();
}

bool AnimationFrameSet::IsComplete() const {
    return _curFrame == _frameStrip.cend();
}

bool AnimationFrameSet::IsComplete() {
    return static_cast<const AnimationFrameSet&>(*this).IsComplete();
}

const AnimationFrame& AnimationFrameSet::GetCurFrame() const {
    return *_curFrame;
}

AnimationFrame& AnimationFrameSet::GetCurFrame() {
    return const_cast<AnimationFrame&>(static_cast<const AnimationFrameSet&>(*this).GetCurFrame());
}

const AnimationFrame& AnimationFrameSet::at(std::size_t pos) const {
    return _frameStrip.at(pos);
}

AnimationFrame& AnimationFrameSet::at(std::size_t pos) {
    return const_cast<AnimationFrame&>(static_cast<const AnimationFrameSet&>(*this).at(pos));
}

A2DE_END