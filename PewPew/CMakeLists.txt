file(GLOB_RECURSE PEWPEW_HEADERS
	${ParticlePlay_SOURCE_DIR}/PewPew/*.hpp
)
file(GLOB_RECURSE PEWPEW_SOURCES
	${ParticlePlay_SOURCE_DIR}/PewPew/*.cpp
)

include_directories(${ParticlePlay_SOURCE_DIR})
add_executable(PewPew ${PEWPEW_SOURCES})
target_link_libraries(PewPew ParticlePlay)
