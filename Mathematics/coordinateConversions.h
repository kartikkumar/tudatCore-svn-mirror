/*! \file coordinateConversions.h
 *    Header file that defines the coordinate conversion functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 15
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
 *      Spiegel, M.R., Stephens, L.J. Statistics, Fourth Edition, Schaum's
 *          Outlines, McGraw-Hill, 2008.
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
 *      100903    K. Kumar          File header and footer added.
 *      100916    L. Abdulkadir     File checked.
 *      100929    K. Kumar          Checked code by D. Dirkx added.
 *      101110    K. Kumar          Added raiseToIntegerExponent() function.
 *      102410    D. Dirkx          Minor comment changes during code check.
 *      101213    K. Kumar          Modified raiseToIntegerExponent() function;
 *                                  renamed raiseToIntegerPower().
 *                                  Added computeAbsoluteValue() functions.
 *      110111    J. Melman         Added computeModulo() function.
 *      110202    K. Kumar          Added overload for State* for computeLinearInterpolation().
 *      110411    K. Kumar          Added convertCartesianToSpherical() function.
 *      110707    K. Kumar          Added computeSampleMean(), computeSampleVariance() functions.
 *      110810    J. Leloux         Corrected doxygen documentation (equations).
 *      110824    J. Leloux         Corrected doxygen documentation.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      120127    D. Dirkx          First version branched from basic mathematics in Tudat Core.
 *      120127    K. Kumar          Minor comment edits.
 */

#ifndef TUDAT_COORDINATE_CONVERSIONS_H
#define TUDAT_COORDINATE_CONVERSIONS_H

// Include statements.
#include <Eigen/Core>

//! Tudat library namespace.
/*!
 * The Tudat library namespace.
 */
namespace tudat
{

//! Mathematics namespace.
/*!
 * The mathematics namespace, containing free functions and classes.
 */
namespace mathematics
{

//! Coordinate conversions namespace.
/*!
 * The coordinate conversions namespace contains free functions to convert between standard
 * coordinate frames, e.g, spherical-to-Cartesian, cylindrical-to-Cartesian etc.
 */
namespace coordinate_conversions
{

//! Convert spherical (radius, zenith, azimuth) to cartesian (x,y,z) coordinates.
/*!
 * Function to convert spherical to cartesian coordinates.
 * Schematic representation can be found on, e.g.,
 * http://mathworld.wolfram.com/SphericalCoordinates.html.
 * The transformation equations are the following, with \f$ r \f$ the radius,
 * \f$ \theta \f$ the azimuth angle and \f$ \phi \f$ the zenith angle:
 * \f{eqnarray*}{
 *      x &=& r\cos\theta\sin\phi \\
 *      y &=& r\sin\theta\sin\phi \\
 *      z &=& r\cos\phi \\
 * \f}
 * \param sphericalCoordinates Vector containing radius, zenith and azimuth (in that order).
 * \return Vector containing Cartesian coordinates, as calculated from sphericalCoordinates.
*/
Eigen::VectorXd convertSphericalToCartesian( const Eigen::VectorXd& sphericalCoordinates );

//! Convert Cartesian (x,y,z) to spherical (radius, zenith, azimuth) coordinates.
/*!
 * Converts Cartesian to spherical coordinates.
 * Schematic representation can be found on, e.g.,
 * http://mathworld.wolfram.com/SphericalCoordinates.html.
 * The transformation equations are the following, with \f$ r \f$ the radius,
 * \f$ \theta \f$ the azimuth angle and \f$ \phi \f$ the azimuth angle:
 * \f{eqnarray*}{
 *      r &=& \sqrt{ x^{ 2 } + y^{ 2 } + z^{ 2 } } \\
 *      \theta &=& \arctan\frac{ y }{ x } \\
 *      \phi &=& \arccos\frac{ z }{ r } \\
 * \f}
 * \param cartesianCoordinates Vector containing Cartesian coordinates.
 * \return Vector containing sphericalCoordinates radius, zenith and azimuth (in that
 *          order), as calculated from sphericalCoordinates.
*/
Eigen::VectorXd convertCartesianToSpherical( const Eigen::VectorXd& cartesianCoordinates );

//! Convert cylindrical (radius, azimuth, z) to Cartesian coordinates (x,y,z), z value unaffected.
/*!
 * Function to convert cylindrical to Cartesian coordinates.
 * Schematic representation can be found on, e.g.,
 * http://mathworld.wolfram.com/CylindricalCoordinates.html.
 * The transformation equations are the following, with \f$ r \f$  the radius and
 * \f$ \theta \f$ the azimuth angle:
 * \f{eqnarray*}{
 *      x &=& r\cos\theta \\
 *      y &=& r\sin\theta \\
 *      z &=& z \\
 * \f}
 * The value of z is left unaffected by this transformation.
 * \param cylindricalCoordinates Vector containing radius, azimuth and z (in that order).
 * \return Vector containing Cartesian coordinates, as calculated from cylindricalCoordinates.
*/
Eigen::VectorXd convertCylindricalToCartesian( const Eigen::VectorXd& cylindricalCoordinates );

} // Namespace coordinate_conversions.

} // Namespace mathematics.

} // Namespace tudat.

#endif // TUDAT_COORDINATECONVERSIONS_H

// End of file.