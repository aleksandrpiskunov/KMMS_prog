#!/bin/bash

BUILD_FOLDER="build_qt"
QT_PATH="/opt/homebrew/opt/qt6"

cmake -S src -B "${BUILD_FOLDER}" -G Ninja \
	-DGAME_TYPE=Qt \
	-DCMAKE_PREFIX_PATH="${QT_PATH}"

cmake --build "${BUILD_FOLDER}"
