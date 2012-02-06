/*! \file coordinateConversions.cpp
 *    Source file that implements the coordinate conversion functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 14
 *    Check status      : Checked
 *    Date created      : 3 September, 2010
 *    Last modified     : 27 January, 2012
 *
 *    References
 *      Press W.H., et al. Numerical Recipes in C++: The Art of
 *          Scientific Computing. Cambridge University Press, February 2002.
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
 */

// Include statements.
#include <cmath>
#include <limits>
#include <numeric>
#include "TudatCore/Mathematics/coordinateConversions.h"

//! Convert spherical (radius_, zenith, azimuth) to Cartesian (x,y,z) coordinates.
Eigen::VectorXd tudat::mathematics::coordinate_conversions::convertSphericalToCartesian(
        const Eigen::VectorXd& sphericalCoordinates )
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

//! Convert Cartesian (x,y,z) to spherical (radius_, zenith, azimuth) coordinates.
Eigen::VectorXd tudat::mathematics::coordinate_conversions::convertCartesianToSpherical(
        const Eigen::VectorXd& cartesianCoordinates )
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
        convertedSphericalCoordinates_( 1 ) = std::atan2( cartesianCoordinates( 1 ),
                                                          cartesianCoordinates( 0 ) );
        convertedSphericalCoordinates_( 2 ) = std::acos( cartesianCoordinates( 2 )
                                                         / convertedSphericalCoordinates_( 0 ) );
    }

    return convertedSphericalCoordinates_;
}

//! Convert cylindrical (radius_, azimuth, z) to Cartesian coordinates (x,y,z), z value unaffected.
Eigen::VectorXd tudat::mathematics::coordinate_conversions::convertCylindricalToCartesian(
        const Eigen::VectorXd& cylindricalCoordinates )
{
    // Create output VectorXd.
    Eigen::VectorXd convertedCartesianCoordinates_ = Eigen::VectorXd::Zero( 3 );

    // Perform transformation, z value should be set outside function.
    double radius_ = cylindricalCoordinates( 0 );
    double azimuthAngle_ =  cylindricalCoordinates( 1 );
    convertedCartesianCoordinates_( 0 ) = radius_ * std::cos( azimuthAngle_ );
    convertedCartesianCoordinates_( 1 ) = radius_ * std::sin( azimuthAngle_ );
    convertedCartesianCoordinates_( 2 ) = cylindricalCoordinates( 2 );

    return convertedCartesianCoordinates_;
}

// End of file.
