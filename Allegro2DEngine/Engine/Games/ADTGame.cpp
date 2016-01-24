/**************************************************************************************************
// file:	Engine\Games\ADTGame.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the adt game class
 **************************************************************************************************/
#include "ADTGame.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>
#include <ratio>

#include "../a2de_exceptions.h"

#include <allegro5/display.h>
#include <allegro5/altime.h>
#include <allegro5/timer.h>
#include <allegro5/drawing.h>


#include "../Input/CInputHandler.h"
#include "../Input/CKeyboardInputHandler.h"
#include "../Input/CMouseInputHandler.h"
#include "../Input/CJoystickInputHandler.h"
#include "../Input/CDisplayInputHandler.h"

#include "../Input/CMouse.h"

A2DE_BEGIN

Game::Game(std::unique_ptr<a2de::GameWindow> window)
:
_FRAME_RATE(0.016666666),
_MAX_FRAME_TIME(2.0 * _FRAME_RATE),
_deltaTime(0.016666666),
_gameWindow(std::move(window)),
_isQuitting(false),
_input_handler(),
_keyboard_input_handler(nullptr),
_mouse_input_handler(nullptr),
_joystick_input_handler(nullptr),
_display_input_handler(nullptr)
{
        _gameWindow->ShowWindow();
        
        _keyboard_input_handler.reset( new a2de::KeyboardInputHandler());

        _mouse_input_handler.reset(
            new a2de::MouseInputHandler(
                std::make_unique<a2de::Mouse>(_gameWindow->GetDisplay())));

        _joystick_input_handler.reset(new a2de::JoystickInputHandler());

        _display_input_handler.reset(new a2de::DisplayInputHandler());

        _keyboard_input_handler->SetNext(_mouse_input_handler);
        _mouse_input_handler->SetNext(_joystick_input_handler);
        _joystick_input_handler->SetNext(_display_input_handler);
        _display_input_handler->SetNext(decltype(_input_handler)());

        _input_handler = _keyboard_input_handler;

}

const std::chrono::duration<double>& a2de::Game::GetDeltaTime() const {
        return _deltaTime;
}

std::chrono::duration<double>& a2de::Game::GetDeltaTime() {
    return const_cast<std::chrono::duration<double>&>(static_cast<const a2de::Game&>(*this).GetDeltaTime());
}

void a2de::Game::MainLoop() {


    ALLEGRO_EVENT_QUEUE* e = al_create_event_queue();
    al_register_event_source(e, al_get_keyboard_event_source());
    al_register_event_source(e, al_get_mouse_event_source());
    al_register_event_source(e, al_get_joystick_event_source());
    al_register_event_source(e, al_get_display_event_source(&GetWindow()->GetDisplay()));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    auto start_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto accumulator_start = std::chrono::high_resolution_clock::now();

    while(!_isQuitting) {
        _deltaTime = end_time - start_time;
        start_time = std::chrono::high_resolution_clock::now();

        this->GetKeyboardInputHandler().Update();

        ALLEGRO_EVENT ev;
        while(al_peek_next_event(e, &ev)) {
            _input_handler.lock()->ProcessEvent(&ev);
            al_drop_next_event(e);
        }

        while((std::chrono::high_resolution_clock::now() - accumulator_start).count() >= 16666666 /* 1/60 second in nanoseconds */ ) {
            if(!this->IsQuitting()) {
                this->Processing();
            }
            accumulator_start = std::chrono::high_resolution_clock::now();
        }

        if(!this->IsQuitting()) {
            this->GetWindow()->StartRender();
            this->Render();
            this->GetWindow()->EndRender();
        }

        end_time = std::chrono::high_resolution_clock::now();
    }

    al_unregister_event_source(e, al_get_keyboard_event_source());
    al_unregister_event_source(e, al_get_mouse_event_source());
    al_unregister_event_source(e, al_get_joystick_event_source());
    al_unregister_event_source(e, al_get_display_event_source(&GetWindow()->GetDisplay()));
}

void a2de::Game::Run(int argc, char** argv) {
    if(this->Initialize(argc, argv)) MainLoop();
    this->CleanUp();
}

