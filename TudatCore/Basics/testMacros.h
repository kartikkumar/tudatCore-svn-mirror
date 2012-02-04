/*! \file testMacros.h
 *
 *    Path              : /
 *    Version           : 1
 *    Check status      : Checked
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

#ifndef TUDAT_CORE_TESTMACROS_H
#define TUDAT_CORE_TESTMACROS_H

// Include Eigen for the matrix operations, format to generate a fancy error message and unit_test
// to delegate the actual tests to
#include <Eigen/Core>
#include <boost/version.hpp>
#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>

//! Base macro for various matrix tests.
/**
 * This macro tests if both matrices are equal in size. If they are non-equal, an error is shown 
 * with the mismatching dimension. If they are equal, then this macro initiates a loop over each
 * Element in the matrix using counters 'row' and 'col'. The next statement after this macro is the
 * statement executed for each element.
 *
 * Usage example:
 *   TUDAT_CHECK_MATRIX_BASE( matrix1, matrix2 )
 *      BOOST_CHECK_EQUAL(matrix1.coeff(row, col), matrix2.coeff(row, col));
 *   This will check all corresponding elements from the two matrices if they are equal.
 */
#define TUDAT_CHECK_MATRIX_BASE( L, R )                                                         \
    boost::test_tools::predicate_result equalRows =                                             \
        boost::test_tools::tt_detail::equal_impl(L.rows(), R.rows());                           \
    BOOST_CHECK_MESSAGE(equalRows, boost::str(boost::format(                                    \
        "Matrix number of rows not equal: %d != %d") % L.rows() % R.rows() ));                  \
    boost::test_tools::predicate_result equalCols =                                             \
        boost::test_tools::tt_detail::equal_impl(L.cols(), R.cols());                           \
    BOOST_CHECK_MESSAGE(equalCols, boost::str(boost::format(                                    \
        "Matrix number of columns not equal: %d != %d") % L.cols() % R.cols() ));               \
    if (equalRows.p_predicate_value && equalCols.p_predicate_value)                             \
        for (signed int row=0; row < L.rows(); row++ )                                          \
        for (signed int col=0; col < L.cols(); col++ )

//! Same as BOOST_CHECK_CLOSE, but operates on Eigen vectors/matrices
/**
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE(L, R, T)
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 */
#if (BOOST_VERSION && (BOOST_VERSION / 100 % 1000) >= 49)
#define TUDAT_CHECK_MATRIX_CLOSE( L, R, T ) {                                                   \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_TEST_TOOL_IMPL( 0, ::boost::test_tools::check_is_close, boost::str(boost::format( \
            "Element [%d, %d] not within expected tolerance: expected %f, was %f, tolerance[%%]")\
                % row % col % L.coeff(row, col) % R.coeff(row, col) ),                          \
            CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))                            \
            (::boost::math::fpc::percent_tolerance(T)), BOOST_PP_EMPTY() );                     \
}
#else
#define TUDAT_CHECK_MATRIX_CLOSE( L, R, T ) {                                                   \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_CHECK_WITH_ARGS_IMPL( ::boost::test_tools::check_is_close, boost::str(boost::format(\
            "Element [%d, %d] not within expected tolerance: expected %f, was %f, error[%%]")   \
                % row % col % L.coeff(row, col) % R.coeff(row, col) ),                          \
            CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))                            \
            (::boost::test_tools::percent_tolerance(T)) );                                      \
}
#endif

//! Same as BOOST_CHECK_CLOSE_FRACTION, but operates on Eigen vectors/matrices
/**
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE_FRACTION(L, R, T)
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 */
#if (BOOST_VERSION && (BOOST_VERSION / 100 % 1000) >= 49)
#define TUDAT_CHECK_MATRIX_CLOSE_FRACTION( L, R, T ) {                                          \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_TEST_TOOL_IMPL( 0, ::boost::test_tools::check_is_close, boost::str(boost::format( \
            "Element [%d, %d] not within expected tolerance: expected %f, was %f, tolerance")   \
                % row % col % L.coeff(row, col) % R.coeff(row, col) ),                          \
            CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))(T), BOOST_PP_EMPTY() );    \
}
#else
#define TUDAT_CHECK_MATRIX_CLOSE_FRACTION( L, R, T ) {                                          \
    TUDAT_CHECK_MATRIX_BASE( L, R )                                                             \
        BOOST_CHECK_WITH_ARGS_IMPL( ::boost::test_tools::check_is_close, boost::str(boost::format(\
            "Element [%d, %d] not within expected tolerance: expected %f, was %f, error")   \
                % row % col % L.coeff(row, col) % R.coeff(row, col) ),                          \
            CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))                            \
            (::boost::test_tools::fraction_tolerance(T)) );                                     \
}
#endif

#endif // TUDAT_CORE_TESTMACROS_H
