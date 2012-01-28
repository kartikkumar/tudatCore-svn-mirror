/*! \file unitTestLinearAlgebra.cpp
 *    Source file that executes the unit tests to test all linear algebra functions contained in
 *    Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 3
 *    Check status      : Checked
 *
 *    Author            : D.Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Checker           : S. Billemont
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : simon@angelcorp.be
 *
 *    Date created      : 27 January, 2012
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
 *      120127    D. Dirkx          File created.
 *      120127    K. Kumar          Transferred unit tests over to Boost unit test framework.
 *      120128    K. Kumar          Changed some BOOST_CHECK to BOOST_CHECK_CLOSE_FRACTION and
 *                                  BOOST_CHECK_SMALL for unit test comparisons.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>
#include <cmath>
#include "Mathematics/linearAlgebra.h"

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_coordinate_conversions )

//! Test if angle between vectors is computed correctly.
BOOST_AUTO_TEST_CASE( testAngleBetweenVectorFunctions )
{
    // Using declarations.
    using std::cos;
    using tudat::mathematics::linear_algebra::computeAngleBetweenVectors;
    using tudat::mathematics::linear_algebra::computeCosineOfAngleBetweenVectors;

    // Three tests are executed. First, the equality of the caluclated cosineOfAngle and the cosine
    // of the calculated angle is checked. Subsequently, the values of the angle and cosineOfAngle
    // are checked against reference values, which are analytical in the first two cases and
    // taken from Matlab results in the third.

    // Test 1: Test values for two equal vectors.
    {
        Eigen::Vector3d testVector1_ = Eigen::Vector3d( 3.0, 2.1, 4.6 );
        Eigen::Vector3d testVector2_ = Eigen::Vector3d( 3.0, 2.1, 4.6 );

        double angle = computeAngleBetweenVectors( testVector1_, testVector2_ );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1_, testVector2_ );

        // Check if computed angle and cosine-of-angle are correct.
        BOOST_CHECK_SMALL( cos( angle ) - cosineOfAngle,
                           std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK( cosineOfAngle > std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_SMALL( cosineOfAngle - 1.0, std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK( angle < std::numeric_limits< double >::epsilon( ) );
    }

    // Test 2: Test values for two equal, but opposite vectors.
    {
        Eigen::Vector3d testVector1_ = Eigen::Vector3d( 3.0, 2.1, 4.6 );
        Eigen::Vector3d testVector2_ = Eigen::Vector3d( -3.0, -2.1, -4.6 );

        double angle = computeAngleBetweenVectors( testVector1_, testVector2_ );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1_, testVector2_ );

        // Check if computed angle and cosine-of-angle are correct.
        BOOST_CHECK_SMALL( cos( angle ) - cosineOfAngle,
                           std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK( cosineOfAngle < std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_SMALL( cosineOfAngle + 1.0, std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( angle, M_PI, std::numeric_limits< double >::epsilon( ) );
    }

    // Test 3: Test values for two equal vectors, benchmark values computed using Matlab.
    {
        Eigen::Vector3d testVector1_ = Eigen::Vector3d( 1.0, 2.0, 3.0 );
        Eigen::Vector3d testVector2_ = Eigen::Vector3d( -3.74, 3.7, -4.6 );

        double angle = computeAngleBetweenVectors( testVector1_, testVector2_ );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1_, testVector2_ );

        // Check if computed angle and cosine-of-angle are correct.
        BOOST_CHECK_SMALL( cos( angle ) - cosineOfAngle,
                           std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK( cosineOfAngle < std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( cosineOfAngle, -0.387790156029810,
                                    std::numeric_limits< double >::epsilon( ) );
        BOOST_CHECK_CLOSE_FRACTION( angle, 1.969029256915446,
                                    std::numeric_limits< double >::epsilon( ) );
    }
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( )

// End of file.
