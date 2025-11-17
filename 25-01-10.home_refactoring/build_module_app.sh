#!/bin/bash
CPP_FILES="io.cpp sortings.cpp main.cpp"
APP=example

if [ -f $APP ]; then
    rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP
