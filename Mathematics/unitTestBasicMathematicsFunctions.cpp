/*! \file unitTestBasicMathematicsFunctions.cpp
 *    Source file that defines the unitTestBasicMathematicsFunctions unit test,
 *    containing all basic mathematics functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 7
 *    Check status      : Checked
 *
 *    Author            : B. Romgens
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : bart.romgens@gmail.com
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : K. Kumar
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
 */

// Include statements.
#include <cmath>
#include <iostream>
#include "Mathematics/basicMathematicsFunctions.h"

//! Function to test modulo function.
/**
 * \param Return true if the test fail to meet the required test accuracy 
 *               (something does not work as expected)
 */
bool testModuloFunction( )
{
    using std::cerr;
    using std::endl;
    using std::fabs;
    using tudat::mathematics::computeModulo;

    // Declare and initialize test result to false.
    bool isBasicMathematicsFunctionErroneous = false;

    // Test modulo function.
    // Test 1: Test 0.0 mod 0.0.
    // Test 2: Test 2.0 mod 0.0.
    // Test 3: Test 2.0 mod 2.0.
    // Test 4: Test 3.0 mod 2.5.
    // Test 5: Test 3.0 mod -2.5.

    {
        double resultUsingModuloFunction = computeModulo( 0.0, 0.0 );

        if ( fabs( resultUsingModuloFunction - 0.0 ) > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The computeModulo function does not "
                 << "function correctly, as the computed value: "
                 << resultUsingModuloFunction
                 << " does not match the expected value: " << 0.0 << endl;
            isBasicMathematicsFunctionErroneous = true;
        }
    }

    {
        double resultUsingModuloFunction = computeModulo( 2.0, 0.0 );

        if ( fabs( resultUsingModuloFunction - 2.0 ) > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The computeModulo function does not "
                 << "function correctly, as the computed value: "
                 << resultUsingModuloFunction
                 << " does not match the expected value: " << 2.0 << endl;
            isBasicMathematicsFunctionErroneous = true;
        }
    }

    {
        double resultUsingModuloFunction = computeModulo( 2.0, 2.0 );

        if ( fabs( resultUsingModuloFunction - 0.0 ) > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The computeModulo function does not "
                 << "function correctly, as the computed value: "
                 << resultUsingModuloFunction
                 << " does not match the expected value: " << 0.0 << endl;
            isBasicMathematicsFunctionErroneous = true;
        }
    }

    {
        double resultUsingModuloFunction = computeModulo( 3.0, 2.5 );

        if ( fabs( resultUsingModuloFunction - 0.5 ) > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The computeModulo function does not "
                 << "function correctly, as the computed value: "
                 << resultUsingModuloFunction
                 << " does not match the expected value: " << -0.5 << endl;
            isBasicMathematicsFunctionErroneous = true;
        }
    }

    {
        double resultUsingModuloFunction = computeModulo( 3.0, -2.5 );

        if ( fabs( resultUsingModuloFunction + 2.0 ) > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The computeModulo function does not "
                 << "function correctly, as the computed value: "
                 << resultUsingModuloFunction
                 << " does not match the expected value: " << -2.0 << endl;
            isBasicMathematicsFunctionErroneous = true;
        }
    }
    return isBasicMathematicsFunctionErroneous;
}

//! Test implementation of basic mathematics functions.
int main( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;
    using std::fabs;
    using tudat::mathematics::computeModulo;

    // Declare and initialize test result to false.
    bool isBasicMathematicsFunctionsErroneous = false;

    if( testModuloFunction( ) )
    {
        isBasicMathematicsFunctionsErroneous = true;
    }

    // Return a message if a test has failed.
    if( isBasicMathematicsFunctionsErroneous == true )
    {
        std::cerr << "testBasicMathematicsFunctions failed!" << std::endl;
    }

    // Return a non-zero exit code if any test failed
    return isBasicMathematicsFunctionsErroneous;
}
