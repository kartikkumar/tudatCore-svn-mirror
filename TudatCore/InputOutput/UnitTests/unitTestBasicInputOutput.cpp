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
 *      120127    S. Billemont      File created.
 *      120127    K. Kumar          Minor comment modifications.
 *
 *    References
 *
 */

#define BOOST_TEST_MAIN

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
        BOOST_CHECK(std::string( TUDAT_CORE_CUSTOM_ROOT_PATH ).compare( tio::getCoreRootPath( ) == 0 );
    #endif
}

} // namespace unit_tests
} // namespace tudat
