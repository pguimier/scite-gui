#!/bin/sh

cd scite_src
cd src/scintilla/gtk
make

cd ../../scite/gtk
make

cp ../bin/SciTE $(dirname $0)

echo complete
read _wait_
