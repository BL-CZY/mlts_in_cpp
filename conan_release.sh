#!/bin/sh

conan install . -s build_type=Release --build=missing
cmake --preset conan-release
