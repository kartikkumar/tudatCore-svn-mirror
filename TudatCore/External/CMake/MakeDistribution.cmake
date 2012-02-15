# \file MakeDistribution.cmake
 #    This file defines the install target to create a distribution of Tudat Core, Eigen and Boost
 #
 #    Copyright (c) 2012 Delft University of Technology.
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
 #      120210    B. Tong Minh      File created
 #/

if(NOT TUDAT_CORE_DISTRIBUTION_PATH)
    set(TUDAT_CORE_DISTRIBUTION_PATH "${CODEROOT}/dist/core")
endif(NOT TUDAT_CORE_DISTRIBUTION_PATH)

# Slash normalization for Windows
string(REPLACE "\\" "/" EIGEN3_INCLUDE_DIR_NORMALIZED "${EIGEN3_INCLUDE_DIR}")
string(REPLACE "\\" "/" Boost_INCLUDE_DIRS_NORMALIZED "${Boost_INCLUDE_DIRS}")

# Install the Tudat Core static library
install(TARGETS tudat_core
    ARCHIVE DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/lib"
)
# Install the Tudat Core header files
install(DIRECTORY "${SRCROOT}/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/TudatCore"
        FILES_MATCHING PATTERN "*.h"
)
# Install Eigen
install(DIRECTORY "${EIGEN3_INCLUDE_DIR_NORMALIZED}/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/eigen3"
)
# Install Boost
install(DIRECTORY "${Boost_INCLUDE_DIRS_NORMALIZED}/boost/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/boost/boost"
)
install(DIRECTORY "${Boost_LIBRARY_DIRS}/"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}/boost/stage/lib"
        FILES_MATCHING
            PATTERN "libboost_*.*"
            PATTERN "*.dylib" EXCLUDE
            PATTERN "*.dll" EXCLUDE
            PATTERN "*.so" EXCLUDE
            PATTERN "*.so.*" EXCLUDE
)
# Install the environment file
install(FILES "${SRCROOT}/External/CMake/TudatCoreEnvironment.cmake"
        DESTINATION "${TUDAT_CORE_DISTRIBUTION_PATH}"
)
