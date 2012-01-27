/*! \file basicMathematicsFunctions.cpp
 *    Source file that defines the basicMathematicsFunctions namespace,
 *    containing all basic functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 12
 *    Check status      : Checked
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Author            : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Author            : J.C.P Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Checker           : L. Abdulkadir
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : L.Abdulkadir@student.tudelft.nl
 *
 *    Checker           : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
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
 *      120127    D. Dirkx          First version branched from basic mathematics in Tudat core.
 */

// Include statements.
#include <cmath>
#include <limits>
#include <numeric>
#include "Mathematics/coordinateConversions.h"

namespace tudat
{
namespace mathematics
{
namespace coordinate_conversions
{

//! Convert spherical (radius, zenith, azimuth) to Cartesian (x,y,z) coordinates.
Eigen::VectorXd convertSphericalToCartesian( const Eigen::VectorXd& sphericalCoordinates )
{
    // Create local variables.
    double radius = sphericalCoordinates( 0 );
    double zenithAngle = sphericalCoordinates( 1 );
    double azimuthAngle = sphericalCoordinates( 2 );

    // Declaring sine which has multiple usages to save computation time.
    double sineOfZenithAngle = std::sin( sphericalCoordinates( 1 ) );

    // Create output VectorXd.
    Eigen::VectorXd cartesianCoordinates = Eigen::VectorXd( 3 );

    // Perform transformation.
    cartesianCoordinates( 0 ) = radius * std::cos( azimuthAngle ) * sineOfZenithAngle;
    cartesianCoordinates( 1 ) = radius * std::sin( azimuthAngle ) * sineOfZenithAngle;
    cartesianCoordinates( 2 ) = radius * std::cos( zenithAngle );

    return cartesianCoordinates;
}

//! Convert Cartesian (x,y,z) to spherical (radius, zenith, azimuth) coordinates.
Eigen::VectorXd convertCartesianToSpherical( const Eigen::VectorXd&cartesianCoordinates )
{
    // Create output VectorXd.
    Eigen::VectorXd sphericalCoordinates = Eigen::VectorXd( 3 );

    // Compute transformation of Cartesian coordinates to spherical coordinates.
    sphericalCoordinates( 0 ) = cartesianCoordinates.norm( );

    // Check if coordinates are at origin.
    if ( sphericalCoordinates( 0 ) < std::numeric_limits< double >::epsilon( ) )
    {
        sphericalCoordinates( 1 ) = 0.0;
        sphericalCoordinates( 2 ) = 0.0;
    }
    // Else compute coordinates using trigonometric relationships.
    else
    {
        sphericalCoordinates( 1 ) = std::atan2( cartesianCoordinates( 1 ),
                                                cartesianCoordinates( 0 ) );
        sphericalCoordinates( 2 ) = std::acos( cartesianCoordinates( 2 )
                                               / sphericalCoordinates( 0 ) );
    }

    return sphericalCoordinates;
}

//! Convert cylindrical (radius, azimuth, z) to Cartesian coordinates (x,y,z), z value unaffected.
Eigen::VectorXd convertCylindricalToCartesian( const Eigen::VectorXd& cylindricalCoordinates )
{
    // Create output VectorXd.
    Eigen::VectorXd cartesianCoordinates = Eigen::VectorXd( 3 );

    // Perform transformation, z value should be set outside function.
    double radius = cylindricalCoordinates( 0 );
    double azimuthAngle =  cylindricalCoordinates( 1 );
    cartesianCoordinates( 0 ) = radius * std::cos( azimuthAngle );
    cartesianCoordinates( 1 ) = radius * std::sin( azimuthAngle );
    cartesianCoordinates( 2 ) = cylindricalCoordinates( 2 );

    return cartesianCoordinates;
}

} // namespace coordinate_conversions
} // namespace mathematics
} // namespace tudat
