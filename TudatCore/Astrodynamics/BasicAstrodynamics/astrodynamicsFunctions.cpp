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
 *      111115    K. Kumar          Added checker info.
 *      120127    D. Dirkx          File moved to Tudat core.
 *
 *    References
 *
 */

#include <cmath>
#include "TudatCore/Astrodynamics/BasicAstrodynamics/astrodynamicsFunctions.h"
#include "TudatCore/Astrodynamics/BasicAstrodynamics/physicalConstants.h"
#include "TudatCore/Mathematics/BasicMathematics/mathematicalConstants.h"

using tudat::mathematics::PI;

namespace tudat
{
namespace astrodynamics
{

//! Compute Kepler orbital period.
double computeKeplerOrbitalPeriod( const double semiMajorAxis,
                                   const double gravitationalParameterOfCentralBody,
                                   const double massOfOrbitingBody )
{
    return 2.0 * PI * std::sqrt( std::pow( semiMajorAxis, 3.0 )
                                   /  ( ( physical_constants::GRAVITATIONAL_CONSTANT
                                          * massOfOrbitingBody )
                                        + gravitationalParameterOfCentralBody ) );
}

//! Compute Kepler angular momentum.
double computeKeplerAngularMomentum( const double semiMajorAxis, const double eccentricity,
                                     const double gravitationalParameterOfCentralBody,
                                     const double massOfOrbitingBody )
{
    return massOfOrbitingBody * std::sqrt( gravitationalParameterOfCentralBody * semiMajorAxis
                                           * ( 1.0 - std::pow( eccentricity, 2.0 ) ) );
}

//! Compute Kepler mean motion.
double computeKeplerMeanMotion( const double semiMajorAxis,
                                const double gravitationalParameterOfCentralBody,
        const double massOfOrbitingBody )
{
    return std::sqrt( ( ( physical_constants::GRAVITATIONAL_CONSTANT * massOfOrbitingBody )
                      + gravitationalParameterOfCentralBody ) / std::pow( semiMajorAxis, 3.0 ) );
}

//! Compute Kepler orbital energy.
double computeKeplerEnergy( const double semiMajorAxis,
                            const double gravitationalParameterOfCentralBody,
                            const double massOfOrbitingBody )
{
    return -massOfOrbitingBody * gravitationalParameterOfCentralBody / ( 2.0 * semiMajorAxis );
}

//! Compute synodic period.
double computeSynodicPeriod( const double orbitalPeriodBody1, const double orbitalPeriodBody2 )
{
    return 1.0 / std::fabs( 1.0 / orbitalPeriodBody1 - 1.0 / orbitalPeriodBody2 );
}

} // namespace astrodynamics
} // namespace tudat