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
 #      120127    B. Tong Minh      File created.
 #
 #    References
 #

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
