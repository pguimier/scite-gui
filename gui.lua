package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
_ALERT(package.cpath)
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())

local pagecontrol=gui.New_Pagecontrol(scite.GetSidebarHandle())
local tab=0
tab=gui.Pagecontrol_Add_Page(pagecontrol,"gui-test")
_ALERT("Tab1:"..tab)
tab=gui.Pagecontrol_Add_Page(pagecontrol,"zweite Seite")
_ALERT("Tab2:"..tab)
tab=gui.Pagecontrol_Add_Page(pagecontrol,"3. Seite")
_ALERT("Tab3:"..tab)