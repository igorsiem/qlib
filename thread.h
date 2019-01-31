/**
 * \file thread.h
 * Basic thread definitions for qLib
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <future>
#include <shared_mutex>

#ifndef _qlib_thread_h_included
#define _qlib_thread_h_included

namespace qlib {

/**
 * \brief The main qLib mutex type
 */
using shared_mutex = std::shared_mutex;

/**
 * \brief A non-exclusive lock for reading a resource
 */
using write_lock = std::unique_lock<shared_mutex>;

/**
 * \brief An exclusive lock for writing to a resource
 */
using read_lock = std::shared_lock<shared_mutex>;

/**
 * \brief A standard (non-shared) mutex
 */
using mutex = std::mutex;

/**
 * \brief A standard lock guard on a standard mutex
 */
using lock = std::unique_lock<mutex>;

/**
 * \brief The condition variable type used by qLib
 */
using condition_variable = std::condition_variable;

/**
 * \brief Asynchronous future type used by qLib
 *
 * \tparam The return type of the future (returned by the `get` method)
 */
template <typename T> using future = std::future<T>;

/**
 * \brief Packaged task type used by qLib
 *
 * \tparam R The type of the task function
 *
 * \tparam Args The argument types for the task function
 */
template <typename R, typename... Args>
using packaged_task = std::packaged_task<R, Args...>;

}   // end qlib namespace

#endif
