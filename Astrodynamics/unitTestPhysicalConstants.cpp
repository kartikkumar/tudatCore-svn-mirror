/*! \file unitTestphysical_constants.cpp
 *    This unit test will test the physical constants that are defined in physical_constants.h.
 *
 *    Path              : /Astrodynamics/
 *    Version           : 4
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
 *    Last modified     : 27 January, 2011
 *
 *    References
 *
 *    Notes
 *      Test runs code and verifies result against expected value.
 *      If the tested code is erroneous, the test function returns a boolean
 *      true; if the code is correct, the function returns a boolean false.
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
 */

// Include statements.
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "Astrodynamics/physicalConstants.h"

//! Check if the physical constants have the correct relations (ratios/offsets)
/**
 * \param Return true if the test fail to meet the required test accuracy 
 *               (something does not work as expected)
 */
bool testRelationsBetweenPhysicalConstant( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;
    using std::fabs;

    bool isPhysicalConstantErroneous = false;

    {
        // Test for the number of seconds in a year.
        if ( fabs( ( tudat::physical_constants::JULIAN_YEAR - tudat::physical_constants::JULIAN_DAY
                   * tudat::physical_constants::JULIAN_YEAR_IN_DAYS ) /
                   ( tudat::physical_constants::JULIAN_DAY *
                     tudat::physical_constants::JULIAN_YEAR_IN_DAYS ) )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The Julian year in seconds does not correspond to the Julian "
                 << "day in seconds multiplied with the number of days per year."
                 << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for the number of seconds in a year.
        if ( fabs( ( tudat::physical_constants::SIDEREAL_YEAR -
                     tudat::physical_constants::JULIAN_DAY
                   * tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS ) /
                   ( tudat::physical_constants::JULIAN_DAY
                   * tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS ) )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The sidereal year in seconds does not correspond to the julian "
                 << "day in seconds multiplied with the number of sidereal days per year."<< endl;
            isPhysicalConstantErroneous = true;
        }
    }

    return isPhysicalConstantErroneous;
}

//! Check if physical constants have the expected value
/**
 * \param Return true if the test fail to meet the required test accuracy 
 *               (something does not work as expected)
 */
bool testOtherConstants( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;

    bool isPhysicalConstantErroneous = false;

    {
        // Test for gravitational constant.
        if ( fabs( ( tudat::physical_constants::GRAVITATIONAL_CONSTANT - 6.67259e-11 ) /
             6.67259e-11 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The gravitational constant is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for astronomical unit.
        // As expected, indeed approximately equal to 150 million kilometers.
        if ( fabs( ( tudat::physical_constants::SPEED_OF_LIGHT - 299792458.0 ) / 299792458.0 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The speed of light is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for astronomical unit.
        // As expected, indeed approximately equal to 150 million kilometers.
        if ( fabs( ( tudat::physical_constants::ASTRONOMICAL_UNIT - 1.49597870691e11 ) /
                   1.49597870691e11 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The astronomical unit is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }
    return isPhysicalConstantErroneous;
}

//! Check if the time constants have the expected values
/**
 * \param Return true if the test fail to meet the required test accuracy 
 *               (something does not work as expected)
 */
bool testTimeConstants( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;

    bool isPhysicalConstantErroneous = false;

    {
        // Test for the number of Julian days in a year.
        if ( fabs( ( tudat::physical_constants::JULIAN_YEAR_IN_DAYS - 365.25 ) / 365.25 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The Julian year in days is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for the number of sidereal days in a year.
        if ( fabs( ( tudat::physical_constants::SIDEREAL_YEAR_IN_DAYS - 365.25636 ) / 365.25636 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The sidereal year in days is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for the Julian day length.
        if ( fabs( ( tudat::physical_constants::SIDEREAL_DAY - 86164.09054 ) / 86164.09054 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The sidereal day is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }

    {
        // Test for the sidereal day length.
        if ( fabs( ( tudat::physical_constants::JULIAN_DAY - 86400.0 ) / 86400.0 )
             > std::numeric_limits< double >::epsilon( ) )
        {
            cerr << "The Julian day is not set correctly." << endl;
            isPhysicalConstantErroneous = true;
        }
    }
    
    return isPhysicalConstantErroneous;
}



//! Test physical constants header file.
int main( )
{
    // Using declarations.
    using std::cerr;
    using std::endl;

    // Test result initialised to false.
    bool isPhysicalConstantsErroneous = false;

    if ( testRelationsBetweenPhysicalConstant( ) )
    {
        isPhysicalConstantsErroneous = true;
    }

    if ( testTimeConstants( ) )
    {
        isPhysicalConstantsErroneous = true;
    }

    if ( testOtherConstants( ) )
    {
        isPhysicalConstantsErroneous = true;
    }

    // Return a message if a test has failed.
    if ( isPhysicalConstantsErroneous )
    {
        cerr << "testphysical_constants failed!" << endl;
    }
    // Return a non-zero exit code if any test failed.
    return isPhysicalConstantsErroneous;
}

// End of file.
