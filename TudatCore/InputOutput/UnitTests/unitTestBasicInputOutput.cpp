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
 *      120127    S. Billemont      File created.
 *      120127    K. Kumar          Minor comment modifications.
 *
 *    References
 *
 *    Notes
 *
 */

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include "TudatCore/InputOutput/basicInputOutput.h"

namespace tudat
{
namespace unit_tests
{

//! Check if the Tudat rootpath is detected correctly.
BOOST_AUTO_TEST_CASE( test_getRootPath )
{
    // Check if the rootpath is a folder which contains the 'External' subdirectory.
    BOOST_CHECK( boost::filesystem::is_directory(
                    tudat::input_output::getCoreRootPath( ) ) );
    BOOST_CHECK( boost::filesystem::is_directory(
                     tudat::input_output::getCoreRootPath( ) + "External" ) );

    // If using a TUDAT_CORE_CUSTOM_ROOT_PATH define, check if it matches the macro value.
    #ifdef TUDAT_CORE_CUSTOM_ROOT_PATH
        BOOST_CHECK( std::string( TUDAT_CORE_CUSTOM_ROOT_PATH ).compare(
                         tio::getCoreRootPath( ) == 0 );
    #endif
}

} // namespace unit_tests
} // namespace tudat
