/*! \file unitTestBasicMathematicsFunctions.cpp
 *    Source file that defines the unitTestBasicMathematicsFunctions unit test,
 *    containing all basic mathematics functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 1
 *    Check status      : Checked
 *
 *    Author            : D.Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *
 *    Checker           : S. Billemont
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : simon@angelcorp.be
 *
 *    Date created      : 27 January, 2011
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
 *      110207    D. Dirkx          File created.
 */

// Include statements.
#include <cmath>
#include <iostream>
#include <vector>
#include "Mathematics/linearAlgebra.h"

//! Function to angle between, and cosine of angle between, function from linear algebra namespace
/**
 * \param Return true if the test fail to meet the required test accuracy 
 *               (something does not work as expected)
 */
bool testAngleBetweenVectorFunctions( )
{
    // Using declarations.
    using std::cos;
    using std::cerr;
    using std::endl;
    using std::fabs;
    using tudat::mathematics::linear_algebra::computeAngleBetweenVectors;
    using tudat::mathematics::linear_algebra::computeCosineOfAngleBetweenVectors;

    bool isLinearAlbegraOperationErroneous = 0;

    // Three tests are executed. First, the equality of the caluclated cosineOfAngle and the cosine
    // of the calculated angle is checked. Subsequently, the values of the angle and cosineOfAngle
    // are checked against reference values, which are analytical in the first two cases and
    // taken from Matlab results in the third.

    // Test values for two equal vectors.
    {
        Eigen::Vector3d testVector1 = Eigen::Vector3d( 3.0, 2.1, 4.6 );
        Eigen::Vector3d testVector2 = Eigen::Vector3d( 3.0, 2.1, 4.6 );
        double angle = computeAngleBetweenVectors( testVector1, testVector2 );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1, testVector2 );

        if ( fabs( cos( angle ) - cosineOfAngle )
             > std::numeric_limits< double >::epsilon( ) &&
             !( cosineOfAngle < std::numeric_limits< double >::epsilon( ) ) )
        {
            cerr << "Angle between vectors not compatible with cosine of angle between "
                    <<"vectors in test case 1." << endl;
            isLinearAlbegraOperationErroneous = true;
        }
        if ( fabs( cosineOfAngle - 1.0 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Cosine of angle between vectors incorrect in test case 1." << endl;
            isLinearAlbegraOperationErroneous = true;
        }
        if ( fabs( angle )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Angle between vectors incorrect in test case 1." << endl;
            isLinearAlbegraOperationErroneous = true;
        }
    }

    // Test values for two equal, but opposite vectors.
    {
        Eigen::Vector3d testVector1 = Eigen::Vector3d( 3.0, 2.1, 4.6 );
        Eigen::Vector3d testVector2 = Eigen::Vector3d( -3.0, -2.1, -4.6 );
        double angle = computeAngleBetweenVectors( testVector1, testVector2 );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1, testVector2 );

        if ( fabs( cos( angle ) - cosineOfAngle )
             > std::numeric_limits< double >::epsilon( ) &&
             !( cosineOfAngle < std::numeric_limits< double >::epsilon( ) ) )
        {
            cerr << "Angle between vectors not compatible with cosine of angle between "
                    <<"vectors in test case 2." << endl;
            isLinearAlbegraOperationErroneous = true;
        }

        if ( fabs( cosineOfAngle + 1.0 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Cosine of angle between vectors incorrect in test case 2. " << endl;
            isLinearAlbegraOperationErroneous = true;
        }
        if ( fabs( ( angle - M_PI ) / M_PI )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Angle between vectors incorrect in test case 2. " << endl;
            isLinearAlbegraOperationErroneous = true;
        }
    }

    // Test values for two equal vectors, benchmark values computed using Matlab.
    {
        Eigen::Vector3d testVector1 = Eigen::Vector3d( 1.0, 2.0, 3.0 );
        Eigen::Vector3d testVector2 = Eigen::Vector3d( -3.74, 3.7, -4.6 );
        double angle = computeAngleBetweenVectors( testVector1, testVector2 );
        double cosineOfAngle = computeCosineOfAngleBetweenVectors( testVector1, testVector2 );

        if ( fabs( cos( angle ) - cosineOfAngle )
             > std::numeric_limits< double >::epsilon( ) &&
             !( cosineOfAngle < std::numeric_limits< double >::epsilon( ) ) )
        {
            cerr << "Angle between vectors not compatible with cosine of angle between "<< endl;
            isLinearAlbegraOperationErroneous = true;
        }
        if ( fabs( ( cosineOfAngle + 0.387790156029810 ) / 0.387790156029810 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Cosine of angle between vectors incorrect in test case 3. " << endl;
            isLinearAlbegraOperationErroneous = true;
        }
        if ( fabs( ( angle - 1.969029256915446 ) / 1.969029256915446 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "Angle between vectors incorrect in test case 3. "<< endl;
            isLinearAlbegraOperationErroneous = true;
        }
    }

    return isLinearAlbegraOperationErroneous;

}

//! Test implementation of basic mathematics functions.
int main( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;

    bool isLinearAlbegraOperationErroneous = 0;

    // Test function calculating angles, and cosines of angles, between vectors.
    if( testAngleBetweenVectorFunctions( ) )
    {
        isLinearAlbegraOperationErroneous = 1;
    }

    // Return a message if any test failed
    if( isLinearAlbegraOperationErroneous == true )
    {
        cerr << "testLinearAlgebraFunctions failed!" << endl;
    }
    // Return a non-zero exit state if any tests failed
    return isLinearAlbegraOperationErroneous;
}

// End of file.


