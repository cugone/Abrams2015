/**************************************************************************************************
// file:	Engine\Exceptions\CBitmapLoadFailureException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the bitmap load failure exception class
 **************************************************************************************************/
#include "CBitmapLoadFailureException.h"

A2DE_BEGIN

BitmapLoadFailureException::BitmapLoadFailureException(const std::string& file)
 : Exception("Bitmap file: "), _file(file) { }

BitmapLoadFailureException::~BitmapLoadFailureException() { }

std::string BitmapLoadFailureException::Message() const {
    return Exception::Message() + " \'" + _file + "\' failed to load.";
}

A2DE_END