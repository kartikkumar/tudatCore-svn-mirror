# \file CMakeLists.txt
 #    This is the CMake file for the BASICSDIR sub-directory.
 #
 #    Path              : /BASICSDIR/
 #    Version           : 1
 #    Check status      : Checked
 #
 #    Author            : S. Billemont
 #    Affiliation       : Delft University of Technology
 #    E-mail address    : simon@angelcorp.be
 #
 #    Date created      : 02 February, 2012
 #    Last modified     : 02 February, 2012
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
 #      110820    S. Billemont      File created.
 #/

# Add source files.
set(BASICSDIR_SOURCES
  "${SRCROOT}${BASICSDIR}/dummySourceFile.cpp"
)

# Add header files.
set(BASICSDIR_HEADERS 
  "${SRCROOT}${BASICSDIR}/testMacros.h"
)

# Add static libraries.
add_library(tudatCore_basics STATIC ${BASICSDIR_SOURCES} ${BASICSDIR_HEADERS})
setup_tudat_library_target(tudatCore_basics "${SRCROOT}${BASICSDIR}")
setup_headers("${BASICSDIR_HEADERS}" "${BASICSDIR}")

# Add unit tests.
add_executable(test_TestMacros "${SRCROOT}${BASICSDIR}/UnitTests/unitTest_testMacros.cpp")
setup_custom_test_program(test_TestMacros "${SRCROOT}${BASICSDIR}")
target_link_libraries(test_TestMacros tudatCore_basics ${Boost_LIBRARIES})


# End of file.
