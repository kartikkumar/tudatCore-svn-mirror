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
 #    Last modified     : 26 October, 2011
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
 #/

# Add source files.
set(MATHEMATICS_SOURCES
  "${SRCROOT}${MATHEMATICSDIR}/linearAlgebra.cpp"
  "${SRCROOT}${MATHEMATICSDIR}/basicMathematicsFunctions.cpp"
  "${SRCROOT}${MATHEMATICSDIR}/coordinateConversions.cpp"

)

# Add header files.
set(MATHEMATICS_HEADERS 
  "${SRCROOT}${MATHEMATICSDIR}/linearAlgebra.h"
  "${SRCROOT}${MATHEMATICSDIR}/basicMathematicsFunctions.h"
  "${SRCROOT}${MATHEMATICSDIR}/coordinateConversions.h"
)

# Add static libraries.
add_library(tudat_core_mathematics STATIC ${MATHEMATICS_SOURCES} ${MATHEMATICS_HEADERS})
setup_tudat_library_target(tudat_core_mathematics "${SRCROOT}${MATHEMATICSDIR}")
setup_headers("${ASTRODYNAMICS_HEADERS}" "${MATHEMATICSDIR}")

# Add unit tests.
add_executable(test_CoordinateConversions "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestCoordinateConversions.cpp")
setup_custom_test_program(test_CoordinateConversions "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_CoordinateConversions tudat_core_mathematics tudat_core_astrodynamics ${Boost_LIBRARIES})

add_executable(test_LinearAlgebra "${SRCROOT}${MATHEMATICSDIR}/UnitTests/unitTestLinearAlgebra.cpp")
setup_custom_test_program(test_LinearAlgebra "${SRCROOT}${MATHEMATICSDIR}")
target_link_libraries(test_LinearAlgebra tudat_core_mathematics tudat_core_astrodynamics ${Boost_LIBRARIES})

# End of file.
