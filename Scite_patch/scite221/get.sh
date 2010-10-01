#!/bin/sh
mkdir -p scite_src
hg clone -r rel-2-21 http://scintilla.hg.sourceforge.net:8000/hgroot/scintilla/scintilla scite_src/scintilla
hg clone -r rel-2-21 http://scintilla.hg.sourceforge.net:8000/hgroot/scintilla/scite scite_src/scite

#copy changed files
cp Extender.own.h scite_src/scite/src/Extender.h
cp LuaExtension.own.cxx scite_src/scite/src/LuaExtension.cxx
cp SciTEGTK.own.cxx scite_src/scite/gtk/SciTEGTK.cxx

./build.sh
