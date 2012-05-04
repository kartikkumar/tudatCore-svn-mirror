 #    Copyright (c) 2012 Delft University of Technology.
 #
 #    This software is protected by national and international copyright.
 #    Any unauthorized use, reproduction or modification is unlawful and
 #    will be prosecuted. Commercial and non-private application of the
 #    software in any form is strictly prohibited unless otherwise granted
 #    by the authors.
 #
 #    The code is provided without any warranty; without even the implied
 #    warranty of merchantibility or fitness for a particular purpose.
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
