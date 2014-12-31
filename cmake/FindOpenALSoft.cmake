SET( OPENAL_SOFT_SEARCH_PATHS
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
)

FIND_PATH( OPENAL_SOFT_INCLUDE_DIRS
  NAMES
  al.h alc.h efx.h
  PATHS
    ${OPENAL_SOFT_SEARCH_PATHS}
  PATH_SUFFIXES
    include/AL
    include/OpenAL
    include
  DOC
    "The directory where al.h resides"
)

FIND_LIBRARY( OPENAL_SOFT_LIBRARIES
  NAMES
    OpenAL
    al
    openal
    OpenAL32
    openal32
  PATHS
    ${OPENAL_SOFT_SEARCH_PATHS}
  PATH_SUFFIXES
    lib64
    lib
    libs64
    libs
    libs/Win32
    libs/Win64
  DOC
    "The OpenAL-Soft library"
)

# Check if we found it!
IF ( OPENAL_SOFT_INCLUDE_DIRS AND OPENAL_SOFT_LIBRARIES )
  SET( OPENAL_SOFT_FOUND TRUE )
  MESSAGE(STATUS "Looking for OpenAL-Soft - found")
ELSE ( OPENAL_SOFT_INCLUDE_DIRS AND OPENAL_SOFT_LIBRARIES )
  SET( OPENAL_SOFT_FOUND FALSE )
  MESSAGE(STATUS "Looking for OpenAL-Soft - not found")
ENDIF ( OPENAL_SOFT_INCLUDE_DIRS AND OPENAL_SOFT_LIBRARIES )
