file(GLOB_RECURSE DEMOPROJECT_HEADERS
	${ParticlePlay_SOURCE_DIR}/DemoProject/*.hpp
)
file(GLOB_RECURSE DEMOPROJECT_SOURCES
	${ParticlePlay_SOURCE_DIR}/DemoProject/*.cpp
)

include_directories(${ParticlePlay_SOURCE_DIR})
add_executable(DemoProject ${DEMOPROJECT_SOURCES})
target_link_libraries(DemoProject ParticlePlay)
