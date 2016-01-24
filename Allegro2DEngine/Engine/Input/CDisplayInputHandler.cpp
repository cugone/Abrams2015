#include "CDisplayInputHandler.h"

A2DE_BEGIN

bool DisplayInputHandler::HandleEvent(ALLEGRO_EVENT* ev) {
    if(ev == nullptr) return false;

    switch (ev->type) {

    case ALLEGRO_EVENT_DISPLAY_EXPOSE:
        return _displayexpose_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        return _displayresize_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return _displayclose_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_LOST:
        return _displaylost_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_FOUND:
        return _displayfound_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        return _displayswitchin_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        return _displayswitchout_event_callback(ev);
    case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
        return _displayorientation_event_callback(ev);
    default:
        return false;
    }

}

DisplayInputHandler::DisplayInputHandler() :
InputHandler(),
_displayexpose_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayresize_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayclose_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displaylost_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayfound_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayswitchin_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayswitchout_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; }),
_displayorientation_event_callback([](ALLEGRO_EVENT* /*ev*/) { return false; })
{ /* DO NOTHING */ }

DisplayInputHandler::~DisplayInputHandler() { /* DO NOTHING */ }

void DisplayInputHandler::SetDisplayExposeCallback(std::function<bool(ALLEGRO_EVENT*)> displayexpose_callback) {
    _displayexpose_event_callback = displayexpose_callback;
}

void DisplayInputHandler::SetDisplayResizeCallback(std::function<bool(ALLEGRO_EVENT*)> displayresize_callback) {
    _displayresize_event_callback = displayresize_callback;
}

void DisplayInputHandler::SetDisplayCloseCallback(std::function<bool(ALLEGRO_EVENT*)> displayclose_callback) {
    _displayclose_event_callback = displayclose_callback;
}

void DisplayInputHandler::SetDisplayLostCallback(std::function<bool(ALLEGRO_EVENT*)> displaylost_callback) {
    _displaylost_event_callback = displaylost_callback;
}

void DisplayInputHandler::SetDisplayFoundCallback(std::function<bool(ALLEGRO_EVENT*)> displayfound_callback) {
    _displayfound_event_callback = displayfound_callback;
}

void DisplayInputHandler::SetDisplaySwitchOutCallback(std::function<bool(ALLEGRO_EVENT*)> displayswitchout_callback) {
    _displayswitchout_event_callback = displayswitchout_callback;
}

void DisplayInputHandler::SetDisplaySwitchInCallback(std::function<bool(ALLEGRO_EVENT*)> displayswitchin_callback) {
    _displayswitchin_event_callback = displayswitchin_callback;
}

void DisplayInputHandler::SetDisplayOrientationCallback(std::function<bool(ALLEGRO_EVENT*)> displayorientation_callback) {
    _displayorientation_event_callback = displayorientation_callback;
}

void DisplayInputHandler::SetDisplayHaltDrawingCallback(std::function<bool(ALLEGRO_EVENT*)> displayhaltdrawing_callback) {
    _displayhaltdrawing_event_callback = displayhaltdrawing_callback;
}

void DisplayInputHandler::SetDisplayResumeDrawingCallback(std::function<bool(ALLEGRO_EVENT*)> displayresumedrawing_callback) {
    _displayresumedrawing_event_callback = displayresumedrawing_callback;
}

A2DE_END