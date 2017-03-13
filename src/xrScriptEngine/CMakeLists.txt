set(SOURCES
  BindingsDumper.cpp
  LuaStudio/LuaStudio.cpp
  pch.cpp
  script_callStack.cpp
  script_debugger.cpp
  script_debugger_threads.cpp
  script_engine.cpp
  ScriptEngineScript.cpp
  script_lua_helper.cpp
  script_process.cpp
  script_stack_tracker.cpp
  script_thread.cpp
  ScriptExporter.cpp
  xrScriptEngine.cpp
)

set(HEADERS
  BindingsDumper.hpp
  DebugMacros.hpp
  Functor.hpp
  LuaStudio/Backend/Backend.hpp
  LuaStudio/Backend/Engine.hpp
  LuaStudio/Backend/Interfaces.hpp
  LuaStudio/Backend/LibraryLinkage.hpp
  LuaStudio/Backend/World.hpp
  LuaStudio/Config.hpp
  LuaStudio/Defines.hpp
  LuaStudio/LuaStudio.hpp
  mslotutils.h
  pch.hpp
  ScriptEngineConfig.hpp
  ScriptEngineScript.hpp
  ScriptExporter.hpp
  ScriptExportMacros.hpp
  script_callStack.hpp
  script_debugger.hpp
  script_debugger_messages.hpp
  script_debugger_threads.hpp
  script_engine.hpp
  script_lua_helper.hpp
  script_process.hpp
  script_space_forward.hpp
  script_stack_tracker.hpp
  script_thread.hpp
  xrScriptEngine.hpp
)

include_directories("." ${CMAKE_SOURCE_DIR})

add_library(xrScriptEngine SHARED ${SOURCES} ${HEADERS})

set_target_properties(xrScriptEngine PROPERTIES PREFIX "")

target_link_libraries(xrScriptEngine ${CMAKE_SOURCE_DIR}/src/build/Externals/luajit/libluajit.a)
