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
 *      100910    J. Melman         First creation of code.
 *      110111    J. Melman         Adapted to the offical Tudat standards.
 *      110124    J. Melman         Further adapted to the offical Tudat standards.
 *      110201    J. Melman         Made the tests for obliquity and astronomical unit more
 *                                  accurate.
 *      120127    D. Dirkx          Moved to Tudat core.
 *      120127    K. Kumar          Transferred unit tests over to Boost unit test framework.
 *      120128    K. Kumar          Changed BOOST_CHECK to BOOST_CHECK_CLOSE_FRACTION for unit test
 *                                  comparisons.
 *
 *    References
 *
 */

// Required Boost unit test framework define.
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include "TudatCore/Mathematics/BasicMathematics/mathematicalConstants.h"
#include "boost/math/special_functions/fpclassify.hpp"

namespace unit_test {

// Define Boost test suite.
BOOST_AUTO_TEST_SUITE( test_mathematical_constants )

//! Check correct pi using PI = circumference / diameter:
BOOST_AUTO_TEST_CASE( test_PI )
{    
    double radius = 5;
    // Circumference circle with radius 5, 32 digits precision, see
    // http://www.wolframalpha.com/input/?i=Circumference+of+a+circle+with+radius+5
    // http://www.wolframalpha.com/input/?i=N[10*PI,66]
    double circumference = 31.4159265358979323846264338327950288419716939937510582097494459230; 
    BOOST_CHECK_CLOSE(  tudat::mathematics::PI, 
                        circumference / (2 * radius) , 
                        std::numeric_limits<double>::epsilon() );
}

//! Check correct E using E Wolfram alpha as reference
BOOST_AUTO_TEST_CASE( test_E )
{    
    // Numerical value from:
    // http://www.wolframalpha.com/input/?i=e+72+digits
    BOOST_CHECK_CLOSE(  tudat::mathematics::E, 
        2.71828182845904523536028747135266249775724709369995957496696762772407663, 
        std::numeric_limits<double>::epsilon() );
}

//! Check correct GOLDEN_RATIO using GOLDEN_RATIO Wolfram alpha as reference
BOOST_AUTO_TEST_CASE( test_GOLDEN_RATIO )
{    
    // Numerical value from:
    // http://www.wolframalpha.com/input/?i=golden+ratio+72+digits
    BOOST_CHECK_CLOSE(  tudat::mathematics::GOLDEN_RATIO, 
        1.618033988749894848204586834365638117720309179805762862135448622705260463, 
        std::numeric_limits<double>::epsilon() );
}

//! Check correct NAN using boost Floating Point Classification (fpclassify)
BOOST_AUTO_TEST_CASE( test_NAN )
{    
    // Numerical value from:
    // http://www.wolframalpha.com/input/?i=golden+ratio+72+digits
    BOOST_CHECK(  boost::math::isnan( TUDAT_NAN ) );
}

// Close Boost test suite.
BOOST_AUTO_TEST_SUITE_END( ) // End test_mathematical_constants

}
