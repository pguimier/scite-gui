package.cpath = props["SciteUserHome"].."/?.so;"..package.cpath
require "gui"
gui.InitSidebar(scite.GetSidebarHandle())
local tab=0
tab=gui.Pagecontrol_Add_Page(scite.GetSidebarHandle(),"gui-test")
_ALERT("Tab1:"..tab)
tab=gui.Pagecontrol_Add_Page(scite.GetSidebarHandle(),"zweite Seite")
_ALERT("Tab2:"..tab)
tab=gui.Pagecontrol_Add_Page(scite.GetSidebarHandle(),"3. Seite")
_ALERT("Tab3:"..tab)