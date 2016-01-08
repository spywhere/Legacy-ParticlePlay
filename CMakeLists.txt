cmake_minimum_required(VERSION 2.6)

project(ParticlePlay)

# Build options
option(PP_INSTALL "Install ParticlePlay libs and includes" OFF)
option(PP_BUILD_SHARED "Build ParticlePlay shared libraries" OFF)
option(PP_BUILD_STATIC "Build ParticlePlay static libraries" ON)
option(PP_BUILD_DEMO "Build ParticlePlay demo project" OFF)
option(PP_BUILD_RELEASE "Build actual project" ON)

# Library constants
set(PARTICLEPLAY_VERSION 0.1.0)

add_definitions(
	-Wall
	-std=c++11
	-DAL_ALEXT_PROTOTYPES
)

# Build Version
option(PP_VERSION "Build version" "full")

if(PP_VERSION STREQUAL "demo")
	# set( PPEXECUTABLE "TestGameDemo" CACHE STRING "" FORCE )
	add_definitions( -DDEMO )
else()
	# set( PPEXECUTABLE "TestGame" CACHE STRING "" FORCE )
	add_definitions( -DFULL )
endif()

# Build Target
if(PP_TARGET STREQUAL "")
	set( PP_TARGET "debug" )
endif()

if(PP_TARGET STREQUAL "release")
	add_definitions( -O2 )
else()
	add_definitions( -DPPDEBUG )
endif()

# CMP0042 Fix
if(APPLE)
	set(CMAKE_MACOSX_RPATH ON)
	set(CMAKE_SKIP_BUILD_RPATH  FALSE)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
	list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
	if("${isSystemDir}" STREQUAL "-1")
		set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
	endif("${isSystemDir}" STREQUAL "-1")
endif()

# Main library
add_subdirectory(ParticlePlay)

# Build Example
if(PP_BUILD_DEMO)
	add_subdirectory(DemoProject)
elseif(PP_BUILD_RELEASE)
	add_subdirectory(PewPew)
endif()
