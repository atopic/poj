#! /bin/bash

if [ $# != 1 ]; then
    echo "usage: $0 \"question_id\""
    exit
fi

mkdir "$1"
cp common/template.cc "$1"/a.cc
