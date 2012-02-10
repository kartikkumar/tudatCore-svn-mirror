# Environment file for distribution

if ("${PROJECT_NAME}" STREQUAL "TudatCore")
    message(WARNING "TudatCoreEnvironment.cmake is run while building the Tudat Core")
else()
    set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/eigen3")
    set(BOOST_ROOT "${CMAKE_CURRENT_LIST_DIR}/boost")
	set(BOOST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/boost")
	set(BOOST_LIBRARY_DIR "${CMAKE_CURRENT_LIST_DIR}/boost/stage/lib")
    set(TUDAT_CORE_BASE_PATH "${CMAKE_CURRENT_LIST_DIR}/TudatCore")
endif()
