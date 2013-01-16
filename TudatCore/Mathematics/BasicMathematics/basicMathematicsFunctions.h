/*    Copyright (c) 2010-2013, Delft University of Technology
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
 *      120127    D. Dirkx          First version of basic mathematics in Tudat Core, coordinate
 *                                  conversions put in separate file.
 *      120127    K. Kumar          Minor comment edits.
 *      120217    K. Kumar          Modified computeModuloForSignedValues() to computeModulo().
 *      121205    D. Dirkx          Migrated namespace to directory-based protocol and added
 *                                  backwards compatibility.
 *      121205    D. Dirkx          Migrated namespace to directory-based protocol and added
 *                                  backwards compatibility.
 *
 *    References
 *      Press W.H., et al. Numerical Recipes in C++: The Art of Scientific Computing. Cambridge
 *          University Press, February 2002.
 *      Spiegel, M.R., Stephens, L.J. Statistics, Fourth Edition, Schaum's Outlines, McGraw-Hill,
 *          2008.
 *
 *    Notes
 *      Backwards compatibility of namespaces is implemented for Tudat Core 2 in this file. The
 *      code block marked "DEPRECATED!" at the end of the file should be removed in Tudat Core 3.
 *
 */

#ifndef TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H
#define TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H

#include <boost/random/mersenne_twister.hpp>

namespace tudat
{
namespace basic_mathematics
{

//! Random number generator typedef.
/*!
 * Random number generator typedef. This can be modified to any other Boost random number
 * generator type (http://www.boost.org/doc/libs/1_47_0/doc/html/boost_random/reference.html).
 */
typedef boost::mt19937 GlobalRandomNumberGeneratorType;

//! Get global random number generator.
/*!
 * Returns global random number generator. The default seed is set to the current time.
 * \return Global random number generator.
 */
GlobalRandomNumberGeneratorType& getGlobalRandomNumberGenerator( );

//! Compute modulo of double.
/*!
 * Computes the remainder of division of one floating-point number by another. The modulo
 * computation is based on the mathematical definition of congruence, which is different from the
 * implementation of std::fmod() in the cmath standard library. For a description of congruence
 * see: http://mathworld.wolfram.com/Congruence.html.
 * The remainder is in the range [ 0, divisor ).
 * \param dividend Number to be divided.
 * \param divisor Number that is divided by.
 * \return Remainder of division of dividend by divisor.
 */
double computeModulo( const double dividend, const double divisor );

} // namespace basic_mathematics
} // namespace tudat

// DEPRECATED!
// The following namespace declaration ensures backwards compatibility of namespace for release of
// Tudat Core 2. This will be removed in Tudat Core 3.
namespace tudat
{
namespace mathematics
{

using namespace tudat::basic_mathematics;

} // namespace mathematics
} // namespace tudat

#endif // TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H
