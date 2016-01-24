/**************************************************************************************************
// file:	Engine\Exceptions\CFileNotFoundException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the file not found exception class
 **************************************************************************************************/
#include "CFileNotFoundException.h"

A2DE_BEGIN

FileNotFoundException::FileNotFoundException(const std::string& file)
 : Exception("File Not Found"), _file(file) { }

FileNotFoundException::~FileNotFoundException() { }

std::string FileNotFoundException::Message() const {
    return Exception::Message() + ": " + _file;
}

A2DE_END