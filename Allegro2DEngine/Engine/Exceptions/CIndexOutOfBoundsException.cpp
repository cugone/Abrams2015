/**************************************************************************************************
// file:	Engine\Exceptions\CIndexOutOfBoundsException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the index out of bounds exception class
 **************************************************************************************************/
#include "CIndexOutOfBoundsException.h"

A2DE_BEGIN

IndexOutOfBoundsException::IndexOutOfBoundsException(const std::string& argument, const std::string& lowerBound, const std::string& upperBound)
 : Exception("Index out of bounds"), _lower(lowerBound), _upper(upperBound), _argument(argument) { }

IndexOutOfBoundsException::~IndexOutOfBoundsException() { }

std::string IndexOutOfBoundsException::Message() const {
    return Exception::Message() + ": Argument '" + _argument + "' is not in the range [" + _lower + " " + _upper + ")";
}

A2DE_END