#!/bin/bash

my_qmake="qmake"
my_build=build

if [ ! -d "$my_build" ]; then
    mkdir $my_build
fi

cd $my_build

echo $PATH $my_qmake ../Match3Model
make

echo $PATH $my_qmake ../main
make

./main
