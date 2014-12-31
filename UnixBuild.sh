BUILD_TARGET="debug"
BUILD_VERSION="full"

# First parameter, if any, is used as build target.
# If no parameter is given, then default to debug
if [ "$#" -ne 0 ]; then
	BUILD_TARGET="$1"
	if [ "$#" -ne 1 ]; then
		BUILD_VERSION="$2"
	fi
fi

# All remaining parameters are used as parameters to CMake
cd build/
cmake -DPPTARGET="$BUILD_TARGET" -DPPVERSION="full" "${@:2}" ../
make
