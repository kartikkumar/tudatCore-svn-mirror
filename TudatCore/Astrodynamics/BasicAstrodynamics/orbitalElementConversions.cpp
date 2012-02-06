/*! \file orbitalElementConversions.cpp
 *    This source file contains a namespace with orbital element conversion functions.
 *
 *    Path              : /Astrodynamics/States/
 *    Version           : 19
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
 */

// Include statements.
#include <boost/exception/all.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <Eigen/Geometry>
#include <numeric>
#include <cmath>
#include "TudatCore/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h"
#include "TudatCore/Mathematics/linearAlgebra.h"

//! Tudat library namespace.
namespace tudat
{

//! Orbital element conversions namespace.
namespace orbital_element_conversions
{

//! Convert Keplerian to Cartesian orbital elements.
Eigen::VectorXd convertKeplerianToCartesianElements(
        const Eigen::VectorXd& keplerianElements, const double centralBodyGravitationalParameter )
{
    // Using declarations.
    using std::cos;
    using std::fabs;
    using std::pow;
    using std::sin;
    using std::sqrt;

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
    Eigen::Vector2d positionPerifocal_ = Eigen::Vector2d::Zero( 2 );
    positionPerifocal_.x( ) = semiLatusRectum_ * cosineOfTrueAnomaly_
            / ( 1.0 + eccentricity_ * cosineOfTrueAnomaly_ );
    positionPerifocal_.y( ) = semiLatusRectum_ * sineOfTrueAnomaly_
            / ( 1.0 + eccentricity_ * cosineOfTrueAnomaly_ );

    // Definition of velocity in the perifocal coordinate system.
    Eigen::Vector2d velocityPerifocal_(
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
    Eigen::Vector3d position_ = transformationMatrix_ * positionPerifocal_;
    convertedCartesianElements_.segment( 0, 3 ) = position_;

    // Compute value of velocity in Cartesian coordinates.
    Eigen::Vector3d velocity_ = transformationMatrix_ * velocityPerifocal_;
    convertedCartesianElements_.segment( 3, 3 ) = velocity_;

    // Return Cartesian elements.
    return convertedCartesianElements_;
}

//! Convert Cartesian to Keplerian orbital elements.
Eigen::VectorXd convertCartesianToKeplerianElements(
        const Eigen::VectorXd& cartesianElements, const double centralBodyGravitationalParameter )
{
    // Using declarations.
    using std::acos;
    using std::atan2;
    using std::fabs;
    using std::pow;

    // Declare converted Keplerian elements.
    Eigen::VectorXd computedKeplerianElements_ = Eigen::VectorXd::Zero( 6 );

    // Declare position in the inertial frame.
    Eigen::Vector3d position_ = cartesianElements.segment( 0, 3 );

    // Declare velocity in the inertial frame.
    Eigen::Vector3d velocity_ = cartesianElements.segment( 3, 3 );

    // Definition of orbit angular momentum.
    Eigen::Vector3d orbitAngularMomentum_ = position_.cross( velocity_ );

    // Definition of the (unit) vector to the ascending node.
    Eigen::Vector3d unitVectorToAscendingNode_ = Eigen::Vector3d::UnitZ( ).cross(
                orbitAngularMomentum_.normalized( ) );

    // Definition of eccentricity vector.
    Eigen::Vector3d eccentricityVector_ =
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
            if ( cartesianElements( 5 ) < 0.0 )
            { computedKeplerianElements_( trueAnomalyIndex )
                        = 2.0 * M_PI - computedKeplerianElements_( trueAnomalyIndex ); }
        }
    }

