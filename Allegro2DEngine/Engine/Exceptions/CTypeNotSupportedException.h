/**************************************************************************************************
// file:	Engine\Exceptions\CTypeNotSupportedException.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the type not supported exception class
 **************************************************************************************************/
#ifndef A2DE_CTYPENOTSUPPORTEDEXCEPTION_H
#define A2DE_CTYPENOTSUPPORTEDEXCEPTION_H

#include "../a2de_vals.h"
#include "CException.h"
#include <string>
#include <set>

A2DE_BEGIN

/**************************************************************************************************
 * <summary>Exception for signaling type not supported errors.</summary>
 * <remarks>Casey Ugone, 7/30/2011.</remarks>
 * <seealso cref="Exception"/>
 **************************************************************************************************/
class TypeNotSupportedException : public Exception {
public:

    /**************************************************************************************************
     * <summary>Initializes a new instance of the TypeNotSupportedException class.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <param name="name">The name of the type (file extension).</param>
     **************************************************************************************************/
    explicit TypeNotSupportedException(const std::string& name);

    /**************************************************************************************************
     * <summary>Destructor</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     **************************************************************************************************/
    virtual ~TypeNotSupportedException();

    /**************************************************************************************************
     * <summary>Gets the message of the exception.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <returns>The message returned by the exception.</returns>
     **************************************************************************************************/
    virtual std::string Message() const;

    /**************************************************************************************************
     * <summary>Registers the file type to the set of supported types.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <param name="name">The name of the type.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    static void RegisterFileType(const std::string& name);

    /**************************************************************************************************
     * <summary>Unregisters the file type to the set of supported types.</summary>
     * <remarks>Casey Ugone, 7/30/2011.</remarks>
     * <param name="name">The name of the type.</param>
     * <returns>true if it succeeds, false if it fails.</returns>
     **************************************************************************************************/
    static void UnregisterFileType(const std::string& name);
protected:
private:
    /// <summary> The file type name </summary>
    std::string _name;
    /// <summary> Collection of supported types </summary>
    static std::set<std::string> _supportedTypes;
};

A2DE_END

#endif