#ifndef INCLUDES_HEADER
	#define INCLUDES_HEADER
	#ifdef __APPLE__
		//Compile on Macintosh (both GCC and XCode)

		// SDL2
		#include <SDL2/SDL.h>
		#include <SDL2_image/SDL_image.h>
		// #include <SDL2_mixer/SDL_mixer.h>
		#include <SDL2_net/SDL_net.h>

		// OpenGL
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>

		// OpenAL Soft
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/efx.h>

		// Box2D
		#include <Box2D/Box2D.h>

		// XCode related
		// #include <CoreFoundation/CoreFoundation.h>

		//Redirect to resources folder
		// char path[PATH_MAX];
		// CFURLRef res = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
		// CFURLGetFileSystemRepresentation(res, true, (UInt8 *)path, PATH_MAX);
		// CFRelease(res);
		// chdir(path);
	#elif _MSC_VER
		//Compile with Visual Studio
		#include <windows.h>

		// SDL2
		#include <SDL.h>
		#include <SDL_image.h>
		// #include <SDL_mixer.h>
		#include <SDL_net.h>

		// OpenGL
		#include <GL/gl.h>
		#include <GL/glu.h>
		#include <glut.h>

		// OpenAL Soft
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/efx.h>

		// Box2D
		#include <Box2D/Box2D.h>
	#elif __WIN32__
		//Compile with MinGW

		// SDL2
		#include "SDL2/SDL.h"
		#include "SDL2/SDL_image.h"
		// #include "SDL2/SDL_mixer.h"
		#include "SDL2/SDL_net.h"

		// OpenGL
		#include "GL/gl.h"
		#include "GL/glu.h"

		// OpenAL Soft
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/efx.h>

		// Box2D
		#include <Box2D/Box2D.h>
	#elif __LINUX__
		//Compile on Linux (not tested)

		// SDL2
		#include <SDL2/SDL.h>
		#include <SDL2/SDL_image.h>
		// #include <SDL2/SDL_mixer.h>
		#include <SDL2/SDL_net.h>

		// OpenGL
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>

		// OpenAL Soft
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/efx.h>

		// Box2D
		#include <Box2D/Box2D.h>
	#else
		//Other platform

		// SDL2
		#include <SDL2/SDL.h>
		#include <SDL2/SDL_image.h>
		// #include <SDL2/SDL_mixer.h>
		#include <SDL2/SDL_net.h>

		// OpenGL
		#include <GL/gl.h>
		#include <GL/glu.h>

		// OpenAL Soft
		#include <AL/al.h>
		#include <AL/alc.h>
		#include <AL/efx.h>

		// Box2D
		#include <Box2D/Box2D.h>
	#endif
#endif