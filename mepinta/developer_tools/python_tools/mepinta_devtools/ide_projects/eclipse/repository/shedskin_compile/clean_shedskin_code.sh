#!/bin/bash

cd $(dirname $0)

find ./mepinta/pipeline/ -iname "*.cpp" -exec rm {} \;
find ./mepinta/pipeline/ -iname "*.hpp" -exec rm {} \;
find ./ -iname "Makefile" -exec rm {} \;
find ./ -iname "*.ss.py" -exec rm {} \;

rm *.cpp
rm *.hpp
