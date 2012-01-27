/*! \file unitTestCoordinateConversions.cpp
 *    Source file that executes the unit tests to test all coordinate conversion functions
 *    contained in Tudat.
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
 *    Last modified     : 27 January, 2012
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
 *      120127    D. Dirkx          Moved unit to separate file from basic mathematics test; moved
 *                                  tests to separate functions; moved to Tudat Core.
 *      120127    K. Kumar          Transferred unit tests over to Boost unit test framework.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/unit_test.hpp>
#include <cmath>
#include <Eigen/Core>
#include <iostream> 
#include <limits>
#include <vector>
#include "Mathematics/coordinateConversions.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_coordinate_conversions )

//! Test if cylindrical-to-Cartesian conversion is working correctly.
BOOST_AUTO_TEST_CASE( testCylindricalToCartesianConversion )
{
    // Using declarations.
    using std::fabs;
    using tudat::mathematics::coordinate_conversions::convertCylindricalToCartesian;

    // Test 1: Test conversion of ( 2.0, 0.0 ).
    {
        Eigen::VectorXd cylindricalCoordinates_ = Eigen::Vector3d( 2.0, 0.0, 0.0 );

        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d::Zero( 3 );

        // Convert cylindrical coordinates to Cartesian elements.
        cartesianCoordinates_ = convertCylindricalToCartesian( cylindricalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) - 2.0 ) / 2.0 < 1.0e-15 ||
                     fabs( cartesianCoordinates_( 1 ) - 0.0 ) < 1.0e-15 );
    }

    // Test 2: Test conversion of ( 2.0, pi ).
    {
        Eigen::VectorXd cylindricalCoordinates_ = Eigen::Vector3d( 2.0, M_PI, 0.0 );

        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d::Zero( 3 );

        // Convert cylindrical coordinates to Cartesian elements.
        cartesianCoordinates_ = convertCylindricalToCartesian( cylindricalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) + 2.0 ) < 1.0e-15 ||
                     fabs( cartesianCoordinates_( 1 ) - 0.0 ) < 1.0e-15 );
    }

    // Test 3: Test conversion of ( 2.0, -2pi ).
    {
        Eigen::VectorXd cylindricalCoordinates_ = Eigen::Vector3d( 2.0, -2.0 * M_PI, 0.0 );

        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d::Zero( 3 );

        // Convert cylindrical coordinates to Cartesian elements.
        cartesianCoordinates_ = convertCylindricalToCartesian( cylindricalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) - 2.0 ) < 1.0e-15 ||
                     fabs( cartesianCoordinates_( 1 ) - 0.0 ) < 1.0e-15 );
    }

    // Test 4: Test conversion of ( 2.0, 225 deg ).
    {
        Eigen::Vector3d cylindricalCoordinates_ = Eigen::Vector3d( 2.0, 225.0 / 180.0 * M_PI, 0.0 );

        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d::Zero( 3 );

        // Convert cylindrical coordinates to Cartesian elements.
        cartesianCoordinates_ = convertCylindricalToCartesian( cylindricalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) + sqrt( 2.0 ) )
                     < std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 1 ) + sqrt( 2.0 ) ) < 1.0e-15 );
    }

    // Test 5: Test conversion of ( 2.0, -225 deg ).
    {
        Eigen::VectorXd cylindricalCoordinates_ = Eigen::Vector3d( 2.0, -225.0 / 180 * M_PI, 0.0 );

        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d::Zero( 3 );

        // Convert cylindrical coordinates to Cartesian elements.
        cartesianCoordinates_ = convertCylindricalToCartesian( cylindricalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) + sqrt( 2.0 ) ) <
                     std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 1 ) - sqrt( 2.0 ) ) < 1.0e-15 );
    }
}

//! Test if spherical-to-Cartesian conversion is working correctly.
BOOST_AUTO_TEST_CASE( testSphericalToCartesianConversion )
{
    // Using declarations.
    using std::fabs;
    using tudat::mathematics::coordinate_conversions::convertSphericalToCartesian;
    
    // Test 1: Test conversion of: ( 0.0, 0.0, 0.0 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d::Zero( 3 );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) + 0.0 ) <
                     std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 1 ) - 0.0 ) <
                     std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 2 ) - 0.0 ) <
                     std::numeric_limits< double >::epsilon( ) );
    }

    // Test 2: Test conversion of: ( 2.0, 225, 225 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d(
                    2.0, 225.0 / 180.0 * M_PI, 225.0 / 180.0 * M_PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) - 1.0 )
                     < std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 1 ) - 1.0 )
                     < std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 2 ) + sqrt( 2.0 ) ) < 1.0e-15 );
    }

    // Test 3: Test conversion of: ( 2.0, -225, -225 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d(
                    2.0, -225.0 / 180.0 * M_PI, -225.0 / 180.0 * M_PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) + 1.0 )
                     < std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 1 ) - 1.0 )
                     < std::numeric_limits< double >::epsilon( ) ||
                     fabs( cartesianCoordinates_( 2 ) + sqrt( 2.0 ) ) < 1.0e-15 );
    }

    // Test 4: Test conversion of: ( 2.0, 180, 180 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d( 2.0, M_PI, M_PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        BOOST_CHECK( fabs( cartesianCoordinates_( 0 ) - 0.0 ) < 1.0e-15 ||
                     fabs( cartesianCoordinates_( 1 ) - 0.0 ) < 1.0e-15 ||
                     fabs( cartesianCoordinates_( 2 ) + 2.0 ) / 2.0 < 1.0e-15 );
    }
}

//! Test if Cartesian-to-spherical conversion is working correctly.
BOOST_AUTO_TEST_CASE( testCartesianToSphericalConversion )
{
    // Using declarations.
    using std::acos;
    using std::atan2;
    using std::fabs;
    using std::pow;
    using std::sqrt;
    using tudat::mathematics::coordinate_conversions::convertCartesianToSpherical;

    // Test 1: Test conversion of: ( 0.0, 0.0, 0.0 ).
    {
        Eigen::VectorXd cartesianCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Expected vector in spherical coordinates.
        Eigen::VectorXd expectedSphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Result vector in spherical coordinates.
        Eigen::VectorXd sphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Compute conversions.
        sphericalCoordinates_ = convertCartesianToSpherical( cartesianCoordinates_ );

        // Check if relative error is too large.
        BOOST_CHECK( fabs( sphericalCoordinates_.norm( )
                           - expectedSphericalCoordinates_.norm( ) )
                     < std::numeric_limits< double >::epsilon( ) );
    }

    // Test 2: Test conversion of: ( 2.0, 3.5, -4.1 ).
    {
        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d( 2.0, 3.5, -4.1 );

        // Expected vector in spherical coordinates.
        Eigen::Vector3d expectedSphericalCoordinates_ = Eigen::Vector3d(
                    sqrt( pow( cartesianCoordinates_( 0 ), 2.0 )
                          + pow( cartesianCoordinates_( 1 ), 2.0 )
                          + pow( cartesianCoordinates_( 2 ), 2.0 ) ),
                    atan2( cartesianCoordinates_( 1 ), cartesianCoordinates_( 0 ) ),
                    acos( cartesianCoordinates_( 2 ) / cartesianCoordinates_.norm( ) ) );

        // Result vector in spherical coordinates.
        Eigen::VectorXd sphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Compute conversions.
        sphericalCoordinates_ = convertCartesianToSpherical( cartesianCoordinates_ );

        // Check if relative error is too large.
        BOOST_CHECK( fabs( sphericalCoordinates_.norm( )
                           - expectedSphericalCoordinates_.norm( ) )
                     / expectedSphericalCoordinates_.norm( )
                     < std::numeric_limits< double >::epsilon( ) );
    }

    // Test 3: Test conversion of: ( 5.2, -6.3, 0.0 ).
    {
        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d( 5.2, -6.3, 0.0 );

        // Expected vector in spherical coordinates.
        Eigen::Vector3d expectedSphericalCoordinates_ = Eigen::Vector3d(
                    sqrt( pow( cartesianCoordinates_( 0 ), 2.0 )
                          + pow( cartesianCoordinates_( 1 ), 2.0 )
                          + pow( cartesianCoordinates_( 2 ), 2.0 ) ),
                    atan2( cartesianCoordinates_( 1 ), cartesianCoordinates_( 0 ) ),
                    acos( cartesianCoordinates_( 2 ) / cartesianCoordinates_.norm( ) ) );

        // Result vector in spherical coordinates.
        Eigen::VectorXd sphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Compute conversions.
        sphericalCoordinates_ = convertCartesianToSpherical( cartesianCoordinates_ );

        // Check if relative error is too large.
        BOOST_CHECK( fabs( sphericalCoordinates_.norm( )
                           - expectedSphericalCoordinates_.norm( ) )
                     / expectedSphericalCoordinates_.norm( )
                     < std::numeric_limits< double >::epsilon( ) );
    }

    // Test 4: Test conversion of: ( 0.0, 12.2, -0.9 ).
    {
        Eigen::Vector3d cartesianCoordinates_ = Eigen::Vector3d( 0.0, 12.2, -0.9 );

        // Expected vector in spherical coordinates.
        Eigen::Vector3d expectedSphericalCoordinates_ = Eigen::Vector3d(
                    sqrt( pow( cartesianCoordinates_( 0 ), 2.0 )
                          + pow( cartesianCoordinates_( 1 ), 2.0 )
                          + pow( cartesianCoordinates_( 2 ), 2.0 ) ),
                    atan2( cartesianCoordinates_( 1 ), cartesianCoordinates_( 0 ) ),
                    acos( cartesianCoordinates_( 2 ) / cartesianCoordinates_.norm( ) ) );

        // Result vector in spherical coordinates.
        Eigen::VectorXd sphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

        // Compute conversions.
        sphericalCoordinates_ = convertCartesianToSpherical( cartesianCoordinates_ );

        // Check if relative error is too large.
        BOOST_CHECK( fabs( sphericalCoordinates_.norm( )
                           - expectedSphericalCoordinates_.norm( ) )
                     / expectedSphericalCoordinates_.norm( )
                     < std::numeric_limits< double >::epsilon( ) );
    }
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.
