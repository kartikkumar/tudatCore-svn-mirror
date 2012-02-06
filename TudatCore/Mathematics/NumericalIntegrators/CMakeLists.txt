# \file CMakeLists.txt
 #    This is the CMake file for the NumericalIntegrators sub-directory.
 #
 #    Path              : /Mathematics/NumericalIntegrators/
 #    Version           : 1
 #    Check status      : Broken
 #    Date created      : 27 January, 2011
 #    Last modified     : 27 January, 2011
 #
 #    References
 #
 #    Notes
 #
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
 #/

# Add source files.
set(NUMERICALINTEGRATORS_SOURCES
  "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/numericalIntegrator.cpp"
)

# Add header files.
set(NUMERICALINTEGRATORS_HEADERS 
  "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/numericalIntegrator.h"
  "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/rungeKutta4Integrator.h"
  "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/UnitTests/benchmarkFunctions.h"
)

# Add static libraries.
add_library(tudat_core_numerical_integrators STATIC ${NUMERICALINTEGRATORS_SOURCES} ${NUMERICALINTEGRATORS_HEADERS})
setup_tudat_library_target(tudat_core_numerical_integrators "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators")
setup_headers("${NUMERICALINTEGRATORS_HEADERS}" "${MATHEMATICSDIR}/NumericalIntegrators")

# Add unit tests.
add_executable(test_NumericalIntegrator "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/UnitTests/unitTestNumericalIntegrator.cpp")
setup_custom_test_program(test_NumericalIntegrator "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators")
target_link_libraries(test_NumericalIntegrator tudat_core_numerical_integrators)

add_executable(test_RungeKutta4Integrator "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators/UnitTests/unitTestRungeKutta4Integrator.cpp")
setup_custom_test_program(test_RungeKutta4Integrator "${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators")
target_link_libraries(test_RungeKutta4Integrator tudat_core_numerical_integrators)

# End of file.
