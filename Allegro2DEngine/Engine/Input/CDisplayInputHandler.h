#ifndef A2DE_CDISPLAYINPUTHANDLER_H
#define A2DE_CDISPLAYINPUTHANDLER_H

#include "../a2de_vals.h"
#include "CInputHandler.h"

#include <functional>

A2DE_BEGIN

class DisplayInputHandler : public a2de::InputHandler {
public:

    /**************************************************************************************************
     * <summary>Default constructor.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     **************************************************************************************************/
    DisplayInputHandler();

    /**************************************************************************************************
     * <summary>Destructor.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     **************************************************************************************************/
    virtual ~DisplayInputHandler();

    /**************************************************************************************************
     * <summary>Callback, called when the set display expose.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayexpose_callback">[in,out] If non-null, the displayexpose callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayExposeCallback(std::function<bool(ALLEGRO_EVENT*)> displayexpose_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display resize.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayresize_callback">[in,out] If non-null, the displayresize callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayResizeCallback(std::function<bool(ALLEGRO_EVENT*)> displayresize_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display close.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayclose_callback">[in,out] If non-null, the displayclose callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayCloseCallback(std::function<bool(ALLEGRO_EVENT*)> displayclose_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display lost.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displaylost_callback">[in,out] If non-null, the displaylost callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayLostCallback(std::function<bool(ALLEGRO_EVENT*)> displaylost_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display found.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayfound_callback">[in,out] If non-null, the displayfound callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayFoundCallback(std::function<bool(ALLEGRO_EVENT*)> displayfound_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display switch out.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayswitchout_callback">[in,out] If non-null, the displayswitchout callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplaySwitchOutCallback(std::function<bool(ALLEGRO_EVENT*)> displayswitchout_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display switch in.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayswitchin_callback">[in,out] If non-null, the displayswitchin callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplaySwitchInCallback(std::function<bool(ALLEGRO_EVENT*)> displayswitchin_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display orientation.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayorientation_callback">[in,out] If non-null, the displayorientation callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayOrientationCallback(std::function<bool(ALLEGRO_EVENT*)> displayorientation_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display halt drawing.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayhaltdrawing_callback">[in,out] If non-null, the displayhaltdrawing callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayHaltDrawingCallback(std::function<bool(ALLEGRO_EVENT*)> displayhaltdrawing_callback);

    /**************************************************************************************************
     * <summary>Callback, called when the set display resume drawing.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="displayresumedrawing_callback">[in,out] If non-null, the displayresumedrawing callback.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    void SetDisplayResumeDrawingCallback(std::function<bool(ALLEGRO_EVENT*)> displayresumedrawing_callback);

    /**************************************************************************************************
     * <summary>Handles the event described by ev.</summary>
     * <remarks>Casey Ugone, 1/7/2015.</remarks>
     * <param name="ev">[in,out] If non-null, the ev.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    virtual bool HandleEvent(ALLEGRO_EVENT* ev);

protected:
private:

    /**************************************************************************************************
     * <summary>The displayexpose event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayexpose_event_callback;

    /**************************************************************************************************
     * <summary>The displayresize event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayresize_event_callback;

    /**************************************************************************************************
     * <summary>The displayclose event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayclose_event_callback;

    /**************************************************************************************************
     * <summary>The displaylost event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displaylost_event_callback;

    /**************************************************************************************************
     * <summary>The displayfound event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayfound_event_callback;

    /**************************************************************************************************
     * <summary>The displayswitchout event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayswitchout_event_callback;

    /**************************************************************************************************
     * <summary>The displayswitchin event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayswitchin_event_callback;

    /**************************************************************************************************
     * <summary>The displayorientation event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayorientation_event_callback;

    /**************************************************************************************************
     * <summary>The displayhaltdrawing event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayhaltdrawing_event_callback;

    /**************************************************************************************************
     * <summary>The displayresumedrawing event callback.</summary>
     **************************************************************************************************/
    std::function<bool(ALLEGRO_EVENT*)> _displayresumedrawing_event_callback;
};

A2DE_END

#endif // CDISPLAYINPUTHANDLER_H
