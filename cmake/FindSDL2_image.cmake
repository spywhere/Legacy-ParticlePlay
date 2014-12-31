# Copyright (C) 2014 Barry Deeney
# Copyright (C) 2014 Benny Bobaganoosh
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#############################################
# Try to find ASSMIP and set the following: #
#                                           #
# SDL2_IMAGE_FOUND                          #
# SDL2_IMAGE_INCLUDE_DIRS                   #
# SDL2_IMAGE_LIBRARIES                      #
#############################################

SET( SDL2_IMAGE_SEARCH_PATHS
	${SDL2_IMAGE_ROOT_DIR}					# SDL2_image!
	./lib/SDL2_image
	$ENV{PROGRAMFILES}/SDL2_image			# WINDOWS
	"$ENV{PROGRAMFILES(X86)}/SDL2_image"	# WINDOWS
	~/Library/Frameworks					# MAC
	/Library/Frameworks						# MAC
	/usr/local								# LINUX/MAC/UNIX
	/usr									# LINUX/MAC/UNIX
	/opt									# LINUX/MAC/UNIX
	/sw										# Fink
	/opt/local								# DarwinPorts
	/opt/csw								# Blastwave
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

# Check if we found it!
IF ( SDL2_IMAGE_INCLUDE_DIRS AND SDL2_IMAGE_LIBRARIES )
	SET( SDL2_IMAGE_FOUND TRUE )
	MESSAGE(STATUS "Looking for SDL2_image - found")
ELSE ( SDL2_IMAGE_INCLUDE_DIRS AND SDL2_IMAGE_LIBRARIES )
	SET( SDL2_IMAGE_FOUND FALSE )
	MESSAGE(STATUS "Looking for SDL2_image - not found")
ENDIF ( SDL2_IMAGE_INCLUDE_DIRS AND SDL2_IMAGE_LIBRARIES )
