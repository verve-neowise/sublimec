#!/bin/bash

name="sublimec"

win_path="bin/win32"
linux_path="bin/linux"
obj_path="build/main.o"

win32_comp () {
    echo "compile to win32 executable with gcc"
    g++ -o $win_path/$name.exe $obj_path
}

linux_comp () {
    echo "compile to linux executable with gcc"
    g++ -o $linux_path/$name $obj_path
}

src2obj () {
    echo "start compiling main.cpp"
    g++  -c src/main.cpp -o $obj_path
}

src2obj

if [[ "$OSTYPE" = "linux-gnu" ]]; then
    linux_comp
elif [[ "$OSTYPE" = "WINDOWS" ]]; then
    win32_comp
else
    echo "Cannot compile. Unknown OS $OSTYPE"
fi
