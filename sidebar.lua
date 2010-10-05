package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
--_ALERT(package.cpath)
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())

--PageControl
local pc=PageControl.new(scite.GetSidebarHandle())
local pc1tab1=pc:Add_Page("1st Page")
local pc1tab2=pc:Add_Page("2nd Page")
local pc1tab3=pc:Add_Page("3rd Page")

function tab_change(selected)
  print("PageControl changed to Tab #"..selected)
end
pc:on_Change(tab_change)

--Listview
local lv=ListView.new(0)
lv:Add_Column("Col 1")
lv:Add_Column("Col 2")
local row
row=lv:Add_Item("Item1")
lv:Set_Item(row,1,"i1c2")
row=lv:Add_Item("Item2")
lv:Set_Item(row,1,"i2c2")

function lv_dblclick(selected)
  print("Listview Doubleclick on Item #"..selected)
end
lv:on_DblClick(lv_dblclick)

--lv:Get_Text
--lv:Clear

--Popup
local p=Popup.new(lv)
function menu_test1()
  print("Menuitem1 :)")
end

function menu_test2()
  print("Menuitem2 :)")
end

function menu_test3()
  print("Menuitem3 :)")
end

p:Add_Item("test1",menu_test1)
p:Add_Item("test2",menu_test2)
p:Add_Item("",0)
p:Add_Item("test3",menu_test3)

--Button
local btn=Button.new(0,"Test-Button")
function btn_click()
  print("Button clicked!")
end
btn:on_Click(btn_click)

--Splitter
local spl=Splitter.new(pc1tab1,true)
spl:Set_Clients(lv,btn)

--RadioGroup
local rg=RadioGroup.new(pc1tab1,"1st choice")
rg:Add_Item("2nd choice")
rg:Add_Item("3rd choice")
function rg_change(selected)
  print("Radiogroup changed to Item #"..selected)
end
rg:on_Change(rg_change)

--checkgroup
local cg=CheckGroup.new(pc1tab1,"1st option")
cg:Add_Item("2nd option")
cg:Add_Item("3rd option")
function cg_change(selected)
  print("Checkgroup-Item #"..selected.." changed!")
end
cg:on_Change(cg_change)


local edit=Edit.new(pc1tab1,"Text: ")
--edit:Get_Text
local memo=Memo.new(pc1tab1)
--memo:Get_Text
