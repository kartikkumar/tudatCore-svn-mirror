/*! \file unitTestRungeKutta4Integrator.cpp
 *    Source file that defines the unit test for the 4th-order, fixed stepsize,
 *    Runge-Kutta integrator included in Tudat.
 *
 *    Path              : /Mathematics/NumericalIntegrators/UnitTests/
 *    Version           : 3
 *    Check status      : Checked
 *    Date created      : 17 May, 2011
 *    Last modified     : 27 January, 2012
 *
 *    References
 *      Burden, R.L., Faires, J.D. Numerical Analysis, 7th Edition, Books/Cole, 2001.
 *
 *    Notes
 *
 *    Copyright (c) 2010-2012 Delft University of Technology.
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
 *      120127    B. Tong Minh      Adapted for new Tudat core RK4 integrator
 */

// Include statements.
#include <limits>
#include <iostream>

#include "TudatCore/Mathematics/NumericalIntegrators/rungeKutta4Integrator.h"
#include "TudatCore/Mathematics/NumericalIntegrators/UnitTests/benchmarkFunctions.h"

//! Using declaration of the RungeKutta4IntegratorXd.
using tudat::mathematics::numerical_integrators::RungeKutta4IntegratorXd;



//! Test the result of the RK4 integrator
/*!
 * Test the result of the Runge-Kutta 4 integrator
 * \param stateDerivativeFunction Function pointer to the state derivative function
 * \param intervalStart The start of the integration interval
 * \param intervalEnd The end of the integration interval
 * \param stepSize The step size to take
 * \param initialState The initial state
 * \param expectedState Expected final state
 * \param tolerance Tolerance when comparing
 * \return true if actual final state equals the expected final state within the specified tolerance
 */
bool testRungeKutta4Integrator( const RungeKutta4IntegratorXd::StateDerivativeFunction& stateDerivativeFunction,
                                const double intervalStart, const double intervalEnd, const double stepSize,
                                const Eigen::VectorXd& initialState, const Eigen::VectorXd expectedState,
                                const double tolerance )
{
    using std::endl;

    // Create Runge-Kutta 4th-order, fixed stepsize integrator.
    {
        RungeKutta4IntegratorXd integrator( stateDerivativeFunction, intervalStart, initialState );

        Eigen::VectorXd finalState = integrator.integrateTo( intervalEnd, stepSize );

        // Compute differences between computed and expected interval end and generate
        // cerr statement if test fails.
        if ( std::abs( integrator.getCurrentInterval() - intervalEnd ) / intervalEnd >
             std::numeric_limits<double>::epsilon() )
        {
            std::cerr << "RungeKutta4Integrator end interval mismatch" << endl
                      << "Expected interval end: " << intervalEnd << endl
                      << "Actual interval end: " << integrator.getCurrentInterval() << endl;
            return false;
        }

        // Compute differences between computed and expected results and generate
        // cerr statement if test fails.
        if ( !expectedState.isApprox( finalState, tolerance ) )
        {
            std::cerr << "RungeKutta4Integrator test failed" << endl
                      << "Expected result: " << expectedState << endl
                      << "Actual result: " << finalState << endl;
            return false;
        }
    }

    // Try the same again, but in two steps
    {
        RungeKutta4IntegratorXd integrator( stateDerivativeFunction, intervalStart, initialState );

        const double intermediateInterval = intervalStart + ( intervalEnd - intervalStart ) / 2.0;

        const Eigen::VectorXd intermediateState = integrator.integrateTo( intermediateInterval,
                                                                          stepSize );
        // Compute differences between computed and expected interval end and generate
        // cerr statement if test fails.
        if ( std::abs( integrator.getCurrentInterval() - intermediateInterval ) /
             intermediateInterval >
             std::numeric_limits<double>::epsilon() )
        {
            std::cerr << "RungeKutta4Integrator intermediate interval mismatch" << endl
                      << "Expected intermediate interval: " << intermediateInterval << endl
                      << "Actual intermediate interval: " << integrator.getCurrentInterval()
                      << endl;
            return false;
        }

        // Integrate to the end
        Eigen::VectorXd finalState = integrator.integrateTo( intervalEnd, stepSize );

        // Compute differences between computed and expected interval end and generate
        // cerr statement if test fails.
        if ( std::abs( integrator.getCurrentInterval() - intervalEnd ) / intervalEnd >
             std::numeric_limits<double>::epsilon() )
        {
            std::cerr << "RungeKutta4Integrator end interval mismatch" << endl
                      << "Expected interval end: " << intervalEnd << endl
                      << "Actual interval end: " << integrator.getCurrentInterval() << endl;
            return false;
        }

        // Compute differences between computed and expected results and generate
        // cerr statement if test fails.
        if ( !expectedState.isApprox( finalState, tolerance ) )
        {
            std::cerr << "RungeKutta4Integrator two step test failed" << endl
                      << "Expected result: " << expectedState << endl
                      << "Actual result: " << finalState << endl;
            return false;
        }

        integrator.performIntegrationStep( stepSize );
        if ( !integrator.rollbackToPreviousState() )
        {
            std::cerr << "RungeKutta4Integrator rollback returned false" << endl;
            return false;
        }
        if ( std::abs( integrator.getCurrentInterval() - intervalEnd ) / intervalEnd >
             std::numeric_limits<double>::epsilon() )
        {
            std::cerr << "RungeKutta4Integrator rollback to invalid interval" << endl
                      << "Expected result: " << intervalEnd << endl
                      << "Actual result: " << integrator.getCurrentInterval() << endl;
            return false;
        }
        // This result should be exactly the same
        if ( integrator.getCurrentState() != finalState )
        {
            std::cerr << "RungeKutta4Integrator rollback to invalid state" << endl
                      << "Expected result: " << finalState << endl
                      << "Actual result: " << integrator.getCurrentState() << endl;
            return false;
        }

        if ( integrator.rollbackToPreviousState() )
        {
            std::cerr << "RungeKutta4Integrator second rollback returned true" << endl;
            return false;
        }
    }

    return true;
}

