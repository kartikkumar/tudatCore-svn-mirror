#ifndef TUDAT_CORE_BENCHMARKFUNCTIONS_H
#define TUDAT_CORE_BENCHMARKFUNCTIONS_H

#include <map>

#include <Eigen/Core>
#include <boost/function.hpp>


namespace tudat
{

namespace unit_tests
{

namespace numerical_integrators
{

//! Struct containing information about a benchmark function
/*!
 * Struct containing information about a benchmark function
 * \sa getBenchmarkFunctions()
 */
struct BenchmarkFunction
{
    //! Typedef to a benchmark state derivative function
    typedef boost::function< Eigen::VectorXd( const double, const Eigen::VectorXd& ) >
        StateDerivativeFunction;
    //! Pointer to a benchmark state derivative function
    StateDerivativeFunction pointerToStateDerivativeFunction;

    //! Integration interval start
    double initialInterval;
    //! Integration initial state
    Eigen::VectorXd initialState;

    //! Integration interval end
    double endInterval;
    //! Expected end state
    Eigen::VectorXd endState;

    //! Default constructor
    /*!
     * Default constructor
     */
    BenchmarkFunction() { }

    //! Initializer constructor
    /*!
     * Initializer constructor
     * \param pointerToStateDerivativeFunction_ Pointer to benchmark function
     * \param initialInterval_ Integration interval start
     * \param initialState_ Integration initial state
     * \param endInterval_ Integration interval end
     * \param endState_ Expected end state
     */
    BenchmarkFunction( const StateDerivativeFunction& pointerToStateDerivativeFunction_,
                       const double initialInterval_, const Eigen::VectorXd& initialState_,
                       const double endInterval_, const Eigen::VectorXd& endState_ ) :
        pointerToStateDerivativeFunction( pointerToStateDerivativeFunction_ ),
        initialInterval( initialInterval_ ), initialState( initialState_ ),
        endInterval( endInterval_ ), endState( endState_ )
    { }
};
typedef struct BenchmarkFunction BenchmarkFunction;


//! State derivative function that always returns zero.
/*!
 * State derivative function that always returns a zero vector with length equal to the input.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State at which the state derivative needs to be evalated.
 * \return Zero vector with length equal to state.
 */
Eigen::VectorXd zeroStateDerivative( const double time, const Eigen::VectorXd& state )
{
    return Eigen::VectorXd::Zero( state.rows( ) );
}

//! State derivative function that always returns one.
/*!
 * State derivative function that always returns a one vector with length equal to the input.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State at which the state derivative needs to be evalated.
 * \return State derivative, length equal to state, all zeroes.
 */
Eigen::VectorXd constantStateDerivative( const double time, const Eigen::VectorXd& state )
{
    return Eigen::VectorXd::Constant( state.rows( ), 1.0 );
}

//! State derivative function that always returns the state.
/*!
 * State derivative function that always returns the state itself.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State at which the state derivative needs to be evalated.
 * \return State derivative, length equal to state, all entries equal to state.
 */
Eigen::VectorXd exponentialStateDerivative( const double time, const Eigen::VectorXd& state )
{
    return state;
}

//! Compute test state derivative.
/*!
 * Computes test state derivative. The state derivative function defined
 * corresponds to Example 3, pg. 278 in (Burden and Faires, 2001).
 * The initial-value problem is:
 * \f[
 *      y' = y - t^{ 2 } + 1
 * \f]
 * with \f$ 0 \leq t \leq 2 \f$ and \f$ y( 0 ) = 0.5 \f$.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State, length of which should be 1, at which the state derivative needs to
 * be evalated.
 * \return State derivative, length equal to stat values according to above expression.
 */
Eigen::VectorXd numericalRecipesStateDerivative( const double time, const Eigen::VectorXd& state )
{
    Eigen::VectorXd stateDerivative( 1 );
    stateDerivative( 0 ) = state( 0 ) - std::pow( time, 2.0 ) + 1.0;
    return stateDerivative;
}

//! Enum of available benchmark functions
enum BenchmarkFunctions
{
    Zero,
    Constant,
    Exponential,
    InverseExponential,
    NumericalRecipes
};

//! Get all defined benchmark functions
std::map<BenchmarkFunctions, BenchmarkFunction>& getBenchmarkFunctions()
{
    static std::map<BenchmarkFunctions, BenchmarkFunction> benchmarkFunctions;
    if ( benchmarkFunctions.empty() )
    {
        benchmarkFunctions[Zero] = BenchmarkFunction( &zeroStateDerivative,
                                                      0.0, Eigen::VectorXd::Constant( 10, 0.5 ),
                                                      2.0, Eigen::VectorXd::Constant( 10, 0.5 ) );
        benchmarkFunctions[Constant] = BenchmarkFunction( &constantStateDerivative,
                                                          0.0, Eigen::VectorXd::Constant( 3, 0.6 ),
                                                          3.0, Eigen::VectorXd::Constant( 3, 3.6 ) );

        benchmarkFunctions[Exponential] = BenchmarkFunction( &exponentialStateDerivative,
                                                             0.0, Eigen::VectorXd::Constant( 1, 0.7 ),
                                                             20.0, std::exp( 20.0 ) * Eigen::VectorXd::Constant( 1, 0.7 ) );

        benchmarkFunctions[InverseExponential] = BenchmarkFunction( &exponentialStateDerivative,
                                                             4.0, std::exp( 4.0 ) * Eigen::VectorXd::Constant( 1, 0.7 ),
                                                             0.0, Eigen::VectorXd::Constant( 1, 0.7 ) );

        benchmarkFunctions[NumericalRecipes] = BenchmarkFunction( &numericalRecipesStateDerivative,
                                                                  0.0, Eigen::VectorXd::Constant( 1, 0.5 ),
                                                                  2.0, Eigen::VectorXd::Constant( 1, 5.3053630 ) );
    }
    return benchmarkFunctions;
}

} // namespace numerical_integrators

} // namespace unit_tests

} // namespace tudat



#endif // BENCHMARKFUNCTIONS_H
