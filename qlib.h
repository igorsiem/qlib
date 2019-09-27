/**
 * \file qlib.h
 * Single-point include file for qLib
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include "default_decs.h"
#include "logger.h"
#include "strutils.h"
#include "thread.h"
#include "thread_pool.h"

/**
 * \mainpage Welcome to qLib
 * 
 * This is the documentation for *qLib*, a set of miscellaneous C++ utilities
 * written by Igor Siemienowicz (igor@qprise.com).
 * 
 * Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or
 * copy at https://www.boost.org/LICENSE_1_0.txt
 */

/**
 * \brief A namespace qLib-related declarations and functionality
 */
namespace qlib
{
    static const char* version = "0.1.4";
}   // end qlib namespace
