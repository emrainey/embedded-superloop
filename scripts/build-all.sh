#!/bin/bash
set -e
set -x
set -o pipefail

CLEAN_FIRST="false"

while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -rm|--clean)
            CLEAN_FIRST="true"
            shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

CMAKE_BUILD_TYPES=(MinRelSize Debug)
TOOLCHAINS=(modules/stm32/cmake/stm32.cmake modules/native/cmake/mac-clang.cmake)

for toolchain in ${TOOLCHAINS[@]}; do
    for build_type in ${CMAKE_BUILD_TYPES[@]}; do
        platform=$(basename ${toolchain} .cmake)
        build_folder=build/${build_type}/${platform}
        echo "Building ${build_type} for ${platform} in ${build_folder}"
        if [[ ${CLEAN_FIRST} == "true" ]]; then
            rm -rf ${build_folder}
        fi
        cmake -B ${build_folder} -S . -DCMAKE_TOOLCHAIN_FILE=`pwd`/${toolchain} -DCMAKE_BUILD_TYPE=${build_type}
        VERBOSE=1 cmake --build ${build_folder} -j12
    done
done
