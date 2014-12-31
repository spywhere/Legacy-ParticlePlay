SET( BOX2D_SEARCH_PATHS
	${BOX2D_ROOT_DIR}					# Box2D!
	./lib/Box2D
	$ENV{PROGRAMFILES}/Box2D			# WINDOWS
	"$ENV{PROGRAMFILES(X86)}/Box2D"		# WINDOWS
	~/Library/Frameworks				# MAC
	/Library/Frameworks					# MAC
	/usr/local							# LINUX/MAC/UNIX
	/usr								# LINUX/MAC/UNIX
	/opt								# LINUX/MAC/UNIX
	/sw									# Fink
	/opt/local							# DarwinPorts
	/opt/csw							# Blastwave
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

# Check if we found it!
IF ( BOX2D_INCLUDE_DIRS AND BOX2D_LIBRARIES )
	SET( BOX2D_FOUND TRUE )
	MESSAGE(STATUS "Looking for Box2D - found")
ELSE ( BOX2D_INCLUDE_DIRS AND BOX2D_LIBRARIES )
	SET( BOX2D_FOUND FALSE )
	MESSAGE(STATUS "Looking for Box2D - not found")
ENDIF ( BOX2D_INCLUDE_DIRS AND BOX2D_LIBRARIES )





# Locate Box2D
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables

# FIND_PATH(BOX2D_INCLUDE_DIRS Box2D.h
# 	HINTS
# 	$ENV{BOX2D_DIR}
# 	$ENV{BOX2D_PATH}
# 	${ADDITIONAL_SEARCH_PATHS}
# 	PATH_SUFFIXES include Include
# 	PATHS
# 		~/Library/Frameworks
# 		/Library/Frameworks
# 		/usr/local
# 		/usr
# 		/sw # Fink
# 		/opt/local # DarwinPorts
# 		/opt/csw # Blastwave
# 		/opt
# )

# FIND_LIBRARY(BOX2D_LIBRARIES
# 	NAMES box2d
# 	HINTS
# 	$ENV{BOX2D_DIR}
# 	$ENV{BOX2D_PATH}
# 	${ADDITIONAL_SEARCH_PATHS}
# 	PATH_SUFFIXES lib64 lib lib/release Library
# 	PATHS
# 		~/Library/Frameworks
# 		/Library/Frameworks
# 		/usr/local
# 		/usr
# 		/sw
# 		/opt/local
# 		/opt/csw
# 		/opt
# )

# FIND_LIBRARY(BOX2D_LIBRARIES_DEBUG
# 	NAMES box2dd box2d_d
# 	HINTS
# 	$ENV{BOX2D_DIR}
# 	$ENV{BOX2D_PATH}
# 	${ADDITIONAL_SEARCH_PATHS}
# 	PATH_SUFFIXES lib64 lib lib/debug Library
# 	PATHS
# 		~/Library/Frameworks
# 		/Library/Frameworks
# 		/usr/local
# 		/usr
# 		/sw
# 		/opt/local
# 		/opt/csw
# 		/opt
# )


# # handle the QUIETLY and REQUIRED arguments and set CURL_FOUND to TRUE if
# # all listed variables are TRUE
# INCLUDE(FindPackageHandleStandardArgs)
# FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOX2D DEFAULT_MSG BOX2D_LIBRARIES BOX2D_INCLUDE_DIRS)
# INCLUDE(FindPackageTargetLibraries)
# FIND_PACKAGE_SET_STD_INCLUDE_AND_LIBS(BOX2D)
