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
 *      110517    K. Kumar          File created.
 *      110905    S. Billemont      Reorganized includes.
 *                                  Moved (con/de)structors and getter/setters to header.
 *      120127    B. Tong Minh      Adapted for new Tudat core RK4 integrator.
 *      120207    K. Kumar          Adapted to Boost unit test framework.
 *      120213    K. Kumar          Modified getCurrentInterval() to getIndependentVariable().
 *      120321    K. Kumar          Updated to use new Burden and Faires benchmark function.
 *
 *    References
 *      Burden, R.L., Faires, J.D. Numerical Analysis, 7th Edition, Books/Cole, 2001.
 *
 */

#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <limits>
#include <map>
#include "TudatCore/Mathematics/NumericalIntegrators/rungeKutta4Integrator.h"
#include "TudatCore/Mathematics/NumericalIntegrators/UnitTests/benchmarkFunctions.h"

namespace tudat
{
namespace unit_tests
{

//! Test suite for Runge-Kutta 4 integrator.
BOOST_AUTO_TEST_SUITE( test_runge_kutta_4_integrator )

//! Using declaration of the RungeKutta4IntegratorXd.
using tudat::mathematics::numerical_integrators::RungeKutta4IntegratorXd;

//! Test the validity of the RK4 integrator.
/*!
 * Tests the validity of the Runge-Kutta 4 integrator.
 * \param stateDerivativeFunction Function pointer to the state derivative function.
 * \param intervalStart The start of the integration interval.
 * \param intervalEnd The end of the integration interval.
 * \param stepSize The step size to take.
 * \param initialState The initial state.
 * \param expectedState Expected final state.
 * \param tolerance Tolerance when comparing.
 * \return True if actual final state equals the expected final state within the specified
 *          tolerance.
 */
bool testValidityOfRungeKutta4Integrator(
        const RungeKutta4IntegratorXd::StateDerivativeFunction& stateDerivativeFunction,
        const double intervalStart, const double intervalEnd, const double stepSize,
        const Eigen::VectorXd& initialState, const Eigen::VectorXd expectedState,
        const double tolerance )
{
    // Create Runge-Kutta 4th-order, fixed stepsize integrator.
    {
        RungeKutta4IntegratorXd integrator( stateDerivativeFunction, intervalStart, initialState );

        Eigen::VectorXd finalState = integrator.integrateTo( intervalEnd, stepSize );

        // Compute differences between computed and expected interval end.
        if ( std::fabs( integrator.getCurrentIndependentVariable( ) - intervalEnd )
            / intervalEnd > std::numeric_limits< double >::epsilon( ) )
        {
            return false;
        }

        // Compute differences between computed and expected results.
        if ( !expectedState.isApprox( finalState, tolerance ) )
        {
            return false;
        }
    }

    // Try the same again, but in two steps.
    {
        RungeKutta4IntegratorXd integrator( stateDerivativeFunction, intervalStart, initialState );

        const double intermediateIndependentVariable
                = intervalStart + ( intervalEnd - intervalStart ) / 2.0;

        const Eigen::VectorXd intermediateState = integrator.integrateTo(
                    intermediateIndependentVariable, stepSize );

        // Compute differences between computed and expected interval end.
        if ( std::fabs( integrator.getCurrentIndependentVariable( )
                        - intermediateIndependentVariable ) /
             intermediateIndependentVariable > std::numeric_limits< double >::epsilon( ) )
        {
            return false;
        }

        // Integrate to the end.
        Eigen::VectorXd finalState = integrator.integrateTo( intervalEnd, stepSize );

        // Compute differences between computed and expected interval end.
        if ( std::fabs( integrator.getCurrentIndependentVariable( ) - intervalEnd )
             / intervalEnd > std::numeric_limits< double >::epsilon( ) )
        {
            return false;
        }

        // Compute differences between computed and expected results and generate
        // cerr statement if test fails.
        if ( !expectedState.isApprox( finalState, tolerance ) )
        {
            return false;
        }

        integrator.performIntegrationStep( stepSize );
        if ( !integrator.rollbackToPreviousState( ) )
        {
            return false;
        }

        if ( std::fabs( integrator.getCurrentIndependentVariable( ) - intervalEnd )
             / intervalEnd > std::numeric_limits<double>::epsilon( ) )
        {
            return false;
        }

        // This result should be exactly the same.
        if ( integrator.getCurrentState( ) != finalState )
        {
            return false;
        }

        if ( integrator.rollbackToPreviousState () )
        {
            return false;
        }
    }

    return true;
}

//! Test different types of states and state derivatives.
/*!
 * Test if different types of states and state derivatives work. If something
 * is broken, then a compile time error will be generated.
 * \return Unconditionally true.
 */
bool testDifferentStateAndStateDerivativeTypes( )
{
    tudat::mathematics::numerical_integrators::RungeKutta4Integrator
            < double, Eigen::Vector3d, Eigen::VectorXd > integrator(
                &computeZeroStateDerivative, 0.0, Eigen::Vector3d::Zero( ) );

    integrator.integrateTo( 1.0, 0.1 );

    // No need to test anything, this is just to check compile time errors.
    return true;
}

//! Test if the Runge-Kutta 4 integrator is working correctly.
BOOST_AUTO_TEST_CASE( testRungeKutta4Integrator )
{
    using namespace tudat::mathematics::numerical_integrators;
    std::map< BenchmarkFunctions, BenchmarkFunction >& benchmarkFunctions =
            getBenchmarkFunctions( );

    // Case 1: test with x_dot = 0, which results in x_f = x_0.
    {
        BOOST_CHECK( testValidityOfRungeKutta4Integrator(
                         benchmarkFunctions[ Zero ].pointerToStateDerivativeFunction_,
                         benchmarkFunctions[ Zero ].intervalStart_,
                         benchmarkFunctions[ Zero ].intervalEnd_, 0.2,
                         benchmarkFunctions[ Zero ].initialState_,
                         benchmarkFunctions[ Zero ].finalState_,
                         std::numeric_limits< double >::epsilon( ) ) );
    }

    // Case 2: test with x_dot = 1, which results in x_f = x_0 + t_f.
    {
        BOOST_CHECK( testValidityOfRungeKutta4Integrator(
                         benchmarkFunctions[ Constant ].pointerToStateDerivativeFunction_,
                         benchmarkFunctions[ Constant ].intervalStart_,
                         benchmarkFunctions[ Constant ].intervalEnd_, 0.2,
                         benchmarkFunctions[ Constant ].initialState_,
                         benchmarkFunctions[ Constant ].finalState_,
                         std::numeric_limits< double >::epsilon( ) ) );
    }

    // Case 3: test with x_dot = x, which results in x_f = x0 * exp( t_f ).
    {
        BOOST_CHECK( testValidityOfRungeKutta4Integrator(
                         benchmarkFunctions[ Exponential ].pointerToStateDerivativeFunction_,
                         benchmarkFunctions[ Exponential ].intervalStart_,
                         benchmarkFunctions[ Exponential ].intervalEnd_, 0.2,
                         benchmarkFunctions[ Exponential ].initialState_,
                         benchmarkFunctions[ Exponential ].finalState_, 1.0e-3 ) );
    }

    // Case 4: test with x_dot = x, but integrate backwards.
    {
        BOOST_CHECK( testValidityOfRungeKutta4Integrator(
                         benchmarkFunctions[ BackwardsExponential ]
                         .pointerToStateDerivativeFunction_,
                         benchmarkFunctions[ BackwardsExponential ].intervalStart_,
                         benchmarkFunctions[ BackwardsExponential ].intervalEnd_, -0.2,
                         benchmarkFunctions[ BackwardsExponential ].initialState_,
                         benchmarkFunctions[ BackwardsExponential ].finalState_, 1e-3 ) );
    }

    // Case 5: test with an example from Burden and Faires.
    {
        BOOST_CHECK( testValidityOfRungeKutta4Integrator(
                         benchmarkFunctions[ BurdenAndFairesRungeKutta4 ]
                         .pointerToStateDerivativeFunction_,
                         benchmarkFunctions[ BurdenAndFairesRungeKutta4 ].intervalStart_,
                         benchmarkFunctions[ BurdenAndFairesRungeKutta4 ].intervalEnd_,  0.2,
                         benchmarkFunctions[ BurdenAndFairesRungeKutta4 ].initialState_,
                         benchmarkFunctions[ BurdenAndFairesRungeKutta4 ].finalState_, 1.0e-8 ) );
    }

    // Case 6: test if difference in type between state and state derivative works.
    {
        BOOST_CHECK( testDifferentStateAndStateDerivativeTypes( ) );
    }
}

BOOST_AUTO_TEST_SUITE_END( )

} // namespace unit_tests
} // namespace tudat
