BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"
BUILD_FOLDER="build_linux_${BUILD_SUFFIX}"
SOURCE_FOLDER="src"

mkdir -p "${BUILD_FOLDER}"
cd "${BUILD_FOLDER}"

export GAME_TYPE="LinuxConsole"

cmake -G "${BUILD_TYPE}" -DGAME_TYPE="${GAME_TYPE}" "../${SOURCE_FOLDER}"
cmake --build .

cd ..
