/*! \file unitTestNumericalIntegrator.cpp
 *    Source file that defines the unit test for the abstract base class for numerical integrators
 *    in Tudat.
 *
 *    Path              : /Mathematics/NumericalIntegrators/
 *    Version           : 2
 *    Check status      : Checked
 *
 *    Author            : B. Tong Minh
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : b.tongminh@student.tudelft.nl
 *
 *    Checker           : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Date created      : 27 January, 2012
 *    Last modified     : 6 February, 2012
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2012 Delft University of Technology.
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
 *      120127    B. Tong Minh      File created.
 *      120128    D. Dirkx          Minor changes during code check.
 *      120206    K. Kumar          Minor comment corrections.
 */

// Include statements.
#include <boost/bind.hpp>
#include <Eigen/Core>
#include <iostream>
#include <limits>
#include "TudatCore/Mathematics/NumericalIntegrators/numericalIntegrator.h"
#include "TudatCore/Mathematics/NumericalIntegrators/UnitTests/benchmarkFunctions.h"

//! Using declaration of the NumericalIntegrator.
using tudat::mathematics::numerical_integrators::NumericalIntegrator;

//! Dummy numerical integrator.
/*!
 * Dummy numerical integrator that keeps track of the amount of steps made.
 */
class DummyNumericalIntegrator :
        public NumericalIntegrator< double, Eigen::VectorXd, Eigen::VectorXd >
{
public:

    //! Default constructor.
    /*!
     * Default constructor, setting zeroDerivative as the state derivative function.
     */
    DummyNumericalIntegrator( const double intervalStart,
                              const Eigen::VectorXd& initialState ) :
        NumericalIntegrator< double, Eigen::VectorXd, Eigen::VectorXd >(
            &tudat::unit_tests::numerical_integrators::zeroStateDerivative ),
        numberOfSteps( 0 ), currentIntegrationIntervalPoint_( intervalStart ), currentState_( initialState ) { }

    //! Get step size of the next step.
    /*!
     * Returns the step size of the next step.
     * \return Step size to be used for the next step.
     */
    virtual double getNextStepSize( ) const { return stepSize_; }

    //! Get current state.
    /*!
     * Returns the current state stored interally by the integrator.
     * \return Current state.
     */
    virtual Eigen::VectorXd getCurrentState( ) const { return currentState_; }

    //! Get current interval.
    /*!
     * Returns the current interval stored interally by the integrator.
     * \return Current interval.
     */
    virtual double getCurrentInterval( ) const { return currentIntegrationIntervalPoint_; }

    //! Rollback the internal state to the last state.
    /*!
     * Performs rollback of the internal state to the last state. This function can only be called
     * once after calling integrateTo( ) or performIntegrationStep( ) unless specified otherwise by
     * implementations, and can not be called before any of these functions have been called. Will
     * return true if the rollback was succesful, and false otherwise.
     * \return True if the rollback was successful.
     */
    virtual bool rollbackToPreviousState( )
    {
        return true;
    }

    //! Perform a single integration step that does not do anything.
    /*!
     * Performs a single integration step that does not do anything, except incrementing the
     * step counter.
     * \param initialStateHistory The initial state, as a map of initial time <> initial state.
     * \param stepSize The step size of this step.
     * \return The state history at the end of the interval, which is basically equal to the input.
     */
    virtual Eigen::VectorXd performIntegrationStep( const double stepSize )
    {
        // Increment the step counter.
        numberOfSteps++;

        stepSize_ = stepSize;
        currentIntegrationIntervalPoint_ += this->stepSize_;

        return currentState_;
    }

    //! Counter of the number of steps.
    /*!
     * Counter of the number of steps taken.
     */
    int numberOfSteps;

protected:

    //! Last used step size by this integrator.
    /*!
     * Last used step size by this integrator.
     */
    double stepSize_;

    //! Current integration interval point.
    /*!
     * Current integration interval point stored internally by the integrator.
     */
    double currentIntegrationIntervalPoint_;

    //! Current state.
    /*!
     * Current state stored internally by the integrator.
     */
    Eigen::VectorXd currentState_;
};

//! Test the amount of steps that NumericalIntegrator::integrateTo takes.
/*!
 * Test the amount of steps that NumericalIntegrator::integrateTo takes.
 * \param intervalStart The start of the integration interval
 * \param intervalEnd The end of the integration interval
 * \param initialState The initial state.
 * \param stepSize The step size to take.
 * \param expectedNumberOfSteps Number of steps from intervalStart to intervalEnd.
 * \returnTtrue if actual number of steps is equal to actual number of steps; false otherwise.
 */
bool testIntegrateToFunction( const double intervalStart, const double intervalEnd,
                              const Eigen::VectorXd& initialState,
                              const double stepSize )
{
    DummyNumericalIntegrator integrator( intervalStart, initialState );
    Eigen::VectorXd integratedState = integrator.integrateTo( intervalEnd, stepSize );

    // Calculate expected number of steps.
    int expectedNumberOfSteps = static_cast< int >( std::ceil( ( intervalEnd - intervalStart ) / stepSize ) );

    // Check if the actual number of steps is equal to the expected number of steps.
    if ( integrator.numberOfSteps != expectedNumberOfSteps )
    {
        std::cerr << "NumericalIntegrator::execute test failed" << std::endl
                  << "Expected number of steps: " << expectedNumberOfSteps << std::endl
                  << "Actual number of steps: " << integrator.numberOfSteps << std::endl;
        return false;
    }

    // Check if the integrated state is equal to the initial state.
    // This is an exact comparison, because no arithmetics are performed on the state.
    if ( integratedState != initialState )
    {
        std::cerr << "DummyNumericalIntegrator was not a dummy integrator!" << std::endl;
        return false;
    }

    return true;

}

//! Test main
int main( )
{
    bool testOk = true;

    // Random initial state.
    Eigen::VectorXd initialState( 4 );
    initialState << 0.34, 0.24, 0.76, 0.10;

    // Test the number of steps for various intervals.
    testOk &= testIntegrateToFunction( 0.0, 0.0, initialState, 10.0 );
    testOk &= testIntegrateToFunction( 0.0, 10.0, initialState, 10.0 );
    testOk &= testIntegrateToFunction( 0.0, 20.0, initialState, 10.0 );
    testOk &= testIntegrateToFunction( 0.0, 30.0, initialState, 10.0 );

    testOk &= testIntegrateToFunction( 0.0, 10.0, initialState, 2.5 );
    testOk &= testIntegrateToFunction( 0.0, 10.0, initialState, 3.0 );
    testOk &= testIntegrateToFunction( 0.0, 10.0, initialState, 3.5 );

    return !testOk;
}

// End of file.
