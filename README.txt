Scite-Patch:
============
copy folder "Scite_Patch" to a location you want (with exec- and write-rights) and run get.sh
this will create a subfolder "scite_src", download scite-ru-repository, replace 3 files and compile it

Compile GUI-Extension:
======================
simply run "make" in root-folder of this source-Package

Konfiguration:
==============

~/.SciTEUser.properties:

if PLAT_GTK
  ext.lua.startup.script=$(SciteUserHome)/base.lua --/home/user/base.lua
sidebar.show=1

~/base.lua:
dofile(props["SciteUserHome"].."gui.lua") --/home/user/gui.lua

copy/symlink these files (maybe your paths):
gui.lua to ~/gui.lua
gui.so to ~/gui.so

now you can run scite from the subfolder scite_src/src/scite/bin and see the sidebar


i hope i have forgotten nothing, lese tell it me ;)
