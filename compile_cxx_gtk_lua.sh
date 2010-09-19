#!/bin/sh

LUA=/usr/src/scite/scite_ru_older/src/scite/lua
INC="-I$LUA/include -I$LUA/src"
GTK_INC=`pkg-config --cflags --libs gtk+-2.0`
OUT_FILE=$(echo $1 | sed -e 's/l\(.*\).c[x]*/\1/').so

g++ $INC $GTK_INC -shared -o $OUT_FILE $1
