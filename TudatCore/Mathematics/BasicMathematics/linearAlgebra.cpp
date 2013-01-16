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
 *      090807    J. Melman         First creation of code.
 *      100930    D. Dirkx          Modified to comply with Tudat standards
 *      100930    J. Melman         Implemented namespace, minor comment
 *                                  changes.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      120127    D. Dirkx          Moved to Tudat Core.
 *      120127    K. Kumar          Minor edits.
 *      120128    K. Kumar          Corrected computeCosineOfAngleBetweenVectors() to work with
 *                                  vectors of arbitrary length.
 *      121205    D. Dirkx          Migrated namespace to directory-based protocol.
 *      121205    K. Kumar          Fixed incorrect namespace migration.
 *
 *    References
 *
 *    Notes
 *
 */

#include <cassert>
#include <cmath>

#include "TudatCore/Mathematics/BasicMathematics/linearAlgebra.h"

namespace tudat
{
namespace basic_mathematics
{
namespace linear_algebra
{

//! Compute cosine of the angle between two vectors.
double computeCosineOfAngleBetweenVectors( const Eigen::VectorXd& vector0,
                                           const Eigen::VectorXd& vector1 )
{
    assert( vector0.size( ) == vector1.size( ) );

    // Get the cosine of the angle by dotting the normalized vectors.
    double dotProductOfNormalizedVectors = vector0.normalized( ).dot( vector1.normalized( ) );

    // Explicitly define the extreme cases, which can give problems with the acos function.
    if ( dotProductOfNormalizedVectors >= 1.0 )
    {
        return 1.0;
    }

    else if ( dotProductOfNormalizedVectors <= -1.0 )
    {
        return -1.0;
    }
    // Determine the actual angle.
    else
    {
        return dotProductOfNormalizedVectors;
    }
}

//! Compute angle between two vectors.
double computeAngleBetweenVectors( const Eigen::VectorXd& vector0, const Eigen::VectorXd& vector1 )
{
    // Determine the cosine of the angle by using another routine.
    double dotProductOfNormalizedVectors = computeCosineOfAngleBetweenVectors( vector0, vector1 );

    // Return arccosine of the above, which is effectively the angle.
    return std::acos( dotProductOfNormalizedVectors );
}

} // namespace linear_algebra
} // namespace basic_mathematics
} // namespace tudat
