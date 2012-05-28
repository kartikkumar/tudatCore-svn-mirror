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
 *
 *    References
 *
 */

#ifndef TUDAT_CORE_COORDINATE_CONVERSIONS_H
#define TUDAT_CORE_COORDINATE_CONVERSIONS_H

#include <Eigen/Core>

namespace tudat
{
namespace mathematics
{
namespace coordinate_conversions
{

//! Convert spherical (radius, zenith, azimuth) to Cartesian (x,y,z) coordinates.
/*!
 * Converts spherical to cartesian coordinates. Schematic representation can be found on, e.g.,
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
 * Converts Cartesian to spherical coordinates. Schematic representation can be found on, e.g.,
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

} // namespace coordinate_conversions
} // namespace mathematics
} // namespace tudat

#endif // TUDAT_CORE_COORDINATE_CONVERSIONS_H
