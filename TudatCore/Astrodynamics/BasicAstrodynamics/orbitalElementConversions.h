/*! \file orbitalElementConversions.h
 *    This header file contains a namespace with orbital element conversion functions.
 *
 *    Path              : /Astrodynamics/BasicAstrodynamics/
 *    Version           : 11
 *    Check status      : Checked
 *
 *    Author            : E. Iorfida
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : elisabetta_iorfida@yahoo.it
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Checker           : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Checker           : B. Tong Minh
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : B.TongMinh@student.tudelft.nl
 *
 *    Date created      : 20 October, 2010
 *    Last modified     : 31 January, 2012
 *
 *    References
 *      Chobotov, V.A. Orbital Mechanics, Third Edition, AIAA Education Series, VA, 2002.
 *      Wertz, J. R. Mission geometry; orbit and constellation design and management.
 *      Mengali, G., Quarta, A.A. Fondamenti di meccanica del volo spaziale.
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
 *      101020    K. Kumar          First creation of code.
 *      101025    E. Iorfida        Fulfillment of the code with gravitational parameter.
 *      101130    E. Iorfida        Gravitational parameter removed.
 *      101202    J. Melman         Replaced endif statement and changed. Doxygen return statement.
 *      101203    E. Iorfida        Gravitational parameter added.
 *      101219    J. Melman         Doxygen comment on gravitational parameter added.
 *      110128    K. Kumar          Changed references to pointers for functions.
 *      110510    K. Kumar          Updated conversion functions to not use dynamic memory
 *                                  allocation.
 *      110805    K. Kumar          Added mean motion to semi-major axis conversion.
 *      110810    J. Leloux         Corrected doxygen documentation.
 *      120131    K. Kumar          Adapted for Tudat Core, interfaces changed to use VectorXd,
 *                                  only Keplerian <-> Cartesian conversions included.
 */

#ifndef TUDAT_CORE_ORBITAL_ELEMENT_CONVERSIONS_H
#define TUDAT_CORE_ORBITAL_ELEMENT_CONVERSIONS_H

// Include statements.
#include <Eigen/Core>

//! Tudat library namespace.
/*!
 * The Tudat library namespace.
 */
