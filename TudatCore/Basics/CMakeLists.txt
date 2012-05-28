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
 #      110820    S. Billemont      File created.
 #
 #    References
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

# Add unit tests.
add_executable(test_TestMacros "${SRCROOT}${BASICSDIR}/UnitTests/unitTestTestMacros.cpp")
setup_custom_test_program(test_TestMacros "${SRCROOT}${BASICSDIR}")
target_link_libraries(test_TestMacros tudat_core_basics ${Boost_LIBRARIES})
