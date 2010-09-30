#!/bin/sh

make clean
make

echo "checking for unresolved symbols..."
echo "(i) if module lua not found, look in makefile for a solution"
rm -f debug.so
make -s debug.so

GUI_DIR=$(pwd)

ln -fs $GUI_DIR/gui.so ~/gui.so

echo press enter to close window...
read _wait_
