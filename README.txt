Dependency
================
 - OpenAL-Soft
 - OpenGL

 - libogg
 - libvorbis
 - flac

Configurations
================
Using C++11

Windows
	Rename soft_oal.dll to OpenAL32.dll and place in one of the following locations...
		- Same place as executable file (keep old OpenAL)
		- Same place as OpenAL32.dll is located (upgrade OpenAL)
	In makefile, change -lOpenAL to -lopenal32

Building/Running
================
All
	Building
		`make`

Demo
	Building
		`make demo`
	Running
		'make run-demo'

Full
	Building
		`make full`
	Running
		`make run-full`

Copy Resources
	`make resources`

Clean
	`make clean`