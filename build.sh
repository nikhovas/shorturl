#!/usr/bin/env bash

case $1 in
 "debug") BUILD_FOLDER_SUFFIX="debug" ;;
 *)       BUILD_FOLDER_SUFFIX="release" ;;
esac
BUILD_FOLDER=./cmake-build-${BUILD_FOLDER_SUFFIX}/

mkdir -p ${BUILD_FOLDER}
cd ${BUILD_FOLDER}
cmake ../
make
cd ..
