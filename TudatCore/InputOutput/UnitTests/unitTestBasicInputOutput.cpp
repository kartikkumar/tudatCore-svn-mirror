/*! \file unitTestBasicInputOutput.cpp
 *
 *    Path              : /InputOutput/
 *    Version           : 2
 *    Check status      : Checked
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
 *      120127    S. Billemont      File created.
 *      120127    K. Kumar          Minor comment modifications.
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

// Include statements.
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "TudatCore/InputOutput/basicInputOutput.h"

//! Check if the Tudat rootpath is detected correctly.
BOOST_AUTO_TEST_CASE( test_getRootPath )
{
    // Check if the rootpath is a folder which contains the 'External' subdirectory.
    BOOST_CHECK( boost::filesystem::is_directory(
                    tudat::input_output::getCoreRootPath( ) ) );
    BOOST_CHECK( boost::filesystem::is_directory(
                     tudat::input_output::getCoreRootPath( ) + "External" ) );

    // If using a TUDAT_CUSTOM_ROOT_PATH define, check if it matches the macro value.
    #ifdef TUDAT_CUSTOM_ROOT_PATH
        BOOST_CHECK(std::string( TUDAT_CUSTOM_ROOT_PATH ).compare( tio::getCoreRootPath( ) == 0 );
    #endif
}

// End of file.