namespace tudat
{

//! Orbital element conversions namespace.
/*!
 * Orbital element conversions namespace, containing classical Keplerian to Cartesian element
 * conversions, and other conversions between classical Keplerian elements, e.g., true anomaly
 * to/from eccentric anomaly.
 */
namespace orbital_element_conversions
{

//! Keplerian element vector indices.
/*!
 * Keplerian elements defined by the following indices in VectorXd(6) objects:
 *  semi-major axis = 0,
 *  eccentricity = 1,
 *  inclination = 2,
 *  argument of periapsis = 3,
 *  longitude of ascending node = 4,
 *  true anomaly = 5.
 */
enum KeplerianElementVectorIndices
{
    semiMajorAxisIndex, eccentricityIndex, inclinationIndex, argumentOfPeriapsisIndex,
    longitudeOfAscendingNodeIndex, trueAnomalyIndex
};

//! Cartesian element vector indices.
/*!
 * Cartesian elements defined by the following indices in VectorXd(6) objects:
 *  x-position = 0,
 *  y-position = 1,
 *  z-position = 2,
 *  x-velocity = 3,
 *  y-velocity = 4,
 *  z-velocity = 5.
 */
enum CartesianElementVectorIndices
{ xPositionIndex, yPositionIndex, zPositionIndex, xVelocityIndex, yVelocityIndex, zVelocityIndex };


//! Convert Keplerian to Cartesian orbital elements.
/*!
 * Converts Keplerian to Cartesian orbital elements.
 * \param keplerianElements Vector containing Keplerian elements. Order of elements is important!
 *          keplerianElements( 0 ) = semiMajorAxis,                                             [m]
 *          keplerianElements( 1 ) = eccentricity,                                              [-]
 *          keplerianElements( 2 ) = inclination,                                             [rad]
 *          keplerianElements( 3 ) = argument of periapsis,                                   [rad]
 *          keplerianElements( 4 ) = longitude of ascending node,                             [rad]
 *          keplerianElements( 5 ) = true anomaly.                                            [rad]
 *          WARNING: If eccentricity is 1.0 within machine precision,
 *          keplerianElements( 0 ) = semi-latus rectum.
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.
 * \return Converted state in Cartesian elements. The order of elements is fixed!
 *          cartesianElements( 0 ) = x-position coordinate,                                     [m]
 *          cartesianElements( 1 ) = y-position coordinate,                                     [m]
 *          cartesianElements( 2 ) = z-position coordinate,                                     [m]
 *          cartesianElements( 3 ) = x-velocity coordinate,                                   [m/s]
 *          cartesianElements( 4 ) = y-velocity coordinate,                                   [m/s]
 *          cartesianElements( 5 ) = z-velocity coordinate.                                   [m/s]
 */
Eigen::VectorXd convertKeplerianToCartesianElements(
        const Eigen::VectorXd& keplerianElements, const double centralBodyGravitationalParameter );

//! Convert Cartesian to Keplerian orbital elements.
/*!
 * \param cartesianElements Vector containing Cartesian elements. Order of elements is important!
 *          cartesianElements( 0 ) = x-position coordinate,                                     [m]
 *          cartesianElements( 1 ) = y-position coordinate,                                     [m]
 *          cartesianElements( 2 ) = z-position coordinate,                                     [m]
 *          cartesianElements( 3 ) = x-velocity coordinate,                                   [m/s]
 *          cartesianElements( 4 ) = y-velocity coordinate,                                   [m/s]
 *          cartesianElements( 5 ) = z-velocity coordinate.                                   [m/s]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.
 * \return Converted state in Keplerian elements. The order of elements is fixed!
 *          keplerianElements( 0 ) = semiMajorAxis,                                             [m]
 *          keplerianElements( 1 ) = eccentricity,                                              [-]
 *          keplerianElements( 2 ) = inclination,                                             [rad]
 *          keplerianElements( 3 ) = argument of periapsis,                                   [rad]
 *          keplerianElements( 4 ) = longitude of ascending node,                             [rad]
 *          keplerianElements( 5 ) = true anomaly.                                            [rad]
 *          WARNING: If eccentricity is 1.0 within machine precision,
 *          keplerianElements( 0 ) = semi-latus rectum.
 *          WARNING: If eccentricity is 0.0 within machine precision,
 *          argument of periapsis is set to 0.0.
 *          WARNING: If inclination is 0.0 within machine precision,
 *          longitude of ascending node is set to 0.0.
 */
Eigen::VectorXd convertCartesianToKeplerianElements(
        const Eigen::VectorXd& cartesianElements, const double centralBodyGravitationalParameter );

//! Convert true anomaly to eccentric anomaly.
/*!
 * Converts true anomaly to eccentric anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 ).
 * The equations used can be found in (Chobotov, 2002).
 * \param trueAnomaly True anomaly.                                                           [rad]
 * \param eccentricity Eccentricity.                                                            [-]
 * \return Eccentric anomaly [rad].
 */
double convertTrueAnomalyToEccentricAnomaly( const double trueAnomaly, const double eccentricity );

//! Convert eccentric anomaly to true anomaly.
/*!
 * Converts eccentric anomaly to true anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 ).
 * The equations used can be found in (Chobotov, 2002).
 * \param eccentricAnomaly Eccentric anomaly.                                                 [rad]
 * \param eccentricity Eccentricity.                                                            [-]
 * \return True anomaly.                                                                      [rad]
 */
double convertEccentricAnomalyToTrueAnomaly( const double eccentricAnomaly,
                                             const double eccentricity );

//! Convert true anomaly to hyperbolic eccentric anomaly.
/*!
 * Converts true anomaly to hyperbolic eccentric anomaly for hyperbolic orbits
 * ( eccentricity > 1.0 ). The equations used can be found in (Chobotov, 2002).
 * \param trueAnomaly True anomaly.                                                           [rad]
 * \param eccentricity Eccentricity.                                                            [-]
 * \return Hyperbolic eccentric anomaly.                                                      [rad]
 */
double convertTrueAnomalyToHyperbolicEccentricAnomaly( const double trueAnomaly,
                                                       const double eccentricity );

//! Convert hyperbolic eccentric anomaly to true anomaly.
/*!
 * Converts hyperbolic eccentric anomaly to true anomaly for hyperbolic orbits
 * ( eccentricity > 1.0 ). The equations used can be found in (Chobotov, 2002).
 * \param hyperbolicEccentricAnomaly Hyperbolic eccentric anomaly.                            [rad]
 * \param eccentricity Eccentricity.                                                            [-]
 * \return True anomaly.                                                                      [rad]
 */
double convertHyperbolicEccentricAnomalyToTrueAnomaly( const double hyperbolicEccentricAnomaly,
                                                       const double eccentricity );

//! Convert eccentric anomaly to mean anomaly.
/*!
 * Converts eccentric anomaly to mean anomaly for elliptical orbits ( 0 <= eccentricity < 1.0 ).
 * The equations used can be found in (Chobotov, 2002).
 * \param eccentricity Eccentricity.                                                            [-]
 * \param eccentricAnomaly Eccentric anomaly [rad].
 * \return Mean anomaly [rad].
 */
double convertEccentricAnomalyToMeanAnomaly( const double eccentricAnomaly,
                                             const double eccentricity );

//! Convert hyperbolic eccentric anomaly to mean anomaly.
/*!
 * Converts hyperbolic eccentric anomaly to mean anomaly for hyperbolic orbits
 * ( eccentricity > 1.0 ). The equations used can be found in (Chobotov, 2002).
 * \param hyperbolicEccentricAnomaly Hyperbolic eccentric anomaly.                            [rad]
 * \param eccentricity Eccentricity.                                                            [-]
 * \return Mean anomaly.                                                                      [rad]
 */
double convertHyperbolicEccentricAnomalyToMeanAnomaly( const double hyperbolicEccentricAnomaly,
                                                       const double eccentricity );

//! Convert elapsed time to mean anomaly change for elliptical orbits.
/*!
 * Converts elapsed time to mean anomaly change for elliptical orbits ( 0 <= eccentricity < 1.0 ).
 * The equation used can be found in (Chobotov, 2002).
 * \param elapsedTime Elapsed time.                                                             [s]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \param semiMajorAxis Semi-major axis.                                                        [m]
 * \return Mean anomaly change.                                                               [rad]
 */
double convertElapsedTimeToMeanAnomalyChangeForEllipticalOrbits(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis );

//! Convert mean anomaly change to elapsed time for elliptical orbits.
/*!
 * Converts mean anomaly change to elapsed time for elliptical orbits ( 0 <= eccentricity < 1.0 ).
 * The equation used can be found in (Chobotov, 2002).
 * \param meanAnomalyChange Mean anomaly change.                                              [rad]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \param semiMajorAxis Semi-major axis.                                                        [m]
 * \return Elapsed time.                                                                        [s]
 */
double convertMeanAnomalyChangeToElapsedTimeForEllipticalOrbits(
        const double meanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis );

//! Convert elapsed time to mean anomaly change for hyperbolic orbits.
/*!
 * Converts elapsed time to mean anomaly change for hyperbolic orbits ( eccentricity > 1.0 ).
 * The equation used can be found in (Chobotov, 2002).
 * \param elapsedTime Elapsed time.                                                             [s]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \param semiMajorAxis Semi-major axis.                                                        [m]
 * \return Mean anomaly change.                                                               [rad]
 */
double convertElapsedTimeToMeanAnomalyChangeForHyperbolicOrbits(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis );

//! Convert mean anomaly change to elapsed time for hyperbolic orbits.
/*!
 * Converts mean anomaly change to elapsed time for hyperbolic orbits ( eccentricity > 1.0 ).
 * The equation used can be found in (Chobotov, 2002).
 * \param meanAnomalyChange Mean anomaly change.                                              [rad]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \param semiMajorAxis Semi-major axis.                                                        [m]
 * \return Elapsed time.                                                                        [s]
 */
double convertMeanAnomalyChangeToElapsedTimeForHyperbolicOrbits(
        const double meanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis );

//! Convert mean motion to semi-major axis.
/*!
 * Converts mean motion to semi-major axis.
 * \param meanMotion Mean motion.                                                           [rad/s]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \return semiMajorAxis Semi-major axis.                                                       [m]
 */
double convertMeanMotionToSemiMajorAxis( const double meanMotion,
                                         const double centralBodyGravitationalParameter );

//! Convert semi-major axis to mean motion.
/*!
 * Converts semi-major axis to mean motion.
 * \param semiMajorAxis Semi-major axis.                                                        [m]
 * \param centralBodyGravitationalParameter Gravitational parameter of central body.      [m^3/s^2]
 * \return meanMotion Mean motion.                                                          [rad/s]
 */
double convertSemiMajorAxisToMeanMotion( const double semiMajorAxis,
                                         const double centralBodyGravitationalParameter );

} // namespace orbital_element_conversions.

} // namespace tudat.

#endif // TUDAT_CORE_ORBITAL_ELEMENT_CONVERSIONS_H

// End of file.
