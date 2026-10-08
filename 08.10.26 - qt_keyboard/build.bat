@echo off

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=.
set IMG_FOLDER=img

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

if not exist %IMG_FOLDER% mkdir %IMG_FOLDER%
copy ..\%IMG_FOLDER%\grustnii-smail.png %IMG_FOLDER%\

cd ..
