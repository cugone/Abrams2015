/**************************************************************************************************
// file:	Engine\GFX\CGameWindow.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the game Windows Form
 **************************************************************************************************/
#include "CGameWindow.h"

#include <allegro5/display.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_color.h>

#include "../a2de_exceptions.h"

#include <sstream>

A2DE_BEGIN

GameWindow::GameWindow() noexcept :
_display_flags(ALLEGRO_WINDOWED | ALLEGRO_DIRECT3D_INTERNAL),
_dimensions(640, 480),
_title(""),
_display(nullptr, al_destroy_display)
{ /* DO NOTHING */ }

GameWindow::GameWindow(int display_flags) noexcept :
_display_flags(display_flags),
_dimensions(640, 480),
_title(""),
_display(nullptr, al_destroy_display)
{ /* DO NOTHING */ }

GameWindow::GameWindow(int display_flags, int width, int height) noexcept :
_display_flags(display_flags),
_dimensions(width, height),
_title(""),
_display(nullptr, al_destroy_display)
{ /* DO NOTHING */ }

GameWindow::GameWindow(int display_flags, int width, int height, const std::string& title) noexcept :
_display_flags(display_flags),
_dimensions(width, height),
_title(title),
_display(nullptr, al_destroy_display)
{ /* DO NOTHING */ }

GameWindow::~GameWindow() noexcept {
    al_set_target_bitmap(nullptr);
}

bool GameWindow::IsWindowed() const noexcept {
    return (_display_flags & (ALLEGRO_WINDOWED | ALLEGRO_FULLSCREEN_WINDOW)) != 0;
}

int GameWindow::GetWidth() const noexcept {
    return _dimensions.first;
}
int GameWindow::GetWidth() noexcept {
    return static_cast<const GameWindow&>(*this).GetWidth();
}
int GameWindow::GetHeight() const noexcept {
    return _dimensions.second;
}
int GameWindow::GetHeight() noexcept {
    return static_cast<const GameWindow&>(*this).GetHeight();
}

/*************************************************************************************/
/* Trim function courtesy of GManNickG via http://stackoverflow.com/a/1798170/421178 */
/*************************************************************************************/
std::string trim(std::string& str, const std::string& whitespace = " \t") noexcept {
    const auto strBegin = str.find_first_not_of(whitespace);
    if(strBegin == std::string::npos) {
        return ""; // no content
    }

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

void GameWindow::ShowWindow() noexcept {
    //Trim extra space in user-supplied title.
    _title = trim(_title) + "   Created using the Abrams 2D Engine (c) Casey Ugone";

    //Trim extra space from copyright if trimmed user-supplied title is already empty.
    _title = trim(_title);

    al_set_new_display_flags(_display_flags);

    _display.reset(al_create_display(_dimensions.first, _dimensions.second));

    al_set_window_title(_display.get(), _title.c_str());
    al_set_target_bitmap(al_get_backbuffer(_display.get()));
}

void GameWindow::StartRender() noexcept {
    al_set_target_backbuffer(_display.get());
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GameWindow::EndRender() noexcept {
    al_flip_display();
}

const ALLEGRO_DISPLAY& GameWindow::GetDisplay() const noexcept {
    return *_display.get();
}

ALLEGRO_DISPLAY& GameWindow::GetDisplay() noexcept {
    return const_cast<ALLEGRO_DISPLAY&>(static_cast<const GameWindow&>(*this).GetDisplay());
}

A2DE_END