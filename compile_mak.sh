#!/bin/sh

make clean
make

GUI_DIR=$(pwd)
ln -fs $GUI_DIR/gui.so ~/gui.so

echo press enter to close window...
read _wait_
