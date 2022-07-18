#!/bin/bash

PROTO_PATH='../proto'
OUTPUT_PATH='../proto/protogen'
CPP_PLUGIN=`whereis grpc_cpp_plugin | awk '{print $2}'`

function generate # $1 = proto name
{
    echo "Generating sources for $1 ..."
    protoc -I$PROTO_PATH \
        --cpp_out=$OUTPUT_PATH $1
    protoc -I$PROTO_PATH \
        --grpc_out=$OUTPUT_PATH \
        --plugin=protoc-gen-grpc=$CPP_PLUGIN $1
}

function check_pwd
{
    CWD=`pwd | rev | cut -d "/" -f1-2 | rev`
    if [ $CWD != "ChessGame/scripts" ]
    then
        echo "Error: Please go to project scripts directory or provide project home directory as argument"
        exit 2
    fi
}

function project_home # $1 = first cmd argument
{
    if [ "$1" != "" ]
    then
        cd "$1/scripts"
        echo "Current working directory changed to $PWD/scripts"
    fi
}

function main
{
    project_home $1
    check_pwd
    mkdir -p $OUTPUT_PATH
    for proto in `ls $PROTO_PATH/*.proto`
    do
        generate $proto
    done
    echo "Sources was successfully generated"
    cd - > /dev/null
}

if [ "$CPP_PLUGIN" == "" ]
then
    echo "Error: protoc-gen-grpc plugin no found"
    exit 1
fi

main $1
