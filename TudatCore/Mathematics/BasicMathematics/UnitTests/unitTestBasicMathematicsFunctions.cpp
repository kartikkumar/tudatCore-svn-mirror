/*!   Copyright (c) 2010-2012 Delft University of Technology.
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
 *
 *    References
 *
 */

#include <cmath>
#include <iostream>
#include <limits>
#include "TudatCore/Mathematics/BasicMathematics/basicMathematicsFunctions.h"

//! Test implementation of basic mathematics functions.
int main( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;
    using tudat::mathematics::computeModuloForSignedValues;

    // Declare and initialize test result to false.
    bool isBasicMathematicsFunctionsErroneous = false;

    // Test modulo function.
    // Test 10: Test 0.0 mod 0.0.
    // Test 11: Test 2.0 mod 0.0.
    // Test 12: Test 2.0 mod 2.0.
    // Test 13: Test 3.0 mod 2.5.
    // Test 14: Test 3.0 mod -2.5.
    double resultUsingModuloFunction = computeModuloForSignedValues( 0.0, 0.0 );

    if ( fabs( resultUsingModuloFunction - 0.0 ) > std::numeric_limits< double >::epsilon( ) )
    {
        cerr << "The computeModulo function does not "
             << "function correctly, as the computed value: "
             << resultUsingModuloFunction
             << " does not match the expected value: " << 0.0 << endl;
        isBasicMathematicsFunctionsErroneous = true;
    }

    resultUsingModuloFunction = computeModuloForSignedValues( 2.0, 0.0 );

    if ( fabs( resultUsingModuloFunction - 2.0 ) > std::numeric_limits< double >::epsilon( ) )
    {
        cerr << "The computeModulo function does not "
             << "function correctly, as the computed value: "
             << resultUsingModuloFunction
             << " does not match the expected value: " << 2.0 << endl;
        isBasicMathematicsFunctionsErroneous = true;
    }

    resultUsingModuloFunction = computeModuloForSignedValues( 2.0, 2.0 );

    if ( fabs( resultUsingModuloFunction - 0.0 ) > std::numeric_limits< double >::epsilon( ) )
    {
        cerr << "The computeModulo function does not "
             << "function correctly, as the computed value: "
             << resultUsingModuloFunction
             << " does not match the expected value: " << 0.0 << endl;
        isBasicMathematicsFunctionsErroneous = true;
    }

    resultUsingModuloFunction = computeModuloForSignedValues( 3.0, 2.5 );

    if ( fabs( resultUsingModuloFunction - 0.5 ) > std::numeric_limits< double >::epsilon( ) )
    {
        cerr << "The computeModulo function does not "
             << "function correctly, as the computed value: "
             << resultUsingModuloFunction
             << " does not match the expected value: " << -0.5 << endl;
        isBasicMathematicsFunctionsErroneous = true;
    }

    resultUsingModuloFunction = computeModuloForSignedValues( 3.0, -2.5 );

    if ( fabs( resultUsingModuloFunction + 2.0 ) > std::numeric_limits< double >::epsilon( ) )
    {
        cerr << "The computeModulo function does not "
             << "function correctly, as the computed value: "
             << resultUsingModuloFunction
             << " does not match the expected value: " << -2.0 << endl;
        isBasicMathematicsFunctionsErroneous = true;
    }

    return isBasicMathematicsFunctionsErroneous;
}
