# - Try to find ocmath
# Once done this will define
#  OCMATH_FOUND - System has ocmath
#  OCMATH_INCLUDE_DIRS - The ocmath include directories
#  OCMATH_LIBRARIES - The libraries needed to use ocmath
#  OCMATH_DEFINITIONS - Compiler switches required for using ocmath

find_package(PkgConfig)
pkg_check_modules(OCMATH QUIET ocmath) 
set(OCMATH_DEFINITIONS ) 

find_path(OCMATH_INCLUDE_DIR ocmath.hpp )
find_library(OCMATH_LIBRARY NAMES ocmath libocmath )

set(OCMATH_LIBRARIES ${OCMATH_LIBRARY} )
set(OCMATH_INCLUDE_DIRS ${OCMATH_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set OCMATH_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ocmath  DEFAULT_MSG
                                  OCMATH_LIBRARY OCMATH_INCLUDE_DIR)

mark_as_advanced(OCMATH_INCLUDE_DIR OCMATH_LIBRARY )
