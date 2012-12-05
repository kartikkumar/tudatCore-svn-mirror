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
 *      120203    B. Tong Minh      File created.
 *      120207    K. Kumar          Minor comment corrections; changed "NumericalRecipes" to
 *                                  "BurdenAndFaires", "InverseExponential" to
 *                                  "BackwardsExponential".
 *      120213    K. Kumar          Updated variable-naming.
 *
 *    References
 *      Burden, R.L., Faires, J.D. Numerical Analysis, 7th Edition, Books/Cole, 2001.
 *
 *    Notes
 *
 */

#ifndef TUDAT_CORE_BENCHMARK_FUNCTIONS_H
#define TUDAT_CORE_BENCHMARK_FUNCTIONS_H

#include <map>

#include <boost/function.hpp>

#include <Eigen/Core>

namespace tudat
{
namespace unit_tests
{

//! Struct containing information about a benchmark function.
/*!
 * Struct containing information about a benchmark function.
 * \sa getBenchmarkFunctions().
 */
struct BenchmarkFunction
{
public:

    //! Typedef to a benchmark state derivative function.
    typedef boost::function< Eigen::VectorXd( const double, const Eigen::VectorXd& ) >
    StateDerivativeFunction;

    //! Default constructor.
    /*!
     * Default constructor.
     */
    BenchmarkFunction( ) { }

    //! Initializer constructor.
    /*!
     * Initializer constructor.
     * \param pointerToStateDerivativeFunction Pointer to benchmark function.
     * \param intervalStart Integration interval start.
     * \param initialState Integration initial state.
     * \param intervalEnd Integration interval end.
     * \param finalState Expected final state.
     */
    BenchmarkFunction( const StateDerivativeFunction& pointerToStateDerivativeFunction,
                       const double intervalStart, const Eigen::VectorXd& initialState,
                       const double intervalEnd, const Eigen::VectorXd& finalState ) :
        pointerToStateDerivativeFunction_( pointerToStateDerivativeFunction ),
        intervalStart_( intervalStart ), initialState_( initialState ),
        intervalEnd_( intervalEnd ), finalState_( finalState ) { }

    //! Pointer to a benchmark state derivative function.
    StateDerivativeFunction pointerToStateDerivativeFunction_;

    //! Integration interval start.
    double intervalStart_;

    //! Integration initial state.
    Eigen::VectorXd initialState_;

    //! Integration interval end.
    double intervalEnd_;

    //! Expected end state.
    Eigen::VectorXd finalState_;

protected:

private:

};

//! Typedef to a benchmark function.
typedef struct BenchmarkFunction BenchmarkFunction;

//! State derivative function that always returns zero.
/*!
 * State derivative function that always returns a zero vector with length equal to the input.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State at which the state derivative needs to be evalated.
 * \return Zero vector with length equal to state.
 */
static Eigen::VectorXd computeZeroStateDerivative( const double time,
                                                   const Eigen::VectorXd& state )
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
static Eigen::VectorXd computeConstantStateDerivative( const double time,
                                                       const Eigen::VectorXd& state )
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
static Eigen::VectorXd computeExponentialStateDerivative( const double time,
                                                          const Eigen::VectorXd& state )
{
    return state;
}

//! Compute test state derivative for Burden and Faires example.
/*!
 * Computes test state derivative. The state derivative function defined corresponds to Example 3,
 * pg. 278 in (Burden and Faires, 2001).
 * The initial-value problem is:
 * \f[
 *      y' = y - t^{ 2 } + 1
 * \f]
 * with \f$ 0 \leq t \leq 2 \f$ and \f$ y( 0 ) = 0.5 \f$.
 * \param time Time at which the state derivative needs to be evaluated.
 * \param state State, length of which should be 1, at which the state derivative needs to
 *          be evaluated.
 * \return State derivative, length equal to stat values according to above expression.
 */
static Eigen::VectorXd computeBurdenAndFairesStateDerivative( const double time,
                                                              const Eigen::VectorXd& state )
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
    BackwardsExponential,
    BurdenAndFaires
};

//! Get all defined benchmark functions.
static std::map< BenchmarkFunctions, BenchmarkFunction >& getBenchmarkFunctions( )
{
    static std::map< BenchmarkFunctions, BenchmarkFunction > benchmarkFunctions;

    if ( benchmarkFunctions.empty( ) )
    {
        benchmarkFunctions[ Zero ] = BenchmarkFunction(
                    &computeZeroStateDerivative, 0.0, Eigen::VectorXd::Constant( 10, 0.5 ),
                    2.0, Eigen::VectorXd::Constant( 10, 0.5 ) );

        benchmarkFunctions[ Constant ] = BenchmarkFunction(
                    &computeConstantStateDerivative, 0.0, Eigen::VectorXd::Constant( 3, 0.6 ),
                    3.0, Eigen::VectorXd::Constant( 3, 3.6 ) );

        benchmarkFunctions[Exponential] = BenchmarkFunction(
                    &computeExponentialStateDerivative, 0.0, Eigen::VectorXd::Constant( 1, 0.7 ),
                    20.0, std::exp( 20.0 ) * Eigen::VectorXd::Constant( 1, 0.7 ) );

        benchmarkFunctions[ BackwardsExponential ] = BenchmarkFunction(
                    &computeExponentialStateDerivative, 4.0,
                    std::exp( 4.0 ) * Eigen::VectorXd::Constant( 1, 0.7 ),
                    0.0, Eigen::VectorXd::Constant( 1, 0.7 ) );

        benchmarkFunctions[ BurdenAndFaires ] = BenchmarkFunction(
                    &computeBurdenAndFairesStateDerivative,
                    0.0, Eigen::VectorXd::Constant( 1, 0.5 ),
                    2.0, Eigen::VectorXd::Constant( 1, 5.3053630 ) );
    }

    return benchmarkFunctions;
}

} // namespace unit_tests
} // namespace tudat

#endif // TUDAT_CORE_BENCHMARK_FUNCTIONS_H