//! Test different types of states and state derivatives
/*!
 * Test if different types of states and state derivatives work. If something
 * is broken, then a compile time error will be generated.
 * \return Unconditionally true
 */
bool testDifferentStateAndStateDerivativeTypes()
{
    using tudat::unit_tests::numerical_integrators::zeroStateDerivative;
    tudat::mathematics::numerical_integrators::RungeKutta4Integrator
            <double, Eigen::Vector3d, Eigen::VectorXd> integrator( &zeroStateDerivative,
                                                                   0.0, Eigen::Vector3d::Zero() );
    integrator.integrateTo( 1.0, 0.1 );

    // No need to test anything, this is just to check compile time errors
    return true;
}


//! Test implementation of 4th-order, fixed stepsize, Runge-Kutta integrator.
int main( )
{

    // Test result initialised to false.
    bool testRK4IsOk = true;

    using namespace tudat::unit_tests::numerical_integrators;
    std::map< BenchmarkFunctions, BenchmarkFunction >& benchmarkFunctions =
             getBenchmarkFunctions();


    // Test with x_dot = 0, which results in x_f = x_0
    {
        testRK4IsOk &= testRungeKutta4Integrator( benchmarkFunctions[Zero].pointerToStateDerivativeFunction,
                                                  benchmarkFunctions[Zero].initialInterval,
                                                  benchmarkFunctions[Zero].endInterval,
                                                  0.2,
                                                  benchmarkFunctions[Zero].initialState,
                                                  benchmarkFunctions[Zero].endState,
                                                  std::numeric_limits<double>::epsilon() );
    }

    // Test with x_dot = 1, which results in x_f = x_0 + t_f
    {
        testRK4IsOk &= testRungeKutta4Integrator( benchmarkFunctions[Constant].pointerToStateDerivativeFunction,
                                                  benchmarkFunctions[Constant].initialInterval,
                                                  benchmarkFunctions[Constant].endInterval,
                                                  0.2,
                                                  benchmarkFunctions[Constant].initialState,
                                                  benchmarkFunctions[Constant].endState,
                                                  std::numeric_limits<double>::epsilon() );
    }

    // Test with x_dot = x, which results in x_f = x0 * exp( t_f )
    {
        testRK4IsOk &= testRungeKutta4Integrator( benchmarkFunctions[Exponential].pointerToStateDerivativeFunction,
                                                  benchmarkFunctions[Exponential].initialInterval,
                                                  benchmarkFunctions[Exponential].endInterval,
                                                  0.2,
                                                  benchmarkFunctions[Exponential].initialState,
                                                  benchmarkFunctions[Exponential].endState,
                                                  1e-3 );
    }

    // Test with x_dot = x, but integrate backwards
    {
        testRK4IsOk &= testRungeKutta4Integrator( benchmarkFunctions[InverseExponential].pointerToStateDerivativeFunction,
                                                  benchmarkFunctions[InverseExponential].initialInterval,
                                                  benchmarkFunctions[InverseExponential].endInterval,
                                                  -0.2,
                                                  benchmarkFunctions[InverseExponential].initialState,
                                                  benchmarkFunctions[InverseExponential].endState,
                                                  1e-3 );
    }

    // Test with an example from numerical recipes
    {
        testRK4IsOk &= testRungeKutta4Integrator( benchmarkFunctions[NumericalRecipes].pointerToStateDerivativeFunction,
                                                  benchmarkFunctions[NumericalRecipes].initialInterval,
                                                  benchmarkFunctions[NumericalRecipes].endInterval,
                                                  0.2,
                                                  benchmarkFunctions[NumericalRecipes].initialState,
                                                  benchmarkFunctions[NumericalRecipes].endState,
                                                  1e-8 );
    }

    testRK4IsOk &= testDifferentStateAndStateDerivativeTypes();

    return !testRK4IsOk;
}

// End of file.
