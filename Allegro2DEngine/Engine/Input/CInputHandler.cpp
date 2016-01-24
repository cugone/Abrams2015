#include "CInputHandler.h"

A2DE_BEGIN


InputHandler::InputHandler() : _next_handler() { /* DO NOTHING */ }

InputHandler::~InputHandler() { /* DO NOTHING */ }

void InputHandler::ProcessEvent(ALLEGRO_EVENT* ev) {
    if(ev == nullptr) return;

    if(this->HandleEvent(ev)) return;
    
    if(!_next_handler.expired()) _next_handler.lock()->ProcessEvent(ev);
}

void InputHandler::SetNext(std::weak_ptr<InputHandler> next_handler) {
    _next_handler.swap(next_handler);
}


A2DE_END