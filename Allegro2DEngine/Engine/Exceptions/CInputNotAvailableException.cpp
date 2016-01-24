/**************************************************************************************************
// file:	Engine\Exceptions\CInputNotAvailableException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the input not available exception class
 **************************************************************************************************/
#include "CInputNotAvailableException.h"

A2DE_BEGIN

InputNotAvailableException::InputNotAvailableException(const std::string& inputType)
 : Exception("Input Not Available"), _input(inputType) { }

InputNotAvailableException::~InputNotAvailableException() { }

std::string InputNotAvailableException::Message() const {
    return _input + " " + Exception::Message();
}

A2DE_END