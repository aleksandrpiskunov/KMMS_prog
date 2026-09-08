@echo off

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_windows_%BUILD_SUFFIX%
set SOURCE_FOLDER=src

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

set GAME_TYPE=WindowsConsole

cmake -G %BUILD_TYPE% -DGAME_TYPE=%GAME_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

cd ..
