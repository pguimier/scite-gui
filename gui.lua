package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
--_ALERT(package.cpath)
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())

local pagecontrol=gui.New_Pagecontrol(scite.GetSidebarHandle())
local tab
tab=gui.Pagecontrol_Add_Page(pagecontrol,"gui-test")

local lv=gui.New_Listview(tab)
gui.Listview_Add_Column(lv,"Col 1")
gui.Listview_Add_Column(lv,"Col 2")
local row
row=gui.Listview_Add_Item(lv,"Item1");
gui.Listview_Set_Item(lv,row,1,"i1c2")
--_ALERT(row)
row=gui.Listview_Add_Item(lv,"Item2");
gui.Listview_Set_Item(lv,row,1,"i2c2")
--_ALERT(row)
tab=gui.Pagecontrol_Add_Page(pagecontrol,"2nd Page")
tab=gui.Pagecontrol_Add_Page(pagecontrol,"3rd Page")
-- 

