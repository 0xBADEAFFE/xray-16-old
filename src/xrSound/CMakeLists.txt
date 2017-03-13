#http://kcat.strangesoft.net/openal.html
set(SOURCES
	guids.cpp
	OpenALDeviceList.cpp
	sound.cpp
	SoundRender_Cache.cpp
	SoundRender_Core.cpp
	SoundRender_CoreA.cpp
	SoundRender_Core_Processor.cpp
	SoundRender_Core_SourceManager.cpp
	SoundRender_Core_StartStop.cpp
	SoundRender_Emitter.cpp
	SoundRender_Emitter_FSM.cpp
	SoundRender_Emitter_StartStop.cpp
	SoundRender_Emitter_streamer.cpp
	SoundRender_Environment.cpp
	SoundRender_Source.cpp
	SoundRender_Source_loader.cpp
	SoundRender_Target.cpp
	SoundRender_TargetA.cpp
	stdafx.cpp
)

set(HEADERS
	OpenALDeviceList.h
	Sound.h
	SoundRender.h
	SoundRender_Cache.h
	SoundRender_Core.h
	SoundRender_CoreA.h
	SoundRender_Emitter.h
	SoundRender_Environment.h
	SoundRender_Source.h
	SoundRender_Target.h
	SoundRender_TargetA.h
	stdafx.h
)

include_directories("." ${CMAKE_SOURCE_DIR} ${OGG_INCLUDE_DIR} ${OPENAL_INCLUDE_DIR} ${THEORA_INCLUDE_DIRS})

add_library(xrSound SHARED ${SOURCES} ${HEADERS})

set_target_properties(xrSound PROPERTIES PREFIX "")

target_link_libraries(xrSound ${OGG_LIBRARIES} ${OPENAL_LIBRARY} ${THEORA_LIBRARIES})
