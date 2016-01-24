/**************************************************************************************************
// file:	Engine\Games\ADTGame.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the Game abstract data type.
 **************************************************************************************************/
#ifndef A2DE_ADTGAME_H
#define A2DE_ADTGAME_H

#include <chrono>
#include <forward_list>
#include <memory>

#include <allegro5/events.h>

#include "../a2de_vals.h"
#include "../GFX/CGameWindow.h"
#include "../Time/CStopwatch.h"

A2DE_BEGIN

class InputHandler;
class KeyboardInputHandler;
class MouseInputHandler;
class JoystickInputHandler;
class DisplayInputHandler;

class Game {
public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="window">The window to attach to this game. !The game will take ownership of the pointer!</param>
     **************************************************************************************************/
    Game(std::unique_ptr<a2de::GameWindow> window);

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    virtual ~Game() = default;

    /**************************************************************************************************
     * <summary>Runs the game.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="argc">The argc parameter from main.</param>
     * <param name="argv">The argv parameter from main</param>
     **************************************************************************************************/
    void Run(int argc, char** argv);

    /**************************************************************************************************
     * <summary>Initialization phase method. A method to set up any variables, etc. before the main loop starts.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="argc">The argc parameter from main.</param>
     * <param name="argv">The argv parameter from main</param>
     * <returns>true if it successfully initializes, false if it does not.</returns>
     **************************************************************************************************/
    virtual bool Initialize(int argc, char** argv) = 0;

    /**************************************************************************************************
     * <summary>Processing phase method. This method is called as many times as needed per frame to keep the frame rate as close to the defined frame rate as
     * possible.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="gameTime"> The elapsed time of the game.</param>
     * <param name="deltaTime">The time between frames in seconds.</param>
     **************************************************************************************************/
    virtual void a2de::Game::Processing() = 0;

    /**************************************************************************************************
     * <summary>Rendering phase method. This method is called once per frame.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <param name="gameTime"> The elapsed time of the game.</param>
     * <param name="deltaTime">The time between frames in seconds.</param>
     **************************************************************************************************/
    virtual void a2de::Game::Render() = 0;

