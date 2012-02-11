# \file TudatCoreEnvironment.cmake
 #    Environment file for distribution. This file defines the required 
 #    variables to find Tudat Core, Eigen and Boost.
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

if ("${PROJECT_NAME}" STREQUAL "TudatCore")
    message(WARNING "TudatCoreEnvironment.cmake is run while building the Tudat Core")
else()
    set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/eigen3")
    set(BOOST_ROOT "${CMAKE_CURRENT_LIST_DIR}/boost")
    #set(Boost_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/boost")
    #set(Boost_LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/boost/stage/lib")
    set(TUDAT_CORE_BASE_PATH "${CMAKE_CURRENT_LIST_DIR}/TudatCore")
endif()
