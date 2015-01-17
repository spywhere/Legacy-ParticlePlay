cmake_minimum_required(VERSION 2.6)

project(ParticlePlay)

add_definitions(
	-Wall
	-std=c++11
	-DAL_ALEXT_PROTOTYPES
)

# Build Version
option(PPVERSION "Build version" "full")

if(PPVERSION STREQUAL "demo")
	# set( PPEXECUTABLE "TestGameDemo" CACHE STRING "" FORCE )
	add_definitions( -DDEMO )
else()
	# set( PPEXECUTABLE "TestGame" CACHE STRING "" FORCE )
	add_definitions( -DFULL )
endif()

# Build Target
if(PPTARGET STREQUAL "")
	set( PPTARGET "debug" )
endif()

if(PPTARGET STREQUAL "release")
	add_definitions( -O2 )
else()
	add_definitions( -DPPDEBUG )
endif()

file(GLOB_RECURSE HEADERS
	${ParticlePlay_SOURCE_DIR}/src/*.hpp
)
file(GLOB_RECURSE SOURCES
	${ParticlePlay_SOURCE_DIR}/src/*.cpp
)

add_executable(ParticlePlay ${HEADERS} ${SOURCES})
# set_target_properties(ParticlePlay
# 	PROPERTIES OUTPUT_NAME ${PPEXECUTABLE}
# 	PREFIX ""
# )

################
# Dependencies #
################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ParticlePlay_SOURCE_DIR}/cmake")

# OpenGL
find_package(OpenGL REQUIRED)

# OpenAL-Soft
if(APPLE)
	set(CMAKE_FIND_FRAMEWORK_save ${CMAKE_FIND_FRAMEWORK} CACHE STRING "" FORCE)
	set(CMAKE_FIND_FRAMEWORK "LAST" CACHE STRING "" FORCE)
endif()

find_package(OpenALSoft REQUIRED)

if(APPLE)
	set(CMAKE_FIND_FRAMEWORK ${CMAKE_FIND_FRAMEWORK_save} CACHE STRING "" FORCE)
endif()

# SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)

# Box2D
find_package(Box2D REQUIRED)

include_directories(
	${ParticlePlay_SOURCE_DIR}/headers
	${ParticlePlay_SOURCE_DIR}/sources
	${OPENGL_INCLUDE_DIRS}
	${OPENAL_SOFT_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${SDL2_NET_INCLUDE_DIRS}
	${BOX2D_INCLUDE_DIRS}
)

target_link_libraries(
	ParticlePlay
	${OPENGL_LIBRARIES}
	${OPENAL_SOFT_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	${SDL2_NET_LIBRARIES}
	${BOX2D_LIBRARIES}
)