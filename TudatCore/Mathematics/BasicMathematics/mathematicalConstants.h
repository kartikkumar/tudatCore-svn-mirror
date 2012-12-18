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
 *      100906    S. Billemont      First creation of code.
 *      121205    K. Kumar          Migrated namespace to directory-based protocol and added
 *                                  backwards compatibility.
 *
 *    References
 *      Wolfram MathWorld, Constant:
 *          http://mathworld.wolfram.com/Constant.html (retrieved 2012/02/08).
 *
 *    Notes
 *      Backwards compatibility of namespaces is implemented for Tudat Core 2 in this file. The
 *      code block marked "DEPRECATED!" at the end of the file should be removed in Tudat Core 3.
 *
 */

#ifndef TUDAT_CORE_MATHEMATICAL_CONSTANTS_H
#define TUDAT_CORE_MATHEMATICAL_CONSTANTS_H

#include <cmath>
#include <limits>

namespace tudat
{
namespace basic_mathematics
{
namespace mathematical_constants
{

//! Constant E = exp(1) \f$\approx\f$ 2.71828.
/*!
 * The constant E is base of the natural logarithm, and is also known as Napier's constant.
 * \sa Wolfram MathWorld, Constant: http://mathworld.wolfram.com/e.html.
 */
const static double E = std::exp( 1.0 );

//! The Golden ratio \f$\approx\f$ 1.6180.
/*!
 * The golden ratio, also known as the divine proportion, golden mean, or golden section, is a 
 * number often encountered when taking the ratios of distances in simple geometric figures such as 
 * the pentagon, pentagram, decagon and dodecahedron.
 * \sa Wolfram MathWorld, Constant: http://mathworld.wolfram.com/GoldenRatio.html.
 */
const static double GOLDEN_RATIO = 0.5 * ( 1.0 + std::sqrt( 5.0 ) );

//! The constant PI \f$\approx\f$ 3.14159.
/*!
 * The constant PI, denoted \f$\pi\f$, is a real number defined as the ratio of a circle's circumference
 * C to its diameter, d = 2r.
 * \sa Wolfram MathWorld, Constant: http://mathworld.wolfram.com/Pi.html.
 */
#ifdef M_PI
    const static double PI = M_PI;
#else
    const static double PI = 3.141592653589793238; // 18 digits.
#endif

//! Not-a-number (NaN).
/*!
 * NaN (Not a Number) is a value of the numeric data type representing an undefined or 
 * unrepresentable value.
 *
 * This is a shorthand notation for std::numeric_limits<double>::signaling_NaN();
 */
#define TUDAT_NAN std::numeric_limits< double >::signaling_NaN( )

} // namespace mathematical_constants
} // namespace basic_mathematics
} // namespace tudat

// DEPRECATED!
// The following namespace declaration ensures backwards compatibility of namespace for release of
// Tudat Core 2. This will be removed in Tudat Core 3.
namespace tudat
{
namespace mathematics
{

using namespace tudat::basic_mathematics::mathematical_constants; 

} // namespace mathematics
} // namespace tudat

#endif // TUDAT_CORE_MATHEMATICAL_CONSTANTS_H
