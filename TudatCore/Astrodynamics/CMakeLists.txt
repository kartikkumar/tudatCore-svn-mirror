 #    Copyright (c) 2010-2011 Delft University of Technology.
 #
 #    This software is protected by national and international copyright.
 #    Any unauthorized use, reproduction or modification is unlawful and
 #    will be prosecuted. Commercial and non-private application of the
 #    software in any form is strictly prohibited unless otherwise granted
 #    by the authors.
 #
 #    The code is provided without any warranty; without even the implied
 #    warranty of merchantibility or fitness for a particular purpose. #
 #    References
 #
 #    Changelog
 #      YYMMDD    Author            Comment
 #      110820    S.M. Persson      File created.
 #      120204    K. Kumar          Adapted for Astrodynamics sub-directory.
 #
 #    References
 #
 #/

# Define the main sub-directories.
set(BASICASTRODYNAMICSDIR "${ASTRODYNAMICSDIR}/BasicAstrodynamics")

# Add source files.
set(ASTRODYNAMICS_SOURCES
)

# Add header files.
set(ASTRODYNAMICS_HEADERS
)

# Add subdirectories.
add_subdirectory("${SRCROOT}${BASICASTRODYNAMICSDIR}")

# Get target properties for static libraries.
get_target_property(BASICASTRODYNAMICSSOURCES tudat_core_basic_astrodynamics SOURCES)

# Add static libraries.
add_library(tudat_core_astrodynamics STATIC ${ASTRODYNAMICS_SOURCES} ${ASTRODYNAMICS_HEADERS} ${BASICASTRODYNAMICSSOURCES})
setup_tudat_library_target(tudat_core_astrodynamics "${SRCROOT}${ASTRODYNAMICSDIR}")
setup_headers("${ASTRODYNAMICS_HEADERS}" "${ASTRODYNAMICSDIR}")
