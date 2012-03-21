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
 *      100906    S. Billemont      First creation of code.
 *
 *    References
 *      Wolfram MathWorld, Constant:
 *          http://mathworld.wolfram.com/Constant.html (retrieved 2012/02/08).
 */

#ifndef TUDAT_CORE_MATHEMATICAL_CONSTANTS_H
#define TUDAT_CORE_MATHEMATICAL_CONSTANTS_H

#include <cmath>
#include <limits>

namespace tudat
{
namespace mathematics
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

} // namespace mathematics
} // namespace tudat

#endif // TUDAT_CORE_MATHEMATICAL_CONSTANTS_H
