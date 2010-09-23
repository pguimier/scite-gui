package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
--_ALERT(package.cpath)
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())

local pagecontrol=gui.New_Pagecontrol(scite.GetSidebarHandle())
local tab
tab=gui.Pagecontrol_Add_Page(pagecontrol,"gui-test")

--local lv=gui.New_Listview(tab)
local lv=gui.New_Listview(0)
gui.Listview_Add_Column(lv,"Col 1")
gui.Listview_Add_Column(lv,"Col 2")
local row
row=gui.Listview_Add_Item(lv,"Item1")
gui.Listview_Set_Item(lv,row,1,"i1c2")
--_ALERT(row)
row=gui.Listview_Add_Item(lv,"Item2")
gui.Listview_Set_Item(lv,row,1,"i2c2")

--local btn=gui.New_Button(tab,"Test")
local btn=gui.New_Button(0,"Test")

local spl=gui.New_Splitter(tab,true)
gui.Splitter_Set_Clients(spl,lv,btn)

--_ALERT(row)
tab=gui.Pagecontrol_Add_Page(pagecontrol,"2nd Page")
--local btn=gui.New_Button(tab,"Test")
tab=gui.Pagecontrol_Add_Page(pagecontrol,"3rd Page")
-- 

