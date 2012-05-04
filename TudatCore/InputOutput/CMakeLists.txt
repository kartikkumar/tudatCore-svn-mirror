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
 #      110820    S.M. Persson      File created.
 #      120127    K. Kumar          Adapted for Tudat Core.
 #      120127    K. Kumar          Added stream filter code and unit test.
 #
 #    References
 #

# Add source files.
set(INPUTOUTPUT_SOURCES
  "${SRCROOT}${INPUTOUTPUTDIR}/streamFilters.cpp"
)

# Add header files.
set(INPUTOUTPUT_HEADERS 
  "${SRCROOT}${INPUTOUTPUTDIR}/basicInputOutput.h"
  "${SRCROOT}${INPUTOUTPUTDIR}/streamFilters.h"
)

# Add static libraries.
add_library(tudat_core_input_output STATIC ${INPUTOUTPUT_SOURCES} ${INPUTOUTPUT_HEADERS})
setup_tudat_library_target(tudat_core_input_output "${SRCROOT}${INPUTOUTPUTDIR}")

# Add unit tests.
add_executable(test_BasicInputOutput "${SRCROOT}${INPUTOUTPUTDIR}/UnitTests/unitTestBasicInputOutput.cpp")
setup_custom_test_program(test_BasicInputOutput "${SRCROOT}${INPUTOUTPUTDIR}")
target_link_libraries(test_BasicInputOutput tudat_core_input_output ${Boost_LIBRARIES})

add_executable(test_StreamFilters "${SRCROOT}${INPUTOUTPUTDIR}/UnitTests/unitTestStreamFilters.cpp")
setup_custom_test_program(test_StreamFilters "${SRCROOT}${INPUTOUTPUTDIR}")
target_link_libraries(test_StreamFilters tudat_core_input_output ${Boost_LIBRARIES})
