# \file CMakeLists.txt
 #    This is the CMake file for the Basics sub-directory.
 #
 #    Path              : /Basics/
 #    Version           : 3
 #    Check status      : Checked
 #
 #    Author            : S.M. Persson
 #    Affiliation       : McGill University, Department of Mechanical Engineering
 #    E-mail address    : mikael.s.persson@gmail.com
 #
 #    Author            : K. Kumar
 #    Affiliation       : Delft University of Technology
 #    E-mail address    : K.Kumar@tudelft.nl
 #
 #    Author            : S.M. Persson
 #    Affiliation       : McGill University, Department of Mechanical Engineering
 #    E-mail address    : mikael.s.persson@gmail.com
 #
 #    Date created      : 20 August, 2011
 #    Last modified     : 27 January, 2012
 #
 #    References
 #
 #    Notes
 #
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
 #/

# Add source files.
set(ASTRODYNAMICS_SOURCES
  "${SRCROOT}${ASTRODYNAMICSDIR}/astrodynamicsFunctions.cpp"
  "${SRCROOT}${ASTRODYNAMICSDIR}/orbitalElementConversions.cpp"
)

# Add header files.
set(ASTRODYNAMICS_HEADERS
  "${SRCROOT}${ASTRODYNAMICSDIR}/astrodynamicsFunctions.h"
  "${SRCROOT}${ASTRODYNAMICSDIR}/orbitalElementConversions.h"
  "${SRCROOT}${ASTRODYNAMICSDIR}/physicalConstants.h"
  "${SRCROOT}${ASTRODYNAMICSDIR}/unitConversions.h"
)

# Add static libraries.
add_library(tudat_core_astrodynamics STATIC ${ASTRODYNAMICS_SOURCES} ${ASTRODYNAMICS_HEADERS})
setup_tudat_library_target(tudat_core_astrodynamics "${SRCROOT}${ASTRODYNAMICSDIR}")
setup_headers("${ASTRODYNAMICS_HEADERS}" "${ASTRODYNAMICSDIR}")

# Add unit tests.
add_executable(test_PhysicalConstants "${SRCROOT}${ASTRODYNAMICSDIR}/UnitTests/unitTestPhysicalConstants.cpp")
setup_custom_test_program(test_PhysicalConstants "${SRCROOT}${ASTRODYNAMICSDIR}")
target_link_libraries(test_PhysicalConstants tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_AstrodynamicsFunctions "${SRCROOT}${ASTRODYNAMICSDIR}/UnitTests/unitTestAstrodynamicsFunctions.cpp")
setup_custom_test_program(test_AstrodynamicsFunctions "${SRCROOT}${ASTRODYNAMICSDIR}")
target_link_libraries(test_AstrodynamicsFunctions tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_OrbitalElementConversions "${SRCROOT}${ASTRODYNAMICSDIR}/UnitTests/unitTestOrbitalElementConversions.cpp")
setup_custom_test_program(test_OrbitalElementConversions "${SRCROOT}${ASTRODYNAMICSDIR}")
target_link_libraries(test_OrbitalElementConversions tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

add_executable(test_UnitConversions "${SRCROOT}${ASTRODYNAMICSDIR}/UnitTests/unitTestUnitConversions.cpp")
setup_custom_test_program(test_UnitConversions "${SRCROOT}${ASTRODYNAMICSDIR}")
target_link_libraries(test_UnitConversions tudat_core_astrodynamics tudat_core_mathematics ${Boost_LIBRARIES})

# End of file.
