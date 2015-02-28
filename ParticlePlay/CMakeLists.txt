include_directories(${ParticlePlay_SOURCE_DIR})

file(GLOB_RECURSE PARTICLEPLAY_HEADERS
	${ParticlePlay_SOURCE_DIR}/ParticlePlay/*.hpp
)

file(GLOB_RECURSE PARTICLEPLAY_SOURCES
	${ParticlePlay_SOURCE_DIR}/ParticlePlay/*.cpp
)

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
	${OPENGL_INCLUDE_DIRS}
	${OPENAL_SOFT_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${SDL2_NET_INCLUDE_DIRS}
	${BOX2D_INCLUDE_DIRS}
)

###########
# Library #
###########

if(PP_BUILD_SHARED)
	add_library(ParticlePlay_shared SHARED ${PARTICLEPLAY_SOURCES})
	set_target_properties(
		ParticlePlay_shared PROPERTIES
		OUTPUT_NAME "ParticlePlay"
		CLEAN_DIRECT_OUTPUT 1
		VERSION ${PARTICLEPLAY_VERSION}
	)

	target_link_libraries(
		ParticlePlay_shared
		${OPENGL_LIBRARIES}
		${OPENAL_SOFT_LIBRARIES}
		${SDL2_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_NET_LIBRARIES}
		${BOX2D_LIBRARIES}
	)
endif()

if(PP_BUILD_STATIC)
	add_library(ParticlePlay STATIC ${PARTICLEPLAY_SOURCES})
	set_target_properties(
		ParticlePlay PROPERTIES
		CLEAN_DIRECT_OUTPUT 1
		VERSION ${PARTICLEPLAY_VERSION}
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
endif()

if(PP_INSTALL)
	# Install headers
	install(FILES ${PARTICLEPLAY_HEADERS} DESTINATION include/ParticlePlay)

	# Install libraries
	if(PP_BUILD_SHARED)
		install(
			TARGETS ParticlePlay_shared EXPORT ParticlePlay-targets
			LIBRARY DESTINATION ${LIB_INSTALL_DIR}
			ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
			RUNTIME DESTINATION bin
		)
	endif()

	if(PP_BUILD_STATIC)
		install(
			TARGETS ParticlePlay EXPORT ParticlePlay-targets
			DESTINATION ${LIB_INSTALL_DIR}
		)
	endif()
endif(PP_INSTALL)
