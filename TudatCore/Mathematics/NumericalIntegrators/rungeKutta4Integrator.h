/*!   Copyright (c) 2012 Delft University of Technology.
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
 *
 *    References
 *
 */

#ifndef TUDAT_CORE_RUNGE_KUTTA_4_INTEGRATOR_H
#define TUDAT_CORE_RUNGE_KUTTA_4_INTEGRATOR_H

// Include statements.
#include "TudatCore/Mathematics/NumericalIntegrators/numericalIntegrator.h"

//! Tudat library namespace.
/*!
 * The Tudat library namespace.
 */
namespace tudat
{

//! Mathematics namespace.
/*!
 * The mathematics namespace included in Tudat.
 */
namespace mathematics
{

//! Numerical integrators namespace.
/*!
 * The numerical integrators namespace included in Tudat.
 */
namespace numerical_integrators
{

//! Class that implements the Runge-Kutta 4 integrator.
/*!
 * Class that implements the Runge-Kutta 4, fixed order, fixed step size integrator.
 * \tparam StateType The type of the state. This type should support addition with
 *          StateDerivativeType.
 * \tparam StateDerivativeType The type of the state derivative. This type should support
 *          multiplication with IndependentVariableType and doubles.
 * \tparam IndependentVariableType The type of the independent variable.
 * \sa NumericalIntegrator.
 */
template < typename IndependentVariableType = double, typename StateType = Eigen::VectorXd,
           typename StateDerivativeType = Eigen::VectorXd >
class RungeKutta4Integrator :
        public NumericalIntegrator< IndependentVariableType, StateType, StateDerivativeType >
{
public:

    //! Typedef of the base class.
    /*!
     * Typedef of the base class with all template parameters filled in.
     */
    typedef NumericalIntegrator< IndependentVariableType, StateType, StateDerivativeType > Base;

    //! Typedef to the state derivative function.
    /*!
     * Typedef to the state derivative function inherited from the base class.
     * \sa NumericalIntegrator::StateDerivativeFunction.
     */
    typedef typename Base::StateDerivativeFunction StateDerivativeFunction;

    //! Default constructor.
    /*!
     * Default constructor, taking a state derivative function as argument.
     * \param stateDerivativeFunction State derivative function.
     * \param intervalStart The start of the integration interval.
     * \param initialState The initial state.
     * \sa NumericalIntegrator::NumericalIntegrator.
     */
    RungeKutta4Integrator( const StateDerivativeFunction& stateDerivativeFunction,
                           const IndependentVariableType intervalStart,
                           const StateType& initialState ) :
        Base( stateDerivativeFunction ), currentInterval_( intervalStart ),
        currentState_( initialState ), lastInterval_( intervalStart ) { }

    //! Get step size of the next step.
    /*!
     * Returns the step size of the next step.
     * \return Step size to be used for the next step.
     */
    virtual IndependentVariableType getNextStepSize( ) const { return stepSize_; }

    //! Get current state.
    /*!
     * Returns the current state of the integrator. Derived classes should override this and
     * provide the computed state by performIntegrationStep().
     * \return Current integrated state,
     */
    virtual StateType getCurrentState( ) const { return currentState_; }

    //! Returns the current interval
    /*!
     * Returns the current interval of the integrator. Child classes should override this and
     * provide the computed interval by performIntegrationStep().
     * \return Current interval
     */
    virtual IndependentVariableType getCurrentInterval( ) const { return currentInterval_; }

    //! Perform a single integration step.
    /*!
     * Perform a single integration step.
     * \param stepSize The step size to take.
     * \return The state at the end of the interval,
     */
    virtual StateType performIntegrationStep( const IndependentVariableType stepSize )
    {
        lastInterval_ = currentInterval_;
        lastState_ = currentState_;

        // Calculate k1-k4.
        const StateDerivativeType k1 = stepSize * stateDerivativeFunction_(
                    currentInterval_, currentState_ );
        const StateDerivativeType k2 = stepSize * stateDerivativeFunction_(
                    currentInterval_ + stepSize / 2.0,
                    static_cast< StateType >( currentState_ + k1 / 2.0 ) );
        const StateDerivativeType k3 = stepSize * stateDerivativeFunction_(
                    currentInterval_ + stepSize / 2.0,
                    static_cast< StateType >( currentState_ + k2 / 2.0 ) );
        const StateDerivativeType k4 = stepSize * stateDerivativeFunction_(
                    currentInterval_ + stepSize,
                    static_cast< StateType >( currentState_ + k3 ) );

        stepSize_ = stepSize;
        currentInterval_ += stepSize_;
        currentState_ += ( k1 + 2.0 * k2 + 2.0 * k3 + k4 ) / 6.0;

        // Return the integration result.
        return currentState_;
    }

    //! Rollback internal state to the last state.
    /*!
     * Performs rollback of internal state to the last state. This function can only be called once
     * after calling integrateTo( ) or performIntegrationStep( ) unless specified otherwise by
     * implementations, and can not be called before any of these functions have been called. Will
     * return true if the rollback was succesful, and false otherwise.
     * \return True if the rollback was successful.
     */
    virtual bool rollbackToPreviousState( )
    {
        if ( currentInterval_ == lastInterval_ )
        {
            return false;
        }

        currentInterval_ = lastInterval_;
        currentState_ = lastState_;
        return true;
    }

protected:

    //! Last used step size.
    /*!
     * Last used step size, passed to either integrateTo() or performIntegrationStep().
     */
    IndependentVariableType stepSize_;

    //! Current interval.
    /*!
     * Current interval as computed by performIntegrationStep().
     */
    IndependentVariableType currentInterval_;

    //! Current state.
    /*!
     * Current state as computed by performIntegrationStep().
     */
    StateType currentState_;

    //! Last interval.
    /*!
     * Last interval as computed by performIntegrationStep().
     */
    IndependentVariableType lastInterval_;

    //! Last state.
    /*!
     * Last state as computed by performIntegrationStep().
     */
    StateType lastState_;

}; // class RungeKutta4Integrator.

//! Typedef of RK4 integrator (state/state derivative = VectorXd, independent variable = double).
/*!
 * Typedef of an RK4 integrator with VectorXds as state and state derivative and double as
 * independent variable.
 */
typedef RungeKutta4Integrator< > RungeKutta4IntegratorXd;

//! Typedef of a scalar RK4 integrator.
/*!
 * Typedef of an RK4 integrator with doubles as state and state derivative and independent variable.
 */
typedef RungeKutta4Integrator< double, double, double > RungeKutta4Integratord;

} // namespace integrators.

} // namespace mathematics.

} // namespace tudat.

#endif // TUDAT_CORE_RUNGE_KUTTA_4_INTEGRATOR_H

// End of file.
