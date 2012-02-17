/*!   Copyright (c) 2010-2012 Delft University of Technology.
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
 *      120127    K. Kumar          Adapted for Tudat Core; moved other functions to Tudat
 *                                  library.
 *
 *    References
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
 * \param Root-path.
 */
static std::string getCoreRootPath( )
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
