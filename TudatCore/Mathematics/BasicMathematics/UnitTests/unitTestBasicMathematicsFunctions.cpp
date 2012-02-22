/*    Copyright (c) 2010-2012 Delft University of Technology.
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
 *      110207    B. Romgens        File created.
 *      110215    K. Kumar          Minor modifications to layout, comments
 *                                  and variable-naming.
 *      110411    K. Kumar          Added unit test for
 *                                  convertCartesianToSpherical( ) function.
 *      110701    K. Kumar          Updated failing tests with relative errors.
 *      110708    K. Kumar          Added unit tests for computeSampleMean( )
 *                                  and computeSampleVariance( ) functions.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      111111    K. Kumar          Strange error with convertCylindricalToCartesian function;
 *                                  achieved precision of results is less than machine precision,
 *                                  fixed by using slightly larger precision tolerance.
 *      120217    D. Dirkx          Bootified unit tests.
 *      120217    K. Kumar          Updated computeModuloForSignedValues() to computeModulo().
 *
 *    References
 *
 */

#define BOOST_TEST_MAIN

#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <limits>
#include "TudatCore/Mathematics/BasicMathematics/basicMathematicsFunctions.h"

namespace tudat
{
namespace unit_tests
{

using mathematics::computeModulo;

BOOST_AUTO_TEST_SUITE( test_BasicMathematics )

//! Test if tudat modulo function is working.
BOOST_AUTO_TEST_CASE( testComputeModulo )
{
    // Test modulo function.
    // Test 1: Test 2.0 mod 2.0.
    // Test 2: Test 3.0 mod 2.5.
    // Test 3: Test 3.0 mod -2.5.
    // Test 4: Test -3.0 mod -2.5.
    // Test 5: Test -3.0 mod 2.5.

    double machinePrecision = std::numeric_limits< double >::epsilon( );

    double resultUsingModuloFunction = computeModulo( 2.0, 2.0 );
    BOOST_CHECK_CLOSE_FRACTION( resultUsingModuloFunction, 0.0 , machinePrecision );

    resultUsingModuloFunction = computeModulo( 3.0, 2.5 );
    BOOST_CHECK_CLOSE_FRACTION( resultUsingModuloFunction, 0.5 , machinePrecision );

    resultUsingModuloFunction = computeModulo( 3.0, -2.5 );
    BOOST_CHECK_CLOSE_FRACTION( resultUsingModuloFunction, -2.0 , machinePrecision );

    resultUsingModuloFunction = computeModulo( -3.0, -2.5 );
    BOOST_CHECK_CLOSE_FRACTION( resultUsingModuloFunction, -0.5 , machinePrecision );

    resultUsingModuloFunction = computeModulo( -3.0, 2.5 );
    BOOST_CHECK_CLOSE_FRACTION( resultUsingModuloFunction, 2.0 , machinePrecision );
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests
} // namespace tudat
