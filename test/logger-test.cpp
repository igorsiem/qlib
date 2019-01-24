/**
 * \file logger-test.cpp
 * Test logger class utilities
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <catch/catch.hpp>
#include "../logger.h"

// Simple test of the logger - note that logging can be observed in the
// output by un-commenting the calls to the `log` method
TEST_CASE("logger", "[unit]")
{

    REQUIRE_NOTHROW(qlib::logger::instance().set_for_console());

    // Un-comment these lines to output test log messages
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::error,
    //     L"a wide-string error");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::warning,
    //     L"a wide-string warning");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::info,
    //     L"wide-string information");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::debug,
    //     L"wide-string debugging");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::error,
    //     "a standard string error");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::warning,
    //     "a standard string warning");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::info,
    //     "standard string information");
    // qlib::logger::instance().log(
    //     qlib::logger::level_t::debug,
    //     "standard string debugging");

    REQUIRE_NOTHROW(qlib::logger::instance().clear());

}   // end strutils test
