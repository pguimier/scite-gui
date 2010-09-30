#!/bin/sh
GUI_DIR=$(pwd)

ln -fs $GUI_DIR/gui.so ~/gui.so
cd Scite_patch #/scite_src/src/scite/bin/

./SciTE -check.if.already.open=0 -save.session=0 -sidebar.show=1 -sidebar.width=200 -ext.lua.startup.script="$GUI_DIR/sidebar.lua"

echo press enter to close window...
read _wait_
