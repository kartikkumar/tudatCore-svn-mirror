 #    Copyright (c) 2010-2011 Delft University of Technology.
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
 #      110820    S.M. Persson      File created.
 #      111025    K. Kumar          Adapted file to work with Revision 194.
 #      111026    K. Kumar          Adapted file so all headers show in project tree in Qt Creator.
 #
 #    References
 #
 #/

# Add source files.
set(MATHEMATICS_SOURCES
  "${SRCROOT}${MATHEMATICSDIR}/basicMathematicsFunctions.cpp"
  "${SRCROOT}${MATHEMATICSDIR}/coordinateConversions.cpp"
  "${SRCROOT}${MATHEMATICSDIR}/linearAlgebra.cpp"
)

# Add header files.
set(MATHEMATICS_HEADERS 
  "${SRCROOT}${MATHEMATICSDIR}/basicMathematicsFunctions.h"
  "${SRCROOT}${MATHEMATICSDIR}/coordinateConversions.h"
  "${SRCROOT}${MATHEMATICSDIR}/linearAlgebra.h"
  "${SRCROOT}${MATHEMATICSDIR}/mathematicalConstants.h"
)


# Add sub-directories.
add_subdirectory("${SRCROOT}${MATHEMATICSDIR}/NumericalIntegrators")

# Get target properties for static libraries.
get_target_property(NUMERICALINTEGRATORSSOURCES tudat_core_numerical_integrators SOURCES)


# Add static libraries.
add_library(tudat_core_mathematics STATIC ${MATHEMATICS_SOURCES} ${MATHEMATICS_HEADERS} ${NUMERICALINTEGRATORS_SOURCES} ${NUMERICALINTEGRATORS_HEADERS})
setup_tudat_library_target(tudat_core_mathematics "${SRCROOT}${MATHEMATICSDIR}")
setup_headers("${ASTRODYNAMICS_HEADERS}" "${MATHEMATICSDIR}")

# Add unit tests.
add_executable(test_CoordinateConversions "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestCoordinateConversions.cpp")
setup_custom_test_program(test_CoordinateConversions "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_CoordinateConversions tudat_core_mathematics tudat_core_astrodynamics ${Boost_LIBRARIES})

add_executable(test_LinearAlgebra "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestLinearAlgebra.cpp")
setup_custom_test_program(test_LinearAlgebra "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_LinearAlgebra tudat_core_mathematics tudat_core_astrodynamics ${Boost_LIBRARIES})

# Add unit tests.
add_executable(test_BasicMathematics "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestBasicMathematicsFunctions.cpp")
setup_custom_test_program(test_BasicMathematics "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_BasicMathematics tudat_core_mathematics tudat_core_astrodynamics ${Boost_LIBRARIES})

add_executable(test_MathematicalConstants "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestBasicMathematicsFunctions.cpp")
setup_custom_test_program(test_MathematicalConstants "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_MathematicalConstants tudat_core_mathematics ${Boost_LIBRARIES})
