#!/bin/bash
rm -rf build bin lib
mkdir build
cmake -S . -B build
cmake --build build