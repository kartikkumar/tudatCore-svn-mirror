/*! \file utilityMacros.h
 *
 *    Path              : /Basics/
 *    Version           : 1
 *    Check status      : Unchecked
 *
 *    Author            : Simon Billemont
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : simon@angelcorp.be
 *
 *    Checker           : 
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : 
 *
 *    Date created      : 2 February, 2012
 *    Last modified     : 2 February, 2012
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2010-2011 Delft University of Technology.
 *
 *    This software is protected by national and international copyright.
 *    Any unauthorized use, reproduction or modification is unlawful and
 *    will be prosecuted. Commercial and non-private application of the
 *    software in any form is strictly prohibited unless otherwise granted
 *    by the authors.
 *
 *    The code is provided without any warranty; without even the implied
 *    warranty of merchantibility or fitness for a particular purpose.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      120202    S. Billemont      File created.
 */

//! Suppress compile time unused parameter warnings
/**
 * This macro suppresses the warning that a parameter passed to a function/method is not used, but
 * still passed in. This commonly occurs when overriding virtual methods.
 * 
 * Example:
 * int foo( int bar) {
 *     TUDAT_UNUSED_PARAMETER(bar);
 *     return -1;
 * }
 *
 * \param unusedParameter Parameter that is not being used in a function.
 */
#define TUDAT_UNUSED_PARAMETER( unusedParameter ) { ( void ) unusedParameter; }

//! Mark a declaration as deprecated
/**
 * When a declaration is marked as deprecated, it should be avoided, as most likely it performs 
 * something unwanted, superseded by another functionality or marked for removal in a future a 
 * release. The user should check where the deprecation warning comes from in order to get information
 * from the developer on how to resolve the warning. Commonly one should use another, recommended
 * function or alternative code block.
 *
 * Snippets:
 * TUDAT_DEPRECATED("Deprecated function!", void f() );
 * TUDAT_DEPRECATED("Deprecated type!",     typedef int my_int);
 * TUDAT_DEPRECATED("Deprecated variable!", int bar);
 *
 * Example:
 * //! Do something. 
 * // Depricated; use Foo::NewFunc(int, float) instead.
 * // \see Foo::NewFunc(int, float)
 * TUDAT_DEPRECATED("Depricated, you should use Foo::NewFunc(int, float) instead.", void OldFunc(int a, float b));
 *
 * //! Do something better
 * void NewFunc(int a, double b);
 *
 * \param message Warning message to show when compiling. One should mention "Deprecated", and why
 *                  the function was deprecated in a short one liner.
 * \param expression The expression which has to be deprecated.
 */
#ifdef __GNUC__
#define TUDAT_DEPRECATED(message, expression) expression __attribute__ ((deprecated(message)))
#elif defined(_MSC_VER)
#define TUDAT_DEPRECATED(message, expression) __declspec(deprecated(message)) expression
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define TUDAT_DEPRECATED(message, expression) expression
#endif