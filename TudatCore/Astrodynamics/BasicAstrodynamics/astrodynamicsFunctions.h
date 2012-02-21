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
 *      100906    K. Kumar          First creation of code.
 *      111115    K. Kumar          Added checker info; corrected Doxygenc comments.
 *      120127    D. Dirkx          Moved file to Tudat core.
 *
 *    References
 *
 */

#ifndef TUDAT_CORE_ASTRODYNAMICS_FUNCTIONS_H
#define TUDAT_CORE_ASTRODYNAMICS_FUNCTIONS_H

#include "TudatCore/Astrodynamics/BasicAstrodynamics/physicalConstants.h"

namespace tudat
{
namespace astrodynamics
{

//! Compute two-body orbital period.
/*!
 * Computes the two-body orbital period of an orbiting body that follows a closed conic section
 * (circle or ellipse Kepler orbit). The mass of the orbiting body is set to that of a test
 * particle by default.
 * \param semiMajorAxis Semi-major axis of Kepler orbit (circle or ellipse).
 * \param gravitationalParameterOfCentralBody Gravitational parameter of central body.
 * \param massOfOrbitingBody Mass of orbiting body.
 * \return Two-body orbital period.
 */
double computeKeplerOrbitalPeriod( const double semiMajorAxis,
                                   const double gravitationalParameterOfCentralBody,
                                   const double massOfOrbitingBody = 0.0 );

//! Compute two-body angular momentum.
/*!
 * Computes the angular momentum of an orbiting body that follows a conic section (Kepler orbit), 
 * relative to the center-of-mass of the central body. The default mass value is for the angular 
 * momentum per unit mass.
 * \param semiMajorAxis Semi-major axis of Kepler orbit.
 * \param eccentricity Eccentricity of Kepler orbit.
 * \param gravitationalParameterOfCentralBody Gravitational parameter of central body.
 * \param massOfOrbitingBody Mass of orbiting body.
 * \return Two-body angular momentum.
 */
double computeKeplerAngularMomentum( const double semiMajorAxis, const double eccentricity,
                                     const double gravitationalParameterOfCentralBody,
                                     const double massOfOrbitingBody = 1.0 );

//! Compute two-body mean motion.
/*!
 * Computes the two-body mean motion of an orbiting body that follows a conic section
 * (Kepler orbit). The mass of the orbiting body is set to that of a test particle by default.
 * \param semiMajorAxis Semi-major axis of Kepler orbit.
 * \param gravitationalParameterOfCentralBody Gravitational parameter of central body.
 * \param massOfOrbitingBody Mass of orbiting body.
 * \return Two-body mean motion.
 */
double computeKeplerMeanMotion( const double semiMajorAxis,
                                 const double gravitationalParameterOfCentralBody,
                                 const double massOfOrbitingBody = 0.0 );

//! Compute Kepler energy.
/*!
 * Computes the energy of an orbiting body that follows a conic section (Kepler orbit). The 
 * default mass value is for the two-body orbital energy per unit mass. For closed conic sections 
 * (circles, ellipses), the semi-major axis is positive, and for open sections (hyperbolas) the 
 * semi-major axis is negative.
 * \param semiMajorAxis Semi-major axis of Kepler orbit.
 * \param gravitationalParameterOfCentralBody Gravitational parameter of central body.
 * \param massOfOrbitingBody Mass of orbiting body.
 * \return Kepler orbital energy.
 */
double computeKeplerEnergy( const double semiMajorAxis,
                            const double gravitationalParameterOfCentralBody,
                            const double massOfOrbitingBody = 1.0 );

//! Compute synodic period.
/*!
 * Computes synodic period between two bodies in different Kepler orbits (closed conic sections).
 * The orbital periods must be positive values for the synodic period to be sensible.
 * \param orbitalPeriodBody1 Orbital period of Body 1.
 * \param orbitalPeriodBody2 Orbital period of Body 2.
 * \return Synodic period.
 */
double computeSynodicPeriod( const double orbitalPeriodBody1, const double orbitalPeriodBody2 );

} // namespace astrodynamics
} // namespace tudat

#endif // TUDAT_CORE_ASTRODYNAMICS_FUNCTIONS_H