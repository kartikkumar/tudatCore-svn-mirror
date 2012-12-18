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
 *      100903    K. Kumar          File created.
 *      100916    L. Abdulkadir     File checked.
 *      100929    K. Kumar          Checked code by D. Dirkx added.
 *      101110    K. Kumar          Added raiseToExponentPower() function.
 *      102410    D. Dirkx          Minor comment changes as code check.
 *      101213    K. Kumar          Bugfix raiseToIntegerExponent(); renamed raiseToIntegerPower().
 *                                  Added computeAbsoluteValue() functions.
 *      110202    K. Kumar          Added overload for State* for computeLinearInterpolation().
 *      110111    J. Melman         Added computeModulo() function.
 *      110411    K. Kumar          Added convertCartesianToSpherical() function.
 *      110606    J. Melman         Removed possible singularity from
 *                                  convertCartesianToSpherical.
 *      110707    K. Kumar          Added computeSampleMean(), computeSampleVariance() functions.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      120127    D. Dirkx          First version branched from basic mathematics in Tudat Core.
 *      120127    K. Kumar          Minor comment edits.
 *      120716    D. Dirkx          Fixed bug in else-case in convertCartesianToSpherical().
 *      121205    D. Dirkx          Migrated namespace to directory-based protocol.
 *      121205    K. Kumar          Fixed incorrect namespace migration.
 *
 *    References
 *
 *    Notes
 *
 */

#include <cmath>
#include <limits>
#include <numeric>

#include "TudatCore/Mathematics/BasicMathematics/coordinateConversions.h"

namespace tudat
{
namespace basic_mathematics
{
namespace coordinate_conversions
{

//! Convert spherical (radius_, zenith, azimuth) to Cartesian (x,y,z) coordinates.
Eigen::VectorXd convertSphericalToCartesian( const Eigen::VectorXd& sphericalCoordinates )
{
    // Create local variables.
    double radius_ = sphericalCoordinates( 0 );
    double zenithAngle_ = sphericalCoordinates( 1 );
    double azimuthAngle_ = sphericalCoordinates( 2 );

    // Declaring sine which has multiple usages to save computation time.
    double sineOfZenithAngle_ = std::sin( sphericalCoordinates( 1 ) );

    // Create output VectorXd.
    Eigen::VectorXd convertedCartesianCoordinates_ = Eigen::VectorXd::Zero( 3 );

    // Perform transformation.
    convertedCartesianCoordinates_( 0 ) = radius_ * std::cos( azimuthAngle_ ) * sineOfZenithAngle_;
    convertedCartesianCoordinates_( 1 ) = radius_ * std::sin( azimuthAngle_ ) * sineOfZenithAngle_;
    convertedCartesianCoordinates_( 2 ) = radius_ * std::cos( zenithAngle_ );

    return convertedCartesianCoordinates_;
}

//! Convert Cartesian (x,y,z) to spherical (radius, zenith, azimuth) coordinates.
Eigen::VectorXd convertCartesianToSpherical( const Eigen::VectorXd& cartesianCoordinates )
{
    // Create output VectorXd.
    Eigen::VectorXd convertedSphericalCoordinates_ = Eigen::VectorXd::Zero( 3 );

    // Compute transformation of Cartesian coordinates to spherical coordinates.
    convertedSphericalCoordinates_( 0 ) = cartesianCoordinates.norm( );

    // Check if coordinates are at origin.
    if ( convertedSphericalCoordinates_( 0 ) < std::numeric_limits< double >::epsilon( ) )
    {
        convertedSphericalCoordinates_( 1 ) = 0.0;
        convertedSphericalCoordinates_( 2 ) = 0.0;
    }
    // Else compute coordinates using trigonometric relationships.
    else
    {
        convertedSphericalCoordinates_( 1 ) = std::acos( cartesianCoordinates( 2 )
                                                         / convertedSphericalCoordinates_( 0 ) );
        convertedSphericalCoordinates_( 2 ) = std::atan2( cartesianCoordinates( 1 ),
                                                          cartesianCoordinates( 0 ) );        
    }

    return convertedSphericalCoordinates_;
}

} // namespace coordinate_conversions
} // namespace basic_mathematics
} // namespace tudat
