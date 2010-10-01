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

function menu_test1()
  print("Menuitem1 :)")
end

function menu_test2()
  print("Menuitem2 :)")
end

function menu_test3()
  print("Menuitem3 :)")
end

pu=gui.New_Popup(lv)
gui.Popup_Add_Item(pu,"test1",menu_test1)
gui.Popup_Add_Item(pu,"test2",menu_test2)
gui.Popup_Add_Item(pu,"",0)
gui.Popup_Add_Item(pu,"test3",menu_test3)

--local btn=gui.New_Button(tab,"Test")
local btn=gui.New_Button(0,"Test")

local spl=gui.New_Splitter(tab,true)

local spl2=gui.New_Splitter(0,true)
gui.Splitter_Set_Clients(spl,lv,spl2)
local pagecontrol2=gui.New_Pagecontrol(0)
gui.Splitter_Set_Clients(spl2,btn,pagecontrol2);
local tab=gui.Pagecontrol_Add_Page(pagecontrol2,"gui-test2")
local radio=gui.New_Radiogroup(tab,"1st choice")
gui.Radiogroup_Add_Item(radio,"2nd choice")
--_ALERT(row)
tab=gui.Pagecontrol_Add_Page(pagecontrol,"2nd Page")
--local btn=gui.New_Button(tab,"Test")
tab=gui.Pagecontrol_Add_Page(pagecontrol,"3rd Page")
-- 

