/**
 * \file thread_pool-test.cpp
 * Test logger class utilities
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <catch/catch.hpp>
#include "../thread_pool.h"

// Some simple thread pool tests - queueing up several tasks of different
// types, and then checking the results
TEST_CASE("thread_pool", "[unit]")
{
    qlib::thread_pool pool;

    // Enqueue some tasks to be executed in parallel
    bool test_flag = false;
    auto r1 = pool.enqueue([&test_flag](void) { test_flag = true; });

    // task that returns a result
    auto r2 = pool.enqueue([](void) { return std::string("abc"); });

    // task that takes arguments, and returns a result
    auto r3 = pool.enqueue([](int a, int b) { return a+b; }, 2, 3);

    // Check the results from the futures we got before
    r1.get();
    REQUIRE(test_flag == true);
    REQUIRE(r2.get() == "abc");
    REQUIRE(r3.get() == 5);
}   // end thread pool test
