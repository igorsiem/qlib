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
    qlib::thread_pool tp;

    // verify regular parallel execution
    SECTION("parallel execution")
    {
        // Enqueue some tasks to be executed in parallel
        bool test_flag = false;
        auto r1 = tp.enqueue([&test_flag](void) { test_flag = true; });

        // task that returns a result
        auto r2 = tp.enqueue([](void) { return std::string("abc"); });

        // task that takes arguments, and returns a result
        auto my_fn = [](int a, int b) { return a+b; };
        auto r3 = tp.enqueue(my_fn, 2, 3);

        // All futures are valid
        REQUIRE(r1.valid());
        REQUIRE(r2.valid());
        REQUIRE(r3.valid());

        // Check the results from the futures we got before
        r1.get();
        REQUIRE(test_flag == true);
        REQUIRE(r2.get() == "abc");
        REQUIRE(r3.get() == 5);
    }   // end parallel execution section

    // Test exception handling in tasks
    SECTION("exceptions")
    {
        auto result = tp.enqueue([](void)
            {
                throw std::runtime_error("test");
            });

        REQUIRE(result.valid());
        REQUIRE_NOTHROW(result.wait());
        REQUIRE_THROWS_AS(result.get(), std::runtime_error);
    }

}   // end thread pool test
