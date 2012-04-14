##########################################################
# Build a library
##########################################################

PROJECT(OCMATH)

set(HEADERS
  vector4.hpp
  vector3.hpp
  point3.hpp
  matrix.hpp
  ocmath.hpp
)

set(SOURCES
  vector4.cpp
  vector3.cpp
  point3.cpp
  matrix.cpp
  ocmath.cpp
)


##########################################################
# Build the library 
##########################################################

ADD_LIBRARY(ocmath STATIC ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(ocmath) 
