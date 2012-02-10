/*! Copyright (c) 2010-2011 Delft University of Technology.
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
 */

#ifndef TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
#define TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H

namespace tudat
{

//! The input/output namespace.
/*!
 * The input/output namespace.
 */
namespace input_output
{

//! The stream filters namespace.
/*!
 * The stream filters namespace.
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

//! Mathematics namespace.
/*!
 * The mathematics namespace, containing free functions and classes.
 */
namespace mathematics
{

//! Coordinate conversions namespace.
/*!
 * The coordinate conversions namespace contains free functions to convert between standard
 * coordinate frames, e.g, spherical-to-Cartesian, cylindrical-to-Cartesian etc.
 */
namespace coordinate_conversions
{

} // namespace coordinate_conversions

//! Numerical integrators namespace.
/*!
 * The numerical integrators namespace included in Tudat.
 */
namespace numerical_integrators
{

} // namespace numerical_integrators

} // namespace mathematics

//! Physical constants namespace.
/*!
 * The physical constants namespace includes selected constants commonly used in astrodynamics.
 */
namespace physical_constants
{

} // namespace physical_constants

namespace unit_tests
{

} // namespace unit_tests
} // namespace tudat

#endif // TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
