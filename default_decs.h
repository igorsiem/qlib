/**
 * \file default_decs.h
 * Helpful macros for default declarations in classes
 * 
 * The macros in this file are short-cuts for declaring or disabling default
 * combinations of life-cycle (constructor and destructor) methods and copy /
 * move semantics.
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#ifndef _qlib_default_decs_h_included
#define _qlib_default_decs_h_included

/**
 * \brief Declare a default constructor for the given class name
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_CONSTRUCTOR( classname ) \
    classname(void) = default;

/**
 * \brief Disable the default constructor for the given class name
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_DEFAULT_CONSTRUCTOR( classname ) \
    classname(void) = delete;

/**
 * \brief Declare a default destructor for the given class name
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_DESTRUCTOR( classname ) \
    ~classname(void) = default;

/**
 * \brief Declare a default virtual constructor for the given class name
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR( classname ) \
    virtual ~classname(void) = default;

// Note, there is no DECLARE_NO_DEFAULT_DESTRUCTOR, because everything needs
// a destructor

/**
 * \brief Declare default life-cycle (constructor and destructor) methods
 * for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_LIFE_CYCLE( classname ) \
    DECLARE_DEFAULT_CONSTRUCTOR(classname) \
    DECLARE_DEFAULT_DESTRUCTOR(classname)

/**
 * \brief Declare default life-cycle (constructor and destructor) methods
 * for the given class with a virtual destructor
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_VIRTUAL_LIFE_CYCLE( classname ) \
    DECLARE_DEFAULT_CONSTRUCTOR(classname) \
    DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(classname)

/**
 * \brief Declare a default copy constructor for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_COPY_CONSTRUCTOR( classname ) \
    classname(const classname&) = default;

/**
 * \brief Disable the default copy constructor for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_COPY_CONSTRUCTOR( classname ) \
    classname(const classname&) = delete;

/**
 * \brief Declare a default assignment operator for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_ASSIGN_COPY( classname ) \
    classname& operator=(const classname&) = default;

/**
 * \brief Disable the default assignment operator for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_ASSIGN_COPY( classname ) \
    classname& operator=(const classname&) = delete;

/**
 * \brief Declare default copy semantics (copy constructor and assignment
 * operator) for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_COPY_SEMANTICS( classname ) \
    DECLARE_DEFAULT_COPY_CONSTRUCTOR(classname) \
    DECLARE_DEFAULT_ASSIGN_COPY(classname)

/**
 * \brief Disable copy semantics (copy constructor and assignment operator)
 * for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_COPY_SEMANTICS( classname ) \
    DECLARE_NO_COPY_CONSTRUCTOR(classname) \
    DECLARE_NO_ASSIGN_COPY(classname)

/**
 * \brief Declare the default move constructor for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_MOVE_CONSTRUCTOR( classname ) \
    classname(classname&&) noexcept = default;

/**
 * \brief Disable the default move constructor for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_MOVE_CONSTRUCTOR( classname ) \
    classname(classname&&) = delete;

/**
 * \brief Declare the default move assignment operator for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_MOVE_ASSIGN( classname ) \
    classname& operator=(classname&&) noexcept = default;

/**
 * \brief Disable the default move assignment operator for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_MOVE_ASSIGN( classname ) \
    classname& operator=(classname&&) = delete;

/**
 * \brief Declare default move semantics (move constructor and move
 * assignment) for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_MOVE_SEMANTICS( classname ) \
    DECLARE_DEFAULT_MOVE_CONSTRUCTOR(classname) \
    DECLARE_DEFAULT_MOVE_ASSIGN(classname)

/**
 * \brief Disable move semantics (move constructor and move assignment) for
 * the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_MOVE_SEMANTICS( classname ) \
    DECLARE_NO_MOVE_CONSTRUCTOR(classname) \
    DECLARE_NO_MOVE_ASSIGN(classname)

/**
 * \brief Declare default move and copy semantics (move and copy constructors
 * and move and copy assignment operators) for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_DEFAULT_MOVE_AND_COPY_SEMANTICS( classname ) \
    DECLARE_DEFAULT_COPY_SEMANTICS(classsname) \
    DECLARE_DEFAULT_MOVE_SEMANTICS(classname);

/**
 * \brief Declare move and copy semantics (move and copy constructors and
 * move and copy assignment operators) for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_MOVE_AND_COPY_SEMANTICS( classname ) \
    DECLARE_NO_COPY_SEMANTICS(classsname) \
    DECLARE_NO_MOVE_SEMANTICS(classname);

/**
 * \brief Declare default life cycle (constructor and destructor) and
 * move and copy semantics (move/copy constructors and move/copy assignment
 * operators) for the given class
 * 
 * \param classname The name of the class
 */
#define DECLARE_ALL_DEFAULTS( classname ) \
    DECLARE_DEFAULT_LIFE_CYCLE( classname ) \
    DECLARE_DEFAULT_MOVE_AND_COPY_SEMANTICS( classname )

/**
 * \brief Declare default life cycle (constructor and destructor) and
 * move and copy semantics (move/copy constructors and move/copy assignment
 * operators) for the given class, with a virtual destructor
 * 
 * \param classname The name of the class
 */
#define DECLARE_ALL_VIRTUAL_DEFAULTS( classname ) \
    DECLARE_DEFAULT_VIRTUAL_LIFE_CYCLE( classname ) \
    DECLARE_DEFAULT_MOVE_AND_COPY_SEMANTICS( classname )

/**
 * \brief Disable default constructor, and move and copy semantics (move/copy
 * constructors and move/copy assignment operators) for the given class
 * 
 * Note that the destructor cannot be disabled.
 * 
 * \param classname The name of the class
 */
#define DECLARE_NO_DEFAULTS( classname ) \
    DECLARE_NO_DEFAULT_CONSTRUCTOR( classname ) \
    DECLARE_NO_MOVE_AND_COPY_SEMANTICS( classname )

#endif
