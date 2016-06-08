/**************************************************************************************************
// file:	Engine\Input\CMouse.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the mouse class
 **************************************************************************************************/
#include "CMouse.h"

#include <cassert>

#include "../GFX/CGameWindow.h"
#include "../GFX/CAnimatedSprite.h"

#include "../Math/CMiscMath.h"
#include "../a2de_exceptions.h"

A2DE_BEGIN

bool Mouse::_is_instanced = false;

void Mouse::Init() {

	assert(!_is_instanced);

    al_set_system_mouse_cursor(&_parent_display, ALLEGRO_SYSTEM_MOUSE_CURSOR::ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    _numButtons = al_get_mouse_num_buttons();

    al_get_mouse_state(&_curState);

}

void a2de::Mouse::Init(const ALLEGRO_DISPLAY& parent_display, const std::string& file, const a2de::Vector2D& focus, ALLEGRO_SYSTEM_MOUSE_CURSOR cursor_id) {

}

void Mouse::Deinit() {

	_image.reset();

    al_uninstall_mouse();

}

Mouse::Mouse(ALLEGRO_DISPLAY& parent_display) :
_position(),
_mickeys(),
_focus(),
_image(),
_isVisible(true),
_numButtons(0),
_prevState(),
_curState(),
_cursor(nullptr, al_destroy_mouse_cursor),
_parent_display(parent_display),
_cursor_id(ALLEGRO_SYSTEM_MOUSE_CURSOR::ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT) {

    assert(!_is_instanced);
    _is_instanced = true;

    al_set_system_mouse_cursor(&_parent_display, _cursor_id);

    _numButtons = al_get_mouse_num_buttons();

    al_get_mouse_state(&_curState);


}

Mouse::~Mouse() {
    _is_instanced = false;

	_image.reset();
    _cursor.reset(nullptr);

    al_uninstall_mouse();

}

int Mouse::GetNumButtons() const {
    return _numButtons;
}

int Mouse::GetNumButtons() {
    return static_cast<const Mouse&>(*this).GetNumButtons();
}

void Mouse::SetPosition(const a2de::Vector4D& pos) {

	al_set_mouse_xy(&_parent_display, pos.GetX(), pos.GetY());
	al_set_mouse_z(pos.GetZ());
	al_set_mouse_w(pos.GetW());
	_position = pos;
}

void Mouse::SetFocus(const a2de::Vector2D& pos) {
	_focus = pos;
}

void Mouse::Update() {

    _prevState = _curState;
    al_get_mouse_state(&_curState);

    _cursor ? al_set_mouse_cursor(&_parent_display, _cursor.get()) : al_set_system_mouse_cursor(&_parent_display, _cursor_id);

    _isVisible ?  al_show_mouse_cursor(&_parent_display) : al_hide_mouse_cursor(&_parent_display);
}

void Mouse::SetImage(std::shared_ptr<a2de::Sprite> image, int focusX, int focusY) {
    if(image.get() == nullptr) return;
    _image = image;
    _focus = Vector2D();
    if(_image.expired() == false) {
        _focus = Vector2D(focusX, focusY);
        _cursor = std::unique_ptr<ALLEGRO_MOUSE_CURSOR, decltype(&al_destroy_mouse_cursor)>(al_create_mouse_cursor(_image.lock().get()->GetImage().lock().get(), _focus.GetX(), _focus.GetY()), al_destroy_mouse_cursor);
    } else {
        al_set_system_mouse_cursor(&_parent_display, _cursor_id);
        _cursor.reset(nullptr);
    }
}

bool Mouse::IsVisible() {
    return _isVisible;
}
void Mouse::SetVisible(bool visible) {
    _isVisible = visible;
}

void Mouse::Show() {
    SetVisible(true);
}
void Mouse::Hide() {
    SetVisible(false);
}

void Mouse::SetImageToDefault(ALLEGRO_SYSTEM_MOUSE_CURSOR cursor /* = ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT*/) {
    _cursor.reset(nullptr);
    _cursor_id = cursor;
    al_set_system_mouse_cursor(&_parent_display, _cursor_id);
}

std::weak_ptr<Sprite> a2de::Mouse::GetSprite() const {
    return _image;
}

std::weak_ptr<Sprite> a2de::Mouse::GetSprite() {
	return static_cast<const a2de::Mouse&>(*this).GetSprite();
}

const Vector4D& Mouse::GetPosition() const {
    return _position;
}

Vector4D& Mouse::GetPosition() {
    return const_cast<a2de::Vector4D&>(static_cast<const Mouse&>(*this).GetPosition());
}

const a2de::Vector4D& Mouse::GetMickeys() const {
    return _mickeys;
}

a2de::Vector4D& Mouse::GetMickeys() {
    return const_cast<a2de::Vector4D&>(static_cast<const Mouse&>(*this).GetMickeys());
}

const a2de::Vector2D& Mouse::GetFocus() const {
    return _focus;
}

a2de::Vector2D& Mouse::GetFocus() {
    return const_cast<a2de::Vector2D&>(static_cast<const Mouse&>(*this).GetFocus());
}

bool Mouse::MouseLostFocus() const {
    return _prevState.display != _curState.display;
}

bool Mouse::MouseLostFocus() {
    return static_cast<const Mouse&>(*this).MouseLostFocus();
}


A2DE_END