/**
 * \file strutils.h
 * String-related utilities
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or
 * copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <string>
#include <codecvt>
#include <boost/lexical_cast.hpp>

#ifndef _qlib_strutils_h_included
#define _qlib_strutils_h_included

namespace boost {

/**
 * \brief Convert a wide string to a string, as an extension to Boost's
 * `lexical_cast` system
 * 
 * Usig [this simple fix](https://dbj.org/c17-codecvt-deprecated-panic/) for
 * the deprecation of the codecvt header that we were using before.
 * 
 * \param arg The wide string to convert
 * 
 * \return The  string string version of the wide string
 */
template<>
inline std::string lexical_cast(const std::wstring& arg)
{
    ///std::wstring_convert<deletable_facet<convert_type> > string_converter;
    ///return string_converter.to_bytes(arg);
    if (arg.empty()) return {};
    return { std::begin(arg), std::end(arg) };
}   // end lexical cast

/**
 * \brief Convert a string to a wide string, as an extension to Boost's
 * `lexical_cast` system
 * 
 * Usig [this simple fix](https://dbj.org/c17-codecvt-deprecated-panic/) for
 * the deprecation of the codecvt header that we were using before.
 * 
 * \param arg The string to convert
 * 
 * \return The wide string version of the string
 */
template<>
inline std::wstring lexical_cast(const std::string& arg)
{
    ///std::wstring_convert<deletable_facet<convert_type> > string_converter;
    ///return string_converter.from_bytes(arg);
    if (arg.empty()) return {};
    return { std::begin(arg), std::end(arg) };
}   // end lexical cast

}   // end boost namespace

#endif
