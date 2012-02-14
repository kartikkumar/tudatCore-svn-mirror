/*!   Copyright (c) 2010-2012 Delft University of Technology.
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
 *      101025    E. Iorfida        First development of the code with conversion equations.
 *      101028    E. Iorfida        Modification of code for updating of the  Keplerian elements
 *                                  and Cartesian elements classes.
 *      101103    E. Iorfida        Additional conversion equations for extra  Keplerian elements.
 *      101104    E. Iorfida        Modification of the code (no pointers, but directly call of
 *                                  variables).
 *      101119    E. Iorfida        Removed computation for extra Keplerian elements.
 *      101130    E. Iorfida        Added different orbital cases with if-else operators.
 *      101202    J. Melman         Compile errors taken out.
 *      101203    E. Iorfida        Added gravitational parameter, and modified punctuation.
 *      101215    E. Iorfida        Added tolerance, modified punctuation, added comments, deleted
 *                                  raiseToIntegerExponent, used pow.
 *      101219    J. Melman         Suggested efficiency improvement of if-statements.
 *      110107    E. Iorfida        Written a better definition of the range in which angles are
 *                                  computed, and made some punctuation modifications.
 *      110109    J. Melman         Incorporated function computeModulo and
 *                                  determineAngleBetweenVectors. Reduced number of if-statements
 *                                  considerably and bundled all eccentricity and inclination
 *                                  checks in convertCartesianTopointerToCartesianElements_
 *      110128    K. Kumar          Changed references to pointers.
 *      110204    K. Kumar          Removed "vector" naming.
 *      110310    K. Kumar          Changed right ascension of ascending node to longitude of
 *                                  ascending node.
 *      110510    K. Kumar          Updated conversion functions to not use dynamic memory
 *                                  allocation.
 *      110805    K. Kumar          Added mean motion to semi-major axis conversion.
 *      120131    K. Kumar          Adapted for Tudat Core, interfaces changed to use VectorXd,
 *                                  only Keplerian <-> Cartesian conversions included.
 *      120206    K. Kumar          Added wrapper functions for orbital element conversions when
 *                                  eccentricity is not known a priori (if-statement to choose
 *                                  between elliptical and hyperbolic orbits).
 *
 *    References
 *      Chobotov, V.A. Orbital Mechanics, Third Edition, AIAA Education Series, VA, 2002.
 *      Wertz, J. R. Mission geometry; orbit and constellation design and management.
 *      Mengali, G., Quarta, A.A. Fondamenti di meccanica del volo spaziale.
 *
 */

#include <boost/exception/all.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <Eigen/Geometry>
#include <numeric>
#include <cmath>
#include "TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h"
#include "TudatCore/Mathematics/BasicMathematics/linearAlgebra.h"

