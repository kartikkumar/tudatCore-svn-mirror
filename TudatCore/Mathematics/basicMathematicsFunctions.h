/*! \file basicMathematicsFunctions.h
 *    Header file that defines all basic mathematics functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 15
 *    Check status      : Checked
 *
 *    Author            : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Author/Checker    : D. Dirkx
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
 *      120127    D. Dirkx          First version of basic mathematics in Tudat Core, coordinate
 *                                  conversions put in separate file.
 *      120127    K. Kumar          Minor comment edits.
 */

#ifndef TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H
#define TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H

// Include statements.
#include <boost/random/mersenne_twister.hpp>

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

} // Namespace mathematics.

} // Namespace tudat.

#endif // TUDAT_CORE_BASIC_MATHEMATICS_FUNCTIONS_H

// End of file.