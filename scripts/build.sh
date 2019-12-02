#!/bin/sh

start_time=`date +%s`

# Configure build variables.
BASE_DIR=$(dirname "$0")
if [ "$1" != "" ] then
	BUILD_MODE="$1"
else
	BUILD_MODE=Release
fi

if [ "$2" != "" ] then
	BUILD_ARCH="$2"
else
	BUILD_ARCH=x64
fi

if [ "$3" != "" ] then
	if [ "$3" ] then
		ENABLE_TESTING=TRUE
	else
		ENABLE_TESTING=FALSE
	fi
else
	ENABLE_TESTING=TRUE
fi

BUILD_DIR=${BASE_DIR}/../build/gcc-${BUILD_ARCH}-${BUILD_MODE}
ENABLE_CLANG_TIDY=FALSE

# Color configuration.
COLOR_OFF='\033[0m'
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_BLUE='\033[0;34m'

PrintInfoMsg() {
	printf "${COLOR_GREEN} >> $1 ${COLOR_OFF}\n"
}

PrintErrorMsg() {
	printf "${COLOR_RED} >> $1 ${COLOR_OFF}\n"
}

CheckError() {
	if [ $? -ne 0 ]; then
		PrintErrorMsg "$1"
		exit 1
	fi
}

PrintInfoMsg "Creating a build directory..."
mkdir -p ${BUILD_DIR}
CheckError "Failed to make the build directory."

cd ${BUILD_DIR}

PrintInfoMsg "[CMake] Generating the project..."
cmake \
	-G "Unix Makefiles" \
	-DCMAKE_BUILD_TYPE:STRING=${BUILD_MODE} \
	-DENABLE_TESTING:BOOL=${ENABLE_TESTING} \
	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=${ENABLE_CLANG_TIDY} \
	-DENABLE_CLANG_TIDY:BOOL=${ENABLE_CLANG_TIDY} \
	-Wno-dev \
	"$@" \
	../..
CheckError "[CMake] Failed to generate the project."

CPU_COUNT=`nproc --all`

PrintInfoMsg "[Make] Building the project..."
make -j $CPU_COUNT
CheckError "[Make] Failed to build the project."

PrintInfoMsg "Project has been built successfully!"

if [ "$ENABLE_TESTING" = TRUE ]; then
	PrintInfoMsg "Running tests..."
	ctest --extra-verbose
fi

if [ "${ENABLE_CLANG_TIDY}" = TRUE ]; then
	PrintInfoMsg "[Clang-Tidy] Performing code analysis..."
	make tidy
fi

end_time=`date +%s`
echo Summary build time was `expr $end_time - $start_time` seconds.
