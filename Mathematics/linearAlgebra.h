/*! \file linearAlgebra.h
 *    This file contains include statements for common Eigen components,
 *    typedef for vectors and a number of useful vector operation definitions.
 *
 *    Path              : /Mathematics/LinearAlgebra/
 *    Version           : 3
 *    Check status      : Checked
 *
 *    Author            : J. Melman
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : J.C.P.Melman@tudelft.nl
 *
 *    Checker           : D. Dirkx
 *    Affiliation       : Delft University of Technology
 *    E-mail address    : d.dirkx@tudelft.nl
 *
 *    Date created      : 7 August, 2009
 *    Last modified     : 27 January, 2012
 *
 *    References
 *
 *    Notes
 *
 *    Copyright (c) 2010-2011 Delft University of Technology.
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
 *      090807    J. Melman         First creation of code.
 *      100930    D. Dirkx          Modified to comply with Tudat standards.
 *      100930    J. Melman         Implemented namespace, minor comment changes.
 *      120127    D. Dirkx          Moved to Tudat core, added doxygen param and return.
 */

#ifndef TUDAT_LINEAR_ALGEBRA_H
#define TUDAT_LINEAR_ALGEBRA_H

// Notice that coefficient access methods in Eigen have assertions
// checking the ranges. So if you do a lot of coefficient access,
// these assertions can have an important cost. If you want to
// save cost, define EIGEN_NO_DEBUG, and it won't check assertions.
//#ifndef EIGEN_NO_DEBUG
//#define EIGEN_NO_DEBUG
//#endif

// Include statements.
#include <Eigen/Core>

namespace tudat
{
namespace mathematics
{
namespace linear_algebra
{

//! Determine the cosine of the angle between two vectors.
/*!
 * Function to compute the cosine of the angle between two vectors;
 * both vectors must have non-zero norm.
 * \param vector0 First vector.
 * \param vector1 Second vector.
 * \return Cosine of angle between vectors.
 */
double computeCosineOfAngleBetweenVectors( const Eigen::VectorXd& vector0,
                                           const Eigen::VectorXd& vector1 );

//! Determine the angle between two vectors.
/*!
 * Function to compute the angle between two vectors;
 * both vectors must have non-zero norm.
 * \param vector0 First vector.
 * \param vector1 Second vector.
 * \return Angle between vectors.
 */
double computeAngleBetweenVectors( const Eigen::VectorXd& vector0,
                                   const Eigen::VectorXd& vector1 );

} // namespace linear_algebra
} // namespace mathematics
} // namespace tudat

#endif // TUDAT_LINEAR_ALGEBRA_H
