 #    Copyright (c) 2010-2012, Delft University of Technology
 #    All rights reserved.
 #
 #    Redistribution and use in source and binary forms, with or without modification, are
 #    permitted provided that the following conditions are met:
 #      - Redistributions of source code must retain the above copyright notice, this list of
 #        conditions and the following disclaimer.
 #      - Redistributions in binary form must reproduce the above copyright notice, this list of
 #        conditions and the following disclaimer in the documentation and/or other materials
 #        provided with the distribution.
 #      - Neither the name of the Delft University of Technology nor the names of its contributors
 #        may be used to endorse or promote products derived from this software without specific
 #        prior written permission.
 #
 #    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 #    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 #    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 #    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 #    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 #    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 #    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 #    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 #    OF THE POSSIBILITY OF SUCH DAMAGE.
 #
 #    Changelog
 #      YYMMDD    Author            Comment
 #      120127    B. Tong Minh      File created.
 #
 #    References
 #

# Add source files.
set(NUMERICALINTEGRATORS_SOURCES
  "${SRCROOT}${NUMERICALINTEGRATORSDIR}/numericalIntegrator.cpp"
)

# Add header files.
set(NUMERICALINTEGRATORS_HEADERS 
  "${SRCROOT}${NUMERICALINTEGRATORSDIR}/numericalIntegrator.h"
  "${SRCROOT}${NUMERICALINTEGRATORSDIR}/rungeKutta4Integrator.h"
  "${SRCROOT}${NUMERICALINTEGRATORSDIR}/UnitTests/benchmarkFunctions.h"
)

# Add static libraries.
add_library(tudat_core_numerical_integrators STATIC ${NUMERICALINTEGRATORS_SOURCES} ${NUMERICALINTEGRATORS_HEADERS})
setup_tudat_library_target(tudat_core_numerical_integrators "${SRCROOT}${NUMERICALINTEGRATORSDIR}")

# Add unit tests.
add_executable(test_NumericalIntegrator "${SRCROOT}${NUMERICALINTEGRATORSDIR}/UnitTests/unitTestNumericalIntegrator.cpp")
setup_custom_test_program(test_NumericalIntegrator "${SRCROOT}${NUMERICALINTEGRATORSDIR}")
target_link_libraries(test_NumericalIntegrator tudat_core_numerical_integrators ${Boost_LIBRARIES})

add_executable(test_RungeKutta4Integrator "${SRCROOT}${NUMERICALINTEGRATORSDIR}/UnitTests/unitTestRungeKutta4Integrator.cpp")
setup_custom_test_program(test_RungeKutta4Integrator "${SRCROOT}${NUMERICALINTEGRATORSDIR}")
target_link_libraries(test_RungeKutta4Integrator tudat_core_numerical_integrators ${Boost_LIBRARIES})
