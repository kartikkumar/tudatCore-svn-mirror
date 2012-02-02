/*! \file testMacros.cpp
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

// Include Eigen for the matrix operations, format to generate a fancy error message and unit_test
// to delegate the actual tests to
#include <Eigen/Core>
#include <boost/format.hpp>
#include <boost/test/unit_test.hpp>

//! Same as BOOST_CHECK_CLOSE, but operates on Eigen vectors/matrices
/**
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE(L, R, T)
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 */
#define TUDAT_CHECK_MATRIX_CLOSE( L, R, T ) {                                                   \
    using namespace boost::test_tools;                                                          \
    predicate_result equalRows = tt_detail::equal_impl(L.rows(), R.rows());                     \
    BOOST_CHECK_MESSAGE(equalRows, boost::str(boost::format(                                    \
        "Matrix number of rows not equal: %d != %d") % L.rows() % R.rows() ));                  \
    predicate_result equalCols = tt_detail::equal_impl(L.cols(), R.cols());                     \
    BOOST_CHECK_MESSAGE(equalCols, boost::str(boost::format(                                    \
        "Matrix number of columns not equal: %d != %d") % L.cols() % R.cols() ));               \
    if (equalRows.p_predicate_value && equalCols.p_predicate_value)                             \
        for (signed int row=0; row < L.rows(); row++ )                                          \
        for (signed int col=0; col < L.cols(); col++ )                                          \
            BOOST_TEST_TOOL_IMPL( 0, ::boost::test_tools::check_is_close, boost::str(boost::format(\
                "Element [%d, %d] not within expected tolerance: expected %e, was %e, tolerance ")\
                    % row % col % L.coeff(row, col) % R.coeff(row, col) ),                      \
                CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))                        \
                (::boost::math::fpc::percent_tolerance(T)), BOOST_PP_EMPTY() );                 \
}

//! Same as BOOST_CHECK_CLOSE_FRACTION, but operates on Eigen vectors/matrices
/**
 * Checks for an equal amount of rows/columns and if each element falls with the passed tolerance
 * The actual comparison is done element wise using BOOST_CHECK_CLOSE_FRACTION(L, R, T)
 * \see http://www.boost.org/libs/test/doc/html/utf/testing-tools/reference.html
 */
#define TUDAT_CHECK_MATRIX_CLOSE_FRACTION( L, R, T ) {                                          \
    using namespace boost::test_tools;                                                          \
    predicate_result equalRows = tt_detail::equal_impl(L.rows(), R.rows());                     \
    BOOST_CHECK_MESSAGE(equalRows, boost::str(boost::format(                                    \
        "Matrix number of rows not equal: %d != %d") % L.rows() % R.rows() ));                  \
    predicate_result equalCols = tt_detail::equal_impl(L.cols(), R.cols());                     \
    BOOST_CHECK_MESSAGE(equalCols, boost::str(boost::format(                                    \
        "Matrix number of columns not equal: %d != %d") % L.cols() % R.cols() ));               \
    if (equalRows.p_predicate_value && equalCols.p_predicate_value)                             \
        for (signed int row=0; row < L.rows(); row++ )                                          \
        for (signed int col=0; col < L.cols(); col++ )                                          \
            BOOST_TEST_TOOL_IMPL( 0, ::boost::test_tools::check_is_close, boost::str(boost::format(\
                "Element [%d, %d] not within expected tolerance: expected %e, was %e, tolerance ")\
                    % row % col % L.coeff(row, col) % R.coeff(row, col) ),                      \
                CHECK, CHECK_MSG, (L.coeff(row, col))(R.coeff(row, col))                        \
                (::boost::math::fpc::percent_tolerance(T)), BOOST_PP_EMPTY() );                 \
}