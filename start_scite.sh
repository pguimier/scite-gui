#!/bin/sh
GUI_DIR=$(pwd)
cd Scite_patch #/scite_src/src/scite/bin/

./SciTE -check.if.already.open=0 -save.session=0 -ext.lua.startup.script=$GUI_DIR/gui.lua

echo press enter to close window...
read _wait_
