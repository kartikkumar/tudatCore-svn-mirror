 #    Copyright (c) 2010-2013, Delft University of Technology
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
 #      120210    B. Tong Minh      File created.
 #      120503    B. Tong Minh      Improved Boost detection routines.
 #      130116    K. Kumar          Removed bundling of Tudat Core static libraries.
 #
 #    References
 #
 #    Notes
 #      This file defines the install target to create a distribution of Tudat Core, Eigen and
 #      Boost.
 #

if(NOT TUDAT_CORE_DISTRIBUTION_PATH)
    set(TUDAT_CORE_DISTRIBUTION_PATH "${CODEROOT}/dist/tudatCore")
endif(NOT TUDAT_CORE_DISTRIBUTION_PATH)
if(NOT TUDAT_CORE_BOOST_SHARED_DISTRIBUTION_PATH)
    set(TUDAT_CORE_BOOST_SHARED_DISTRIBUTION_PATH "${CODEROOT}/dist/boost-shared")
endif(NOT TUDAT_CORE_BOOST_SHARED_DISTRIBUTION_PATH)

# Slash normalization for Windows.
string(REPLACE "\\" "/" EIGEN3_INCLUDE_DIR_NORMALIZED "${EIGEN3_INCLUDE_DIR}")
string(REPLACE "\\" "/" Boost_INCLUDE_DIRS_NORMALIZED "${Boost_INCLUDE_DIRS}")

# Detect if the correct build version of Boost is used.
string(REGEX MATCH "libboost[^-]*(([a-zA-Z0-9_.]|[-])*)" BOOST_ABI_STRING "${Boost_LIBRARIES}")
set(BOOST_ABI_STRING ${CMAKE_MATCH_1})

# Check if Boost was built with multithreading support.
string(REGEX MATCH "-mt" BOOST_WITH_MT "${BOOST_ABI_STRING}")

# Try extract the version.
string(REGEX MATCH "([0-9_]*)[.]" BOOST_VERSION "${BOOST_ABI_STRING}")
set(BOOST_VERSION ${CMAKE_MATCH_1})
if(NOT BOOST_VERSION)
    # Library name did not contain a version string, so the part before the extension is the ABI tag.
    string(REGEX MATCH "([a-z]*)[.]" BOOST_ABI_TAG "${BOOST_ABI_STRING}")
    set(BOOST_ABI_TAG ${CMAKE_MATCH_1})
else()
    # Library name did contain version string, so the part before the version string is the ABI tag.
    string(REGEX MATCH "([a-z]*)-[0-9_]*[.]" BOOST_ABI_TAG "${BOOST_ABI_STRING}")
    set(BOOST_ABI_TAG ${CMAKE_MATCH_1})
endif()

# Detect the toolset.
string(REGEX MATCH "-([^.-]*)" BOOST_TOOLSET "${BOOST_ABI_STRING}")
set(BOOST_TOOLSET ${CMAKE_MATCH_1})

if(BOOST_TOOLSET)
    if("${BOOST_TOOLSET}" STREQUAL "mt" OR "${BOOST_TOOLSET}" STREQUAL "${BOOST_ABI_TAG}")
        set(BOOST_TOOLSET "")
    endif()
endif()

set(BOOST_SHARED_ABI_STRING "mt")
if(BOOST_TOOLSET)
    set(BOOST_SHARED_ABI_STRING "${BOOST_TOOLSET}-${BOOST_SHARED_ABI_STRING}")
endif()
if(BOOST_VERSION)
    set(BOOST_SHARED_ABI_STRING "${BOOST_SHARED_ABI_STRING}-${BOOST_VERSION}")
endif()

if(NOT BOOST_WITH_MT)
    install(CODE "message(FATAL_ERROR \"Making single-threaded distribution (ABI string: ${BOOST_ABI_STRING})\")")
endif()

