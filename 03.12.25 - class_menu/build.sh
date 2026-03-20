#!/bin/bash
CPP_FILES="menu.cpp menu_func.cpp menu_items.cpp"
APP=example

if [ -f $APP ]; then
    rm $APP
fi

g++ $CPP_FILES -o $APP

./$APP
