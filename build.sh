#!/usr/bin/env bash

case $1 in
 "debug") BUILD_FOLDER="./cmake-build-debug" ;;
 *)       BUILD_FOLDER="./cmake-build" ;;
esac
SOURCE_FOLDER="."

cmake -B ${BUILD_FOLDER} -S ${SOURCE_FOLDER}
cd ${BUILD_FOLDER}
make
cd ..