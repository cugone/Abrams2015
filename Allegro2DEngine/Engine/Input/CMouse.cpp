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

    //TODO: Uncomment Mouse functions after testing window.
    //SetImage(_image, _focus.GetX(), _focus.GetY());

    al_set_system_mouse_cursor(&_parent_display, _cursor_id);
    _numButtons = al_get_mouse_num_buttons();

    al_get_mouse_state(&_curState);

}

void Mouse::Deinit() {

    //TODO: Uncomment Mouse functions after testing window.

    //delete _image;
    //_image = nullptr;

    al_uninstall_mouse();

}

Mouse::Mouse(ALLEGRO_DISPLAY& parent_display) :
_position(),
_mickeys(),
_focus(),
//TODO: Uncomment Mouse functions after testing window.
//_image(nullptr),
_isVisible(true),
_numButtons(0),
_prevState(),
_curState(),
_cursor(nullptr, al_destroy_mouse_cursor),
_parent_display(parent_display),
_cursor_id(ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT) {

    assert(!_is_instanced);
    _is_instanced = true;

    bool mouse_init = al_install_mouse();
    if(mouse_init == false) {
        throw InputNotAvailableException("Mouse");
    }

    al_set_system_mouse_cursor(&_parent_display, _cursor_id);

    _numButtons = al_get_mouse_num_buttons();

    al_get_mouse_state(&_curState);


}

Mouse::~Mouse() {
    _is_instanced = false;

    //delete _image;
    //_image = nullptr;

    this->_cursor.reset(nullptr);

    al_uninstall_mouse();

}

//TODO: Uncomment Mouse functions after testing window.
//Sprite* Mouse::GetSprite() const {
//	return _image;
//}

int Mouse::GetX() const {
    return _position.GetX();
}
int Mouse::GetY() const {
    return _position.GetY();
}
int Mouse::GetZ() const {
    return _position.GetZ();
}

int Mouse::GetW() const {
    return _position.GetW();
}

int Mouse::GetX() {
    return static_cast<const Mouse&>(*this).GetX();
}
int Mouse::GetY() {
    return static_cast<const Mouse&>(*this).GetY();
}
int Mouse::GetZ() {
    return static_cast<const Mouse&>(*this).GetZ();
}

int Mouse::GetW() {
    return static_cast<const Mouse&>(*this).GetW();
}

int Mouse::GetMickeyX() const {
    return _mickeys.GetX();
}
int Mouse::GetMickeyY() const {
    return _mickeys.GetY();
}
int Mouse::GetMickeyZ() const {
    return _mickeys.GetZ();
}
int Mouse::GetMickeyW() const {
    return _mickeys.GetW();
}

int Mouse::GetMickeyX() {
    return static_cast<const Mouse&>(*this).GetMickeyX();
}
int Mouse::GetMickeyY() {
    return static_cast<const Mouse&>(*this).GetMickeyY();
}
int Mouse::GetMickeyZ() {
    return static_cast<const Mouse&>(*this).GetMickeyZ();
}
int Mouse::GetMickeyW() {
    return static_cast<const Mouse&>(*this).GetMickeyW();
}

int Mouse::GetFocusX() const {
    return _focus.GetX();
}
int Mouse::GetFocusY() const {
    return _focus.GetY();
}

int Mouse::GetFocusX() {
    return static_cast<const Mouse&>(*this).GetFocusX();
}
int Mouse::GetFocusY() {
    return static_cast<const Mouse&>(*this).GetFocusY();
}

int Mouse::GetNumButtons() const {
    return _numButtons;
}

int Mouse::GetNumButtons() {
    return static_cast<const Mouse&>(*this).GetNumButtons();
}

void Mouse::SetX(double x) {
    SetPosition(x, GetY(), GetZ(), GetW());
}
void Mouse::SetY(double y) {
    SetPosition(GetX(), y, GetZ(), GetW());
}

void Mouse::SetZ(double z) {
    SetPosition(GetX(), GetY(), z, GetW());
}

void Mouse::SetW(double w) {
    SetPosition(GetX(), GetY(), GetZ(), w);
}

