/**************************************************************************************************
// file:	Engine\Exceptions\CTypeNotSupportedException.cpp
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Implements the type not supported exception class
 **************************************************************************************************/
#include "CTypeNotSupportedException.h"
#include <algorithm>

A2DE_BEGIN

/// <summary> List of types of the type not supported exception supports </summary>
std::set<std::string> TypeNotSupportedException::_supportedTypes;

TypeNotSupportedException::TypeNotSupportedException(const std::string& name)
    : Exception("Type Not Supported"), _name(name) { }

TypeNotSupportedException::~TypeNotSupportedException() { }

std::string TypeNotSupportedException::Message() const {
    return Exception::Message() + ": " + _name;
}

void TypeNotSupportedException::RegisterFileType(const std::string& name) {
    std::string c_name = name;
    std::transform(c_name.begin(), c_name.end(), c_name.begin(), tolower);

    auto lb = _supportedTypes.lower_bound(c_name);
    _supportedTypes.insert(lb, c_name);
}

void TypeNotSupportedException::UnregisterFileType(const std::string& name) {
    std::string c_name = name;
    std::transform(c_name.begin(), c_name.end(), c_name.begin(), tolower);

    auto lb = _supportedTypes.lower_bound(c_name);
    if(lb != _supportedTypes.end()) {
        _supportedTypes.erase(lb);
    }
}

A2DE_END