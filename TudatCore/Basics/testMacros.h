/*    Copyright (c) 2010-2012, Delft University of Technology
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without modification, are
 *    permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of
 *        conditions and the following disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *      - Neither the name of the Delft University of Technology nor the names of its contributors
 *        may be used to endorse or promote products derived from this software without specific
 *        prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 *    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    Changelog
 *      YYMMDD    Author            Comment
 *      120202    S. Billemont      File created.
 *      120401    S. Billemont      Updated test macros to work with Boost 1.49 and 1.48.
 *
 *    References
 *
 */

#ifndef TUDAT_CORE_TEST_MACROS_H
#define TUDAT_CORE_TEST_MACROS_H

// Include Eigen for the matrix operations, format to generate a fancy error message and unit_test
// to delegate the actual tests to.
#include <Eigen/Core>

#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>

/************************************************************************/
/* INTERNAL MACROS (Not for use by general users, use with caution)     */
/************************************************************************/

//! Default message to display for matrix checks. If you define this, then that format will be used
#ifndef _TUDAT_CHECK_MATRIX_MESSAGE
#define _TUDAT_CHECK_MATRIX_MESSAGE                                                             \
    "Element [%d, %d] not within expected tolerance: expected %f, was %f, tolerance %f %s."
#endif

//! Creates error message used by TUDAT_CHECK_MATRIX_CLOSE and TUDAT_CHECK_MATRIX_CLOSE_FRACTION.
/*!
 * Creates an error message which displays row/col/left/right/tolerance and and additional string.
 */
#define _TUDAT_CHECK_MESSAGE( L, R, T, additionalString )                                       \
    boost::str( boost::format( _TUDAT_CHECK_MATRIX_MESSAGE )                                    \
            % row % col % L.coeff( row, col ) % R.coeff( row, col ) % T % additionalString )

//! This macro imports the correct boost namespace for percent_tolerance.
/*!
 * This macro imports the namespace where the boost function percent_tolerance resides. Because this
 * function has been moved around, it imports multiple locations. Since some don't exist in older 
 * boost versions, some must be created first.
 */
namespace boost { namespace math { namespace fpc { } } }
#define _TUDAT_USING_PERCENT_TOLERANCE                                                          \
    using namespace ::boost::math::fpc; using namespace ::boost::test_tools;

/************************************************************************/
/* GENERAL TESTING MACROS (use these macros to test your code)          */
/************************************************************************/

//! Base macro for various matrix tests.
/*!
 * This macro tests if both matrices are equal in size. If they are non-equal, an error is shown 
 * with the mismatching dimension. If they are equal, then this macro initiates a loop over each
 * Element in the matrix using counters 'row' and 'col'. The next statement after this macro is the
 * statement executed for each element.
 *
 * The row and col variables are declared, so only a single instance of the macro may exist in a 
 * single scope!
 *
 * Usage example:
 *   TUDAT_CHECK_MATRIX_BASE( matrix1, matrix2 )
 *      BOOST_CHECK_EQUAL(matrix1.coeff(row, col), matrix2.coeff(row, col));
 *   This will check all corresponding elements from the two matrices if they are equal.
 */
#define TUDAT_CHECK_MATRIX_BASE( L, R )                                                         \
    boost::test_tools::predicate_result equalRows =                                             \
        boost::test_tools::tt_detail::equal_impl( L.rows( ), R.rows( ) );                       \
    BOOST_CHECK_MESSAGE( equalRows, boost::str( boost::format(                                  \
        "Matrix number of rows not equal: %d != %d" ) % L.rows( ) % R.rows( ) ) );              \
    boost::test_tools::predicate_result equalCols =                                             \
        boost::test_tools::tt_detail::equal_impl( L.cols( ), R.cols( ) );                       \
    BOOST_CHECK_MESSAGE( equalCols, boost::str( boost::format(                                  \
        "Matrix number of columns not equal: %d != %d" ) % L.cols( ) % R.cols( ) ) );           \
    if ( equalRows.p_predicate_value && equalCols.p_predicate_value )                           \
        for ( signed int row = 0; row < L.rows( ); row++ )                                      \
        for ( signed int col = 0; col < L.cols( ); col++ )

//! Same as BOOST_CHECK_CLOSE, but operates on Eigen vectors/matrices.
/*!
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE(L, R, T).
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 */
#define TUDAT_CHECK_MATRIX_CLOSE( L, R, T ) {                                                   \
    _TUDAT_USING_PERCENT_TOLERANCE                                                              \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_CHECK_MESSAGE(                                                                    \
            ::boost::test_tools::check_is_close( L.coeff( row, col ), R.coeff( row, col ),      \
                percent_tolerance( T ) ).p_predicate_value,                                     \
            _TUDAT_CHECK_MESSAGE( L, R, T, "%" ) );                                             \
}

//! Same as BOOST_CHECK_CLOSE_FRACTION, but operates on Eigen vectors/matrices.
/*!
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE_FRACTION(L, R, T).
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 *
 * Note: the percent_tolerance( T * 100 ) is required because in some versions you need to pass an
 * fraction_tolerance struct and in others this struct does not exist. 
 */
#define TUDAT_CHECK_MATRIX_CLOSE_FRACTION( L, R, T ) {                                          \
    _TUDAT_USING_PERCENT_TOLERANCE                                                              \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_CHECK_MESSAGE(                                                                    \
            ::boost::test_tools::check_is_close( L.coeff( row, col ), R.coeff( row, col ),      \
                percent_tolerance( T * 100 ) ).p_predicate_value,                               \
            _TUDAT_CHECK_MESSAGE( L, R, T, "" ) );                                              \
}

#endif // TUDAT_CORE_TEST_MACROS_H
