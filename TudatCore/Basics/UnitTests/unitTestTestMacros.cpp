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
 *      120202    S. Billemont      File created.
 *      120401    S. Billemont      Adapted unit test to include pattern generation.
 *
 *    References
 *
 */

/* <p>
 * IMPORTANT:
 *    IF YOU ADD/REMOVE LINES THE TESTS WILL FAIL BECAUSE THE LINENUMBERS NO LONGER MATCH !!
 * </p>
 * <p>
 * Solve: 
 *    Be sure that all tests behave as they should and do the following:
 *  <ul>
 *    <li>Enable the GENERATE_PATTERN macro (set to 1)</li>
 *    <li>Run the test: ./unitTest_testMacros.exe</li>
 *    <li>Remove the first line from the regenerated pattern file</li>
 *    <li>Overwrite the old unitTest_testMacros.pattern with the new one</li>
 *    <li>Disable the GENERATE_PATTERN macro (set to 0)</li>
 * </ul>
 */

//! Flag for generating test results instead of running the test.
/*!
 * Flag, if true, the system will not run the unit test, but generate the same output that it 
 * expects the pattern file to contain for the unit test to succeed.
 *
 * Enable this to regenerate the correct expected pattern file if this test file of the test macros 
 * change.
 */
#define GENERATE_PATTERN 0

#include <fstream>
#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/detail/suppress_warnings.hpp>

#include <Eigen/Core>

#include "TudatCore/Basics/testMacros.h"
#include "TudatCore/InputOutput/basicInputOutput.h"

/************************************************************************/
/* Prepare for the test cases                                           */
/************************************************************************/
using namespace boost::unit_test;
using namespace boost::test_tools;

//! New formatter for the boost test messages.
struct logMessageFormatter : public output::compiler_log_formatter
{
    // Suppress the file and log level:
    void log_entry_start( std::ostream& output, log_entry_data const& entry_data, log_entry_types )
    {
        // Don't suppress line nr! Otherwise validation can be skipped!
        output << entry_data.m_line_num << ": ";
    }

    void print_prefix( std::ostream&, boost::unit_test::const_string, std::size_t ) { }
};

//! Location of file which contains the exact output which has to be produced for test to succeed.
std::string match_file_name;

//! Location to save the output of this test.
std::string save_file_name( "unitTest_testMacros.pattern" );

//! Get the output test stream, stream of the test output to the test output content file
boost::test_tools::output_test_stream& outputTestStream( )
{
    // Singleton output stream.
    static boost::shared_ptr< output_test_stream > inst;

    if( !inst )
    {
        // Reinitialize the first time.
        inst.reset( 
            framework::master_test_suite().argc <= 1
            ? new output_test_stream( runtime_config::save_pattern( )
                                      ? save_file_name : match_file_name,
                                      !runtime_config::save_pattern( ) )
            : new output_test_stream( framework::master_test_suite( ).argv[ 1 ],
                                      !runtime_config::save_pattern( ) ) );
    }

    return *inst;
}

