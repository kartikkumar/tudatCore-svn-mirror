/*    Copyright (c) 2010-2013 Delft University of Technology.
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
 *      120209    K. Kumar          File created.
 *
 *    References
 *
 *    Notes
 *
 */

#ifndef TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
#define TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H

//! The Tudat namespace.
/*!
 * The Tudat namespace contains all the functionality offered in Tudat Core. Additionally, the
 * Tudat namespace also contains all the functionality in the Tudat library.
 * \sa http://tudat.tudelft.nl/doxygen/Tudat/html/index.html.
 */
namespace tudat
{

//! The input/output namespace.
/*!
 * The input/output namespace contains the stream filters namespace and a function get the root-
 * directory of the Tudat Core library.
 */
namespace input_output
{

//! The stream filters namespace.
/*!
 * The stream filters namespace contains functions to remove comments, skip the first several
 * lines and search and replace text in a stream.
 */
namespace stream_filters
{

} // namespace stream_filters

} // namespace input_output

//! Orbital element conversions namespace.
/*!
 * Orbital element conversions namespace, containing classical Keplerian to Cartesian element
 * conversions, and other conversions between classical Keplerian elements, e.g., true anomaly
 * to/from eccentric anomaly.
 */
namespace orbital_element_conversions
{

} // namespace orbital_element_conversions

//! Coordinate conversions namespace.
/*!
 * The coordinate conversions namespace contains free functions to convert between standard
 * coordinate frames, e.g, spherical-to-Cartesian, cylindrical-to-Cartesian etc.
 */
namespace coordinate_conversions
{

} // namespace coordinate_conversions

//! Linear algebra namespace.
/*!
 * The linear algebra namespace contains functions to compute the angle and the cosine of
 * the angle between two vectors
 */
namespace linear_algebra
{

} // namespace linear algebra

//! Mathematical constants namespace.
/*!
 * The mathematical constants namespace includes selected constants commonly used in mathematical
 * operations (e, golden ratio, pi, NaN).
 */
namespace mathematical_constants
{

} // namespace mathematical constants

//! Numerical integrators namespace.
/*!
 * The numerical integrators namespace contains the base class for the numerical integrators,
 * a function to integrate to an independent variable value and a class that implements the RK4
 * integrator.
 */
namespace numerical_integrators
{

} // namespace numerical_integrators

//! Physical constants namespace.
/*!
 * The physical constants namespace includes selected constants commonly used in astrodynamics.
 */
namespace physical_constants
{

} // namespace physical_constants


//! Unit tests namespace.
/*!
 * The unit tests namespace includes all unit test and associated code.
 */
namespace unit_tests
{

} // namespace unit_tests

//! Unit conversions namespace.
/*!
 * The unit conversions namespace contains functions to convert angles (rad,deg,arcmin,arcsec),
 * distance (m,km,ft), time (s,min,hr,JD,JY,sid-day), temperature (K,R) and pressure (lbs/ft2,
 * N/m2).
 */
namespace unit_conversions
{

} // namespace unit_conversions

} // namespace tudat

#endif // TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
