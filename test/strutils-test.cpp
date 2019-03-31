/**
 * \file strutils-test.cpp
 * Test string utilities
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <catch2/catch.hpp>
#include "../strutils.h"

// Verify extensions to `boost::lexical_cast` allowing conversion between
// `std::string` and `std::wstring`
TEST_CASE("strutils", "[unit]")
{
    using namespace boost;
    REQUIRE(lexical_cast<std::wstring>(std::string("abc")) == L"abc");
    REQUIRE(lexical_cast<std::string>(std::wstring(L"abc")) == "abc");
}   // end strutils test
