Scite-Patch (for compiling yourself):
=====================================
note: precompiled versions of scite 2.21 and Scite-RU 2.03.75 are in this package
copy folder "Scite_Patch" to a location you want (with exec- and write-rights) and run get.sh from your preferred scite-version (Scite 2.21 or Scite-RU)
this will create a subfolder "scite_src", download scite-repository, replace 3 files and compile it

Compile GUI-Extension:
======================
not needed if you havn't made changes (gui.so exists)
simply run compile_mak.sh

running scite with gui-ext
==========================
simply run start_scite.sh

Konfiguration out of this package:
==================================

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


i hope i have forgotten nothing, else tell it me ;)
