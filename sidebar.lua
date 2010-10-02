package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
--_ALERT(package.cpath)
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())

--PageControl
local pagecontrol=gui.New_Pagecontrol(scite.GetSidebarHandle())

function tab_change(selected)
  print("PageControl changed to Tab #"..selected)
end

local pc1tab1=gui.Pagecontrol_Add_Page(pagecontrol,"1st Page")
local pc1tab2=gui.Pagecontrol_Add_Page(pagecontrol,"2nd Page")
--local pc1tab3=gui.Pagecontrol_Add_Page(pagecontrol,"3rd Page")

gui.Set_Event(pagecontrol,2,tab_change)--radiogroup,evChange,function

--Listview
local lv=gui.New_Listview(0)
gui.Listview_Add_Column(lv,"Col 1")
gui.Listview_Add_Column(lv,"Col 2")
local row
row=gui.Listview_Add_Item(lv,"Item1")
gui.Listview_Set_Item(lv,row,1,"i1c2")
row=gui.Listview_Add_Item(lv,"Item2")
gui.Listview_Set_Item(lv,row,1,"i2c2")

function lv_doubleclick(row)
  print("Listview doubleclicked on row #"..row)
end
gui.Set_Event(lv,1,lv_doubleclick)--listview,evDoubleClick,function

--PopupMenu
pu=gui.New_Popup(lv)

function menu_test1()
  print("Menuitem1 :)")
end

function menu_test2()
  print("Menuitem2 :)")
end

function menu_test3()
  print("Menuitem3 :)")
end

gui.Popup_Add_Item(pu,"test1",menu_test1)
gui.Popup_Add_Item(pu,"test2",menu_test2)
gui.Popup_Add_Item(pu,"",0)
gui.Popup_Add_Item(pu,"test3",menu_test3)

--Button
local btn=gui.New_Button(0,"Test")

function button_clicked()
  print("button clicked")
end
gui.Set_Event(btn,0,button_clicked)--button,evClick,function

--Splitter
local spl=gui.New_Splitter(pc1tab1,true)

local spl2=gui.New_Splitter(0,true)
gui.Splitter_Set_Clients(spl,lv,spl2)

--another PageControl
local pagecontrol2=gui.New_Pagecontrol(0)
local pc2tab1=gui.Pagecontrol_Add_Page(pagecontrol2,"pc2t1")
local pc2tab2=gui.Pagecontrol_Add_Page(pagecontrol2,"pc2t2")
local pc2tab3=gui.Pagecontrol_Add_Page(pagecontrol2,"pc2t3")

function tab_change2(selected)
  print("PageControl#2 changed to Tab #"..selected)
end
gui.Set_Event(pagecontrol2,2,tab_change2)--radiogroup,evChange,function


gui.Splitter_Set_Clients(spl2,btn,pagecontrol2);

--RadioGroup
local radio=gui.New_Radiogroup(pc2tab1,"1st choice")
gui.Radiogroup_Add_Item(radio,"2nd choice")
function rg_change(selected)
  print("RadioGroup changed to Item #"..selected)
end
gui.Set_Event(radio,2,rg_change)--radiogroup,evChange,function

--CheckGroup
local check=gui.New_Checkgroup(pc2tab2,"1st option")
gui.Checkgroup_Add_Item(check,"2nd option")
gui.Checkgroup_Add_Item(check,"3rd option")

function cg_change(selected)
  print("Item #"..selected.." in CheckGroup changed")
end
gui.Set_Event(check,2,cg_change)--checkgroup,evChange,function

--edit
local edit=gui.New_Edit(pc2tab3,"Text: ")
local memo=gui.New_Memo(pc2tab3)