    /**************************************************************************************************
     * <summary>Clean up phase method. This method is called after the game loop to free up any memory. The user is responsible for deleting any
     * heap-allocated variables from Initialize here.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    virtual void CleanUp() = 0;

    /**************************************************************************************************
     * <summary>Key Down event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     * <remarks>This method defaults to handling KEY_ESCAPE events as quitting the game.</remarks>
     **************************************************************************************************/
    virtual bool KeyDown(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Key Up event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool KeyUp(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Key Char event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool KeyChar(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Axis event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseMove(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Button Down event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseButtonDown(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Button Up event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseButtonUp(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Warp event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseWarp(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Leave Display event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseLeave(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Mouse Enter Display event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool MouseEnter(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Joystick Axis event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool JoystickAxis(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Joystick Button Down event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool JoystickButtonDown(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Joystick Button Up event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">The event to process.</param>
     * <returns>true if the event was handled, false if it was not.</returns>
     **************************************************************************************************/
    virtual bool JoystickButtonUp(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Joystick Configuration event handler.</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     * <remarks>This method defaults to calling al_reconfigure_joysticks</remarks>
     **************************************************************************************************/
    virtual bool JoystickConfiguration(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays an expose described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayExpose(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a resize described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayResize(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a close described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayClose(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a lost described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayLost(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a found described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayFound(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a switch out described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplaySwitchOut(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a switch in described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplaySwitchIn(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays an orientation described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayOrientation(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a halt drawing described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayHaltDrawing(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Displays a resume drawing described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool DisplayResumeDrawing(ALLEGRO_EVENT* ev);

    /**************************************************************************************************
     * <summary>Gets the game window.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>null if it fails, else the window.</returns>
     **************************************************************************************************/
    a2de::GameWindow* const GetWindow() const;

    /**************************************************************************************************
     * <summary>Gets the game window.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>null if it fails, else the window.</returns>
     **************************************************************************************************/
    a2de::GameWindow* const GetWindow();

    /**************************************************************************************************
     * <summary>Quits the game.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     **************************************************************************************************/
    void Quit();

    /**************************************************************************************************
     * <summary>Query if the game is quitting.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>true if quitting, false if not.</returns>
     **************************************************************************************************/
    bool IsQuitting() const;

    /**************************************************************************************************
     * <summary>Query if the game is quitting.</summary>
     * <remarks>Casey Ugone, 1/3/2013.</remarks>
     * <returns>true if quitting, false if not.</returns>
     **************************************************************************************************/
    bool IsQuitting();

    /**************************************************************************************************
     * <summary>Gets delta time.</summary>
     * <remarks>Casey Ugone, 1/13/2016.</remarks>
     * <returns>The delta time.</returns>
     **************************************************************************************************/
    const std::chrono::duration<double>& GetDeltaTime() const;

    /**************************************************************************************************
     * <summary>Gets delta time.</summary>
     * <remarks>Casey Ugone, 1/13/2016.</remarks>
     * <returns>The delta time.</returns>
     **************************************************************************************************/
    std::chrono::duration<double>& GetDeltaTime();

    /**************************************************************************************************
     * <summary>Gets the KeyboardInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The keyboard input handler.</returns>
     **************************************************************************************************/
    const a2de::KeyboardInputHandler& GetKeyboardInputHandler() const;

    /**************************************************************************************************
     * <summary>Gets the KeyboardInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The keyboard input handler.</returns>
     **************************************************************************************************/
    a2de::KeyboardInputHandler& GetKeyboardInputHandler();

    /**************************************************************************************************
     * <summary>Gets the MouseInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The mouse input handler.</returns>
     **************************************************************************************************/
    const a2de::MouseInputHandler& GetMouseInputHandler() const;

    /**************************************************************************************************
     * <summary>Gets the MouseInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The mouse input handler.</returns>
     **************************************************************************************************/
    a2de::MouseInputHandler& GetMouseInputHandler();

    /**************************************************************************************************
     * <summary>Gets the JoystickInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The joystick input handler.</returns>
     **************************************************************************************************/
    const a2de::JoystickInputHandler& GetJoystickInputHandler() const;

    /**************************************************************************************************
     * <summary>Gets the JoystickInputHandler object</summary>
     * <remarks>Casey Ugone, 10/25/2014.</remarks>
     * <returns>The joystick input handler.</returns>
     **************************************************************************************************/
    a2de::JoystickInputHandler& GetJoystickInputHandler();

    const a2de::DisplayInputHandler& GetDisplayInputHandler() const;
    a2de::DisplayInputHandler& GetDisplayInputHandler();

protected:

private:

        /**************************************************************************************************
         * <summary>Main loop.</summary>
         * <remarks>Casey Ugone, 11/23/2013.</remarks>
         **************************************************************************************************/
        void MainLoop();

        /// <summary> The time between frames in seconds.</summary>
        std::chrono::duration<double> _FRAME_RATE;
        /// <summary> Maximum allowed time between frames </summary>
        std::chrono::duration<double> _MAX_FRAME_TIME;
        /// <summary> Time since the last frame.</summary>
        std::chrono::duration<double> _deltaTime;
        /// <summary> The game window </summary>
        std::unique_ptr<a2de::GameWindow> _gameWindow;
        /// <summary> true if is quitting </summary>
        bool _isQuitting;

        std::weak_ptr<a2de::InputHandler> _input_handler;

        ///<summary>The keyboard input handler.</summary>
        std::shared_ptr<a2de::KeyboardInputHandler> _keyboard_input_handler;

        ///<summary>The mouse input handler.</summary>
        std::shared_ptr<a2de::MouseInputHandler> _mouse_input_handler;

        ///<summary>The joystick input handler.</summary>
        std::shared_ptr<a2de::JoystickInputHandler> _joystick_input_handler;

        ///<summary>The display input handler.</summary>
        std::shared_ptr<a2de::DisplayInputHandler> _display_input_handler;

};

A2DE_END

#endif