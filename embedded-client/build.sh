#!/bin/bash

export WORKSPACE="$1"
export THIRDPARTY="$2"

rm -rf build
mkdir build
cd build
cmake ..
make
cd -
