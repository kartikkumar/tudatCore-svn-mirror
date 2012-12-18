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
 *      100902    S. Billemont      File created.
 *      120127    K. Kumar          Added missing comments and clarified variable-naming.
 *      121205    D. Dirkx          Migrated namespace to directory-based protocol.
 *
 *    References
 *
 *    Notes
 *
 */

#include <vector>

#include <boost/assign.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "TudatCore/InputOutput/streamFilters.h"

namespace tudat
{
namespace input_output
{
namespace stream_filters
{

//! Remove comments in a single line.
std::string RemoveComment::do_filter( const std::string& line )
{
    // Find position of the skip character in the line.
    std::size_t index = line.find( skipCharacter_ );

    // Check if the 'skipCharacter_' is the first character and check if empty lines should be
    // returned.
    if ( index == 0 && isOmitIfEmpty_ )
    {
        // This prevents newline characters for empty lines.
        return "";
    }

    // Return filtered line (so the line from start to the first occurrence of the
    // 'skipCharacter_').
    return line.substr( 0, index ) + traits_type::newline( );
}

//! Execute filter on the input line by skipping if required.
std::string SkipFirstLines::do_filter( const std::string& line )
{
    // Check if the required number of lines have already been skipped.
    if ( numberOfSkippedLines_ >= linesToSkip_ )
    {
        // We have already skipped enough lines, just return the input.
        return line + traits_type::newline( );
    }

    // We should skip this line because we did not reach our number of lines to skip
    // Increment counter for number of skipped lines.
    numberOfSkippedLines_++;

    // Return either nothing or a newline character (depending on 'isOmitIfEmpty_').
    return ( isOmitIfEmpty_ ) ? "" : std::string( 1, traits_type::newline( ) );
}

//! Create filter with a basic search and replace string.
ReplaceElements::ReplaceElements( std::string searchFilter, std::string replaceString,
                                  bool isOmitIfEmpty )
    // line_filter is set to true, to indicate to Boost not to append newline characters.
    : boost::iostreams::line_filter( true ), 
      replaceString_(replaceString), isOmitIfEmpty_( isOmitIfEmpty )
{
    // The following are all characters with special meaning in regex, so escape them:
    std::vector< std::string > replaceCharacters_ = boost::assign::list_of
        ("\\")(".")("[")("]")("{")("}")("(")(")")("*")("+")("?")("|")("^")("$");

    // Iterate over each possible character.
    for ( unsigned int i = 0; i < replaceCharacters_.size( ); i++ )
    {
        // For each of the special characters, replace it with the escaped '\' version of that
        // character.
        boost::replace_all( searchFilter, replaceCharacters_[ i ],
                            "\\" + replaceCharacters_[ i ] );
    }

    // Save the escaped version of the input string as the regex search query.
    searchFilter_ = boost::regex( searchFilter );
}

//! Execute filter on a single line to replace matched elements with replace string.
std::string ReplaceElements::do_filter( const std::string& line )
{
    // Perform the regex search & replace
    std::string filteredString = boost::regex_replace( line, searchFilter_, replaceString_ );

    // Check if filtered string is empty and return empty string if true.
    if ( filteredString.size( ) == 0 && isOmitIfEmpty_ )
    {
        return "";
    }
    // Else return filtered string.
    else
    {
        return filteredString + traits_type::newline( );
    }
}

} // namespace stream_filters
} // namespace input_output
} // namespace tudat
