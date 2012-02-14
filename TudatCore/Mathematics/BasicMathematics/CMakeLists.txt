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
 #/

# Add source files.
set(BASICMATHEMATICS_SOURCES
  "${SRCROOT}${BASICMATHEMATICSDIR}/basicMathematicsFunctions.cpp"
  "${SRCROOT}${BASICMATHEMATICSDIR}/coordinateConversions.cpp"
  "${SRCROOT}${BASICMATHEMATICSDIR}/linearAlgebra.cpp"
)

# Add header files.
set(BASICMATHEMATICS_HEADERS
  "${SRCROOT}${BASICMATHEMATICSDIR}/basicMathematicsFunctions.h"
  "${SRCROOT}${BASICMATHEMATICSDIR}/coordinateConversions.h"
  "${SRCROOT}${BASICMATHEMATICSDIR}/linearAlgebra.h"
  "${SRCROOT}${BASICMATHEMATICSDIR}/mathematicalConstants.h"
)

# Add static libraries.
add_library(tudat_core_basic_mathematics STATIC ${BASICMATHEMATICS_SOURCES} ${BASICMATHEMATICS_HEADERS})
setup_tudat_library_target(tudat_core_basic_mathematics "${SRCROOT}${BASICMATHEMATICSDIR}")
setup_headers("${BASICMATHEMATICS_HEADERS}" "${BASICMATHEMATICSDIR}")

# Add unit tests.
add_executable(test_CoordinateConversions "${SRCROOT}${BASICMATHEMATICSDIR}/UnitTests/unitTestCoordinateConversions.cpp")
setup_custom_test_program(test_CoordinateConversions "${SRCROOT}${BASICMATHEMATICSDIR}")
target_link_libraries(test_CoordinateConversions tudat_core_basic_mathematics ${Boost_LIBRARIES})

add_executable(test_LinearAlgebra "${SRCROOT}${BASICMATHEMATICSDIR}/UnitTests/unitTestLinearAlgebra.cpp")
setup_custom_test_program(test_LinearAlgebra "${SRCROOT}${BASICMATHEMATICSDIR}")
target_link_libraries(test_LinearAlgebra tudat_core_basic_mathematics ${Boost_LIBRARIES})

add_executable(test_BasicMathematics "${SRCROOT}${BASICMATHEMATICSDIR}/UnitTests/unitTestBasicMathematicsFunctions.cpp")
setup_custom_test_program(test_BasicMathematics "${SRCROOT}${BASICMATHEMATICSDIR}")
target_link_libraries(test_BasicMathematics tudat_core_basic_mathematics ${Boost_LIBRARIES})

add_executable(test_MathematicalConstants "${SRCROOT}${BASICMATHEMATICSDIR}/UnitTests/unitTestBasicMathematicsFunctions.cpp")
setup_custom_test_program(test_MathematicalConstants "${SRCROOT}${BASICMATHEMATICSDIR}")
target_link_libraries(test_MathematicalConstants tudat_core_basic_mathematics ${Boost_LIBRARIES})

