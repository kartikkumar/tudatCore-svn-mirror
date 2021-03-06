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
 *      100902    K. Kumar          File header and footer added.
 *      100916    D. Dirkx          Added minor comments and placeholder tag during checking.
 *      100928    K. Kumar          Added reference and adjusted include statements.
 *      100929    K. Kumar          Changed EigenRoutines.h include statement
 *                                  to linearAlgebra.h and removed placeholder comment.
 *                                  Added small comment modifications.
 *      110202    K. Kumar          Added overload for map with State* for
 *                                  computeNearestLeftNeighborUsingBinarySearch().
 *      110803    J. Leloux         Added convertStringToTemplate.
 *      110805    J. Leloux         Added outputCurrentRunningTime.
 *      110810    J. Leloux         Minor comment modifications.
 *      110913    K. Kumar          Implemented automatic root-path functions based on
 *                                  suggestions by M. Persson.
 *      111117    K. Kumar          Added listAllFilesInDirectory() function.
 *      120127    K. Kumar          Adapted for Tudat Core; moved other functions to Tudat library.
 *
 *    References
 *
 *    Notes
 *
 */

#ifndef TUDAT_CORE_BASIC_INPUT_OUTPUT_H
#define TUDAT_CORE_BASIC_INPUT_OUTPUT_H

#include <string>

namespace tudat
{
namespace input_output
{

//! Get root-path for Tudat Core library.
/*!
 * Returns root-path corresponding with root-directory of Tudat Core library as a string with
 * trailing slash included.
 * \return Tudat Core root-path.
 */
static inline std::string getCoreRootPath( )
{
#ifdef TUDAT_CORE_CUSTOM_ROOT_PATH
    return std::string( TUDAT_CORE_CUSTOM_ROOT_PATH );
#else
    // Declare file path string assigned to filePath.
    std::string filePath_( __FILE__ );

    // Strip filename from temporary string and return root-path string.
    return filePath_.substr( 0, filePath_.length( ) - 
                                std::string( "InputOutput/basicInputOutput.h" ).length( ) );
#endif
}

} // namespace input_output
} // namespace tudat

#endif // TUDAT_CORE_BASIC_INPUT_OUTPUT_H
