 #    Copyright (c) 2010-2012 Delft University of Technology.
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
 #      110820    S. Billemont      File created.
 #
 #    References
 #
 #

# Add source files.
set(BASICSDIR_SOURCES
  "${SRCROOT}${BASICSDIR}/dummySourceFile.cpp"
)

# Add header files.
set(BASICSDIR_HEADERS 
  "${SRCROOT}${BASICSDIR}/testMacros.h"
  "${SRCROOT}${BASICSDIR}/utilityMacros.h"
)

# Add static libraries.
add_library(tudat_core_basics STATIC ${BASICSDIR_SOURCES} ${BASICSDIR_HEADERS})
setup_tudat_library_target(tudat_core_basics "${SRCROOT}${BASICSDIR}")
setup_headers("${BASICSDIR_HEADERS}" "${BASICSDIR}")

# Add unit tests.
add_executable(test_TestMacros "${SRCROOT}${BASICSDIR}/UnitTests/unitTestTestMacros.cpp")
setup_custom_test_program(test_TestMacros "${SRCROOT}${BASICSDIR}")
target_link_libraries(test_TestMacros tudat_core_basics ${Boost_LIBRARIES})
