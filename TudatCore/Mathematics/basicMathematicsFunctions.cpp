/*! \file basicMathematicsFunctions.cpp
 *    Source file that implements all the basic mathematics functions contained in Tudat.
 *
 *    Path              : /Mathematics/
 *    Version           : 15
 *    Check status      : Checked
 *    Date created      : 3 September, 2010
 *    Last modified     : 30 January, 2012
 *
 *    References
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
 *      120127    D. Dirkx          First version of basic mathematics in Tudat Core.
 *      120127    K. Kumar          Minor comment edits; added modulo-0 case, which should yield
 *                                  equality.
 *      120130    K. Kumar          Added missing implementation of
 *                                  getGlobalRandomNumberGenerator().
 */

// Include statements.
#include <cmath>
#include <ctime>
#include <limits>
#include "TudatCore/Mathematics/basicMathematicsFunctions.h"


#include <iostream>

namespace tudat
{

namespace mathematics
{

//! Get global random number generator.
GlobalRandomNumberGeneratorType& getGlobalRandomNumberGenerator( )
{
  static GlobalRandomNumberGeneratorType globalRandomNumberGenerator(
              static_cast< unsigned int >( std::time( 0 ) ) );
  return globalRandomNumberGenerator;
}

} // namespace mathematics.

} // namespace tudat.

// End of file.
