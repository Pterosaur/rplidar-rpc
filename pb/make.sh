#!/bin/bash

GRPC_CPP_PLUGIN_PATH=`which grpc_cpp_plugin`
PROTOC=`which protoc`

$PROTOC -I=. --grpc_out=. --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN_PATH ./*.proto
$PROTOC -I=. --cpp_out=. ./*.proto
#python -m grpc_tools.protoc -I=. --python_out=../logwatcher/ --grpc_python_out=../logwatcher/ $SRC_DIR/rpc/*.proto