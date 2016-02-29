# Overview #
every object provides a function new() and methods to change properties of the object.
functions are appended using . to the classname
e.g.
```
pc=PageControl.new(0)
```

new-functions returning the object-variable

methods are appended using : to the object-variable
e.g.
```
pc1tab1=pc:Add_Page("1st Page")
```

Scite-GUI-package contains a modified Scite-versions (Scite-Original 2.21 and Scite-ru 2.03.75).
here is the sidebar-functionality included (scite.GetSidebarHandle())


# Objects #

## PageControl ##

### Functions ###
| **Function** | **Description** | **Example** |
|:-------------|:----------------|:------------|
| new(caption) | creates a new PageControl<br>parent can be 0,sidebar-handle or pagecontrol-tab <table><thead><th> pc=PageControl.new(page1) </th></thead><tbody></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Add_Page(caption) </td><td> adds a new tab to the PageControl </td><td> pctab=pc:Add_Page("1st Page") </td></tr></tbody></table>


<h2>ListView</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(caption)    </td><td> creates a new ListView<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> lv=ListView.new(page1) </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Add_Column(caption) </td><td> adds a new column to the Listview </td><td> lv:Add_Column("1st Col") </td></tr>
<tr><td> Add_Item(caption) </td><td> adds a new item to the Listview and returns row-number </td><td> row=lv:Add_Item("1st Item") </td></tr>
<tr><td> Set_Item(row,col,caption) </td><td> changes col of Item in row  </td><td> lv:Set_Item(0,1,"1st Item col 2") </td></tr>
<tr><td> Get_Text(row,col) </td><td> gets Text of item in row and col </td><td> text=lv:Get_Text(0,1) </td></tr>
<tr><td> Clear()       </td><td> clears the Listview </td><td> lv:Clear()     </td></tr></tbody></table>


<h2>Splitter</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent,vertical) </td><td> creates a new Splitter<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> spl=Splitter.new(page1,true) </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Set_Clients(C1,C2) </td><td> setting the 2 Controls as resizable controls in the splitter </td><td> spl:Set_Clients(lv,rg) </td></tr></tbody></table>


<h2>Popup</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent)     </td><td> creates a new Popupmenu<br>parent can be any lua-control </td><td> pu=Popup.new(lv) </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Add_Item(caption,function) </td><td> adds a new item to the popup-menu with reference to a lua-function (for onClick)</td><td> function menu_test1()<br>  print("Menuitem1 :)")<br>end<br>p:Add_Item("test1",menu_test1) </td></tr></tbody></table>


<h2>Button</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent,caption) </td><td> creates a new Button<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> btn=Button.new(page1,"caption") </td></tr></tbody></table>


<h2>RadioGroup</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent,caption_of_first) </td><td> creates a new RadioGroup<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> rg=RadioGroup.new(page1,"1st choice") </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Add_Item(caption) </td><td> adds a new item to the RadioGroup</td><td> rg:Add_Item("2nd choice") </td></tr></tbody></table>


<h2>CheckGroup</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent,caption_of_first) </td><td> creates a new CheckGroup<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> cg=CheckGroup.new(page1,"1st choice") </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Add_Item(caption) </td><td> adds a new item to the CheckGroup </td><td> cg:Add_Item("2nd option") </td></tr></tbody></table>


<h2>Edit</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent,caption) </td><td> creates a new Edit<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> <code>ed=Edit.new(page1,"Text: ")</code> </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Get_Text()    </td><td> gets text of the edit </td><td> <code>text=edit:Get_Text()</code> </td></tr></tbody></table>


<h2>Memo</h2>

<h3>Functions</h3>
<table><thead><th> <b>Function</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> new(parent)     </td><td> creates a new Edit<br>parent can be 0,sidebar-handle or pagecontrol-tab </td><td> me=Memo.new(page1) </td></tr></tbody></table>

<h3>Methods</h3>
<table><thead><th> <b>Method</b> </th><th> <b>Description</b> </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> Get_Text()    </td><td> gets text of the memo </td><td> text=memo:Get_Text() </td></tr></tbody></table>

<h1>Message-Boxes</h1>
gui.Show_Info("caption","text")<br>
<br>
gui.Show_Warning("caption","text")<br>
<br>
gui.Show_Error("caption","text")<br>
<br>
gui.Show_Question("caption","text") --returning true on yes and false on no