    // Return converted Keplerian elements.
    return computedKeplerianElements_;
}

//! Convert true anomaly to eccentric anomaly.
double convertTrueAnomalyToEccentricAnomaly( const double trueAnomaly, const double eccentricity )
{
    if ( eccentricity >= 1.0 || eccentricity < 0.0 )
    {
        boost::throw_exception(
                    boost::enable_error_info(
                        std::runtime_error( "Eccentricity is invalid." ) ) );
    }

    else
    {
        // Using declarations.
        using std::cos;
        using std::sqrt;

        // Declare and compute sine and cosine of eccentric anomaly.
        double sineOfEccentricAnomaly_ = sqrt( 1.0 - std::pow( eccentricity, 2.0 ) )
                * std::sin( trueAnomaly ) / ( 1.0 + eccentricity * cos( trueAnomaly ) );
        double cosineOfEccentricAnomaly_ = ( eccentricity + cos( trueAnomaly ) )
                / ( 1.0 + eccentricity * cos( trueAnomaly ) );

        // Return eccentric anomaly.
        return std::atan2( sineOfEccentricAnomaly_, cosineOfEccentricAnomaly_ );
    }
}

//! Convert eccentric anomaly to true anomaly.
double convertEccentricAnomalyToTrueAnomaly( const double eccentricAnomaly,
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
        // Using declarations.
        using std::cos;
        using std::sqrt;

        // Compute sine and cosine of true anomaly.
        double sineOfTrueAnomaly_ = sqrt( 1.0 - std::pow( eccentricity, 2.0 ) ) *
                std::sin( eccentricAnomaly ) / ( 1.0 - eccentricity * cos( eccentricAnomaly ) );

        double cosineOfTrueAnomaly_ = ( cos( eccentricAnomaly ) - eccentricity )
                / ( 1.0 - eccentricity * cos( eccentricAnomaly ) );

        // Return true anomaly.
        return atan2( sineOfTrueAnomaly_, cosineOfTrueAnomaly_  );
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
        // Using declarations.
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
        // Using declarations.
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

//! Convert eccentric anomaly to mean anomaly.
double convertEccentricAnomalyToMeanAnomaly( const double eccentricAnomaly,
                                             const double eccentricity )
{ return eccentricAnomaly - eccentricity * std::sin( eccentricAnomaly ); }

//! Convert hyperbolic eccentric anomaly to mean anomaly.
double convertHyperbolicEccentricAnomalyToMeanAnomaly(
    const double hyperbolicEccentricAnomaly, const double eccentricity )
{ return eccentricity * std::sinh( hyperbolicEccentricAnomaly ) - hyperbolicEccentricAnomaly; }

//! Convert elapsed time to mean anomaly for elliptical orbits.
double convertElapsedTimeToMeanAnomalyChangeForEllipticalOrbits(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    return std::sqrt( centralBodyGravitationalParameter
                      / std::pow( semiMajorAxis, 3.0 ) ) * elapsedTime;
}

//! Convert mean anomaly to elapsed time for elliptical orbits.
double convertMeanAnomalyChangeToElapsedTimeForEllipticalOrbits(
        const double meanAnomalyChange, const double centralBodyGravitationalParameter,
        double semiMajorAxis )
{
    return meanAnomalyChange * std::sqrt( std::pow( semiMajorAxis, 3.0 )
                                          / centralBodyGravitationalParameter );
}

//! Convert elapsed time to mean anomaly change for hyperbolic orbits.
double convertElapsedTimeToMeanAnomalyChangeForHyperbolicOrbits(
        const double elapsedTime, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    return std::sqrt( centralBodyGravitationalParameter
                      / std::pow( -semiMajorAxis, 3.0 ) ) * elapsedTime;
}

//! Convert mean anomaly change to elapsed time for hyperbolic orbits.
double convertMeanAnomalyChangeToElapsedTimeForHyperbolicOrbits(
        const double meanAnomalyChange, const double centralBodyGravitationalParameter,
        const double semiMajorAxis )
{
    return std::sqrt( std::pow( -semiMajorAxis, 3.0 )
                      / centralBodyGravitationalParameter ) * meanAnomalyChange;
}

//! Convert mean motion to semi-major axis.
double convertMeanMotionToSemiMajorAxis( const double meanMotion,
                                         const double centralBodyGravitationalParameter )
{ return std::pow( centralBodyGravitationalParameter / std::pow( meanMotion, 2.0 ), 1.0 / 3.0 ); }

//! Convert semi-major axis to mean motion.
double convertSemiMajorAxisToMeanMotion( const double semiMajorAxis,
                                         const double centralBodyGravitationalParameter )
{ return std::sqrt( centralBodyGravitationalParameter / std::pow( semiMajorAxis, 3.0 ) ); }

} // namespace orbital_element_conversions.

} // namespace tudat.

// End of file.
