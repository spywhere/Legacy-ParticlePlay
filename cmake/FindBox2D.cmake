SET(PROGRAMFILESX86 "PROGRAMFILES(X86)")
SET( BOX2D_SEARCH_PATHS
	${BOX2D_ROOT_DIR}
	./lib/Box2D
	$ENV{PROGRAMFILES}/Box2D
	$ENV{${PROGRAMFILESX86}}/Box2D
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/opt
	/sw
	/opt/local
	/opt/csw
)

FIND_PATH( BOX2D_INCLUDE_DIRS
	NAMES
	Box2D.h
	PATHS
		${BOX2D_SEARCH_PATHS}
	PATH_SUFFIXES
		include include/Box2D
	DOC
		"The directory where Box2D.h resides"
)

FIND_LIBRARY( BOX2D_LIBRARIES
	NAMES
		Box2D Box2Dmain
	PATHS
		${BOX2D_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC
		"The Box2D library"
)

IF( BOX2D_INCLUDE_DIRS AND BOX2D_LIBRARIES )
	SET( BOX2D_FOUND TRUE )
	MESSAGE(STATUS "Looking for Box2D - found")
ELSE()
	SET( BOX2D_FOUND FALSE )
	MESSAGE(STATUS "Looking for Box2D - not found")
ENDIF()
