BUILT_TARGET="debug"

#First parameter, if any, is used as build target.
#If no parameter is given, then default to debug
if [ "$#" == 0 ]; then
	BUILD_TARGET="debug"
else
	BUILD_TARGET="$1"
fi

#All remaining parameters are used as parameters to CMake

cd build
cmake -DPPTARGET="$BUILD_TARGET" "${@:1}" ../
make
