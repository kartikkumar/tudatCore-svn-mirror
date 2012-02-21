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
 *      120202    S. Billemont      File created.
 *
 *    References
 *
 */

// Temporary notes (move to class/function doxygen):
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 

/* <p>
 * IMPORTANT:
 *    IF YOU ADD/REMOVE LINES THE TESTS WILL FAIL BECAUSE THE LINENUMBERS NO LONGER MATCH !!
 * </p>
 * <p>
 * Solve: 
 *    Be sure that all tests behave as they should and do the following:
 *  <ul>
 *    <li>Replace the entry for the two actual test cases: TEST_CASE => BOOST_AUTO_TEST_CASE</li>
 *    <li>Near the end of the file in the function 
 *              'test_suite* init_unit_test_suite( int, char** )',
 *        enable the section 
 *              'unit_test_log.set_formatter( new logMessageFormatter )'
 *        so that the test generates the same type of output.
 *    <li>Run the test and save the result: 
 *          ./unitTest_testMacros.exe > unitTest_testMacros.match.pattern</li>
 *    <li>Remove the first line:
 *          sed -e '1d' -i unitTest_testMacros.match.pattern</li>
 *    <li>Overwrite the old unitTest_testMacros.match.pattern with the new one</li>
 *    <li>Replace back: BOOST_AUTO_TEST_CASE => TEST_CASE</li>
 * </ul>
 */

// Include statements.
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/test/detail/unit_test_parameters.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/detail/suppress_warnings.hpp>
#include <Eigen/Core>
#include <iostream>
#include "TudatCore/Basics/testMacros.h"
#include "TudatCore/InputOutput/basicInputOutput.h"

/************************************************************************/
/* Prepare for the test cases                                           */
/************************************************************************/
using namespace boost::unit_test;
using namespace boost::test_tools;

//! New formatter for the boost test messages;
struct logMessageFormatter : public output::compiler_log_formatter
{   // Suppress the file and log level:
    void log_entry_start( std::ostream& output, log_entry_data const& entry_data, log_entry_types )
    {
        // Don't suppress line nr! Otherwise validation can be skipped!
        output << entry_data.m_line_num << ": ";
    }
    void print_prefix( std::ostream& , boost::unit_test::const_string, std::size_t ) { }
};
//! Location of the file which contains the exact output which has to be produced for test to succeed
std::string match_file_name;
//! Location to save the output of this test
std::string save_file_name("unitTest_testMacros.pattern");
//! Get the output test stream, stream of the test output to the test output content file
boost::test_tools::output_test_stream& outputTestStream()
{   // Singleton output stream
    static boost::shared_ptr<output_test_stream> inst;
    if( !inst ) { // Reinitialize the first time
        inst.reset( 
            framework::master_test_suite().argc <= 1
            ? new output_test_stream( runtime_config::save_pattern() ? save_file_name : match_file_name, !runtime_config::save_pattern() )
            : new output_test_stream( framework::master_test_suite().argv[1], !runtime_config::save_pattern() ) );
    }
    return *inst;
}
//! Define a new type of test to test the test cases
//  see Boost.test: boost/libs/test/test/test_tools_test.cpp
#define TEST_CASE( name )                                       \
void name ## _impl();                                           \
void name ## _impl_defer();                                     \
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
        runtime_config::log_level() != invalid_log_level        \
            ? runtime_config::log_level()                       \
            : log_all_errors );                                 \
    unit_test_log.set_format( runtime_config::log_format());    \
    unit_test_log.set_stream( std::cout );                      \
    BOOST_CHECK( outputTestStream().match_pattern() );          \
}                                                               \
                                                                \
void name ## _impl()                                            \
{                                                               \
    unit_test_log.set_threshold_level( log_all_errors );        \
                                                                \
    name ## _impl_defer();                                      \
                                                                \
    unit_test_log.set_threshold_level( log_nothing );           \
}                                                               \
                                                                \
void name ## _impl_defer()                                      \
/**/

/************************************************************************/
/* ACTUAL TESTS:                                                        */
/************************************************************************/

