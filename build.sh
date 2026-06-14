#!/bin/bash

CC="gcc"
SRCS="./src/*.c"
DIR="./builds"
OPT="-Wall -Wno-switch -O3"

declare -A argmap=(
    ["--name"]="NAME"
    ["--flags"]="DFLAGS"
    ["--recipe"]="RECIPE"
)

while [[ $# -gt 0 ]]; do
    case $1 in 
        --*)
        if [[ -n "${argmap[$1]}" ]]; then
            varname="${argmap[$1]}"
            declare "$varname=$2"

            shift 2
        else
            echo "Unknown option: $1"
            exit 1
        fi
        ;;
    esac
done

if [[ $RECIPE == "penguin" ]]; then
    libs="-lm -lSDL2"

elif [[ $RECIPE == "win32" ]]; then
    libs="-lm -lmingw32 -lSDL2"

else
    echo "unknown recipe..."
    exit 1
fi

rm -f module_*
$CC $OPT -g $SRCS "./src/modules/viewer.c" -shared -fPIC -o module_$timestamp.so $warnings -D$DFLAGS
mv module_$timestamp.so module.so

$CC $OPT $includes -g $SRCS -o$NAME $libs $warnings -D$DFLAGS
mkdir -p $DIR
mv $NAME $DIR

echo "Succesfully built $DIR/$NAME"
