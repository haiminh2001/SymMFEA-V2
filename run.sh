#!/bin/bash
ARGS=""
# Argument parsing
while [[ $# -gt 0 ]]
do
    key="$1"
    case $key in
        -h|--help)
        echo "Usage: ./run.sh [options]"
        echo "Options:"
        echo "-h, --help                Show help"
        echo "-o, --output <file>       Specify output file"
        exit 0
        ;;
        --build-only)
        BUILD_ONLY=true
        shift
        ;;
        -o|--output)
        OUTPUT_FOLDER="$2"
        shift
        shift
        ;;
        *)
        echo "Add ${1} to cmake's arguments"
        ARGS=$ARGS" "$1
        shift
        ;;
    esac
done

if [ -z $OUTPUT_FOLDER ]; then
    echo "Output folder not specified"
    exit 1
fi

conan install . --output-folder=${OUTPUT_FOLDER} --build=missing
cmake  -DCMAKE_TOOLCHAIN_FILE=${OUTPUT_FOLDER}/build/Release/generators/conan_toolchain.cmake  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW  -S . source -B $OUTPUT_FOLDER $ARGS
cd $OUTPUT_FOLDER && make 

if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1;
else
    echo "Build succeeded"
fi

if [ -z $BUILD_ONLY ]; then
    ./SymMFEA
fi
