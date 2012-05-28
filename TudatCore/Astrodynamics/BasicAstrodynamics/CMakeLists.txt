 #    Copyright (c) 2010-2012, Delft University of Technology
 #    All rights reserved.
 #
 #    Redistribution and use in source and binary forms, with or without modification, are
 #    permitted provided that the following conditions are met:
 #      - Redistributions of source code must retain the above copyright notice, this list of
 #        conditions and the following disclaimer.
 #      - Redistributions in binary form must reproduce the above copyright notice, this list of
 #        conditions and the following disclaimer in the documentation and/or other materials
 #        provided with the distribution.
 #      - Neither the name of the Delft University of Technology nor the names of its contributors
 #        may be used to endorse or promote products derived from this software without specific
 #        prior written permission.
 #
 #    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 #    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 #    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 #    COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 #    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 #    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 #    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 #    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 #    OF THE POSSIBILITY OF SUCH DAMAGE.
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

# Add unit tests.
add_executable(test_PhysicalConstants "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestPhysicalConstants.cpp")
setup_custom_test_program(test_PhysicalConstants "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_PhysicalConstants tudat_core_basic_astrodynamics ${Boost_LIBRARIES})

add_executable(test_AstrodynamicsFunctions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestAstrodynamicsFunctions.cpp")
setup_custom_test_program(test_AstrodynamicsFunctions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_AstrodynamicsFunctions tudat_core_basic_astrodynamics ${Boost_LIBRARIES})

add_executable(test_OrbitalElementConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestOrbitalElementConversions.cpp")
setup_custom_test_program(test_OrbitalElementConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_OrbitalElementConversions tudat_core_basic_astrodynamics tudat_core_basic_mathematics ${Boost_LIBRARIES})

add_executable(test_UnitConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}/UnitTests/unitTestUnitConversions.cpp")
setup_custom_test_program(test_UnitConversions "${SRCROOT}${BASICASTRODYNAMICSDIR}")
target_link_libraries(test_UnitConversions tudat_core_basic_astrodynamics ${Boost_LIBRARIES})
