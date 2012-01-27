/*! \file unitTestBasicMathematicsFunctions.cpp
 *    Source file that executes the unit tests to test all basic mathematics functions contained in
 *    Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 9
 *    Check status      : Checked
 *
 *    Author            : B. Romgens
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : bart.romgens@gmail.com
 *
 *    Author/Checker    : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Date created      : 7 February, 2011
 *    Last modified     : 27 January, 2011
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
 *      110207    B. Romgens        File created.
 *      110215    K. Kumar          Minor modifications to layout, comments
 *                                  and variable-naming.
 *      110411    K. Kumar          Added unit test for
 *                                  convertCartesianToSpherical() function.
 *      110701    K. Kumar          Updated failing tests with relative errors.
 *      110708    K. Kumar          Added unit tests for computeSampleMean()
 *                                  and computeSampleVariance() functions.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      111111    K. Kumar          Strange error with convertCylindricalToCartesian function;
 *                                  achieved precision of results is less than machine precision,
 *                                  fixed by using slightly larger precision tolerance.
 *      120127    D. Dirkx          Moved unit conversions test to separate file; moved separate
 *                                  tests to separate functions; moved to Tudat core.
 *      120127    K. Kumar          Transferred unit tests over to Boost unit test framework.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/unit_test.hpp>
#include <cmath>
#include "Mathematics/basicMathematicsFunctions.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_basic_mathematics_functions )

//! Test if modulo function is working correctly.
BOOST_AUTO_TEST_CASE( testModuloFunction )
{
     // Using declarations.
     using std::fabs;
     using tudat::mathematics::computeModulo;

     // Test modulo function.
     // Test 1: Test 0.0 mod 0.0.
     BOOST_CHECK( fabs( computeModulo( 0.0, 0.0 ) - 0.0 )
                  < std::numeric_limits< double >::epsilon( ) );

     // Test 2: Test 2.0 mod 0.0.
     BOOST_CHECK( fabs( computeModulo( 2.0, 0.0 ) - 2.0 )
                  < std::numeric_limits< double >::epsilon( ) );

     // Test 3: Test 2.0 mod 2.0.
     BOOST_CHECK( fabs( computeModulo( 2.0, 2.0 ) - 0.0 )
                  < std::numeric_limits< double >::epsilon( ) );

     // Test 4: Test 3.0 mod 2.5.
     BOOST_CHECK( fabs( computeModulo( 3.0, 2.5 ) - 0.5 )
                  < std::numeric_limits< double >::epsilon( ) );

     // Test 5: Test 3.0 mod -2.5.
     BOOST_CHECK( fabs( computeModulo( 3.0, -2.5 ) + 2.0 )
                  < std::numeric_limits< double >::epsilon( ) );
 }

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.
