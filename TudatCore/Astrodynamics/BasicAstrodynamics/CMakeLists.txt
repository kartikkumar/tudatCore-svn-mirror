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
 #      120127    K. Kumar          Added Boost libraries to unit tests.
 #	120204    K. Kumar	     Adapted for new BasicAstrodynamics sub-directory.
 #
 #    References
 #
 #/

# Add source files.
set(BASICASTRODYNAMICS_SOURCES
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/astrodynamicsFunctions.cpp"
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/orbitalElementConversions.cpp"
)

# Add header files.
set(BASICASTRODYNAMICS_HEADERS
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/astrodynamicsFunctions.h"
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/orbitalElementConversions.h"
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/physicalConstants.h"
  "${SRCROOT}${BASICASTRODYNAMICSDIR}/unitConversions.h"
)

# Add static libraries.
add_library(tudat_core_basic_astrodynamics STATIC ${BASICASTRODYNAMICS_SOURCES} ${BASICASTRODYNAMICS_HEADERS})
setup_tudat_library_target(tudat_core_basic_astrodynamics "${SRCROOT}${BASICASTRODYNAMICSDIR}")
setup_headers("${BASICASTRODYNAMICS_HEADERS}" "${BASICASTRODYNAMICSDIR}")

# Add unit tests.
add_executable(test_PhysicalConstants "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestPhysicalConstants.cpp")
setup_custom_test_program(test_PhysicalConstants "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_PhysicalConstants tudat_core_basic_astrodynamics tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_AstrodynamicsFunctions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestAstrodynamicsFunctions.cpp")
setup_custom_test_program(test_AstrodynamicsFunctions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_AstrodynamicsFunctions tudat_core_basic_astrodynamics  tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_OrbitalElementConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestOrbitalElementConversions.cpp")
setup_custom_test_program(test_OrbitalElementConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_OrbitalElementConversions tudat_core_basic_astrodynamics  tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_UnitConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestUnitConversions.cpp")
setup_custom_test_program(test_UnitConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_UnitConversions tudat_core_basic_astrodynamics  tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})
