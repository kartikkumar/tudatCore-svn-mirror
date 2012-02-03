/*! \file unitTestUnitConversions.cpp
 *    This unit test will test the unit conversions that are
 *    defined in unitConversions.h.
 *
 *    Path              : /Astrodynamics/
 *    Version           : 7
 *    Check status      : Checked
 *
 *    Author/Checker    : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Author            : F. M. Engelen
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : F.M.Engelen@student.tudelft.nl
 *
 *    Checker           : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Checker           : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Date created      : 10 September, 2010
 *    Last modified     : 27 January, 2012
 *
 *    References
 *      Wikipedia. http://en.wikipedia.org/wiki/Neptune, last accessed: 27 January, 2012(a).
 *      Wikipedia. http://en.wikipedia.org/wiki/Mile, last accessed: 27 January, 2012(b).
 *      Wikipedia. http://en.wikipedia.org/wiki/Atmospheric_pressure,
 *          last accessed: 27 January, 2012(c).
 *      Wikipedia. http://en.wikipedia.org/wiki/Temperature_conversion_formulas,
 *          last accessed: 27, January 2012(d).
 *
 *    Notes
 *      At the moment, not all conversion routines are test both ways. This
 *      should be modified in a next version.
 *
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
 *      110111    J. Melman         First creation of code.
 *      110124    J. Melman         Adapted to the offical Tudat standards.
 *      110411    K. Kumar          Added unit tests for
 *                                  convertDegreesToArcminutes() and
 *                                  convertArcminutesToArcseconds().
 *      110615    F.M. Engelen      Added Rankine, feet, and pound/m^2
 *                                  conversion. Solved bug with respect to
 *                                  absolute precision and relative precision.
 *      110808    J. Melman         Added time conversion unit tests.
 *      110809    K. Kumar          Minor corrections.
 *      110810    J. Melman         Added 3 more time conversion unit tests.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      110127    D. Dirkx          Minor textual changes and made consistent with rewrite of
 *                                  physical constants.
 */

// Include statements.
#include <cmath>
#include <iostream>
#include <limits>
#include "TudatCore/Astrodynamics/physicalConstants.h"
#include "TudatCore/Astrodynamics/unitConversions.h"

//! Test conversion from kilometers to meters.
/*!
 * Tests conversion from kilometers to meters.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromKilometersToMeters( )
{
    if ( std::fabs( tudat::unit_conversions::convertKilometersToMeters( 1.0e6 )
                    - 1.0e6 * 1.0e3 ) / 1.0e9 > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from degrees to radians.
/*!
 * Tests conversion from degrees to radians.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromDegreesToRadians( )
{
    if ( std::fabs( tudat::unit_conversions::convertDegreesToRadians( 45.0 ) - M_PI / 4.0 )
         / M_PI / 4.0 > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from degrees to arcminutes.
/*!
 * Tests conversion from degrees to arcminutes.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromDegreesToArcminutes( )
{
    if ( std::fabs( tudat::unit_conversions::convertDegreesToArcminutes( 43.2 ) - 43.2 * 60.0 )
         / ( 43.2 * 60.0 ) > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from arcminutes to arcseconds.
/*!
 * Tests conversion from arcminutes to arcseconds.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromArcminutesToArcSeconds( )
{
    if ( std::fabs( tudat::unit_conversions::convertArcminutesToArcseconds( 125.9 )
                    - 125.9 * 60.0 ) / ( 125.9 * 60.0 )
         > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from astronomical units to meters.
/*!
 * Tests conversion from astronomical units to meters.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromAstronomicalUnitsToMeters( )
{
    // Case: Neptune's semi-major axis (Wikipedia, 2012a).
    if ( std::fabs( tudat::unit_conversions::convertAstronomicalUnitsToMeters( 30.10366151 )
                    - 4.503443661e+12 ) > 1.0e3 )
    { return true; }
    else
    { return false; }
}

//! Test conversion from minutes to seconds.
/*!
 * Tests conversion from minutes to seconds.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromMinutesToSeconds( )
{
    if ( std::fabs( tudat::unit_conversions::convertMinutesToSeconds( 12.0 ) - 12.0 * 60.0 )
         / ( 12.0 * 60.0 ) > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from seconds to minutes.
/*!
 * Tests conversion from seconds to minutes.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromSecondsToMinutes( )
{
    if ( std::fabs( tudat::unit_conversions::convertSecondsToMinutes( 12.0 ) - 0.2 ) / 0.2
         > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from hours to Julian years.
/*!
 * Test conversion from hours to Julian years.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromHoursToJulianYears( )
{
    if ( std::fabs( tudat::unit_conversions::convertJulianDaysToJulianYears(
                        tudat::unit_conversions::convertSecondsToJulianDays(
                            tudat::unit_conversions::convertHoursToSeconds( 24.0 ) ) )
               - 1.0 / 365.25 ) / ( 1.0 / 365.25 )  > std::numeric_limits< double >::epsilon( )  )
    { return true; }
    else
    { return false; }
}

//! Test conversion from Julian years to hours.
/*!
 * Tests conversion from Julian years to hours.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromJulianYearsToHours( )
{
    if ( std::fabs( tudat::unit_conversions::convertSecondsToHours(
                        tudat::unit_conversions::convertJulianDaysToSeconds(
                            tudat::unit_conversions::convertJulianYearsToJulianDays(
                                1.0 / 365.25 ) ) )
                    - 24.0 ) / ( 24.0 )  > std::numeric_limits< double >::epsilon( )  )
    { return true; }
    else
    { return false; }
}

//! Test conversion from sidereal days to seconds.
/*!
 * Tests conversion from sidereal days to seconds.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromSiderealDaysToSeconds( )
{
    if ( std::fabs( tudat::unit_conversions::convertSiderealDaysToSeconds( 7.0 )
                    - 7.0 * tudat::physical_constants::SIDEREAL_DAY )
         / ( 7.0 * tudat::physical_constants::SIDEREAL_DAY )
         > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion from seconds to sidereal days.
/*!
 * Tests conversion from seconds to sidereal days.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromSecondsToSiderealDays( )
{
    if ( std::fabs( tudat::unit_conversions::convertSecondsToSiderealDays( 100.0 ) -
                    100.0 / tudat::physical_constants::SIDEREAL_DAY )
         / ( 100.0 / tudat::physical_constants::SIDEREAL_DAY )
         > std::numeric_limits< double >::epsilon( ) )
    { return true; }
    else
    { return false; }
}

//! Test conversion of temperature in Rankine to Kelvin.
/*!
 * Tests conversion of temperature in Rankine to Kelvin
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromRankineToKelvin( )
{
    // Case: 0 degree celcius, (Wikipedia, 2012d)
    if ( std::fabs( tudat::unit_conversions::convertRankineToKelvin( 491.67 ) - 273.15 )
         / 273.15 > std::numeric_limits< double >::epsilon( ) )
    { return true; }

    else
    { return false; }
}

//! Test conversion from distance in feet to meters.
/*!
 * Tests conversion from distance in feet to meters.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromFeetToMeters( )
{
    // Case: length of a statute mile (Wikipedia, 2011b).
    if ( std::fabs( tudat::unit_conversions::convertFeetToMeter( 5280.0 ) - 1609.344 ) / 1609.344
         > std::numeric_limits< double >::epsilon( )  )
    { return true; }

    else
    { return false; }
}

//! Test conversion from pounds-per-square-feet to Pascal.
/*!
 * Tests conversion from pounds-per-square-feet to Pascal.
 * \return False if test passes and code is working; true if the test fails and the code is
 *         erroneous.
 */
