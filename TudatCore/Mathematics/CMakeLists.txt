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
 #      111025    K. Kumar          Adapted file to work with Revision 194.
 #      111026    K. Kumar          Adapted file so all headers show in project tree in Qt Creator.
 #
 #    References
 #
 #

# Set the main sub-directories
set(BASICMATHEMATICSDIR "${MATHEMATICSDIR}/BasicMathematics")
set(NUMERICALINTEGRATORSDIR "${MATHEMATICSDIR}/NumericalIntegrators")

# Add source files.
set(MATHEMATICS_SOURCES
)

# Add header files.
set(MATHEMATICS_HEADERS
)

# Add sub-directories.
add_subdirectory("${SRCROOT}${BASICMATHEMATICSDIR}")
add_subdirectory("${SRCROOT}${NUMERICALINTEGRATORSDIR}")

# Get target properties for static libraries.
get_target_property(BASICMATHEMATICSSOURCES tudat_core_basic_mathematics SOURCES)
get_target_property(NUMERICALINTEGRATORSSOURCES tudat_core_numerical_integrators SOURCES)

# Add static libraries.
add_library(tudat_core_mathematics STATIC ${MATHEMATICS_SOURCES} ${MATHEMATICS_HEADERS} ${BASICMATHEMATICSSOURCES} ${NUMERICALINTEGRATORSSOURCES})
setup_tudat_library_target(tudat_core_mathematics "${SRCROOT}${MATHEMATICSDIR}")
setup_headers("${MATHEMATICS_HEADERS}" "${MATHEMATICSDIR}")
