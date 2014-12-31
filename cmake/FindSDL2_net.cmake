SET(PROGRAMFILESX86 "PROGRAMFILES(X86)")
SET( SDL2_NET_SEARCH_PATHS
	${SDL2_NET_ROOT_DIR}
	./lib/SDL2_net
	$ENV{PROGRAMFILES}/SDL2_net
	$ENV{${PROGRAMFILESX86}}/SDL2_net
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/opt
	/sw
	/opt/local
	/opt/csw
)

FIND_PATH( SDL2_NET_INCLUDE_DIRS
	NAMES
	SDL_net.h
	PATHS
		${SDL2_NET_SEARCH_PATHS}
	PATH_SUFFIXES
		include include/SDL2_net
	DOC
		"The directory where SDL_net.h resides"
)

FIND_LIBRARY( SDL2_NET_LIBRARIES
	NAMES
		SDL2_net
	PATHS
		${SDL2_NET_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC
		"The SDL2_net library"
)

IF ( SDL2_NET_INCLUDE_DIRS AND SDL2_NET_LIBRARIES )
	SET( SDL2_NET_FOUND TRUE )
	MESSAGE(STATUS "Looking for SDL2_net - found")
ELSE()
	SET( SDL2_NET_FOUND FALSE )
	MESSAGE(STATUS "Looking for SDL2_net - not found")
ENDIF()
