cmake_minimum_required(VERSION 2.8.0)
project(OpenXRay)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#add_definitions(-std=c++11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fpermissive --std=gnu++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fpermissive --std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive --std=c++11")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -fno-implicit-templates --std=c++11")

#-Wreturn-type-c-linkage -Wabsolute-value -Wundefined-bool-conversion -Wunused-private-field -Wnon-pod-varargs

add_definitions(-D_MT -D_CPPUNWIND -DPURE_DYNAMIC_CAST -DDECLARE_SPECIALIZATION -DM_NOSTDCONTAINERS_EXT -DUSE_OGL)

find_package(Lua51 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Theora REQUIRED)
find_package(OGG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(LZO REQUIRED)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR} {CMAKE_SOURCE_DIR}/Common ${CMAKE_SOURCE_DIR}/../Externals ${CMAKE_SOURCE_DIR}/../Externals/gli/external/glm ${CMAKE_SOURCE_DIR}/../sdk/include/loki)

#add_subdirectory(utils)
add_subdirectory(${CMAKE_SOURCE_DIR}/../Externals ${CMAKE_BINARY_DIR}/Externals)
add_subdirectory(Layers) # successfully building (remove dx dependencies on posix)

add_subdirectory(xrMisc) # successfully building
#add_subdirectory(xrAICore) # not building
add_subdirectory(xrCDB) # successfully building
add_subdirectory(xrCore) # partially building, not finished
add_subdirectory(xrEngine) # not building, not finished
#add_subdirectory(xrGame)
#add_subdirectory(xrNetServer) # not building
add_subdirectory(xrParticles) # successfully building
add_subdirectory(xrPhysics) # successfully building
add_subdirectory(xrScriptEngine) # not building
#add_subdirectory(xrSound) # successfully building
