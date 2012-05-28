/*    Copyright (c) 2010-2012, Delft University of Technology
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without modification, are
 *    permitted provided that the following conditions are met:
 *      - Redistributions of source code must retain the above copyright notice, this list of
 *        conditions and the following disclaimer.
 *      - Redistributions in binary form must reproduce the above copyright notice, this list of
 *        conditions and the following disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *      - Neither the name of the Delft University of Technology nor the names of its contributors
 *        may be used to endorse or promote products derived from this software without specific
 *        prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 *    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGE.
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
 *      120204    K. Kumar          Transferred unit tests to Boost unit test framework.
 *
 *    References
 *      Wikipedia. http://en.wikipedia.org/wiki/Neptune, last accessed: 27 January, 2012(a).
 *      Wikipedia. http://en.wikipedia.org/wiki/Mile, last accessed: 27 January, 2012(b).
 *      Wikipedia. http://en.wikipedia.org/wiki/Atmospheric_pressure,
 *          last accessed: 27 January, 2012(c).
 *      Wikipedia. http://en.wikipedia.org/wiki/Temperature_conversion_formulas,
 *          last accessed: 27, January 2012(d).
 *
 *    At the moment, not all conversion routines are tested both ways. This should be corrected in
 *    an update version.
 */

#define BOOST_TEST_MAIN

#include <cmath>
#include <limits>

#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>

#include "TudatCore/Astrodynamics/BasicAstrodynamics/physicalConstants.h"
#include "TudatCore/Astrodynamics/BasicAstrodynamics/unitConversions.h"

namespace tudat
{
namespace unit_tests
{

//! Test suit for unit conversions.
BOOST_AUTO_TEST_SUITE( test_unit_conversions )

//! Test conversion from kilometers to meters.
BOOST_AUTO_TEST_CASE( testConversionFromKilometersToMeters )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertKilometersToMeters( 1.0e6 ),
                                1.0e6 * 1.0e3, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from degrees to radians.
BOOST_AUTO_TEST_CASE( testConversionFromDegreesToRadians )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertDegreesToRadians( 45.0 ),
                                mathematics::PI / 4.0, std::numeric_limits< double >::epsilon( ) );
}


//! Test conversion from degrees to arcminutes.
BOOST_AUTO_TEST_CASE( testConversionFromDegreesToArcminutes )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertDegreesToArcminutes( 43.2 ),
                                43.2 * 60.0, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from arcminutes to arcseconds.
BOOST_AUTO_TEST_CASE( testConversionFromArcminutesToArcSeconds )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertArcminutesToArcseconds( 125.9 ),
                                125.9 * 60.0, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from astronomical units to meters.
BOOST_AUTO_TEST_CASE( testConversionFromAstronomicalUnitsToMeters )
{
    // Case: Neptune's semi-major axis (Wikipedia, 2012a).
    BOOST_CHECK_CLOSE_FRACTION(
                tudat::unit_conversions::convertAstronomicalUnitsToMeters( 30.10366151 ),
                                4.503443661e+12, 1.0e-9 );
}

//! Test conversion from minutes to seconds.
BOOST_AUTO_TEST_CASE( testConversionFromMinutesToSeconds )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertMinutesToSeconds( 12.0 ),
                                12.0 * 60.0, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from seconds to minutes.
BOOST_AUTO_TEST_CASE( testConversionFromSecondsToMinutes )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertSecondsToMinutes( 12.0 ),
                                0.2, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from hours to Julian years.
BOOST_AUTO_TEST_CASE( testConversionFromHoursToJulianYears )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertJulianDaysToJulianYears(
                                    tudat::unit_conversions::convertSecondsToJulianDays(
                                        tudat::unit_conversions::convertHoursToSeconds( 24.0 ) ) ),
                                1.0 / 365.25, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from Julian years to hours.
BOOST_AUTO_TEST_CASE( testConversionFromJulianYearsToHours )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertSecondsToHours(
                                    tudat::unit_conversions::convertJulianDaysToSeconds(
                                        tudat::unit_conversions::convertJulianYearsToJulianDays(
                                            1.0 / 365.25 ) ) ),
                                24.0, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from sidereal days to seconds.
BOOST_AUTO_TEST_CASE( testConversionFromSiderealDaysToSeconds )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertSiderealDaysToSeconds( 7.0 ),
                                7.0 * tudat::physical_constants::SIDEREAL_DAY,
                                std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from seconds to sidereal days.
BOOST_AUTO_TEST_CASE( testConversionFromSecondsToSiderealDays )
{
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertSecondsToSiderealDays( 100.0 ),
                                100.0 / tudat::physical_constants::SIDEREAL_DAY,
                                std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion of temperature in Rankine to Kelvin.
BOOST_AUTO_TEST_CASE( testConversionFromRankineToKelvin )
{
    // Case: 0 deg Celcius (Wikipedia, 2011d).
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertRankineToKelvin( 491.67 ),
                                273.15, std::numeric_limits< double >::epsilon( ) );
}

//! Test conversion from distance in feet to meters.
BOOST_AUTO_TEST_CASE( testConversionFromFeetToMeters )
{
    // Case: length of a statute mile (Wikipedia, 2011b).
    BOOST_CHECK_CLOSE_FRACTION( tudat::unit_conversions::convertFeetToMeter( 5280.0 ),
                                1609.344, std::numeric_limits< double >::epsilon( ) );
}


//! Test conversion from pounds-per-square-feet to Pascal.
BOOST_AUTO_TEST_CASE( testConversionFromPoundsPerSquareFeetToPascal )
{
    // Case: atmospheric pressure at sea level (Wikipedia, 2011c).
    BOOST_CHECK_CLOSE_FRACTION(
                tudat::unit_conversions::convertPoundPerSquareFeetToPascal( 2116.21662367394 ),
                101325.0, 1.0e-9 );
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests
} // namespace tudat
