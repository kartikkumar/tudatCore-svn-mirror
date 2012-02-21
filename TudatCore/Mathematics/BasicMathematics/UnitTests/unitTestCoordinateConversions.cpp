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
 *      120128    K. Kumar          Changed BOOST_CHECK to BOOST_CHECK_CLOSE_FRACTION and
 *                                  BOOST_CHECK_SMALL for unit test comparisons.
 *
 *    References
 *
 */

#define BOOST_TEST_MAIN

#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>
#include <Eigen/Core>
#include <limits>
#include "TudatCore/Mathematics/BasicMathematics/coordinateConversions.h"
#include "TudatCore/Mathematics/BasicMathematics/mathematicalConstants.h"

using tudat::mathematics::PI;

namespace tudat
{
namespace unit_tests
{

//! Test suite for coordinate conversion functions.
BOOST_AUTO_TEST_SUITE( test_coordinate_conversions )

//! Test if spherical-to-Cartesian conversion is working correctly.
BOOST_AUTO_TEST_CASE( testSphericalToCartesianConversion )
{
    using tudat::mathematics::coordinate_conversions::convertSphericalToCartesian;
    
    // Test 1: Test conversion of: ( 0.0, 0.0, 0.0 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d::Zero( 3 );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        // Check if converted Cartesian coordinates are correct.
        BOOST_CHECK_SMALL( cartesianCoordinates_( 0 ), std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_SMALL( cartesianCoordinates_( 1 ), std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_SMALL( cartesianCoordinates_( 2 ), std::numeric_limits< double >::epsilon( ) );
    }

    // Test 2: Test conversion of: ( 2.0, 225, 225 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d(
                    2.0, 225.0 / 180.0 * PI, 225.0 / 180.0 * PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        // Check if converted Cartesian coordinates are correct.
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 0 ), 1.0,
                                    std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 1 ), 1.0, 1.0e-15 );
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 2 ), -std::sqrt( 2.0 ),
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Test 3: Test conversion of: ( 2.0, -225, -225 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d(
                    2.0, -225.0 / 180.0 * PI, -225.0 / 180.0 * PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        // Check if converted Cartesian coordinates are correct.
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 0 ), -1.0,
                                    std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 1 ), 1.0, 1.0e-15 );
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 2 ), -std::sqrt( 2.0 ),
                                    std::numeric_limits< double >::epsilon( ) );
    }

    // Test 4: Test conversion of: ( 2.0, 180, 180 ).
    {
        Eigen::VectorXd sphericalCoordinates_ = Eigen::Vector3d( 2.0, PI, PI );

        Eigen::VectorXd cartesianCoordinates_( 3 );

        // Convert spherical coordinates to Cartesian coordinates.
        cartesianCoordinates_ = convertSphericalToCartesian( sphericalCoordinates_ );

        // Check if converted Cartesian coordinates are correct.
        BOOST_CHECK_SMALL( cartesianCoordinates_( 0 ), 1.0e-15 );
        BOOST_CHECK_SMALL( cartesianCoordinates_( 1 ), std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( cartesianCoordinates_( 2 ), -2.0,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

//! Test if Cartesian-to-spherical conversion is working correctly.
BOOST_AUTO_TEST_CASE( testCartesianToSphericalConversion )
{
    using std::acos;
    using std::atan2;
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

        // Check if converted spherical coordinates are correct.
        BOOST_CHECK_SMALL( sphericalCoordinates_.norm( ) - expectedSphericalCoordinates_.norm( ),
                           std::numeric_limits< double >::epsilon( ) );
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

        // Check if converted spherical coordinates are correct.
        BOOST_CHECK_CLOSE_FRACTION( sphericalCoordinates_.norm( ),
                                    expectedSphericalCoordinates_.norm( ),
                                    std::numeric_limits< double >::epsilon( ) );
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

        // Check if converted spherical coordinates are correct.
        BOOST_CHECK_CLOSE_FRACTION( sphericalCoordinates_.norm( ),
                                    expectedSphericalCoordinates_.norm( ),
                                    std::numeric_limits< double >::epsilon( ) );
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

        // Check if converted spherical coordinates are correct.
        BOOST_CHECK_CLOSE_FRACTION( sphericalCoordinates_.norm( ),
                                    expectedSphericalCoordinates_.norm( ),
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests
} // namespace tudat