namespace tudat
{
namespace orbital_element_conversions
{

//! Convert Keplerian to Cartesian orbital elements.
Eigen::VectorXd convertKeplerianToCartesianElements(
        const Eigen::VectorXd& keplerianElements, const double centralBodyGravitationalParameter )
{
    using std::cos;
    using std::fabs;
    using std::pow;
    using std::sin;
    using std::sqrt;
    using Eigen::Vector2d;
    using Eigen::Vector3d;

    // Set local keplerian elements.
    double semiMajorAxis_ = keplerianElements( semiMajorAxisIndex );
    double eccentricity_ = keplerianElements( eccentricityIndex );
    double inclination_ = keplerianElements( inclinationIndex );
    double argumentOfPeriapsis_ = keplerianElements( argumentOfPeriapsisIndex );
    double longitudeOfAscendingNode_ = keplerianElements( longitudeOfAscendingNodeIndex );
    double trueAnomaly_ = keplerianElements( trueAnomalyIndex );

    // Pre-compute sines and cosines of involved angles for efficient computation.
    double cosineOfInclination_ = cos( inclination_ );
    double sineOfInclination_ = sin( inclination_ );
    double cosineOfArgumentOfPeriapsis_ = cos( argumentOfPeriapsis_ );
    double sineOfArgumentOfPeriapsis_ = sin( argumentOfPeriapsis_ );
    double cosineOfLongitudeOfAscendingNode_ = cos( longitudeOfAscendingNode_ );
    double sineOfLongitudeOfAscendingNode_ = sin( longitudeOfAscendingNode_ );
    double cosineOfTrueAnomaly_ = cos( trueAnomaly_ );
    double sineOfTrueAnomaly_ = sin( trueAnomaly_ );

    // Declare semi-latus rectum.
    double semiLatusRectum_ = -0.0;

    // Compute semi-latus rectum in the case it is not a parabola.
    if ( fabs( eccentricity_ - 1.0 ) > std::numeric_limits< double >::epsilon( )  )
    {  semiLatusRectum_ = semiMajorAxis_ * ( 1.0 - pow( eccentricity_, 2 ) ); }

    // Else set the semi-latus rectum given for a parabola as the first element in the vector
    // of Keplerian elements..
    else
    { semiLatusRectum_ = semiMajorAxis_; }

    // Definition of position in the perifocal coordinate system.
    Vector2d positionPerifocal_ = Eigen::Vector2d::Zero( 2 );
    positionPerifocal_.x( ) = semiLatusRectum_ * cosineOfTrueAnomaly_
            / ( 1.0 + eccentricity_ * cosineOfTrueAnomaly_ );
    positionPerifocal_.y( ) = semiLatusRectum_ * sineOfTrueAnomaly_
            / ( 1.0 + eccentricity_ * cosineOfTrueAnomaly_ );

    // Definition of velocity in the perifocal coordinate system.
    Vector2d velocityPerifocal_(
                -sqrt( centralBodyGravitationalParameter / semiLatusRectum_ ) * sineOfTrueAnomaly_,
                sqrt( centralBodyGravitationalParameter / semiLatusRectum_ )
                * ( eccentricity_ + cosineOfTrueAnomaly_ ) );

    // Definition of the transformation matrix.
    Eigen::MatrixXd transformationMatrix_ = Eigen::MatrixXd::Zero( 3, 2 );

    // Compute the transformation matrix.
    transformationMatrix_( 0, 0 ) = cosineOfLongitudeOfAscendingNode_
            * cosineOfArgumentOfPeriapsis_ -sineOfLongitudeOfAscendingNode_
            * sineOfArgumentOfPeriapsis_ * cosineOfInclination_;
    transformationMatrix_( 0, 1 ) = -cosineOfLongitudeOfAscendingNode_
            * sineOfArgumentOfPeriapsis_ -sineOfLongitudeOfAscendingNode_
            * cosineOfArgumentOfPeriapsis_ * cosineOfInclination_;
    transformationMatrix_( 1, 0 ) = sineOfLongitudeOfAscendingNode_
            * cosineOfArgumentOfPeriapsis_ + cosineOfLongitudeOfAscendingNode_
            * sineOfArgumentOfPeriapsis_ * cosineOfInclination_;
    transformationMatrix_( 1, 1 ) = -sineOfLongitudeOfAscendingNode_
            * sineOfArgumentOfPeriapsis_ + cosineOfLongitudeOfAscendingNode_
            * cosineOfArgumentOfPeriapsis_ * cosineOfInclination_;
    transformationMatrix_( 2, 0 ) = sineOfArgumentOfPeriapsis_ * sineOfInclination_;
    transformationMatrix_( 2, 1 ) = cosineOfArgumentOfPeriapsis_ * sineOfInclination_;

    // Declare converted Cartesian elements.
    Eigen::VectorXd convertedCartesianElements_ = Eigen::VectorXd::Zero( 6 );

    // Compute value of position in Cartesian coordinates.
    Vector3d position_ = transformationMatrix_ * positionPerifocal_;
    convertedCartesianElements_.segment( 0, 3 ) = position_;

    // Compute value of velocity in Cartesian coordinates.
    Vector3d velocity_ = transformationMatrix_ * velocityPerifocal_;
    convertedCartesianElements_.segment( 3, 3 ) = velocity_;

    // Return Cartesian elements.
    return convertedCartesianElements_;
}

//! Convert Cartesian to Keplerian orbital elements.
Eigen::VectorXd convertCartesianToKeplerianElements(
        const Eigen::VectorXd& cartesianElements, const double centralBodyGravitationalParameter )
{
    using std::acos;
    using std::atan2;
    using std::fabs;
    using std::pow;
    using Eigen::Vector3d;

    // Declare converted Keplerian elements.
    Eigen::VectorXd computedKeplerianElements_ = Eigen::VectorXd::Zero( 6 );

    // Declare position in the inertial frame.
    Vector3d position_ = cartesianElements.segment( 0, 3 );

    // Declare velocity in the inertial frame.
    Vector3d velocity_ = cartesianElements.segment( 3, 3 );

    // Definition of orbit angular momentum.
    Vector3d orbitAngularMomentum_ = position_.cross( velocity_ );

    // Definition of the (unit) vector to the ascending node.
    Vector3d unitVectorToAscendingNode_ = Eigen::Vector3d::UnitZ( ).cross(
                orbitAngularMomentum_.normalized( ) );

    // Definition of eccentricity vector.
    Vector3d eccentricityVector_ =
            velocity_.cross( orbitAngularMomentum_ ) / centralBodyGravitationalParameter
            - position_.normalized( );

    // Compute the total orbital energy.
    double totalOrbitalEnergy_ = pow( velocity_.norm( ), 2.0 ) / 2.0
            - centralBodyGravitationalParameter / position_.norm( );

    // Compute the value of the eccentricity.
    computedKeplerianElements_( eccentricityIndex ) = eccentricityVector_.norm( );

    // Define and compute boolean of whether orbit is circular or not.
    bool isOrbitCircular_ = computedKeplerianElements_( 1 )
            < std::numeric_limits< double >::epsilon( );

    // Compute the value of inclination. Range between 0 degrees and 180 degrees.
    computedKeplerianElements_( inclinationIndex ) = acos( orbitAngularMomentum_.z( )
                                                           / orbitAngularMomentum_.norm(  ) );

    // Define and compute boolean of whether orbit is equatorial or not.
    bool isOrbitEquatorial_ = unitVectorToAscendingNode_.norm( )
            < std::numeric_limits< double >::epsilon( );

    // Compute value of semi-latus rectum.
    double semiLatusRectum_ = pow( orbitAngularMomentum_.norm( ), 2.0 )
            / centralBodyGravitationalParameter;

    // Compute the value of semi-major axis.
    // Non-parabolic orbits.
    if ( fabs( computedKeplerianElements_( eccentricityIndex ) - 1.0 )
         > std::numeric_limits< double >::epsilon( ) )
    {
        computedKeplerianElements_( semiMajorAxisIndex ) = centralBodyGravitationalParameter
                / ( -2.0 * totalOrbitalEnergy_ );
    }

    // Parabolic orbits.
    else
    { computedKeplerianElements_( semiMajorAxisIndex ) = semiLatusRectum_; }

    // Compute the value of argument of periapsis.
    // Range between 0 degrees and 360 degrees.
    // Non-circular, inclined orbits.
    if ( !isOrbitCircular_ && !isOrbitEquatorial_ )
    {
        computedKeplerianElements_( argumentOfPeriapsisIndex )
                = tudat::mathematics::linear_algebra::computeAngleBetweenVectors(
                    eccentricityVector_, unitVectorToAscendingNode_ );

        // Quadrant check.
        if ( eccentricityVector_( 2 ) < 0.0 )
        { computedKeplerianElements_( argumentOfPeriapsisIndex )
                    = 2.0 * M_PI - computedKeplerianElements_( argumentOfPeriapsisIndex ); }
    }

    // Circular orbits.
    else if ( isOrbitCircular_ )
    { computedKeplerianElements_( argumentOfPeriapsisIndex ) = 0.0; }

    // Equatorial orbits.
    // Argument of periapsis is defined as angle between eccentricity vector
    // and x-axis.
    else
    {
        computedKeplerianElements_( argumentOfPeriapsisIndex )
                = std::fmod( atan2( eccentricityVector_( 1 ),
                                    eccentricityVector_( 0 ) ), 2.0 * M_PI );
    }

    // Compute the value of longitude of ascending node.
    // Range between 0 degrees and 360 degrees.
    // Non-equatorial orbits.
    if ( !isOrbitEquatorial_ )
    {
        computedKeplerianElements_( longitudeOfAscendingNodeIndex ) =
                std::fmod( atan2( unitVectorToAscendingNode_.y( ),
                                  unitVectorToAscendingNode_.x( ) ), 2.0 * M_PI );
    }

    // Equatorial orbits.
    else
    { computedKeplerianElements_( longitudeOfAscendingNodeIndex ) = 0.0; }

    // Compute the value of true anomaly.
    // Range between 0 degrees and 360 degrees.
    // Non-circular orbits.
    if ( !isOrbitCircular_ )
    {
        computedKeplerianElements_( trueAnomalyIndex ) = tudat::mathematics::linear_algebra
                ::computeAngleBetweenVectors( position_, eccentricityVector_ );

        // Quadrant check. In the second half of the orbit, the angle
        // between position and velocity vector is larger than 90 degrees.
        if ( velocity_.dot( position_ ) < 0.0 )
        {
            computedKeplerianElements_( trueAnomalyIndex )
                    = 2.0 * M_PI - computedKeplerianElements_( trueAnomalyIndex );
        }
    }

    // Circular orbits.
    else
    {
        // Circular equatorial orbits.
        if ( isOrbitEquatorial_ )
        {
            computedKeplerianElements_( trueAnomalyIndex ) =
                    std::fmod( atan2( position_.y( ), position_.x( ) ), 2.0 * M_PI );
        }

        // Circular inclined orbits.
        else
        {
            computedKeplerianElements_( trueAnomalyIndex ) = tudat::mathematics::linear_algebra
                    ::computeAngleBetweenVectors( position_, unitVectorToAscendingNode_ );

            // Quadrant check. In the second half of the orbit, the body will be below the
            // xy-plane.
            if ( cartesianElements( trueAnomalyIndex ) < 0.0 )
            { computedKeplerianElements_( trueAnomalyIndex )
                        = 2.0 * M_PI - computedKeplerianElements_( trueAnomalyIndex ); }
        }
    }

    // Return converted Keplerian elements.
    return computedKeplerianElements_;
}

//! Convert true anomaly to (elliptic) eccentric anomaly.
double convertTrueAnomalyToEllipticalEccentricAnomaly( const double trueAnomaly,
                                                       const double eccentricity )
{
    if ( eccentricity >= 1.0 || eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    else
    {
        using std::cos;
        using std::sqrt;

        // Declare and compute sine and cosine of eccentric anomaly.
        double sineOfEccentricAnomaly_ = sqrt( 1.0 - std::pow( eccentricity, 2.0 ) )
                * std::sin( trueAnomaly ) / ( 1.0 + eccentricity * cos( trueAnomaly ) );
        double cosineOfEccentricAnomaly_ = ( eccentricity + cos( trueAnomaly ) )
                / ( 1.0 + eccentricity * cos( trueAnomaly ) );

        // Return elliptic eccentric anomaly.
        return std::atan2( sineOfEccentricAnomaly_, cosineOfEccentricAnomaly_ );
    }
}

//! Convert true anomaly to hyperbolic eccentric anomaly.
double convertTrueAnomalyToHyperbolicEccentricAnomaly( const double trueAnomaly,
                                                       const double eccentricity )
{
    if ( eccentricity <= 1.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    else
    {
        using std::cos;

        // Compute hyperbolic sine and hyperbolic cosine of hyperbolic eccentric anomaly.
        double hyperbolicSineOfHyperbolicEccentricAnomaly_
                = std::sqrt( std::pow( eccentricity, 2.0 ) - 1.0 )
                * std::sin( trueAnomaly ) / ( 1.0 + cos( trueAnomaly ) );

        double hyperbolicCosineOfHyperbolicEccentricAnomaly_
                = ( cos( trueAnomaly ) + eccentricity ) / ( 1.0 + cos( trueAnomaly ) );

        // Return hyperbolic eccentric anomaly.
        return boost::math::atanh( hyperbolicSineOfHyperbolicEccentricAnomaly_
                      / hyperbolicCosineOfHyperbolicEccentricAnomaly_ );
    }
}

//! Convert true anomaly to eccentric anomaly.
double convertTrueAnomalyToEccentricAnomaly( const double trueAnomaly,
                                             const double eccentricity )
{
    // Declare computed eccentric anomaly.
    double eccentricAnomaly_ = -0.0;

    // Check if eccentricity is invalid and throw an error if true.
    if ( eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    // Check if orbit is parabolic and throw an error if true.
    else if ( std::fabs( eccentricity - 1.0 ) < std::numeric_limits< double >::epsilon( ) )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error(
                            "Parabolic orbits have not yet been implemented." ) ) );
    }

    // Check if orbit is elliptical and compute eccentric anomaly.
    else if ( eccentricity >= 0.0 && eccentricity < 1.0 )
    {
        eccentricAnomaly_ = convertTrueAnomalyToEllipticalEccentricAnomaly( trueAnomaly,
                                                                            eccentricity );
    }

    else if ( eccentricity > 1.0 )
    {
        eccentricAnomaly_ = convertTrueAnomalyToHyperbolicEccentricAnomaly( trueAnomaly,
                                                                            eccentricity );
    }

    // Return computed eccentric anomaly.
    return eccentricAnomaly_;
}

//! Convert (elliptic) eccentric anomaly to true anomaly.
double convertEllipticalEccentricAnomalyToTrueAnomaly( const double ellipticEccentricAnomaly,
                                                       const double eccentricity )
{
    if ( eccentricity >= 1.0 || eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    else
    {
        using std::cos;
        using std::sqrt;

        // Compute sine and cosine of true anomaly.
        double sineOfTrueAnomaly_ = sqrt( 1.0 - std::pow( eccentricity, 2.0 ) ) *
                std::sin( ellipticEccentricAnomaly )
                / ( 1.0 - eccentricity * cos( ellipticEccentricAnomaly ) );

        double cosineOfTrueAnomaly_ = ( cos( ellipticEccentricAnomaly ) - eccentricity )
                / ( 1.0 - eccentricity * cos( ellipticEccentricAnomaly ) );

        // Return true anomaly.
        return atan2( sineOfTrueAnomaly_, cosineOfTrueAnomaly_  );
    }
}

//! Convert hyperbolic eccentric anomaly to true anomaly.
double convertHyperbolicEccentricAnomalyToTrueAnomaly( const double hyperbolicEccentricAnomaly,
                                                       const double eccentricity )
{
    if ( eccentricity <= 1.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    else
    {
        using std::cosh;

        // Compute sine and cosine of true anomaly.
        double sineOfTrueAnomaly_
                = std::sqrt( std::pow( eccentricity, 2.0 ) - 1.0 )
                * std::sinh( hyperbolicEccentricAnomaly )
                / ( eccentricity * cosh( hyperbolicEccentricAnomaly ) - 1.0 );

        double cosineOfTrueAnomaly_
                = ( eccentricity - cosh( hyperbolicEccentricAnomaly ) )
                / ( eccentricity * cosh( hyperbolicEccentricAnomaly ) - 1.0 );

        // Return true anomaly.
        return std::atan2( sineOfTrueAnomaly_, cosineOfTrueAnomaly_ );
    }

}

//! Convert eccentric anomaly to true anomaly.
double convertEccentricAnomalyToTrueAnomaly( const double eccentricAnomaly,
                                             const double eccentricity )
{
    // Declare computed true anomaly.
    double trueAnomaly_ = -0.0;

    // Check if eccentricity is invalid and throw an error if true.
    if ( eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    // Check if orbit is parabolic and throw an error if true.
    else if ( std::fabs( eccentricity - 1.0 ) < std::numeric_limits< double >::epsilon( ) )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error(
                            "Parabolic orbits have not yet been implemented." ) ) );
    }

    // Check if orbit is elliptical and compute true anomaly.
    else if ( eccentricity >= 0.0 && eccentricity < 1.0 )
    {
        trueAnomaly_ = convertEllipticalEccentricAnomalyToTrueAnomaly( eccentricAnomaly,
                                                                       eccentricity );
    }

    else if ( eccentricity > 1.0 )
    {
        trueAnomaly_ = convertHyperbolicEccentricAnomalyToTrueAnomaly( eccentricAnomaly,
                                                                       eccentricity );
    }

    // Return computed true anomaly.
    return trueAnomaly_;
}

//! Convert (elliptical) eccentric anomaly to mean anomaly.
double convertEllipticalEccentricAnomalyToMeanAnomaly( const double ellipticalEccentricAnomaly,
                                                       const double eccentricity )
{
    return ellipticalEccentricAnomaly - eccentricity * std::sin( ellipticalEccentricAnomaly );
}

//! Convert hyperbolic eccentric anomaly to mean anomaly.
double convertHyperbolicEccentricAnomalyToMeanAnomaly(
    const double hyperbolicEccentricAnomaly, const double eccentricity )
{
    return eccentricity * std::sinh( hyperbolicEccentricAnomaly ) - hyperbolicEccentricAnomaly;
}

//! Convert eccentric anomaly to mean anomaly.
double convertEccentricAnomalyToMeanAnomaly( const double eccentricAnomaly,
                                             const double eccentricity )
{
    // Declare computed mean anomaly.
    double meanAnomaly_ = -0.0;

    // Check if eccentricity is invalid and throw an error if true.
    if ( eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    // Check if orbit is parabolic and throw an error if true.
    else if ( std::fabs( eccentricity - 1.0 ) < std::numeric_limits< double >::epsilon( ) )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error(
                            "Parabolic orbits have not yet been implemented." ) ) );
    }

