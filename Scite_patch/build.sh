#!/bin/sh

cd scite_src
cd src/scintilla/gtk
make

cd ../../scite/gtk
make

echo complete
read _wait_
