Dependency
================
 - OpenAL-Soft
 - OpenGL

Build
================
Windows
	Rename soft_oal.dll to OpenAL32.dll and place in one of the following locations...
		1. Same place as executable file (keep old OpenAL)
		2. Same place as OpenAL32.dll is located (upgrade OpenAL)
	In makefile, change -lOpenAL to -lopenal32