//! Check if incorrect matrix sizes are detected
TEST_CASE( test_TUDAT_CHECK_MATRIX_CLOSE_size ) {
    Eigen::VectorXd v6 = (Eigen::VectorXd(6) << 0,0,0,0,0,0).finished();
    Eigen::VectorXd v5 = (Eigen::VectorXd(5) << 0,0,0,0,0).finished();
    // SUCCESS
    TUDAT_CHECK_MATRIX_CLOSE(v6, v6, 1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(v6, v6, 1);
    // FAIL rows 6 != 5
    TUDAT_CHECK_MATRIX_CLOSE(v6, v5, 1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(v6, v5, 1);
    // FAIL cols 1 != 5
    TUDAT_CHECK_MATRIX_CLOSE(v6, v6.transpose(), 1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(v6, v6.transpose(), 1);
    // SUCCESS
    TUDAT_CHECK_MATRIX_CLOSE(Eigen::Matrix2d::Zero(), Eigen::Matrix2d::Zero(), 1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(Eigen::Matrix2d::Zero(), Eigen::Matrix2d::Zero(), 1);
    // FAIL rows 2 != 3, cols 2 != 3
    TUDAT_CHECK_MATRIX_CLOSE(Eigen::Matrix2d::Zero(), Eigen::Matrix3d::Zero(), 1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(Eigen::Matrix2d::Zero(), Eigen::Matrix3d::Zero(), 1);
}

//! Check if errors in individual elements are detected
TEST_CASE( test_TUDAT_CHECK_MATRIX_CLOSE_elements ) {
    // For more details, see boost/libs/test/test/test_fp_comparisons.cpp
    // SUCCESS
    TUDAT_CHECK_MATRIX_CLOSE(
        (Eigen::VectorXd(1) << 1).finished(),
        (Eigen::VectorXd(1) << 1).finished(),
        0);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(
        (Eigen::VectorXd(1) << 1).finished(),
        (Eigen::VectorXd(1) << 1).finished(),
        0);

    // FAIL ON [0,0]
    TUDAT_CHECK_MATRIX_CLOSE(
        Eigen::Vector2d(0,  1.112e-10), 
        Eigen::Vector2d(-1e-10, 1.111e-10), 
        0.1);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(
        Eigen::Vector2d(0,  1.112e-10), 
        Eigen::Vector2d(-1e-10, 1.111e-10), 
        0.1);
    
    // FAIL ON [2,0]
    TUDAT_CHECK_MATRIX_CLOSE(
        Eigen::Vector3d(1, 1.0002, 1), 
        Eigen::Vector3d(1.0001, 1.0001, 1.0002), 
        1.1e-2);
    // SUCCESS
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(
        Eigen::Vector3d(1, 1.0002, 1), 
        Eigen::Vector3d(1.0001, 1.0001, 1.0002), 
        1.1e-2);

    // FAIL ON [0,1]
    TUDAT_CHECK_MATRIX_CLOSE(
        (Eigen::MatrixXd(2, 2) << 0.123456, 0.123456, 1.23456e28, 1.23456e-10).finished(), 
        (Eigen::MatrixXd(2, 2) << 0.123457, -0.123457, 1.23457e28, 1.23457e-10).finished(), 
        1e-3);
    TUDAT_CHECK_MATRIX_CLOSE_FRACTION(
        (Eigen::MatrixXd(2, 2) << 0.123456, 0.123456, 1.23456e28, 1.23456e-10).finished(), 
        (Eigen::MatrixXd(2, 2) << 0.123457, -0.123457, 1.23457e28, 1.23457e-10).finished(), 
        1e-3);
}

// Entry point for the test, like  '#define BOOST_TEST_MAIN' but allows for some additional logic
test_suite* init_unit_test_suite( int argc, char* argv[] ) 
{   
    // Switch to 1 when generating the 'unitTest_testMacros.match.pattern' with BOOST_AUTO_TEST_CASE
    // This way the same type of output is generated
    #if 0
        // Bind a new log formatter so no file
        unit_test_log.set_formatter( new logMessageFormatter );
    #endif

    // Make sure we have a BOOST_VERSION
    #ifndef BOOST_VERSION
        // Mark boost version as an old boost version 1_45 or prior
        #define BOOST_VERSION 104500
    #endif // BOOST_VERSION

    // Check if we have a new or and old version of boost and select the output accordingly:
    match_file_name = tudat::input_output::getCoreRootPath();
    if ( BOOST_VERSION / 100 % 1000 > 48 ) // Minor version
        match_file_name += "Basics/UnitTests/unitTestTestMacros.newBoost.pattern";
    else
        match_file_name += "Basics/UnitTests/unitTestTestMacros.oldBoost.pattern";

    return 0;
}