void Mouse::SetPosition(double x, double y) {
    SetPosition(x, y, GetZ(), GetW());
}

void Mouse::SetPosition(double x, double y, double z) {
    SetPosition(x, y, z, GetW());
}

void Mouse::SetPosition(double x, double y, double z, double w) {

    al_set_mouse_xy(&_parent_display, x, y);
    al_set_mouse_z(x);
    al_set_mouse_w(w);
    _position = a2de::Vector4D(x, y, z, w);
}

void Mouse::SetFocus(int x, int y) {
	_focus = Vector2D(x, y);
}

void Mouse::Update() {

    _prevState = _curState;
    al_get_mouse_state(&_curState);

    if(_cursor) {
        al_set_mouse_cursor(&_parent_display, _cursor.get());
    } else {
        al_set_system_mouse_cursor(&_parent_display, _cursor_id);
    }
    _isVisible ?  al_show_mouse_cursor(&_parent_display) : al_hide_mouse_cursor(&_parent_display);
}

//TODO: Uncomment Mouse functions after testing window.
//void Mouse::SetImage(Sprite* image, int focusX, int focusY) {
//    if(_image) {
//        al_destroy_mouse_cursor(_cursor);
//    }
//    if(image) {
//        delete _image;
//        _image = nullptr;
//        _image = Sprite::CreateSprite(*image);
//    } else {
//        focusX = 0;
//        focusY = 0;
//    }
//    _focus = Vector2D(focusX, focusY);
//    if(image) {
//        _cursor = al_create_mouse_cursor(_image->GetImage(), _focus.GetX(), _focus.GetY());
//    } else {
//        al_set_system_mouse_cursor(_parent_display, _cursor_id);
//    }
//}

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
    _cursor_id = cursor;
    al_set_system_mouse_cursor(&_parent_display, _cursor_id);
}

const Vector4D& Mouse::GetPosition4d() const {
    return _position;
}

Vector4D& Mouse::GetPosition4d() {
    return const_cast<a2de::Vector4D&>(static_cast<const Mouse&>(*this).GetPosition4d());
}

a2de::Vector3D Mouse::GetPosition3d() const {
    return Vector3D(_position.GetX(), _position.GetY(), _position.GetZ());
}

a2de::Vector3D Mouse::GetPosition3d() {
    return static_cast<const Mouse&>(*this).GetPosition3d();
}

a2de::Vector2D Mouse::GetPosition2d() const {
    return Vector3D(_position.GetX(), _position.GetY());
}

a2de::Vector2D Mouse::GetPosition2d() {
    return static_cast<const Mouse&>(*this).GetPosition2d();
}

void Mouse::SetPosition(const a2de::Vector2D& pos) {
    SetPosition(pos.GetX(), pos.GetY(), GetZ(), GetW());
}

void Mouse::SetPosition(const a2de::Vector3D& pos) {
    SetPosition(pos.GetX(), pos.GetY(), pos.GetZ(), GetW());
}

void Mouse::SetPosition(const a2de::Vector4D& pos) {
    SetPosition(pos.GetX(), pos.GetY(), pos.GetZ(), pos.GetW());
}

const a2de::Vector4D& Mouse::GetMickeys4d() const {
    return _mickeys;
}

a2de::Vector4D& Mouse::GetMickeys4d() {
    return const_cast<a2de::Vector4D&>(static_cast<const Mouse&>(*this).GetMickeys4d());
}

a2de::Vector3D Mouse::GetMickeys3d() const {
    return Vector3D(_mickeys.GetX(), _mickeys.GetY(), _mickeys.GetZ());
}

a2de::Vector3D Mouse::GetMickeys3d() {
    return static_cast<const Mouse&>(*this).GetMickeys3d();
}

a2de::Vector2D Mouse::GetMickeys2d() const {
    return Vector2D(_mickeys.GetX(), _mickeys.GetY());
}

a2de::Vector2D Mouse::GetMickeys2d() {
    return static_cast<const Mouse&>(*this).GetMickeys2d();
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