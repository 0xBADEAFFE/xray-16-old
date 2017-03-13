set(SOURCES
	color.cpp
	gametype_chooser.cpp
	Sound.cpp
	stdafx.cpp
	string_functions.cpp
	WaveForm.cpp
	xrMisc_xrMemory.cpp
)

set(HEADERS
	stdafx.h
)

add_definitions(-DBUILDING_XRMISC_LIB)

include_directories("." ${CMAKE_SOURCE_DIR})

add_library(xrMisc STATIC ${SOURCES} ${HEADERS})
