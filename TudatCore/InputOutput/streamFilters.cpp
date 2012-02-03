/*! \file streamFilters.cpp
 *    Source file that implements the stream filter functions included in Tudat. These can be used
 *    to filter streams of data from, e.g., input files.
 *
 *    Path              : /InputOutput/
 *    Version           : 2
 *    Check status      : Unchecked
 *
 *    Author            : S. Billemont
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : simon@angelcorp.be
 *
 *    Checker           : K. Kumar
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : K.Kumar@tudelft.nl
 *
 *    Date created      : 27 January, 2012
 *    Last modified     : 27 January, 2012
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
 *      100902    S. Billemont      File created.
 *      120127    K. Kumar          Added missing comments and clarified variable-naming.
 */

// Include statements.
#include <boost/assign.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <vector>
#include "TudatCore/InputOutput/streamFilters.h"

//! Remove comments in a single line.
std::string tudat::input_output::stream_filters::RemoveComment::do_filter(
        const std::string& line )
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
std::string tudat::input_output::stream_filters::SkipFirstLines::do_filter(
        const std::string& line )
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
tudat::input_output::stream_filters::ReplaceElements::ReplaceElements( std::string searchFilter,
        std::string replaceString, bool isOmitIfEmpty ) 
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
std::string tudat::input_output::stream_filters::ReplaceElements::do_filter(
        const std::string& line )
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

// End of file.