    // Check if orbit is elliptical and compute true anomaly.
    else if ( eccentricity >= 0.0 && eccentricity < 1.0 )
    {
        meanAnomaly_ = convertEllipticalEccentricAnomalyToMeanAnomaly( eccentricAnomaly,
                                                                       eccentricity );
    }

    else if ( eccentricity > 1.0 )
    {
        meanAnomaly_ = convertHyperbolicEccentricAnomalyToMeanAnomaly( eccentricAnomaly,
                                                                       eccentricity );
    }

    // Return computed mean anomaly.
    return meanAnomaly_;
}

//! Convert elapsed time to (elliptical) mean anomaly change.
double convertElapsedTimeToEllipticalMeanAnomalyChange(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Check if semi-major axis is invalid and throw error if true.
    if ( semiMajorAxis < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Semi-major axis is invalid." ) ) );
    }

    // Else return elliptical mean anomaly change.
    else
    {
        return std::sqrt( centralBodyGravitationalParameter
                          / std::pow( semiMajorAxis, 3.0 ) ) * elapsedTime;
    }
}

//! Convert elapsed time to mean anomaly change for hyperbolic orbits.
double convertElapsedTimeToHyperbolicMeanAnomalyChange(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Check if semi-major axis is invalid and throw error if true.
    if ( semiMajorAxis > 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Semi-major axis is invalid." ) ) );
    }

    // Else return hyperbolic mean anomaly change.
    else
    {
        return std::sqrt( centralBodyGravitationalParameter
                          / std::pow( -semiMajorAxis, 3.0 ) ) * elapsedTime;
    }
}

