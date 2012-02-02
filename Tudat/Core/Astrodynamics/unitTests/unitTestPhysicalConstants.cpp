/*! \file unitTestPhysicalconstants.cpp
 *    This unit test will test the physical constants that are defined in physicalConstants.h.
 *
 *    Path              : /Astrodynamics/
 *    Version           : 7
 *    Check status      : Checked
 *
 *    Author            : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Checker           : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Date created      : 10 September, 2010
 *    Last modified     : 28 January, 2012
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
 *      100910    J. Melman         First creation of code.
 *      110111    J. Melman         Adapted to the offical Tudat standards.
 *      110124    J. Melman         Further adapted to the offical Tudat standards.
 *      110201    J. Melman         Made the tests for obliquity and astronomical unit more
 *                                  accurate.
 *      120127    D. Dirkx          Moved to Tudat core.
 *      120127    K. Kumar          Transferred unit tests over to Boost unit test framework.
 *      120128    K. Kumar          Changed BOOST_CHECK to BOOST_CHECK_CLOSE_FRACTION for unit test
 *                                  comparisons.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <limits>
#include "Astrodynamics/physicalConstants.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_physical_constants )

//! Test if the physical constants have the correct relations (ratios/offsets).
BOOST_AUTO_TEST_CASE( testRelationsBetweenPhysicalConstant )
{    
    // Test for the number of seconds in a year.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::JULIAN_YEAR,
                                tudat::physical_constants::JULIAN_DAY
                                * tudat::physical_constants::JULIAN_YEAR_IN_DAYS,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for the number of seconds in a year.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::SIDEREAL_YEAR,
                                tudat::physical_constants::JULIAN_DAY
                                * tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS,
                                std::numeric_limits< double >::epsilon( ) );
}

//! Test if physical constants have the expected value.
BOOST_AUTO_TEST_CASE( testOtherConstants )
{
    // Test for gravitational constant.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::GRAVITATIONAL_CONSTANT, 6.67259e-11,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for astronomical unit.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::SPEED_OF_LIGHT, 299792458.0,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for astronomical unit.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::ASTRONOMICAL_UNIT,
                                1.49597870691e11,
                                std::numeric_limits< double >::epsilon( ) );
}

//! Check if the time constants have the expected values.
BOOST_AUTO_TEST_CASE( testTimeConstants )
{
    // Test for the number of Julian days in a year.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::JULIAN_YEAR_IN_DAYS, 365.25,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for the number of sidereal days in a year.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS, 365.25636,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for the Julian day length.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::SIDEREAL_DAY, 86164.09054,
                                std::numeric_limits< double >::epsilon( ) );

    // Test for the sidereal day length.
    BOOST_CHECK_CLOSE_FRACTION( tudat::physical_constants::JULIAN_DAY, 86400.0,
                                std::numeric_limits< double >::epsilon( ) );
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.