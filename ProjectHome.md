# GUI-Modifications for Scite with LUA #

currently GTK only, a similar Win32-Plugin can be found [here](http://code.google.com/p/scite-ru/source/browse/#hg/lualib/gui)

![http://scite-gui.googlecode.com/svn/web/images/SciTE-GUI.png](http://scite-gui.googlecode.com/svn/web/images/SciTE-GUI.png)

## Controls implemented with Lua-Access and Events: ##

  * PageControl (TabSwitch: onChange)
  * Listview (onDoubleClick)
  * PopupMenu (MenuItemClick)
  * Button (OnClick)
  * RadioGroup (onChange)
  * CheckGroup (onChange)
  * Splitter (no Events)
  * MessageBox (no Events)
  * Singleline / Multiline-Editcontrol (no Events)

## Controls planned (no lua-Integration): ##
  * Window
  * Box (for holding multiple controls like Pagecontrol-Pages)