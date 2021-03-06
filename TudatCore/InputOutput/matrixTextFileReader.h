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
 *      110530    F.M. Engelen      Code created.
 *      130109    K. Kumar          Ported from Tudat.
 *
 *    References
 *
 *    Notes
 *      If tabs are used as spaces, it doesn't work. The seperator should also be tabs then.
 *
 */

#ifndef TUDAT_CORE_MATRIX_TEXT_FILEREADER_H
#define TUDAT_CORE_MATRIX_TEXT_FILEREADER_H

#include <string>

#include <Eigen/Core>

namespace tudat
{
namespace input_output
{

//! Read the file and return the data matrix.
/*!
 * Read a textfile whith separated (space, tab, comma etc...) numbers. The class returns these
 * numbers as a matrixXd. The first line with numbers is used to define the number of columns.
 * \param relativePath Relative path to file.
 * \param separators Separators used, every character in the string will be used as separators.
 *         (multiple seperators possible).
 * \param skipLinesCharacter Skip lines starting with this character.
 * \return The datamatrix.
 */
Eigen::MatrixXd readMatrixFromFile( const std::string& relativePath,
                                    const std::string& separators = "\t ;,",
                                    const std::string& skipLinesCharacter = "%" );

} // namespace input_output
} // namespace tudat

#endif // TUDAT_CORE_MATRIX_TEXT_FILEREADER_H
