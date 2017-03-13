set(SOURCES
	noise.cpp
	particle_actions.cpp
	particle_actions_collection.cpp
	particle_actions_collection_io.cpp
	particle_core.cpp
	particle_effect.cpp
	particle_manager.cpp
	stdafx.cpp
)

set(HEADERS
	noise.h
	particle_actions.h
	particle_actions_collection.h
	particle_core.h
	particle_effect.h
	particle_manager.h
	psystem.h
	stdafx.h
)

include_directories("." ${CMAKE_SOURCE_DIR})

add_library(xrParticles SHARED ${SOURCES} ${HEADERS})
set_target_properties(xrParticles PROPERTIES PREFIX "")