bool testConversionFromPoundsPerSquareFeetToPascal( )
{
    // Case: atmospheric pressure at sea level (Wikipedia, 2011c).
    if ( std::fabs( tudat::unit_conversions::convertPoundPerSquareFeetToPascal( 2116.21662367394 )
                    - 101325.0 ) > 1.0e-4 )
    { return true; }

    else
    { return false; }
}

//! Test unit conversions.
int main( )
{
    // Declare test result boolean.
    bool isUnitConversionsErroneous = false;

    // Test 1: Test conversion from kilometers to meters.
    if ( testConversionFromKilometersToMeters( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from kilometers to meters failed (Test 1)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 2: Test conversion from degrees to radians.
    if ( testConversionFromDegreesToRadians( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from degrees to radians failed (Test 2)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 3: Test conversion from degrees to arcminutes.
    if ( testConversionFromDegreesToArcminutes( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from degrees to arcminutes failed (Test 3)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 4: Test conversion from arcminutes to acrseconds.
    if ( testConversionFromArcminutesToArcSeconds( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from arcminutes to arcseconds failed (Test 4)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 5: Test conversion from astronomical units to meters.
    if ( testConversionFromAstronomicalUnitsToMeters( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from Astronomical Units to meters failed (Test 5)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 6: Test conversion from minutes to seconds.
    if ( testConversionFromMinutesToSeconds( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from minutes to seconds failed (Test 6)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 7: Test conversion from seconds to minutes.
    if ( testConversionFromSecondsToMinutes( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from seconds to minutes failed (Test 7)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 8: Test conversion from hours to Julian years.
    if ( testConversionFromHoursToJulianYears( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from hours to Julian years failed (Test 8)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 9: Test conversion from Julian years to hours.
    if ( testConversionFromJulianYearsToHours( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from Julian years to hours failed (Test 9)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 10: Test conversion from Sidereal days to seconds.
    if ( testConversionFromSiderealDaysToSeconds( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from Sidereal days to seconds failed (Test 10)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 11: Test conversion from seconds to Sidereal days.
    if ( testConversionFromSecondsToSiderealDays( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from seconds to Sidereal days failed (Test 11)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 12: Test conversion from Rankine to Kelvin.
    if ( testConversionFromRankineToKelvin( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from Rankine to Kelvin failed (Test 12)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 13: Test conversion from feet to meters.
    if ( testConversionFromFeetToMeters( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from feet to meters failed (Test 13)."
                  << std::endl;
        isUnitConversionsErroneous = true;
    }

    // Test 14: Test conversion from pounds-per-square-feet to Pascals.
    if ( testConversionFromPoundsPerSquareFeetToPascal( ) == true )
    {
        std::cerr << "ERROR: Test of conversion from pounds-per-square-feet to Pascals failed "
                  << "(Test 14)." << std::endl;
        isUnitConversionsErroneous = true;
    }

    return isUnitConversionsErroneous;
}

// End of file.
