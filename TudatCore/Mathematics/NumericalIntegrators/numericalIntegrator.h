/*! \file numericalIntegrator.h
 *    Header file that defines the abstract base class for all numerical integrators
 *
 *    Path              : /Mathematics/NumericalIntegrators/
 *    Version           : 1
 *    Check status      : Unchecked
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
 *    Last modified     : 28 January, 2012
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
 *      120127    B. Tong Minh      File created
 *      120128    D. Dirkx          Minor changes during code check
 */

#ifndef TUDAT_CORE_NUMERICALINTEGRATOR_H
#define TUDAT_CORE_NUMERICALINTEGRATOR_H

#include <limits>
#include <boost/function.hpp>
#include <Eigen/Core>

//! Tudat library namespace.
namespace tudat
{

//! Tudat mathematics namespace.
namespace mathematics
{

//! Integrators namespace.
namespace numerical_integrators
{

//! Base class for the numerical integrators.
/*!
 * Base class for numerical integrators.
 * \tparam StateType The type of the state. This type should support addition,
 * subtraction and assignment operators.
 * \tparam StateDerivativeType The type of the state derivative. This type should support
 * multiplication with IndependentVariableType and doubles.
 * \tparam IndependentVariableType The type of the independent variable.
 */
template < typename IndependentVariableType = double, typename StateType = Eigen::VectorXd,
           typename StateDerivativeType = Eigen::VectorXd >
class NumericalIntegrator
{
public:


    //! Typedef to the state derivative function.
    /*!
     * Typedef to the state derivative function. This should be a pointer to a function or a boost
     * function.
     */
    typedef boost::function< StateDerivativeType( const IndependentVariableType, const StateType& ) >
        StateDerivativeFunction;

    //! Standard constructor.
    /*!
     * Standard constructor, taking a state derivative function as argument.
     * \param stateDerivativeFunction_ State derivative function.
     */
    NumericalIntegrator( const StateDerivativeFunction& stateDerivativeFunction ) :
        stateDerivativeFunction_( stateDerivativeFunction )
    { }

    //! Default virtual destructor.
    /*!
     * Default virtual destructor.
     */
    virtual ~NumericalIntegrator( )
    { }

    //! Returns the step size of the next step
    /*!
     * Returns the step size of the next step. Child classes should override this and provide the
     * last step size that was computed or passed to performIntegrationStep( ).
     * \return Step size to be used for the next step
     */
    virtual IndependentVariableType getNextStepSize( ) const = 0;

    //! Returns the current state
    /*!
     * Returns the current state of the integrator. Child classes should override this and provide
     * the computed state by performIntegrationStep( ).
     * \return Current integrated state
     */
    virtual StateType getCurrentState( ) const = 0;

    //! Returns the current interval
    /*!
     * Returns the current interval of the integrator. Child classes should override this and
     * provide the computed interval by performIntegrationStep().
     * \return Current interval
     */
    virtual IndependentVariableType getCurrentInterval( ) const = 0;

    //! Rollback the internal state to the step performed by performIntegrationStep()
    /*!
     * Rollback the internal state to the step performed by performIntegrationStep(). This is not
     * necessarily equal the initial interval after integrateTo() has been called. This function
     * can only be called once after calling or performIntegrationStep( ) unless specified
     * otherwise by implementations, and can not be called before integrateTo() has been called.
     * Will return true if the rollback was succesful, and false otherwise.
     * \return True if the rollback was succesful.
     */
    virtual bool rollbackToPreviousState( ) = 0;


    //! Perform an integration to a specified interval
    /*!
     * Perform an integration to intervalEnd with initial state and interval specified by the
     * current state of the integrator and the provided initial step size.
     * This implementation of integrateTo chooses the final step size such that it exactly
     * coincides with the given intervalEnd.
     * \param intervalEnd The end of the interval to integrate over
     * \param initialStepSize The initial step size to use
     * \return The state at intervalEnd
     */
    virtual StateType integrateTo( const IndependentVariableType intervalEnd,
                                   const IndependentVariableType initialStepSize );


    //! Perform a single integration step
    /*!
     * Perform a single integration step from interval and state as specified by
     * initialStateHistory and specified stepSize. This function should determine the next step
     * and make it available to getNextStepSize(), return the current state and store it for
     * getCurrentState(), and store the current interval for getCurrentInterval().
     * \param stepSize The step size of this step.
     * \return The state at the end of the interval.
     */
    virtual StateType performIntegrationStep( const IndependentVariableType stepSize ) = 0;

protected:
    //! Function that returns the state derivative.
    /*!
     * Function that returns the state derivative, as passed to the constructor.
     */
    StateDerivativeFunction stateDerivativeFunction_;



}; // class NumericalIntegrator

//! Perform an integration to a specified interval
template < typename IndependentVariableType, typename StateType, typename StateDerivativeType >
StateType NumericalIntegrator< IndependentVariableType, StateType, StateDerivativeType >::
integrateTo( const IndependentVariableType intervalEnd,
             const IndependentVariableType initialStepSize )
{
    IndependentVariableType stepSize = initialStepSize;


    // Flag to indicate that the integration interval end has been reached
    bool atIntegrationIntervalEnd = std::numeric_limits<double>::epsilon() <=
            ( getCurrentInterval() + stepSize - intervalEnd );

    while ( !atIntegrationIntervalEnd )
    {
        if ( getCurrentInterval() + stepSize >= intervalEnd )
        {
            // The next step is beyond the end of the integration interval, so adjust the
            // step size accordingly
            stepSize = intervalEnd - getCurrentInterval();

            // Explicitly flag that the integration interval end is reached. Due to rounding
            // off errors, it may not be possible to use ( currentInterval >= intervalEnd )
            // in the while condition.
            atIntegrationIntervalEnd = true;
        }

        // Perform the step
        performIntegrationStep( stepSize );

        stepSize = getNextStepSize( );
    }

    return getCurrentState();
}

} // namespace integrators

} // namespace mathematics

} // namespace tudat

#endif // TUDAT_CORE_NUMERICALINTEGRATOR_H
