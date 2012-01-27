/*! \file physicalConstants.h
 *    This file contains a class with selected constants commonly used in astrodynamics.
 *
 *    Path              : /Astrodynamics/
 *    Version           : 3
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
 *    Date created      : 3 September, 2010
 *    Last modified     : 27 January, 2012
 *
 *    References
 *      Standish, E.M. (1995) "Report of the IAU WGAS Sub-Group on Numerical
 *          Standards", in Highlights of Astronomy (I. Appenzeller, ed.),
 *          Table 1, Kluwer Academic Publishers, Dordrecht.
 *      Standish, E.M. (1998) "JPL Planetary and Lunar Ephemerides,
 *          DE405/LE405", JPL IOM 312.F-98-048.
 *
 *    Notes
 *      The reference for the sidereal day and year should be updated.
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
 *      100906    J. Melman         First creation of code.
 *      110124    K. Kumar          Split into .h and .cpp files.
 *      110629    F.M. Engelen      Added specific gas constants.
 *      120127    D. Dirkx          Moved to Tudat core, removed variables related to
 *                                  obliquity of ecliptic.
 */

#ifndef TUDAT_PHYSICAL_CONSTANTS_H
#define TUDAT_PHYSICAL_CONSTANTS_H

namespace tudat
{

namespace physical_constants
{

//! Julian day.
/*!
 * Julian day in seconds.
 * Reference: http://ssd.jpl.nasa.gov/?constants#ref (temporary).
 */
const static double JULIAN_DAY = 86400.0;

//! Julian year in days.
/*!
 * Julian year in Julian days.
 * Reference: http://ssd.jpl.nasa.gov/?constants#ref (temporary).
 */
const static double JULIAN_YEAR_IN_DAYS = 365.25;

//! Julian year.
/*!
 * Julian year in seconds. Result of JULIAN_YEAR_IN_DAYS * JULIAN_DAY.
 */
const static double JULIAN_YEAR = 3.15576e7;

//! Sidereal day.
/*!
 * Sidereal day in seconds.
 * Reference: http://ssd.jpl.nasa.gov/?constants#ref (temporary).
 */
const static double SIDEREAL_DAY = 86164.09054;

//! Sidereal year in days.
/*!
 * Sidereal year in Julian days in quasar reference frame.
 * Reference: http://ssd.jpl.nasa.gov/?constants#ref (temporary).
 */
const static double SIDEREAL_YEAR_IN_DAYS = 365.25636;

//! Sidereal year.
/*!
 * Sidereal year in seconds in quasar reference frame. Result of
 * SIDEREAL_YEAR_IN_DAYS * JULIAN_DAY.
 */
const static double SIDEREAL_YEAR = 3.1558149504e7;

//! Speed of light.
/*!
 * Speed of light in meters per second.
 * Reference: Standish, E.M. (1995) "Report of the IAU WGAS Sub-Group on Numerical Standards",
 *            in Highlights of Astronomy (I. Appenzeller, ed.), Table 1,
 *            Kluwer Academic Publishers, Dordrecht.
 *            http://iau-comm4.jpl.nasa.gov/iausgnsrpt.pdf.
 */
const static double SPEED_OF_LIGHT = 299792458.0;

//! Gravitational constant.
/*!
 * Gravitational constant in meter^3 per kilogram per second^2.
 * Reference: Standish, E.M. (1995) "Report of the IAU WGAS Sub-Group on Numerical Standards",
 *            in Highlights of Astronomy (I. Appenzeller, ed.), Table 1,
 *            Kluwer Academic Publishers, Dordrecht.
 *            http://iau-comm4.jpl.nasa.gov/iausgnsrpt.pdf
 */
const static double GRAVITATIONAL_CONSTANT = 6.67259e-11;

//! Astronomical Unit.
/*!
 * Astronomical Unit in meters.
 * Reference: Standish, E.M. (1998) "JPL Planetary and Lunar Ephemerides, DE405/LE405",
 *            JPL IOM 312.F-98-048. http://iau-comm4.jpl.nasa.gov/de405iom/de405iom.pdf.
 */
const static double ASTRONOMICAL_UNIT = 1.49597870691e11;


}

}

#endif // TUDAT_PHYSICAL_CONSTANTS_H
