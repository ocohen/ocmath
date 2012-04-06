##########################################################
# Build a library
##########################################################

PROJECT(OCMATH_SRC)

set(HEADERS
  vector4.hpp
)

set(SOURCES
  vector4.cpp
)


##########################################################
# Build the library 
##########################################################

ADD_LIBRARY(ocmath_src STATIC ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(ocmath_src )