bool a2de::Game::Initialize(int /*argc*/, char** /*argv*/) {

    //Keyboard input callbacks
    this->GetKeyboardInputHandler().SetKeyDownCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->KeyDown(ev);
    });
    this->GetKeyboardInputHandler().SetKeyCharCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->KeyChar(ev);
    });
    this->GetKeyboardInputHandler().SetKeyUpCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->KeyUp(ev);
    });

    //Mouse input callbacks
    this->GetMouseInputHandler().SetMouseMoveCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseMove(ev);
    });
    this->GetMouseInputHandler().SetMouseButtonDownCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseButtonDown(ev);
    });
    this->GetMouseInputHandler().SetMouseButtonUpCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseButtonUp(ev);
    });
    this->GetMouseInputHandler().SetMouseWarpCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseWarp(ev);
    });
    this->GetMouseInputHandler().SetMouseLeaveCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseLeave(ev);
    });
    this->GetMouseInputHandler().SetMouseEnterCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->MouseEnter(ev);
    });

    //Joystick input callbacks
    this->GetJoystickInputHandler().SetAxisCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->JoystickAxis(ev);
    });
    this->GetJoystickInputHandler().SetButtonDownCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->JoystickButtonDown(ev);
    });
    this->GetJoystickInputHandler().SetButtonUpCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->JoystickButtonUp(ev);
    });
    this->GetJoystickInputHandler().SetConfigurationCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->JoystickConfiguration(ev);
    });

    //Display input callbacks
    this->GetDisplayInputHandler().SetDisplayExposeCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayExpose(ev);
    });
    this->GetDisplayInputHandler().SetDisplayResizeCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayResize(ev);
    });
    this->GetDisplayInputHandler().SetDisplayCloseCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayClose(ev);
    });
    this->GetDisplayInputHandler().SetDisplayLostCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayLost(ev);
    });
    this->GetDisplayInputHandler().SetDisplayFoundCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayFound(ev);
    });
    this->GetDisplayInputHandler().SetDisplaySwitchOutCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplaySwitchOut(ev);
    });
    this->GetDisplayInputHandler().SetDisplaySwitchInCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplaySwitchIn(ev);
    });
    this->GetDisplayInputHandler().SetDisplayOrientationCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayOrientation(ev);
    });
    this->GetDisplayInputHandler().SetDisplayHaltDrawingCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayHaltDrawing(ev);
    });
    this->GetDisplayInputHandler().SetDisplayResumeDrawingCallback([this](ALLEGRO_EVENT* ev)->bool {
        return this->DisplayResumeDrawing(ev);
    });

    return true;
}

void a2de::Game::Processing() {

}

void a2de::Game::Render() {

}

void a2de::Game::CleanUp() {

}

a2de::GameWindow* const a2de::Game::GetWindow() const {
    return _gameWindow.get();
}

a2de::GameWindow* const a2de::Game::GetWindow() {
    return static_cast<const Game&>(*this).GetWindow();
}

bool a2de::Game::IsQuitting() const {
    return _isQuitting;
}

bool a2de::Game::IsQuitting() {
    return static_cast<const Game&>(*this).IsQuitting();
}

void a2de::Game::Quit() {
    _isQuitting = true;
}

const a2de::KeyboardInputHandler& a2de::Game::GetKeyboardInputHandler() const {
    return *_keyboard_input_handler;
}

a2de::KeyboardInputHandler& a2de::Game::GetKeyboardInputHandler() {
    return const_cast<KeyboardInputHandler&>(static_cast<const Game&>(*this).GetKeyboardInputHandler());
}

const a2de::JoystickInputHandler& a2de::Game::GetJoystickInputHandler() const {
    return *_joystick_input_handler;
}

a2de::JoystickInputHandler& a2de::Game::GetJoystickInputHandler() {
    return const_cast<JoystickInputHandler&>(static_cast<const Game&>(*this).GetJoystickInputHandler());
}

const a2de::MouseInputHandler& a2de::Game::GetMouseInputHandler() const {
    return *_mouse_input_handler;
}

a2de::MouseInputHandler& a2de::Game::GetMouseInputHandler() {
    return const_cast<MouseInputHandler&>(static_cast<const Game&>(*this).GetMouseInputHandler());
}

bool a2de::Game::KeyDown(ALLEGRO_EVENT* ev) {
    if(ev == nullptr) return false;
    if(ev->keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
        this->Quit();
        return true;
    }
    return false;
}

bool a2de::Game::KeyUp(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::KeyChar(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseMove(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseButtonDown(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseButtonUp(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseWarp(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseLeave(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::MouseEnter(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::JoystickAxis(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::JoystickButtonDown(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::JoystickButtonUp(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::JoystickConfiguration(ALLEGRO_EVENT* /*ev*/) {
    al_reconfigure_joysticks();
    return true;
}

bool a2de::Game::DisplayExpose(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayResize(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayClose(ALLEGRO_EVENT* ev) {
    if(ev->display.source == &this->_gameWindow->GetDisplay()) {
        this->Quit();
        return true;
    }
    return false;
}

bool a2de::Game::DisplayLost(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayFound(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplaySwitchOut(ALLEGRO_EVENT* ev) {
    return false;
}

bool a2de::Game::DisplaySwitchIn(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayOrientation(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayHaltDrawing(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

bool a2de::Game::DisplayResumeDrawing(ALLEGRO_EVENT* /*ev*/) {
    return false;
}

const a2de::DisplayInputHandler& a2de::Game::GetDisplayInputHandler() const {
    return *_display_input_handler;
}

a2de::DisplayInputHandler& a2de::Game::GetDisplayInputHandler() {
    return const_cast<a2de::DisplayInputHandler&>(static_cast<const a2de::Game&>(*this).GetDisplayInputHandler());
}

A2DE_END