//! Define a new type of test to test the test cases.
//  see Boost.test: boost/libs/test/test/test_tools_test.cpp
#if ( !GENERATE_PATTERN )
    // RUN TEST MODE.
    #define TEST_CASE( name )                                       \
    void name ## _impl( );                                          \
    void name ## _impl_defer( );                                    \
                                                                    \
    BOOST_AUTO_TEST_CASE( name )                                    \
    {                                                               \
        test_case* impl = make_test_case( &name ## _impl, #name );  \
                                                                    \
        unit_test_log.set_stream( outputTestStream() );             \
        unit_test_log.set_threshold_level( log_nothing );           \
        unit_test_log.set_formatter( new logMessageFormatter );     \
        framework::run( impl );                                     \
                                                                    \
        unit_test_log.set_threshold_level(                          \
            runtime_config::log_level( ) != invalid_log_level       \
                ? runtime_config::log_level( )                      \
                : log_all_errors );                                 \
        unit_test_log.set_format( runtime_config::log_format( ) );  \
        unit_test_log.set_stream( std::cout );                      \
        BOOST_CHECK( outputTestStream( ).match_pattern( ) );        \
    }                                                               \
                                                                    \
    void name ## _impl( )                                           \
    {                                                               \
        unit_test_log.set_threshold_level( log_all_errors );        \
                                                                    \
        name ## _impl_defer( );                                     \
                                                                    \
        unit_test_log.set_threshold_level( log_nothing );           \
    }                                                               \
                                                                    \
    void name ## _impl_defer( )                                     \
    /**/
#else
    // GENERATE PATTERN MODE.
    #define TEST_CASE( name )  BOOST_AUTO_TEST_CASE( name )
#endif

/************************************************************************/
/* ACTUAL TESTS:                                                        */
/************************************************************************/

//! Check if incorrect matrix sizes are detected.
TEST_CASE( test_TUDAT_CHECK_MATRIX_CLOSE_size )
{
    Eigen::VectorXd v6 = ( Eigen::VectorXd( 6 ) << 0,0,0,0,0,0 ).finished( );
    Eigen::VectorXd v5 = ( Eigen::VectorXd( 5 ) << 0,0,0,0,0 ).finished( );

    // SUCCESS.
    TUDAT_CHECK_MATRIX_CLOSE( v6, v6, 1 );
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( v6, v6, 1 );

    // FAIL rows 6 != 5.
    TUDAT_CHECK_MATRIX_CLOSE( v6, v5, 1 );
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( v6, v5, 1 );

    // FAIL cols 1 != 5.
    TUDAT_CHECK_MATRIX_CLOSE( v6, v6.transpose( ), 1 );
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( v6, v6.transpose( ), 1 );

    // SUCCESS.
    TUDAT_CHECK_MATRIX_CLOSE( Eigen::Matrix2d::Zero( ), Eigen::Matrix2d::Zero( ), 1 );
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( Eigen::Matrix2d::Zero( ), Eigen::Matrix2d::Zero( ), 1 );

    // FAIL rows 2 != 3, cols 2 != 3.
    TUDAT_CHECK_MATRIX_CLOSE( Eigen::Matrix2d::Zero( ), Eigen::Matrix3d::Zero( ), 1 );
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( Eigen::Matrix2d::Zero( ), Eigen::Matrix3d::Zero( ), 1 );
}

//! Check if errors in individual elements are detected.
TEST_CASE( test_TUDAT_CHECK_MATRIX_CLOSE_elements )
{
    // For more details, see boost/libs/test/test/test_fp_comparisons.cpp
    // SUCCESS.
    TUDAT_CHECK_MATRIX_CLOSE( ( Eigen::VectorXd(1) << 1.0 ).finished( ),
                              ( Eigen::VectorXd(1) << 1.0 ).finished( ),
                              0.0 );

    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( ( Eigen::VectorXd( 1 ) << 1.0 ).finished( ),
                                       ( Eigen::VectorXd( 1 ) << 1.0 ).finished( ),
                                       0.0 );

    // FAIL ON [0,0].
    TUDAT_CHECK_MATRIX_CLOSE( Eigen::Vector2d( 0.0,  1.112e-10 ),
                              Eigen::Vector2d( -1e-10, 1.111e-10 ),
                              0.1 );

    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( Eigen::Vector2d( 0.0,  1.112e-10 ),
                                       Eigen::Vector2d( -1e-10, 1.111e-10 ),
                                       0.1 );
    
    // FAIL ON [2,0].
    TUDAT_CHECK_MATRIX_CLOSE( Eigen::Vector3d( 1.0, 1.0002, 1.0 ),
                              Eigen::Vector3d( 1.0001, 1.0001, 1.0002 ),
                              1.1e-2 );

    // SUCCESS.
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION( Eigen::Vector3d( 1.0, 1.0002, 1.0 ),
                                       Eigen::Vector3d( 1.0001, 1.0001, 1.0002 ),
                                       1.1e-2 );

    // FAIL ON [0,1]
    TUDAT_CHECK_MATRIX_CLOSE(
        ( Eigen::MatrixXd( 2, 2 ) << 0.123456, 0.123456, 1.23456e28, 1.23456e-10 ).finished( ),
        ( Eigen::MatrixXd( 2, 2 ) << 0.123457, -0.123457, 1.23457e28, 1.23457e-10 ).finished( ),
                1.0e-3 );

    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(
        ( Eigen::MatrixXd( 2, 2 ) << 0.123456, 0.123456, 1.23456e28, 1.23456e-10 ).finished( ),
        ( Eigen::MatrixXd( 2, 2 ) << 0.123457, -0.123457, 1.23457e28, 1.23457e-10 ).finished( ),
        1.0e-3 );
}

// Entry point for the test, like  '#define BOOST_TEST_MAIN' but allows for some additional logic
test_suite* init_unit_test_suite( int argc, char* argv[ ] )
{   
    // Name of the pattern file to check against.
    match_file_name = tudat::input_output::getCoreRootPath( ) +
            "Basics/UnitTests/unitTestTestMacros.pattern";

    // Macro setting the correct message formatter and output stream for generating the pattern
    // file.
    #if GENERATE_PATTERN
        // Bind a new log formatter and output the pattern file.
        // TODO, find a nice way without "new".
        unit_test_log.set_formatter( new logMessageFormatter );
        std::fstream* logFile = new std::fstream( );
        logFile->open( match_file_name.c_str( ) );
        unit_test_log.set_stream( *logFile );
    #endif

    return 0;
}
