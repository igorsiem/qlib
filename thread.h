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

#define BOOST_THREAD_PROVIDES_FUTURE
#include <boost/thread.hpp>

#ifndef _qlib_thread_h_included
#define _qlib_thread_h_included

namespace qlib {

/**
 * \brief The main qLib mutex type
 */
using shared_mutex = boost::shared_mutex;

/**
 * \brief A non-exclusive lock for reading a resource
 */
using write_lock = boost::unique_lock<shared_mutex>;

/**
 * \brief An exclusive lock for writing to a resource
 */
using read_lock = boost::shared_lock<shared_mutex>;

/**
 * \brief A standard (non-shared) mutex
 */
using mutex = boost::mutex;

/**
 * \brief A standard lock guard on a standard mutex
 */
using lock = boost::unique_lock<mutex>;

/**
 * \brief The condition variable type used by qLib
 */
using condition_variable = boost::condition_variable;

/**
 * \brief Asynchronous future type used by qLib
 *
 * \tparam The return type of the future (returned by the `get` method)
 */
template <typename R> using future = boost::future<R>;

/**
 * \brief Packaged task type used by qLib
 *
 * \tparam R The type of the task function
 *
 * \tparam Args The argument types for the task function
 */
template <typename R, typename... Args>
using packaged_task = boost::packaged_task<R, Args...>;

/**
 * \brief The thread type used by qLib
 */
using thread = boost::thread;

}   // end qlib namespace

#endif