//! Convert elapsed time to mean anomaly change.
double convertElapsedTimeToMeanAnomalyChange(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Declare computed mean anomaly change.
    double meanAnomalyChange_ = -0.0;

    // Check if orbit is elliptical and compute mean anomaly change.
    if ( semiMajorAxis > 0.0 )
    {
        meanAnomalyChange_ = convertElapsedTimeToEllipticalMeanAnomalyChange(
                    elapsedTime, centralBodyGravitationalParameter, semiMajorAxis );
    }

    // Else orbit is hyperbolic; compute mean anomaly change.
    else if ( semiMajorAxis < 0.0 )
    {
        meanAnomalyChange_ = convertElapsedTimeToHyperbolicMeanAnomalyChange(
                    elapsedTime, centralBodyGravitationalParameter, semiMajorAxis );
    }

    // Return computed mean anomaly change.
    return meanAnomalyChange_;
}

//! Convert (elliptical) mean anomaly change to elapsed time.
double convertEllipticalMeanAnomalyChangeToElapsedTime(
        const double ellipticalMeanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Check if semi-major axis is invalid and throw error if true.
    if ( semiMajorAxis < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Semi-major axis is invalid." ) ) );
    }

    // Else return elapsed time.
    else
    {
        return ellipticalMeanAnomalyChange * std::sqrt( std::pow( semiMajorAxis, 3.0 )
                                                        / centralBodyGravitationalParameter );
    }
}

