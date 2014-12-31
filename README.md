## ParticlePlay Engine

Cross-platform game engine

##### Features

- State-based game engine
- Adaptive Music System integrated
- Physics engine powered by Box2D
- OpenGL, OpenAL-Soft supported
- Network powered by SDL_net
- Lua script supported

### Tools
 - CMake 2.6 or later
 - make, g++

### Dependencies
- SDL2
- SDL2_image
- SDL2_net
- Box2D
- OpenGL
- OpenAL-Soft
- Lua 5.2

### Configurations
Using C++11

- Windows
  - Rename soft_oal.dll to OpenAL32.dll and place in one of the following locations...
    - Same place as executable file (keep old OpenAL)
    - Same place as OpenAL32.dll is located (upgrade OpenAL)

### Building/Running
**To build project** using

`cd build/`

then

`cmake .. [debug/release] [demo/full]`

or just `make` if you're on Unix

**To run project** move `res` and `tmpres` into `build` and using

`./build/ParticlePlay`

or just `make run`
