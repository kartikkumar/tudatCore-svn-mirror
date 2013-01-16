 #    Copyright (c) 2010-2013 Delft University of Technology.
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
 #      120210    B. Tong Minh      File created.
 #      170210    S. Billemont      Changed so variables are only loaded if they have not
 #                                  yet been set before loading this script.
 #
 #    References
 #
 #    Notes
 #
 #

if ("${PROJECT_NAME}" STREQUAL "TudatCore")
    message(WARNING "TudatCoreEnvironment.cmake is run while building the Tudat Core")
else()
	# Only load EIGEN3_INCLUDE_DIR if that variable does not exist in cmake
	if (NOT EIGEN3_INCLUDE_DIR)
    	    set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/eigen3")
	endif()
	# Only load BOOST_ROOT if that variable does not exist in cmake and the user environment variables.
	if (NOT BOOST_ROOT AND NOT DEFINED ENV{BOOST_ROOT} )
    	    set(BOOST_ROOT "${CMAKE_CURRENT_LIST_DIR}/boost")
	endif()
	# Only load BOOST_INCLUDEDIR if that variable does not exist in cmake and the user environment variables.
	if (NOT BOOST_INCLUDEDIR AND NOT DEFINED ENV{BOOST_INCLUDEDIR} )
    	    #set(BOOST_INCLUDEDIR "${CMAKE_CURRENT_LIST_DIR}/boost")
	endif()
	# Only load BOOST_LIBRARYDIR if that variable does not exist in cmake and the user environment variables.
	if (NOT BOOST_LIBRARYDIR AND NOT DEFINED ENV{BOOST_LIBRARYDIR} )
    	    #set(BOOST_LIBRARYDIR "${CMAKE_CURRENT_LIST_DIR}/boost/stage/lib")
	endif()
    # Only load TUDAT_CORE_BASE_PATH if that variable does not exist in cmake
	if (NOT TUDAT_CORE_BASE_PATH)
	    set(TUDAT_CORE_BASE_PATH "${CMAKE_CURRENT_LIST_DIR}/TudatCore")
	endif()
endif()
