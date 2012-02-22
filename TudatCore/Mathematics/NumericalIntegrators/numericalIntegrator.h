/*    Copyright (c) 2012 Delft University of Technology.
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
 *      120207    K. Kumar          Minor comment corrections.
 *      120213    K. Kumar          Modified getCurrentInterval() to getIndependentVariable().
 *
 *    References
 *
 */

#ifndef TUDAT_CORE_NUMERICAL_INTEGRATOR_H
#define TUDAT_CORE_NUMERICAL_INTEGRATOR_H

#include <limits>
#include <boost/function.hpp>
#include <Eigen/Core>

namespace tudat
{
namespace mathematics
{
namespace numerical_integrators
{

//! Base class for the numerical integrators.
/*!
 * Base class for numerical integrators.
 * \tparam StateType The type of the state. This type should support addition,
 *          subtraction and assignment operators.
 * \tparam StateDerivativeType The type of the state derivative. This type should support
 *          multiplication with IndependentVariableType and doubles.
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
    typedef boost::function< StateDerivativeType(
            const IndependentVariableType, const StateType& ) > StateDerivativeFunction;

    //! Default constructor.
    /*!
     * Default constructor, taking a state derivative function as argument.
     * \param stateDerivativeFunction State derivative function.
     */
    NumericalIntegrator( const StateDerivativeFunction& stateDerivativeFunction ) :
        stateDerivativeFunction_( stateDerivativeFunction ) { }

    //! Default virtual destructor.
    /*!
     * Default virtual destructor.
     */
    virtual ~NumericalIntegrator( ) { }

    //! Get step size of the next step.
    /*!
     * Returns the step size of the next step. Derived classes should override this and provide the
     * last step size that was computed or passed to performIntegrationStep( ).
     * \return Step size to be used for the next step.
     */
    virtual IndependentVariableType getNextStepSize( ) const = 0;

    //! Get current state.
    /*!
     * Returns the current state of the integrator. Derived classes should override this and
     * provide the computed state by performIntegrationStep( ).
     * \return Current integrated state.
     */
    virtual StateType getCurrentState( ) const = 0;

    //! Get current independent variable.
    /*!
     * Returns the current value of the independent variable of the integrator. Derived classes
     * should override this and provide the computed independent variable by
     * performIntegrationStep().
     * \return Current independent variable.
     */
    virtual IndependentVariableType getCurrentIndependentVariable( ) const = 0;

    //! Rollback internal state to the step performed by performIntegrationStep()
    /*!
     * Performs rollback of internal state to the step performed by performIntegrationStep(). This
     * is not necessarily equal the start of the integration interval after integrateTo() has been.
     * called. This function can only be called once after calling or performIntegrationStep()
     * unless specified otherwise by implementations, and can not be called before integrateTo()
     * has been called.
     * Will return true if the rollback was successful, and false otherwise.
     * \return True if the rollback was successful.
     */
    virtual bool rollbackToPreviousState( ) = 0;

    //! Perform an integration to a specified independent variable value.
    /*!
     * Performs an integration to independentVariableEnd with initial state and initial independent
     * variable value specified by the current state of the integrator and the current independent
     * variable value. This implementation of integrateTo chooses the final step size such that it
     * exactly coincides with the given independentVariableEnd.
     * \param intervalEnd The value of the independent variable at the end of the interval to
     *          integrate over.
     * \param initialStepSize The initial step size to use.
     * \return The state at independentVariableEnd.
     */
    virtual StateType integrateTo( const IndependentVariableType intervalEnd,
                                   const IndependentVariableType initialStepSize );


    //! Perform a single integration step.
    /*!
     * Performs a single integration step from current independent variable and state as specified
     * by initialStateHistory and specified stepSize. This function should determine the next step
     * and make it available to getNextStepSize(), return the current state and store it for
     * getCurrentState(), and store the current independent variable value for
     * getCurrentIndependentVariable().
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

};

//! Perform an integration to a specified independent variable value.
template < typename IndependentVariableType, typename StateType, typename StateDerivativeType >
StateType NumericalIntegrator< IndependentVariableType, StateType, StateDerivativeType >::
integrateTo( const IndependentVariableType intervalEnd,
             const IndependentVariableType initialStepSize )
{
    IndependentVariableType stepSize = initialStepSize;

    // Flag to indicate that the integration end value of the independent variable has been
    // reached.
    bool atIntegrationIntervalEnd = ( intervalEnd - getCurrentIndependentVariable( ) )
            * stepSize / std::fabs( stepSize )
            <= std::numeric_limits< IndependentVariableType >::epsilon( );

    while ( !atIntegrationIntervalEnd )
    {
        // Check if the remaining interval is smaller than the step size.
        if ( std::fabs( intervalEnd - getCurrentIndependentVariable( ) )
             <= std::fabs( stepSize ) *
             ( 1.0 + std::numeric_limits< IndependentVariableType >::epsilon( ) ) )
        {
            // The next step is beyond the end of the integration interval, so adjust the
            // step size accordingly.
            stepSize = intervalEnd - getCurrentIndependentVariable( );

            // Explicitly flag that the integration interval end is reached. Due to rounding
            // off errors, it may not be possible to use
            // ( currentIndependentVariable >= independentVariableEnd ) // in the while condition.
            atIntegrationIntervalEnd = true;
        }

        // Perform the step.
        performIntegrationStep( stepSize );

        stepSize = getNextStepSize( );
    }

    return getCurrentState( );
}

} // namespace numerical_integrators
} // namespace mathematics
} // namespace tudat

#endif // TUDAT_CORE_NUMERICAL_INTEGRATOR_H
