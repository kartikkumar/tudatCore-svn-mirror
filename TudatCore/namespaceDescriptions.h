/*    Copyright (c) 2010-2013, Delft University of Technology
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
 *      120209    K. Kumar          File created.
 *      130204    K. Kumar          Updated license in file header.
 *      130326    K. Kumar          Updated namespace descriptions and file layout.
 *
 *    References
 *
 *    Notes
 *
 */

#ifndef TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
#define TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H

//! Tudat namespace.
/*!
 * The Tudat namespace contains all the functionality offered in Tudat Core. Additionally, the
 * Tudat namespace also contains all the functionality in the Tudat library.
 * \sa http://tudat.tudelft.nl/doxygen/Tudat/html/index.html.
 */
namespace tudat
{

    //! Basic astrodynamics namespace.
    /*! 
     * The basic astrodynamics namespace contains a collection of various basic astrodynamics 
     * functions, incuding physical constants, unit conversions, and orbital conversions.
     */
    namespace basic_astrodynamics   
    {

        //! Orbital element conversions namespace.
        /*!
         * Orbital element conversions namespace, containing classical Keplerian to Cartesian 
         * element conversions, and other conversions between classical Keplerian elements, e.g., 
         * true anomaly to/from eccentric anomaly.
         */
        namespace orbital_element_conversions { }

        //! Physical constants namespace.
        /*!
         * The physical constants namespace includes selected constants commonly used in 
         * astrodynamics.
         */
        namespace physical_constants { }

        //! Unit conversions namespace.
        /*!
         * The unit conversions namespace contains functions to convert angles 
         * (rad,deg,arcmin,arcsec), distance (m,km,ft), time (s,min,hr,JD,JY,sid-day), 
         * temperature (K,R) and pressure (lbs/ft2,N/m2).
         */
        namespace unit_conversions { }

    } // namespace basic_astrodynamics

    //! Input/output namespace.
    /*!
     * The input/output namespace contains the stream filters namespace and a function get the 
     * root-directory of the Tudat Core library.
     */
    namespace input_output
    {

        //! The stream filters namespace.
        /*!
         * The stream filters namespace contains functions to remove comments, skip the first 
         * several lines and search and replace text in a stream.
         */
        namespace stream_filters { }

    } // namespace input_output

     //! The basic mathematics namespace.
     /*! 
      * The basic mathematics namespace contains a collection of various basic mathematical 
      * functions, incuding mathematical constants, coordinate conversions, and linear 
      * algebra functions.
      */
    namespace basic_mathematics
    {

        //! Coordinate conversions namespace.
        /*!
         * The coordinate conversions namespace contains free functions to convert between standard
         * coordinate frames, e.g, spherical-to-Cartesian, cylindrical-to-Cartesian etc.
         */
        namespace coordinate_conversions { }

        //! Linear algebra namespace
        /*!
         * The linear algebra namespace contains functions to compute the angle and the cosine of
         * the angle between two vectors
         */
        namespace linear_algebra { }

        //! Mathematical constants namespace.
        /*!
         * The mathematical constants namespace includes selected constants commonly used in 
         * mathematical operations (e, golden ratio, pi, NaN).
         */
        namespace mathematical_constants { }

    } // namespace basic_mathematics

    //! Numerical integrators namespace.
    /*!
     * The numerical integrators namespace contains the base class for the numerical 
     * integrators, a function to integrate to an independent variable value and classes that 
     * implement the Euler and RK4 integrators.
     */
    namespace numerical_integrators { }

} // namespace tudat

#endif // TUDAT_CORE_NAMESPACE_DESCRIPTIONS_H
