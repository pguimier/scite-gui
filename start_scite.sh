#!/bin/sh
cd Scite_patch/scite_src/src/scite/bin/

./SciTE -check.if.already.open=0 -save.session=0

echo press any key to close window...
read _wait_
