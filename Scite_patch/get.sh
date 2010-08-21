#!/bin/sh
mkdir ./scite_src
svn checkout http://scite-ru.googlecode.com/svn/trunk/ scite_src -r1382
cp Extender.own.h scite_src/src/scite/src/Extender.h
cp LuaExtension.own.cxx scite_src/src/scite/src/LuaExtension.cxx
cp SciTEGTK.own.cxx scite_src/src/scite/gtk/SciTEGTK.cxx

cd scite_src
cd src/scintilla/gtk
make

cd ../../scite/gtk
make
