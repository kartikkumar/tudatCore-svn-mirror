/*! \file unitTestAstrodynamicsFunctions.cpp
 *    This unit test will test general astrodynamics functions defined in astrodynamicsFunctions.h.
 *
 *    Path              : /Astrodynamics/
 *    Version           : 7
 *    Check status      : Checked
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Author            : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Date created      : 11 November, 2011
 *    Last modified     : 28 January, 2012
 *
 *    References
 *      Wikipedia. Geostationary orbit, http://en.wikipedia.org/wiki/Geostationary_orbit, last
 *          accessed: 22nd November, 2011.
 *      Keefe, T.J. Synodic Period Calculator, http://www.ccri.edu/physics/keefe/synodic_calc.htm,
 *          last accessed: 6th December, 2011, last modified: 18th November, 2011.
 *
 *    Notes
 *
 *      The tests need to be updated to check benchmark values from literature.
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
 *      100910    K. Kumar          First creation of code.
 *      111115    K. Kumar          Altered tests to override default mass values; corrected
 *                                  bool-variable name; corrected cerr-statement.
 *      111122    K. Kumar          Altered tests to use reference data.
 *      111206    K. Kumar          Updated synodic period test and comments.
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
#include <cmath>
#include <limits>
#include "TudatCore/Astrodynamics/astrodynamicsFunctions.h"
#include "TudatCore/Astrodynamics/physicalConstants.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_astrodynamics_functions )

//! Test if the orbital period of a Kepler orbit is computed correctly.
BOOST_AUTO_TEST_CASE( testKeplerOrbitalPeriod )
{
    // Declare and set satellite mass [kg].
    double satelliteMass = 1.0e3;

    // Declare and set gravitational parameter of Earth [m^3 s^-2].
    double earthGravitationalParameter
            = tudat::physical_constants::GRAVITATIONAL_CONSTANT * 5.9736e24;

    // Declare and set distance between Earth center and satellite.
    double distanceBetweenSatelliteAndEarth = 4.2164e7;

    // Compute orbital period of satellite.
    double orbitalPeriod = tudat::astrodynamics::computeKeplerOrbitalPeriod(
                distanceBetweenSatelliteAndEarth, earthGravitationalParameter, satelliteMass );

    // Declare and set expected orbital period [s].
    double expectedOrbitalPeriod = 86164.09054;

    // Check if computed orbital period matches expected orbital period.
    BOOST_CHECK_CLOSE_FRACTION( orbitalPeriod, expectedOrbitalPeriod, 1.0e-5 );
}

//! Test if the orbital angular momentum of a kepler orbit is computed correctly.
BOOST_AUTO_TEST_CASE( testKeplerAngularMomentum )
{
    // Reference: http://en.wikipedia.org/wiki/Geostationary_orbit.
    // Declare and set satellite mass [kg].
    double satelliteMass = 1.0e3;

    // Declare and set gravitational parameter of Earth [m^3 s^-2].
    double earthGravitationalParameter
            = tudat::physical_constants::GRAVITATIONAL_CONSTANT * 5.9736e24;

    // Declare and set distance between Earth center and satellite.
    double distanceBetweenSatelliteAndEarth = 4.2164e7;

    // Declare and set eccentricity of satellite orbit.
    double eccentricityOfSatelliteOrbit = 0.0;

    // Compute Kepler angular momentum.
    double angularMomentum = tudat::astrodynamics::computeKeplerAngularMomentum(
                distanceBetweenSatelliteAndEarth, eccentricityOfSatelliteOrbit,
                earthGravitationalParameter, satelliteMass );

    // Declare and set expected angular momentum.
    // The expected angular momentum is computed using the fact that for a circular orbit,
    // H = mRV. This is an independent check of the code, which computes angular
    // momentum differently.
    double expectedAngularMomentum = satelliteMass * distanceBetweenSatelliteAndEarth
            * std::sqrt( earthGravitationalParameter / distanceBetweenSatelliteAndEarth );

    // Check if computed angular momentum matches expected angular momentum.
    BOOST_CHECK_CLOSE_FRACTION( angularMomentum, expectedAngularMomentum,
                                std::numeric_limits< double >::epsilon( ) );
}

//! Test if the mean motion of a kepler orbit is computed correctly.
BOOST_AUTO_TEST_CASE( testMeanMotion )
{
    // Declare and set satellite mass [kg].
    double satelliteMass = 1.0e3;

    // Declare and set gravitational parameter of Earth [m^3 s^-2].
    double earthGravitationalParameter
            = tudat::physical_constants::GRAVITATIONAL_CONSTANT * 5.9736e24;

    // Declare and set distance between Earth center and satellite.
    double distanceBetweenSatelliteAndEarth = 4.2164e7;

    // Reference: http://en.wikipedia.org/wiki/Geostationary_orbit.
    double meanMotion = tudat::astrodynamics::computeKeplerMeanMotion(
                distanceBetweenSatelliteAndEarth, earthGravitationalParameter, satelliteMass );

    // Declare and set expected mean motion [rad/s].
    double expectedMeanMotion = 7.2921e-5;

    // Check if computed mean motion matches expected mean motion.
    BOOST_CHECK_CLOSE_FRACTION( meanMotion, expectedMeanMotion, 1.0e-7 );
}

//! Test if the orbital energy of a Kepler orbit is computed correctly.
BOOST_AUTO_TEST_CASE( testKeplerEnergy )
{
    // Declare and set satellite mass [kg].
    double satelliteMass = 1.0e3;

    // Declare and set gravitational parameter of Earth [m^3 s^-2].
    double earthGravitationalParameter
            = tudat::physical_constants::GRAVITATIONAL_CONSTANT * 5.9736e24;

    // Declare and set distance between Earth center and satellite.
    double distanceBetweenSatelliteAndEarth = 4.2164e7;

    // Compute Kepler energy.
    double orbitalEnergy = tudat::astrodynamics::computeKeplerEnergy(
                distanceBetweenSatelliteAndEarth, earthGravitationalParameter, satelliteMass );

    // Declare and set expected orbital energy.
    // The expected orbital energy is computed using the fact that for a circular orbit,
    // E = m ( V^2/2 - mu/R ). This is an independent check of the code, which computes orbital
    // energy differently.
    double expectedOrbitalEnergy = satelliteMass * (
                0.5 * earthGravitationalParameter / distanceBetweenSatelliteAndEarth
                -  earthGravitationalParameter / distanceBetweenSatelliteAndEarth );

    // Check if computed orbital energy matches expected orbital energy.
    BOOST_CHECK_CLOSE_FRACTION( orbitalEnergy, expectedOrbitalEnergy,
                                std::numeric_limits< double >::epsilon( ) );

}

//! Test if the synodic period between two orbits is computed correctly.
BOOST_AUTO_TEST_CASE( testSynodicPeriod )
{
    // Compute synodic period between Earth and Mars.
    double synodicPeriod = tudat::astrodynamics::computeSynodicPeriod( 365.256378, 686.95 );

    // Declare and set expected synodic period.
    double expectedSynodicPeriod = 779.9746457736733;

    // Check if computed synodic period matches expected synodic period.
    BOOST_CHECK_CLOSE_FRACTION( synodicPeriod, expectedSynodicPeriod,
                                std::numeric_limits< double >::epsilon( ) );
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.