if((APPLE AND "${BOOST_ABI_TAG}" STREQUAL "mt" ) OR (NOT APPLE AND "${BOOST_ABI_TAG}" STREQUAL "s"))
else()
    string(REGEX MATCH "s" BOOST_ABI_STATIC "${BOOST_ABI_TAG}")
    string(REGEX MATCH "g" BOOST_ABI_DEBUG_STANDARD_LIBRARY "${BOOST_ABI_TAG}")
    string(REGEX MATCH "y" BOOST_ABI_DEBUG_PYTHON "${BOOST_ABI_TAG}")
    string(REGEX MATCH "d" BOOST_ABI_DEBUG "${BOOST_ABI_TAG}")
    string(REGEX MATCH "p" BOOST_ABI_STLPORT "${BOOST_ABI_TAG}")
    string(REGEX MATCH "n" BOOST_ABI_STLPORT_NATIVE_IOSTREAMS "${BOOST_ABI_TAG}")

    set(BOOST_ABI_ERROR "Invalid ABI tag \"${BOOST_ABI_TAG}\".")
    if(NOT BOOST_ABI_STATIC)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost not linked statically against runtime.")
    endif()
    if(BOOST_ABI_DEBUG_STANDARD_LIBRARY)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost linked against debug static library.")
    endif()
    if(BOOST_ABI_DEBUG_PYTHON)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost linked against debug Python.")
    endif()
    if(BOOST_ABI_DEBUG)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost built in debug mode.")
    endif()
    if(BOOST_ABI_STLPORT)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost linked against STLPort standard library.")
    endif()
    if(BOOST_ABI_STLPORT_NATIVE_IOSTREAMS)
        set(BOOST_ABI_ERROR "${BOOST_ABI_ERROR} Boost linked against STLPort standard library with native iostreams.")
    endif()

    install(CODE "message(FATAL_ERROR \"${BOOST_ABI_ERROR}\")")
endif()

# Install the Tudat Core project tree.
install(DIRECTORY "${SRCROOT}/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/TudatCore"
        PATTERN ".DS_STORE" EXCLUDE
        PATTERN "CMakeLists.txt.user" EXCLUDE
)

install(FILES "${CODEROOT}/LICENSE" "${CODEROOT}/NOTICE" "${CODEROOT}/README" "${CODEROOT}/UserSettings.txt.example"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}"
)

# Install Eigen.
install(DIRECTORY "${EIGEN3_INCLUDE_DIR_NORMALIZED}/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/eigen3"
)
# Install Boost.
install(DIRECTORY "${Boost_INCLUDE_DIRS_NORMALIZED}/boost/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/boost/boost"
)

# Match Boost static libraries.
FILE(GLOB boost_static "${Boost_LIBRARY_DIRS}/libboost_*${BOOST_ABI_STRING}"
)

# Install Boost static libraries.
install(FILES ${boost_static} DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/boost/stage/lib"
)

# Match Boost shared libraries.
FILE(GLOB boost_shared "${Boost_LIBRARY_DIRS}/libboost_*-${BOOST_SHARED_ABI_STRING}.dll"
                "${Boost_LIBRARY_DIRS}/libboost_*-${BOOST_SHARED_ABI_STRING}.dylib"
                "${Boost_LIBRARY_DIRS}/libboost_*-${BOOST_SHARED_ABI_STRING}.so"
                "${Boost_LIBRARY_DIRS}/libboost_*-${BOOST_SHARED_ABI_STRING}.so.*"
)

# Install Boost shared libraries
install(FILES ${boost_shared} DESTINATION  "${TUDAT_CORE_BOOST_SHARED_DISTRIBUTION_PATH}"
)

# Install the environment file.
install(FILES "${SRCROOT}/External/CMake/TudatCoreEnvironment.cmake"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}"
)

# Generate the versions file.
install(CODE "file(WRITE \"${TUDAT_CORE_DISTRIBUTION_PATH}/Versions.txt\"
    \"Packaged library versions:
* Boost version: ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}
* Eigen version: ${EIGEN3_VERSION}\")")
