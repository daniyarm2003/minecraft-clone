#!/usr/bin/env bash

EXEC_PATH="./build/game"

if [[ $# -ge 1 ]]
then
    EXEC_PATH="$1"
fi

make
$EXEC_PATH
gprof $EXEC_PATH ./gmon.out > gmon.log