//! Convert hyperbolic mean anomaly change to elapsed time.
double convertHyperbolicMeanAnomalyChangeToElapsedTime(
        const double hyperbolicMeanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Check if semi-major axis is invalid and throw error if true.
    if ( semiMajorAxis > 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Semi-major axis is invalid." ) ) );
    }

    // Else return elapsed time.
    else
    {
        return std::sqrt( std::pow( -semiMajorAxis, 3.0 )
                          / centralBodyGravitationalParameter ) * hyperbolicMeanAnomalyChange;
    }
}

//! Convert mean anomaly change to elapsed time.
double convertMeanAnomalyChangeToElapsedTime(
        const double meanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    // Declare computed elapsed time.
    double elapsedTime_ = -0.0;

    // Check if orbit is elliptical and compute elapsed time.
    if ( semiMajorAxis > 0.0 )
    {
        elapsedTime_ = convertEllipticalMeanAnomalyChangeToElapsedTime(
                    meanAnomalyChange, centralBodyGravitationalParameter, semiMajorAxis );
    }

    // Else orbit is hyperbolic; compute elapsed time.
    else if ( semiMajorAxis < 0.0 )
    {
        elapsedTime_ = convertHyperbolicMeanAnomalyChangeToElapsedTime(
                    meanAnomalyChange, centralBodyGravitationalParameter, semiMajorAxis );
    }

    // Return computed elapsed time.
    return elapsedTime_;
}

//! Convert (elliptical) mean motion to semi-major axis.
double convertEllipticalMeanMotionToSemiMajorAxis(
        const double ellipticalMeanMotion, const double centralBodyGravitationalParameter )
{
    return std::pow( centralBodyGravitationalParameter
                   / std::pow( ellipticalMeanMotion, 2.0 ), 1.0 / 3.0 );
}

//! Convert semi-major axis to elliptical mean motion.
double convertSemiMajorAxisToEllipticalMeanMotion(
        const double semiMajorAxis, const double centralBodyGravitationalParameter )
{
    // Check if semi-major axis is invalid and throw error if true.
    if ( semiMajorAxis < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Semi-major axis is invalid." ) ) );
    }

    // Else compute and return elliptical mean motion.
    {
        return std::sqrt( centralBodyGravitationalParameter / std::pow( semiMajorAxis, 3.0 ) );
    }
}

} // namespace orbital_element_conversions
} // namespace tudat
