#!/bin/sh

conan install . -s build_type=Debug --build=missing
cmake --preset conan-debug
