SET(PROGRAMFILESX86 "PROGRAMFILES(X86)")
SET( SDL2_IMAGE_SEARCH_PATHS
	${SDL2_IMAGE_ROOT_DIR}
	./lib/SDL2_image
	$ENV{PROGRAMFILES}/SDL2_image
	$ENV{${PROGRAMFILESX86}}/SDL2_image
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/opt
	/sw
	/opt/local
	/opt/csw
)

FIND_PATH( SDL2_IMAGE_INCLUDE_DIRS
	NAMES
	SDL_net.h
	PATHS
		${SDL2_IMAGE_SEARCH_PATHS}
	PATH_SUFFIXES
		include include/SDL2_image
	DOC
		"The directory where SDL_net.h resides"
)

FIND_LIBRARY( SDL2_IMAGE_LIBRARIES
	NAMES
		SDL2_image
	PATHS
		${SDL2_IMAGE_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC
		"The SDL2_image library"
)

IF ( SDL2_IMAGE_INCLUDE_DIRS AND SDL2_IMAGE_LIBRARIES )
	SET( SDL2_IMAGE_FOUND TRUE )
	MESSAGE(STATUS "Looking for SDL2_image - found")
ELSE()
	SET( SDL2_IMAGE_FOUND FALSE )
	MESSAGE(STATUS "Looking for SDL2_image - not found")
ENDIF()
