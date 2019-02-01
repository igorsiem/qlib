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

        boost::wait_for_all(r1, r2, r3);

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

    // Verify behaviour of Boost 'wait_for_all'
    SECTION("verify wait_for_all behaviour")
    {
        using int_future_t = qlib::future<int>;
        std::vector<int_future_t> results;

        for (int i = 0; i < 100; i++)
        {
            results.emplace_back(tp.enqueue([i](void) { return i; }));
        }

        boost::wait_for_all(results.begin(), results.end());

        for (int i = 0; i < 100; i++)
            { REQUIRE(results[i].get() == i); }
    }   // end wait_for_all section

}   // end thread pool test
