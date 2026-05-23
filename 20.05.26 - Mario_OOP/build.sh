#!/usr/bin/env bash
set -euo pipefail

CXX=${CXX:-g++}
CXXFLAGS="-std=c++17 -Wall -Wextra -pedantic -D_XOPEN_SOURCE_EXTENDED=1"
SOURCES=(main.cpp Game.cpp BaseObject.cpp Mario.cpp Brick.cpp MovingItems.cpp)
OUTPUT="mario_game"

"$CXX" $CXXFLAGS "${SOURCES[@]}" -lncurses -o "$OUTPUT"
./"$OUTPUT"
