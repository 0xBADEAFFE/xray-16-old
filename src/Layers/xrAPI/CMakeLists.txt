set(SOURCES
  stdafx.cpp
  xrAPI.cpp
)

set(HEADERS
  ../../Include/xrAPI/xrAPI.h
  stdafx.h
)

include_directories("." ${CMAKE_SOURCE_DIR})

add_library(xrAPI STATIC ${SOURCES} ${HEADERS})
