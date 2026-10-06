#!/bin/sh

cmake --build --preset conan-debug
cd build/Debug

ctest --output-on-failure
