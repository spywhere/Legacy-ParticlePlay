# TODO:
# Windows not tested

ifeq ($(OS), Windows_NT)
	BUILDFILE = ./WinBuild.bat
	REMOVECMD = rem
else
	BUILDFILE = ./UnixBuild.sh
	REMOVECMD = rm -rf
endif

all: full

run-demo: demo run
run-full: full run
re-demo: clean demo
re-full: clean full

run:
	@./build/DemoProject/DemoProject

demo: preclean
	@${BUILDFILE} debug demo

full: preclean
	@${BUILDFILE} debug full

preclean:
	@${REMOVECMD} ./build/DemoProject/DemoProject

clean:
	@${REMOVECMD} ./build/*
