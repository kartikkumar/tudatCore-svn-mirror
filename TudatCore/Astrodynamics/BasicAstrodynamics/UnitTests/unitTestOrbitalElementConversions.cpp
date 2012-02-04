/*! \file unitTestOrbitalElementConversions.cpp
 *    The source file that contains the unit tests to test conversion of Keplerian elements to
 *    Cartesian elements and vice-versa, and various other orbital element conversion functions.
 *
 *    Path              : /Astrodynamics/States/
 *    Version           : 15
 *    Check status      : Unchecked
 *
 *    Author            : E. Iorfida
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : elisabetta_iorfida@yahoo.it
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Checker           : B. Tong Minh
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : B.TongMinh@student.tudelft.nl
 *
 *    Date created      : 3 December, 2010
 *    Last modified     : 3 February, 2012
 *
 *    References
 *      NASA, Goddard Spaceflight Center. Orbit Determination Toolbox (ODTBX), NASA - GSFC Open
 *          Source Software, http://opensource.gsfc.nasa.gov/projects/ODTBX/, last accessed:
 *          31st January, 2012.
 *      Fortescue, P. W., et al. Spacecraft systems engineering, Third Edition,
 *          Wiley, England, 2003.
 *      Vallado, D. A., McClain, W. D. Fundamentals of astrodynamics and applications, 2nd Edition,
 *          Kluwer Academic Publishers, The Netherlands, 2004.
 *      Harvard. Minor Planet Center.
 *          http://scully.cfa.harvard.edu/cgi-bin/returnprepeph.cgi?d=d&o=02060, last accessed:
 *          1st February, 2012.
 *      Wikipedia. Geostationary orbit, http://en.wikipedia.org/wiki/Geostationary_orbit, last
 *      accessed: 1st February, 2012, last modified: 29th January, 2012.
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
 *      101203    E. Iorfida        First creation of the code.
 *      101208    E. Iorfida        Fulfillment of the code with the elliptical case.
 *      101208    E. Iorfida        Modified punctuation.
 *      101215    E. Iorfida        Added tolerance, added parabolic, circular and hyperbolic
 *                                  cases.
 *      101217    E. Iorfida        Added computeAbsoluteValue( ) in the errors computation,
 *                                  modified punctuation.
 *      101219    J. Melman         Put gravitational parameters in one place, changed first right
 *                                  ascension to 15.0 * pi / 8.0, thereby exposing a possible
 *                                  error.
 *      110107    E. Iorfida        orbitalConversionBookExampleUnitTest.test added to this file,
 *                                  to have a unique unit test file for the conversion code. Also
 *                                  some punctuation modifications have been made.
 *      110109    J. Melman         Included test for semi-latus rectum of circular case. Gave the
 *                                  orbital angles less trivial values, and not almost exclusively
 *                                  in the first quadrant.
 *      110111    E. Iorfida        Updated to the new format of unitTest file and added hyperbolic
 *                                  equatorial case.
 *      110204    K. Kumar          Removed "vector" from naming.
 *      110216    K. Kumar          Added unit tests for new orbital element conversion functions.
 *      110310    K. Kumar          Changed right ascension of ascending node to longitude of
 *                                  ascending node.
 *      110510    K. Kumar          Updated to use new orbital element conversion functions and
 *                                  removed dynamic memory allocation.
 *      120131    K. Kumar          Revamped to use the Boost unit test framework. Unit tests
 *                                  now test Kepler <-> Cartesian element conversions individually.
 *                                  Only these two conversions are tested for Tudat Core. Unit
 *                                  tests use ODTBX as benchmark.
 *      120201    K. Kumar          Added unit tests for conversions transferred to Tudat Core.
 *      120203    K. Kumar          Changed orbital element defines to enum.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>
#include <Eigen/Core>
#include <limits>
#include "TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h"
#include "TudatCore/Basics/testMacros.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_orbital_element_conversions )

// Test if conversion from Keplerian elements to Cartesian elements is working correctly.
BOOST_AUTO_TEST_CASE( testKeplerianToCartesianElementConversion )
{
    // Case 1: Elliptical orbit around the Earth.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Set Earth gravitational parameter [m^3/s^2] .
        double earthGravitationalParameter = 3.986004415e14;

        // Set Keplerian elements [m,-,rad,rad,rad,rad].
        Eigen::VectorXd keplerianElements( 6 );
        keplerianElements( semiMajorAxisIndex ) = 8000.0 * 1000.0;
        keplerianElements( eccentricityIndex ) = 0.23;
        keplerianElements( inclinationIndex ) = 20.6 / 180.0 * M_PI;
        keplerianElements( argumentOfPeriapsisIndex ) = 274.78 / 180.0 * M_PI;
        keplerianElements( rightAscensionOfAscendingNodeIndex ) = 108.77 / 180.0 * M_PI;
        keplerianElements( trueAnomalyIndex ) = 46.11 / 180.0 * M_PI;

        // Set expected Cartesian elements [m,m,m,m/s,m/s,m/s].
        Eigen::VectorXd expectedCartesianElements( 6 );
        expectedCartesianElements( xPositionIndex ) = 2.021874804243437e6;
        expectedCartesianElements( yPositionIndex ) = 6.042523817035284e6;
        expectedCartesianElements( zPositionIndex ) = -1.450371183512575e6;
        expectedCartesianElements( xVelocityIndex ) = -7.118283509842652e3;
        expectedCartesianElements( yVelocityIndex ) = 4.169050171542199e3;
        expectedCartesianElements( zVelocityIndex ) = 2.029066072016241e3;

        // Compute Cartesian elements.
        Eigen::VectorXd computedCartesianElements( 6 );
        computedCartesianElements = tudat::orbital_element_conversions::
                convertKeplerianToCartesianElements( keplerianElements,
                                                     earthGravitationalParameter );

        // Check if computed Cartesian elements match the expected values.
        TUDAT_CHECK_MATRIX_CLOSE_FRACTION( expectedCartesianElements,
                                           computedCartesianElements, 1.0e-15 );
    }

    // Case 2: Equatorial, circular orbit around Mars.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Set Mars gravitational parameter [m^3/s^2].
        double marsGravitationalParameter = 4.2828018915e13;

        // Set Keplerian elements [m,-,rad,rad,rad,rad].
        Eigen::VectorXd keplerianElements( 6 );
        keplerianElements( semiMajorAxisIndex ) = 9201.61 * 1000.0;
        keplerianElements( eccentricityIndex ) = 0.0;
        keplerianElements( inclinationIndex ) = 0.0;
        keplerianElements( argumentOfPeriapsisIndex ) = 12.54 / 180.0 * M_PI;
        keplerianElements( rightAscensionOfAscendingNodeIndex ) = 201.55 / 180.0 * M_PI;
        keplerianElements( trueAnomalyIndex ) = -244.09 / 180.0 * M_PI;

        // Set expected Cartesian elements [m,m,m,m/s,m/s,m/s].
        Eigen::VectorXd expectedCartesianElements( 6 );
        expectedCartesianElements( xPositionIndex ) = 7.968828015716932e6;
        expectedCartesianElements( yPositionIndex ) = -4.600804999999997e6;
        expectedCartesianElements( zPositionIndex ) = 0.0;
        expectedCartesianElements( xVelocityIndex ) = 1.078703495685965e3;
        expectedCartesianElements( yVelocityIndex ) = 1.868369260830248e3;
        expectedCartesianElements( zVelocityIndex ) = 0.0;

        // Compute Cartesian elements.
        Eigen::VectorXd computedCartesianElements( 6 );
        computedCartesianElements = tudat::orbital_element_conversions::
                convertKeplerianToCartesianElements( keplerianElements,
                                                     marsGravitationalParameter );

        // Check if computed Cartesian elements match the expected values.
        TUDAT_CHECK_MATRIX_CLOSE_FRACTION( expectedCartesianElements,
                                           computedCartesianElements, 1.0e-15 );
    }

    // Case 3: Hyperbolic orbit around the Sun.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Set Sun gravitational parameter [m^3/s^2].
        double sunGravitationalParameter = 1.32712440018e20;

        // Set Keplerian elements [m,-,rad,rad,rad,rad].
        Eigen::VectorXd keplerianElements( 6 );
        keplerianElements( semiMajorAxisIndex ) = -4.5e11;
        keplerianElements( eccentricityIndex ) = 2.3;
        keplerianElements( inclinationIndex ) = 25.5 / 180.0 * M_PI;
        keplerianElements( argumentOfPeriapsisIndex ) = 156.11 / 180.0 * M_PI;
        keplerianElements( rightAscensionOfAscendingNodeIndex ) = -215.03 / 180.0 * M_PI;
        keplerianElements( trueAnomalyIndex ) = 123.29 / 180.0 * M_PI;

        // Set expected Cartesian elements [m,m,m,m/s,m/s,m/s].
        Eigen::VectorXd expectedCartesianElements( 6 );
        expectedCartesianElements( xPositionIndex ) = -2.776328224174438e12;
        expectedCartesianElements( yPositionIndex ) = -6.053823869632723e12;
        expectedCartesianElements( zPositionIndex ) = 3.124576293512172e12;
        expectedCartesianElements( xVelocityIndex ) = 7.957674684798018e3;
        expectedCartesianElements( yVelocityIndex ) = 1.214817382001788e4;
        expectedCartesianElements( zVelocityIndex ) = -6.923442392618828e3;

        // Compute Cartesian elements.
        Eigen::VectorXd computedCartesianElements( 6 );
        computedCartesianElements = tudat::orbital_element_conversions::
                convertKeplerianToCartesianElements( keplerianElements,
                                                     sunGravitationalParameter );

        // Check if computed Cartesian elements match the expected values.
        TUDAT_CHECK_MATRIX_CLOSE_FRACTION( expectedCartesianElements,
                                           computedCartesianElements, 1.0e-15 );
    }
}

// Test if conversion from Cartesian elements to Keplerian elements is working correctly.
BOOST_AUTO_TEST_CASE( testCartesianToKeplerianElementConversion )
{
    // Case 1: Elliptical orbit around the Earth.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Earth gravitational parameter.
        double earthGravitationalParameter = 3.986004415e14;

        // Set Cartesian elements.
        Eigen::VectorXd cartesianElements( 6 );
        cartesianElements( xPositionIndex ) = 3.75e6;
        cartesianElements( yPositionIndex ) = 4.24e6;
        cartesianElements( zPositionIndex ) = -1.39e6;
        cartesianElements( xVelocityIndex ) = -4.65e3;
        cartesianElements( yVelocityIndex ) = -2.21e3;
        cartesianElements( zVelocityIndex ) = 1.66e3;

        // Set expected Keplerian elements.
        Eigen::VectorXd expectedKeplerianElements( 6 );
        expectedKeplerianElements( semiMajorAxisIndex ) = 3.707478199246163e6;
        expectedKeplerianElements( eccentricityIndex ) = 0.949175203660321;
        expectedKeplerianElements( inclinationIndex ) = 0.334622356632438;
        expectedKeplerianElements( argumentOfPeriapsisIndex ) = 2.168430616511167;
        expectedKeplerianElements( rightAscensionOfAscendingNodeIndex ) = 1.630852596545341;
        expectedKeplerianElements( trueAnomalyIndex ) = 3.302032232567084;

        // Compute Keplerian elements.
        Eigen::VectorXd computedKeplerianElements( 6 );
        computedKeplerianElements = tudat::orbital_element_conversions::
                convertCartesianToKeplerianElements( cartesianElements,
                                                     earthGravitationalParameter );

        // Check if computed Keplerian elements match the expected values.
        TUDAT_CHECK_MATRIX_CLOSE_FRACTION( expectedKeplerianElements,
                                           computedKeplerianElements, 1.0e-14 );
    }

    // Case 2: Equatorial, circular orbit around Venus.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Venus gravitational parameter.
        double venusGravitationalParameter = 3.2485504415e14;

        // Set Cartesian elements.
        Eigen::VectorXd cartesianElements( 6 );
        cartesianElements( xPositionIndex ) = 5.580537430785387e6;
        cartesianElements( yPositionIndex ) = 2.816487703435473e6;
        cartesianElements( zPositionIndex ) = 0.0;
        cartesianElements( xVelocityIndex ) = -3.248092722413634e3;
        cartesianElements( yVelocityIndex ) = 6.435711753323540e3;
        cartesianElements( zVelocityIndex ) = 0.0;

        // Set expected Keplerian elements.
        Eigen::VectorXd expectedKeplerianElements( 6 );
        expectedKeplerianElements( semiMajorAxisIndex ) = 6.251e6;
        expectedKeplerianElements( eccentricityIndex ) = 0.0;
        expectedKeplerianElements( inclinationIndex ) = 0.0;
        expectedKeplerianElements( argumentOfPeriapsisIndex ) = 0.0;
        expectedKeplerianElements( rightAscensionOfAscendingNodeIndex ) = 0.0;
        expectedKeplerianElements( trueAnomalyIndex ) = 26.78 / 180.0 * M_PI;

        // Declare and compute converted Keplerian elements.
        Eigen::VectorXd computedKeplerianElements( 6 );
        computedKeplerianElements = tudat::orbital_element_conversions::
                convertCartesianToKeplerianElements( cartesianElements,
                                                     venusGravitationalParameter );

        // Check if computed semi-major axis matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedKeplerianElements( semiMajorAxisIndex ),
                                    computedKeplerianElements( semiMajorAxisIndex ), 1.0e-15 );

        // Check if computed eccentricity matches the expected value.
        BOOST_CHECK_SMALL( computedKeplerianElements( eccentricityIndex ),
                           std::numeric_limits< double >::epsilon( ) );

        // Check if computed inclination matches the expected value.
        BOOST_CHECK_SMALL( computedKeplerianElements( inclinationIndex ),
                           std::numeric_limits< double >::epsilon( ) );

        // Check if computed argument of periapsis matches the expected value.
        BOOST_CHECK_SMALL( computedKeplerianElements( argumentOfPeriapsisIndex ),
                           std::numeric_limits< double >::epsilon( ) );

        // Check if computed right ascension of ascending node matches the expected value.
        BOOST_CHECK_SMALL( computedKeplerianElements( rightAscensionOfAscendingNodeIndex ),
                           std::numeric_limits< double >::epsilon( ) );

        // Check if computed true anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedKeplerianElements( trueAnomalyIndex ),
                                    computedKeplerianElements( trueAnomalyIndex ), 1.0e-15 );
    }

    // Case 3: Hyperbolic orbit around the Sun.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Using declarations.
        using namespace tudat::orbital_element_conversions;

        // Sun gravitational parameter.
        double sunGravitationalParameter = 1.32712440018e20;

        // Declare and set Cartesian elements.
        Eigen::VectorXd cartesianElements( 6 );
        cartesianElements( xPositionIndex ) = 7.035635643405699e11;
        cartesianElements( yPositionIndex ) = -2.351218213055550e11;
        cartesianElements( zPositionIndex ) = 0.037960971564309e11;
        cartesianElements( xVelocityIndex ) = -1.731375459746510e4;
        cartesianElements( yVelocityIndex ) = -1.535713656317794e4;
        cartesianElements( zVelocityIndex ) = 0.423498718768347e4;

        // Set expected Keplerian elements.
        Eigen::VectorXd expectedKeplerianElements( 6 );
        expectedKeplerianElements( semiMajorAxisIndex ) = -6.78e11;
        expectedKeplerianElements( eccentricityIndex ) = 1.89;
        expectedKeplerianElements( inclinationIndex ) = 167.91 / 180 * M_PI;
        expectedKeplerianElements( argumentOfPeriapsisIndex ) = 45.78 / 180.0 * M_PI;
        expectedKeplerianElements( rightAscensionOfAscendingNodeIndex ) = -17.11 / 180.0 * M_PI;
        expectedKeplerianElements( trueAnomalyIndex ) = 315.62 / 180.0 * M_PI;

        // Compute Keplerian elements.
        Eigen::VectorXd computedKeplerianElements( 6 );
        computedKeplerianElements = tudat::orbital_element_conversions::
                convertCartesianToKeplerianElements( cartesianElements,
                                                     sunGravitationalParameter );

        // Check if computed Keplerian elements match the expected values.
        TUDAT_CHECK_MATRIX_CLOSE_FRACTION( expectedKeplerianElements,
                                           computedKeplerianElements, 1.0e-15 );
    }
}

// Test if conversion from true anomaly to eccentric anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testTrueAnomalyToEccentricAnomalyConversion )
{
    // Case 1: General elliptical orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.146;

        // Set true anomaly.
        double trueAnomaly = 82.16 / 180.0 * M_PI;

        // Set expected eccentric anomaly.
        double expectedEccentricAnomaly = 1.290237398010989;

        // Compute eccentric anomaly.
        double computedEccentricAnomaly = tudat::orbital_element_conversions::
                convertTrueAnomalyToEccentricAnomaly( trueAnomaly, eccentricity );

        // Check if computed eccentric anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedEccentricAnomaly, computedEccentricAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 2: Circular orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set true anomaly.
        double trueAnomaly = 160.43 / 180.0 * M_PI;

        // Set expected eccentric anomaly.
        double expectedEccentricAnomaly = 2.800031718974503;

        // Compute eccentric anomaly.
        double computedEccentricAnomaly = tudat::orbital_element_conversions::
                convertTrueAnomalyToEccentricAnomaly( trueAnomaly, eccentricity );

        // Check if computed eccentric anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedEccentricAnomaly, computedEccentricAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 3: Circular orbit at periapsis.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set true anomaly.
        double trueAnomaly = 0.0;

        // Set expected eccentric anomaly.
        double expectedEccentricAnomaly = 0.0;

        // Compute eccentric anomaly.
        double computedEccentricAnomaly = tudat::orbital_element_conversions::
                convertTrueAnomalyToEccentricAnomaly( trueAnomaly, eccentricity );

        // Check if computed eccentric anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedEccentricAnomaly, computedEccentricAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

// Test if conversion from eccentric anomaly to true anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testEccentricAnomalyToTrueAnomalyConversion )
{
    // Case 1: General elliptical orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.639;

        // Set eccentric anomaly.
        double eccentricAnomaly = 239.45 / 180.0 * M_PI;

        // Set expected true anomaly.
        double expectedTrueAnomaly = 3.665218735816221;

        // Compute true anomaly, modulo 2*pi.
        double convertedTrueAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToTrueAnomaly( eccentricAnomaly, eccentricity )
                + 2.0 * M_PI;

        // Check if computed trie anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedTrueAnomaly, convertedTrueAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 2: Circular orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set eccentric anomaly.
        double eccentricAnomaly = -99.54 / 180.0 * M_PI;

        // Set expected true anomaly.
        double expectedTrueAnomaly = 4.545884569744431;

        // Compute true anomaly.
        double convertedTrueAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToTrueAnomaly( eccentricAnomaly, eccentricity )
                + 2.0 * M_PI;

        // Check if computed true anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedTrueAnomaly, convertedTrueAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 3: Circular orbit at periapsis.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set eccentric anomaly.
        double eccentricAnomaly = 0.0;

        // Set expected true anomaly.
        double expectedTrueAnomaly = 0.0;

        // Compute true anomaly.
        double convertedTrueAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToTrueAnomaly( eccentricAnomaly, eccentricity );

        // Check if computed true anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedTrueAnomaly, convertedTrueAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

}

// Test if conversion from true anomaly to hyperbolic eccentric anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testTrueAnomalyToHyperbolicEccentricAnomalyConversion )
{
    // Case 1: General hyperbolic orbit.
    // The benchmark data is obtained from (Fortescue, 2003).
    {
        // Set eccentricity.
        double eccentricity = 3.0;

        // Set true anomaly.
        double trueAnomaly = 0.5291;

        // Set expected hyperbolic eccentric anomaly.
        double expectedHyperbolicEccentricAnomaly = 0.3879;

        // Compute hyperbolic eccentric anomaly.
        double convertedHyperbolicEccentricAnomaly = tudat::orbital_element_conversions
                ::convertTrueAnomalyToHyperbolicEccentricAnomaly( trueAnomaly, eccentricity );

        // Check if computed hyperbolic eccentric anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedHyperbolicEccentricAnomaly,
                                    convertedHyperbolicEccentricAnomaly, 1.0e-5 );
    }
}

// Test if conversion from hyperbolic eccentric anomaly to true anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testHyperbolicEccentricAnomalyToTrueAnomalyConversion )
{
    // Case 1: General hyperbolic orbit.
    // The benchmark data is obtained from (Fortescue, 2003).
    {
        // Set eccentricity.
        double eccentricity = 3.0;

        // Set hyperbolic eccentric anomaly.
        double hyperbolicEccentricAnomaly = 0.3879;

        // Set expected true anomaly.
        double expectedTrueAnomaly = 0.5291;

        // Compute true anomaly.
        double convertedTrueAnomaly = tudat::orbital_element_conversions
                ::convertHyperbolicEccentricAnomalyToTrueAnomaly(
                    hyperbolicEccentricAnomaly, eccentricity );

        // Check if computed true anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedTrueAnomaly, convertedTrueAnomaly, 1.0e-5 );
    }
}

// Test if conversion from eccentric anomaly to mean anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testEccentricAnomalyToMeanAnomalyConversion )
{
    // Case 1: General elliptical orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.541;

        // Set eccentric anomaly.
        double eccentricAnomaly = 176.09 / 180.0 * M_PI;

        // Set expected mean anomaly.
        double expectedMeanAnomaly = 3.036459804491048;

        // Compute mean anomaly.
        double computedMeanAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToMeanAnomaly( eccentricAnomaly, eccentricity );

        // Check if computed mean anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomaly, computedMeanAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 2: Circular orbit.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set eccentric anomaly.
        double eccentricAnomaly = 320.12 / 180.0 * M_PI;

        // Set expected mean anomaly.
        double expectedMeanAnomaly = 5.587148001484247;

        // Compute mean anomaly.
        double computedMeanAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToMeanAnomaly( eccentricAnomaly, eccentricity );

        // Check if computed mean anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomaly, computedMeanAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Case 3: Circular orbit at periapsis.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    {
        // Set eccentricity.
        double eccentricity = 0.0;

        // Set eccentric anomaly.
        double eccentricAnomaly = 0.0;

        // Set expected mean anomaly.
        double expectedMeanAnomaly = 0.0;

        // Compute mean anomaly.
        double computedMeanAnomaly = tudat::orbital_element_conversions
                ::convertEccentricAnomalyToMeanAnomaly( eccentricAnomaly, eccentricity );

        // Check if computed mean anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomaly, computedMeanAnomaly,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

// Test if conversion from hyperbolic eccentric anomaly to mean anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testHyperbolicEccentricAnomalyToMeanAnomalyConversion )
{
    // Case 1: General hyperbolic orbit.
    // The benchmark data is obtained from (Vallado, 2004).
    {
        // Set eccentricity.
        double eccentricity = 2.4;

        // Set hyperbolic eccentric anomaly.
        double hyperbolicEccentricAnomaly = 1.6013761449;

        // Set expected mean anomaly.
        double expectedMeanAnomaly = 235.4 / 180.0 * M_PI;

        // Compute mean anomaly.
        double computedMeanAnomaly = tudat::orbital_element_conversions
                ::convertHyperbolicEccentricAnomalyToMeanAnomaly( hyperbolicEccentricAnomaly,
                                                                  eccentricity );

        // Check if computed mean anomaly matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomaly, computedMeanAnomaly, 1.0e-8 );
    }
}

// Test if conversion from elapsed time to mean anomaly is working correctly.
BOOST_AUTO_TEST_CASE( testElapsedTimeToMeanAnomalyConversion )
{
    // Case 1: Earth-orbiting satellite.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    // The data is produced by running the kepprop2b_test() function through
    // kepprop2b('ValidationTest'). To see the mean anomaly values computed, in the MATLAB file,
    // remove the semi-colon at the end of line 68 in kepprop2b.m.
    {
        // Set elapsed time [s].
        double elapsedTime = 8640.0;

        // Set Earth gravitational parameter.
        double earthGravitationalParameter = 398600.4415;

        // Set semi-major axis [m].
        double semiMajorAxis = 42165.3431351313;

        // Set expected mean anomaly change [rad].
        double expectedMeanAnomalyChange = 2.580579656848906 - 1.950567148859647;

        // Compute mean anomaly change [rad].
        double computedMeanAnomalyChange = tudat::orbital_element_conversions
                ::convertElapsedTimeToMeanAnomalyChangeForEllipticalOrbits(
                    elapsedTime, earthGravitationalParameter, semiMajorAxis );

        // Check if computed mean anomaly change matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomalyChange, computedMeanAnomalyChange,
                                    1.0e-14 );
    }

    // Case 2: Earth-orbiting satellite with no elapsed time.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    // The data is produced by running the kepprop2b_test() function through
    // kepprop2b('ValidationTest'). To see the mean anomaly values computed, in the MATLAB file,
    // remove the semi-colon at the end of line 68 in kepprop2b.m.
    {
        // Set elapsed time [s].
        double elapsedTime = 0.0;

        // Set Earth gravitational parameter.
        double earthGravitationalParameter = 398600.4415;

        // Set semi-major axis [m].
        double semiMajorAxis = 42165.3431351313;

        // Set expected mean anomaly change [rad].
        double expectedMeanAnomalyChange = 0.0;

        // Compute mean anomaly change [rad].
        double computedMeanAnomalyChange = tudat::orbital_element_conversions
                ::convertElapsedTimeToMeanAnomalyChangeForEllipticalOrbits(
                    elapsedTime, earthGravitationalParameter, semiMajorAxis );

        // Check if computed mean anomaly change matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanAnomalyChange, computedMeanAnomalyChange,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

// Test if conversion from mean anomaly to elapsed time is working correctly.
BOOST_AUTO_TEST_CASE( testMeanAnomalyToElaspedTimeConversion )
{
    // Case 1: Earth-orbiting satellite.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    // The data is produced by running the kepprop2b_test() function through
    // kepprop2b('ValidationTest'). To see the mean anomaly values computed, in the MATLAB file,
    // remove the semi-colon at the end of line 68 in kepprop2b.m.
    {
        // Set mean anomaly change [rad].
        double meanAnomalyChange = 3.210592164838165 - 1.950567148859647;

        // Set Earth gravitational parameter [m^3/s^2].
        double earthGravitationalParameter = 398600.4415;

        // Set semi-major axis [m].
        double semiMajorAxis = 42165.3431351313;

        // Set expected elapsed time [s].
        double expectedElapsedTime = 17280.0;

        // Compute elapsed time [s].
        double computedElapsedTime = tudat::orbital_element_conversions
                ::convertMeanAnomalyChangeToElapsedTimeForEllipticalOrbits(
                    meanAnomalyChange, earthGravitationalParameter, semiMajorAxis );

        // Check if computed elapsed time matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedElapsedTime, computedElapsedTime, 1.0e-15 );
    }

    // Case 2: Earth-orbiting satellite with no mean anomaly change.
    // The benchmark data is obtained by running ODTBX (NASA, 2012).
    // The data is produced by running the kepprop2b_test() function through
    // kepprop2b('ValidationTest'). To see the mean anomaly values computed, in the MATLAB file,
    // remove the semi-colon at the end of line 68 in kepprop2b.m.
    {
        // Set mean anomaly change [rad].
        double meanAnomalyChange = 0.0;

        // Set Earth gravitational parameter [m^3/s^2].
        double earthGravitationalParameter = 398600.4415;

        // Set semi-major axis [m].
        double semiMajorAxis = 42165.3431351313;

        // Set expected elapsed time [s].
        double expectedElapsedTime = 0.0;

        // Compute elapsed time [s].
        double computedElapsedTime = tudat::orbital_element_conversions
                ::convertMeanAnomalyChangeToElapsedTimeForEllipticalOrbits(
                    meanAnomalyChange, earthGravitationalParameter, semiMajorAxis );

        // Check if computed elapsed time matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedElapsedTime, computedElapsedTime,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

// Test if conversion from mean motion to semi-major axis is working correctly.
BOOST_AUTO_TEST_CASE( testMeanMotionToSemiMajorAxisConversion )
{
    // Case 1: Geostationary satellite around the Earth.
    // The benchmark data is obtained from (Wikipedia, 2012).
    {
        // Set mean motion [rad/s].
        double meanMotion = 7.2921e-5;

        // Set Earth gravitational parameter [m^3/s^2].
        double earthGravitationalParameter = 5.9736e24 * 6.67428e-11;

        // Set expected semi-major axis [m].
        double expectedSemiMajorAxis = 42164.0e3;

        // Compute semi-major axis [s].
        double computedSemiMajorAxis = tudat::orbital_element_conversions
                ::convertMeanMotionToSemiMajorAxis( meanMotion, earthGravitationalParameter );

        // Check if computed semi-major axis matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedSemiMajorAxis, computedSemiMajorAxis, 1.0e-4 );
    }

    // Case 2: Geostationary satellite around Mars.
    // The benchmark data is obtained from (Wikipedia, 2012).
    {
        // Set mean motion [rad/s].
        double meanMotion = 7.088218e-5;

        // Set Mars gravitational parameter [m^3/s^2].
        double marsGravitationalParameter = 42828.0e9;

        // Set expected semi-major axis [m].
        double expectedSemiMajorAxis = 20427.0e3;

        // Compute semi-major axis [m].
        double computedSemiMajorAxis = tudat::orbital_element_conversions
                ::convertMeanMotionToSemiMajorAxis( meanMotion, marsGravitationalParameter );

        // Check if computed semi-major axis matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedSemiMajorAxis, computedSemiMajorAxis, 1.0e-4 );
    }
}

// Test if conversion from semi-major axis to mean motion is working correctly.
BOOST_AUTO_TEST_CASE( testSemiMajorAxisToMeanMotionConversion )
{
    // Case 1: Geostationary satellite around the Earth.
    // The benchmark data is obtained from (Wikipedia, 2012).
    {
        // Set semi-major axis [m].
        double semiMajorAxis = 42164.0e3;

        // Set Earth gravitational parameter [m^3/s^2].
        double earthGravitationalParameter = 5.9736e24 * 6.67428e-11;

        // Set expected mean motion [rad/s].
        double expectedMeanMotion = 7.2921e-5;

        // Compute mean motion [rad/s].
        double computedMeanMotion = tudat::orbital_element_conversions
                ::convertSemiMajorAxisToMeanMotion( semiMajorAxis, earthGravitationalParameter );

        // Check if computed mean motion matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanMotion, computedMeanMotion, 1.0e-3 );
    }

    // Case 2: Geostationary satellite around Mars.
    // The benchmark data is obtained from (Wikipedia, 2012).
    {
        // Set semi-major axis [m].
        double semiMajorAxis = 20427.0e3;

        // Set Mars gravitational parameter [m^3/s^2].
        double marsGravitationalParameter = 42828.0e9;

        // Set expected mean motion [rad/s].
        double expectedMeanMotion = 7.088218e-5;

        // Compute mean motion [rad/s].
        double computedMeanMotion = tudat::orbital_element_conversions
                ::convertSemiMajorAxisToMeanMotion( semiMajorAxis, marsGravitationalParameter );

        // Check if computed mean motion matches the expected value.
        BOOST_CHECK_CLOSE_FRACTION( expectedMeanMotion, computedMeanMotion, 1.0e-4 );
    }
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.