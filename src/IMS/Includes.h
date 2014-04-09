#ifndef INCLUDES_HEADER
#define INCLUDES_HEADER
#ifdef __APPLE__
//Compile on Macintosh (both GCC and XCode)

// SDL2
#include <SDL2/SDL.h>
// #include <SDL2_image/SDL_image.h>

// OpenAL Soft
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

// OpenGL
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>

// Box2D
// #include <Box2D/Box2D.h>

#elif _MSC_VER
//Compile with Visual Studio
#include <windows.h>

// SDL2
#include <SDL.h>
// #include <SDL_image.h>

// OpenAL Soft
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

// OpenGL
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <glut.h>

// Box2D
// #include <Box2D/Box2D.h>

#elif __WIN32__
//Compile with MinGW

// SDL2
#include "SDL2/SDL.h"
// #include "SDL2/SDL_image.h"

// OpenAL Soft
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

// OpenGL
// #include "GL/gl.h"
// #include "GL/glu.h"

// Box2D
// #include <Box2D/Box2D.h>

#elif __LINUX__
//Compile on Linux (not tested)

// SDL2
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

// OpenAL Soft
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

// OpenGL
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>

// Box2D
// #include <Box2D/Box2D.h>

#else
//Other platform

// SDL2
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

// OpenAL Soft
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

// OpenGL
// #include <GL/gl.h>
// #include <GL/glu.h>

// Box2D
// #include <Box2D/Box2D.h>

#endif

#endif
