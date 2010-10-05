/*

*/

#define LUA_CORE

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

void *SidebarHandle=NULL;

#include "LuaControl.h"
#include "LuaControls.h"

struct LuaClass
{
  CControl *Ctl;
  int CT;
};

static int PushObject(lua_State* L,CControl *c)
{
	LuaClass *lc = (LuaClass*)lua_newuserdata(L,sizeof(LuaClass));
	lc->Ctl = c;
	lc->CT = c->GetType();
	switch (lc->CT)
	{
	  case cPageControl:luaL_getmetatable(L,"gui.PageControl");break;
	  case cListView:luaL_getmetatable(L,"gui.ListView");break;
	  case cSplitter:luaL_getmetatable(L,"gui.Splitter");break;
	  case cPopupMenu:luaL_getmetatable(L,"gui.Popup");break;
	  case cButton:luaL_getmetatable(L,"gui.Button");break;
	  case cRadioGroup:luaL_getmetatable(L,"gui.RadioGroup");break;
	  case cCheckGroup:luaL_getmetatable(L,"gui.CheckGroup");break;
	  case cEdit:luaL_getmetatable(L,"gui.Edit");break;
	  case cMemo:luaL_getmetatable(L,"gui.Memo");break;
	}
	lua_setmetatable(L,-2);
	return 1;
}

int get_function_ref(lua_State *L)
{
  int ref=0;
  if (!lua_isfunction(L, -1)) //Judging wheather it is a function object the top element of the stack (last param)
	{
		g_print("Top Parameter is not a function!\n");
	}else	ref = luaL_ref(L, LUA_REGISTRYINDEX); //fetch the function reference value
	return ref;
}

static int do_InitSidebar(lua_State *L) //gui.InitSidebar(scite.GetSidebarHandle())
{
  if (SidebarHandle)
    free_children(GTK_CONTAINER(SidebarHandle));
  SidebarHandle=lua_touserdata(L,1);
//  g_print("Sidebar-Handle: 0x%x\n",int(SidebarHandle));
  

  return 1;
}

static int Set_Event(void *iControl,int evType,int functionref)
{
  LuaClass *lc=reinterpret_cast<LuaClass*>(iControl);
  //LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
  CControl *Control=reinterpret_cast<GtkControl*>(lc->Ctl);
  //CControl *Control=reinterpret_cast<GtkControl*>(iControl);
  switch (Control->GetType())
  {
    case cPageControl: {LuaPageControl *c=dynamic_cast<LuaPageControl*>(Control);c->Lua.SetEvent(evType,functionref);} break;
    case cListView: {LuaListView *c=dynamic_cast<LuaListView*>(Control);c->Lua.SetEvent(evType,functionref);} break;
	  case cSplitter: {LuaSplitter *c=dynamic_cast<LuaSplitter*>(Control);c->Lua.SetEvent(evType,functionref);} break;
	  case cButton: {LuaButton *c=dynamic_cast<LuaButton*>(Control);c->Lua.SetEvent(evType,functionref);} break;
    //case cCheckBox: {LuaPageControl *c=dynamic_cast<LuaPageControl*>(Control);c->Lua.SetEvent(evType,functionref);} break;
    case cRadioGroup: {LuaRadioGroup *c=dynamic_cast<LuaRadioGroup*>(Control);c->Lua.SetEvent(evType,functionref);} break;
    case cCheckGroup: {LuaCheckGroup *c=dynamic_cast<LuaCheckGroup*>(Control);c->Lua.SetEvent(evType,functionref);} break;
  	//cPopupMenu,
    //cWindow,
    //cBox,
  };
  return 0;
}

//creating controls
static int do_CreatePageControl(lua_State *L) //pagecontrol=gui.New_Pagecontrol(parent) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  
//  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaPageControl *PageControl=new LuaPageControl(L,GTK_WIDGET(iParent));
  //lua_pushlightuserdata(L,PageControl);//put pointer of Pagecontrol to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,PageControl);
}

static int do_CreateListView(lua_State *L) //lv=gui.New_Listview(parent) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  
//  g_print("Adding Listview to Parent 0x%x...\n",int(iParent));

  LuaListView *Listview=new LuaListView(L,GTK_WIDGET(iParent));
//  g_print("Listview-Widget: %x\n",int(Listview->GetWidget()));
  //lua_pushlightuserdata(L,Listview);//put pointer of Listview to stack
  return PushObject(L,Listview);
  //return 1;//return 1 value (handle)
}

static int do_CreateSplitter(lua_State *L) //spl=gui.New_Splitter(parent,bool vertical) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  bool vertical=lua_toboolean(L,2);
  
//  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaSplitter *Splitter=new LuaSplitter(L,GTK_WIDGET(iParent),vertical);
  //lua_pushlightuserdata(L,Splitter); //put pointer of Splitter to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Splitter);
}

static int do_CreateButton(lua_State *L) //btn=gui.New_Button(parent,"caption") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
//  g_print("Adding Button to Parent 0x%x...\n",int(iParent));

  LuaButton *Button=new LuaButton(L,GTK_WIDGET(iParent),caption);
  
  //lua_pushlightuserdata(L,Button); //put pointer of Button to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Button);
}

static int do_CreatePopup(lua_State *L) //popup=gui.New_Popup(parent)
{
  void *iParent=lua_touserdata(L,1);
//  GtkWidget *P=reinterpret_cast<GtkControl*>(iParent)->GetWidget();
  LuaClass *lc=reinterpret_cast<LuaClass*>(iParent);
  GtkControl *Control=reinterpret_cast<GtkControl*>(lc->Ctl);
  GtkWidget *P=Control->GetWidget();
  
//  g_print("Adding Popup to Parent 0x%x...\n",int(P));

  LuaPopupMenu *Popup=new LuaPopupMenu(L,GTK_WIDGET(P));
  
//  g_print("Popup-Widget: %x\n",int(Popup->GetWidget()));
  //lua_pushlightuserdata(L,Popup); //put pointer of Popup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Popup);
}

static int do_CreateRadioGroup(lua_State *L) //rg=gui.New_RadioGroup(parent,"caption") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
//  g_print("Adding RadioGroup to Parent 0x%x...\n",int(iParent));

  LuaRadioGroup *Radiogroup=new LuaRadioGroup(L,GTK_WIDGET(iParent),caption);
  
//  g_print("RadioGroup-Widget: %x\n",int(Radiogroup->GetWidget()));
  //lua_pushlightuserdata(L,Radiogroup); //put pointer of RadioGroup to stack
  //return 1;//return 1 value (handle)
  
  return PushObject(L,Radiogroup);
}

static int do_CreateCheckGroup(lua_State *L) //cg=gui.New_CheckGroup(parent,"caption") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
  //g_print("Adding CheckGroup to Parent 0x%x...\n",int(iParent));

  LuaCheckGroup *Checkgroup=new LuaCheckGroup(L,GTK_WIDGET(iParent),caption);
  
  //g_print("CheckGroup-Widget: %x\n",int(Checkgroup->GetWidget()));
  //lua_pushlightuserdata(L,Checkgroup); //put pointer of CheckGroup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Checkgroup);
}

static int do_CreateEdit(lua_State *L) //edit=gui.New_Edit(parent,"label") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *label=luaL_checkstring(L,2);
  //g_print("Adding Edit to Parent 0x%x...\n",int(iParent));

  LuaEdit *Edit=new LuaEdit(L,GTK_WIDGET(iParent),label);
  
  //g_print("Edit-Widget: %x\n",int(Edit->GetWidget()));
  //lua_pushlightuserdata(L,Edit); //put pointer of RadioGroup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Edit);
}

static int do_CreateMemo(lua_State *L) //memo=gui.New_Memo(parent) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  
  //g_print("Adding Memo to Parent 0x%x...\n",int(iParent));

  LuaMemo *Memo=new LuaMemo(L,GTK_WIDGET(iParent));
  
  //g_print("Memo-Widget: %x\n",int(Memo->GetWidget()));
  //lua_pushlightuserdata(L,Memo); //put pointer of Memo to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Memo);
}


//window Methods

static int do_PageControlAddPage(lua_State *L) //tab=gui.Pagecontrol_Add_Page(pagecontrol,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaPageControl *Control=reinterpret_cast<LuaPageControl*>(lc->Ctl);

  void *vbox=Control->AddPage(caption,-1);
  lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
  return 1;//return 1 value (handle to vbox)
}

static int do_ListViewAddColumn(lua_State *L) //gui.Listview_Add_Column(Listview,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
  Listview->AddColumn(caption);
  return 0;//return no value
}

static int do_ListViewAddItem(lua_State *L) //row=gui.Listview_Add_Item(Listview,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);//iLuaControl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  int row=Listview->AddNewItem(caption);
  lua_pushinteger(L,row);//put rownumber on stack
  return 1;//return 1 value (row)
}

static int do_ListViewSetItem(lua_State *L) //gui.Listview_Set_Item(listview,row,col,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  const char *caption=luaL_checkstring(L,4);
  //int ArgumentCount = lua_gettop(L);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  Listview->SetValue(row,col,caption);
  return 0;
}

static int do_ListViewGetText(lua_State *L) //gui.Listview_Get_Text(listview,row,col) returns string
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  Listview->GetText(row,col); //LuaListView pushes value to Stack
  return 1;
}

static int do_ListViewClear(lua_State *L) //gui.Listview_Clear(Listview)
{
  void *iLuaControl=lua_touserdata(L,1);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  g_print("clear listview\n");
  Listview->Clear();
  return 0;
}

static int do_SplitterSetClients(lua_State *L) //gui.Splitter_Set_Clients(Splitter,Child1,Child2)
{
  void *iLuaControl=lua_touserdata(L,1);
  void *iChild1=lua_touserdata(L,2);
  void *iChild2=lua_touserdata(L,3);

//  LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(lc->Ctl);
  LuaClass *lc_c1=reinterpret_cast<LuaClass*>(iChild1);
  GtkWidget *C1=reinterpret_cast<GtkControl*>(lc_c1->Ctl)->GetWidget();
  LuaClass *lc_c2=reinterpret_cast<LuaClass*>(iChild2);
  GtkWidget *C2=reinterpret_cast<GtkControl*>(lc_c2->Ctl)->GetWidget();
//  GtkWidget *C1=reinterpret_cast<GtkControl*>(iChild1)->GetWidget();
//  GtkWidget *C2=reinterpret_cast<GtkControl*>(iChild2)->GetWidget();
  Splitter->SetClients(C1,C2);
  Splitter->SetStaticChild(0);

  return 0;
}

static int do_PopupAddItem(lua_State *L) //gui.Popup_Add_Item(Popup,caption,function)
{
  //int ArgumentCount = lua_gettop(L);
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
//  g_print("adding MenuItem %s to Popupmenu %x\n",caption,int(iLuaControl));

//  LuaPopupMenu *Popup=reinterpret_cast<LuaPopupMenu*>(iLuaControl);
//  g_print("PopupClass:%x\n",int(Popup));
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaPopupMenu *Popup=reinterpret_cast<LuaPopupMenu*>(lc->Ctl);
  
  int ref;
  if (strcmp(caption,"")) //do not try to get reference for Separator-Elements
    ref=get_function_ref(L);
  lua_pop(L, 3); // clean the stack, removing 3 Elements

  Popup->AddMenuItem(caption,ref);
    
  return 0;
}

static int do_RadioGroupAddItem(lua_State *L) //gui.Radiogroup_Add_Item(Radiogroup,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

//  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(lc->Ctl);
  Radiogroup->AddRadio(caption);
  return 0;
}

static int do_RadioGroupGetChecked(lua_State *L) //gui.Radiogroup_Get_Checked(Radiogroup) returns integer
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(lc->Ctl);
  lua_pushinteger(L,Radiogroup->GetChecked());
  return 1;
}

static int do_CheckGroupAddItem(lua_State *L) //gui.Checkgroup_Add_Item(Checkgroup,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

//  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(lc->Ctl);
  Checkgroup->AddCheckBox(caption);
  return 0;
}

static int do_CheckGroupIsChecked(lua_State *L) //gui.Checkgroup_Is_Checked(Checkgroup,int ItemIndex) returns bool
{
  void *iLuaControl=lua_touserdata(L,1);
  int index=luaL_checkinteger(L,2);

//  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(lc->Ctl);
  lua_pushboolean(L,Checkgroup->GetChecked(index));
  return 1;
}

static int do_EditGetText(lua_State *L) //gui.Edit_Get_Text(Edit) returns string
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaEdit *Edit=reinterpret_cast<LuaEdit*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaEdit *Edit=reinterpret_cast<LuaEdit*>(lc->Ctl);
  Edit->GetText(); //LuaEdit pushes value to Stack
  return 1;
}

static int do_MemoGetText(lua_State *L) //gui.Memo_Get_Text(Memo) returns string
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaMemo *Memo=reinterpret_cast<LuaMemo*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaMemo *Memo=reinterpret_cast<LuaMemo*>(lc->Ctl);
  Memo->GetText(); //LuaMemo pushes value to Stack
  return 1;
}


static int do_ShowError(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_ERROR);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowInfo(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_INFO);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowWarning(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_WARNING);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowQuestion(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  bool ret=(MessageDialog(caption, message, MESSAGE_QUESTION)==1);
  lua_pushboolean(L,ret);
  return 1;
}

/*
//function taken from gui_ext.cpp by Steve Donovan
static wchar_t** table_to_str_array(lua_State *L, int idx, int* psz = NULL)
{
	if (! lua_istable(L,idx)) 
  {
		throw_error(L,L"table argument expected");
	}
    wchar_t** p = new wchar_t*[100];
    int i = 0;
    lua_pushnil(L); // first key
    while (lua_next(L, idx) != 0) 
    {
      // `key' is at index -2 and `value' at index -1 
		 p[i++] = _wcsdup(StringFromUTF8(lua_tostring(L,-1)));
         lua_pop(L, 1);  // removes `value'; keeps `key' for next iteration
    }
    p[i] = NULL;  // conventional way of indicating end of string array
    if (psz) *psz = i;
    return p;
}
*/
/*
static int do_SetEvent(lua_State *L)
{
  void *iLuaControl=lua_touserdata(L,1);
  //const char *event=luaL_checkstring(L,2);
  int evType=luaL_checkinteger(L,2);
      
  int ref=get_function_ref(L);
  lua_pop(L, 3); // clean the stack, removing 3 Elements
  Set_Event(iLuaControl,evType,ref);
  return 0;
}
*/

//TODO: removing redundant code

static int do_SetOnClick(lua_State *L)//without parameter
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evClick,ref);
  return 0;
}

static int do_SetOnDoubleClick(lua_State *L)//parameter: new index
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evDoubleClick,ref);
  return 0;
}

static int do_SetOnChange(lua_State *L)//used for Pagecontrol-switch; new index
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evChange,ref);
  return 0;
}


static const luaL_reg R[] =
{
  { "InitSidebar", do_InitSidebar},
	{ "Pagecontrol_Add_Page",	do_PageControlAddPage },
	{ "Listview_Add_Column", do_ListViewAddColumn },
	{ "Listview_Add_Item", do_ListViewAddItem },
	{ "Listview_Set_Item", do_ListViewSetItem },
	{ "Listview_Get_Text", do_ListViewGetText },
	{ "Listview_Clear", do_ListViewClear },
	{ "Splitter_Set_Clients", do_SplitterSetClients },
  { "Popup_Add_Item", do_PopupAddItem },
	{ "Radiogroup_Add_Item", do_RadioGroupAddItem },
	{ "Radiogroup_Get_Checked", do_RadioGroupGetChecked },
	{ "Checkgroup_Add_Item", do_CheckGroupAddItem },
	{ "Checkgroup_Is_Checked", do_CheckGroupIsChecked },
	{ "Edit_Get_Text", do_EditGetText },
	{ "Memo_Get_Text", do_MemoGetText },
	{ "New_Pagecontrol",	do_CreatePageControl },
	{ "New_Listview",	do_CreateListView },
	{ "New_Splitter",	do_CreateSplitter },
  { "New_Button", do_CreateButton },
  { "New_Popup", do_CreatePopup },
  { "New_Radiogroup", do_CreateRadioGroup },
  { "New_Checkgroup", do_CreateCheckGroup },
  { "New_Edit", do_CreateEdit },
  { "New_Memo", do_CreateMemo },
  
  { "Show_Error", do_ShowError },
  { "Show_Info", do_ShowInfo },
  { "Show_Warning", do_ShowWarning },
  { "Show_Question", do_ShowQuestion },
//  { "Set_Event", do_SetEvent },
//	{ "Set_OnClick", do_SetOnClick },//without parameter
//	{ "Set_OnDoubleClick", do_SetOnDoubleClick },//parameter: new index
//	{ "Set_OnChange", do_SetOnChange },//used for Pagecontrol-switch; new index
	{ NULL,			NULL	}
};
/*
//code taken from gui_ext.cpp by Steve Donovan
struct WinWrap {
	TWin *window;
	void *data;
};
//const char* WINDOW_CLASS = "WINDOW*";

static int wrap_window(lua_State* L, TWin* win)
{
	WinWrap *wrp = (WinWrap*)lua_newuserdata(L,sizeof(WinWrap));
	wrp->window = win;
	wrp->data = NULL;
	luaL_getmetatable(L,WINDOW_CLASS);
	lua_setmetatable(L,-2);
	return 1;
}

static void throw_error(lua_State* L, const wchar_t *msg)
{
	lua_pushstring(L,UTF8FromString(msg));
	lua_error(L);
}

static TWin* window_arg(lua_State* L, int idx = 1)
{
	WinWrap *wrp = (WinWrap*)lua_touserdata(L,idx);
	if (! wrp) throw_error(L,L"not a window");
	return (PaletteWindow*)wrp->window;
}

//new_*-functions returning a wrap_window(L,control_class);

static int window_on_select(lua_State *L)
{
	// LuaControl* lc = dynamic_cast<LuaControl*>(window_arg(L,1));
	// lc->set_select(2);
	return 0;
}
*/
static const struct luaL_reg window_methods[] = {
	// {"show",window_show},
	// {"hide",window_hide},
	// {"size",window_size},
	// {"position",window_position},
	// {"bounds",window_get_bounds},
	// {"client",window_client},
	// {"add",window_add},
	// {"remove",window_remove},
	// {"context_menu",window_context_menu},
	// {"add_column",window_add_column},
	// {"add_item",window_add_item},
	// {"insert_item",window_insert_item},
	// {"delete_item",window_delete_item},
	// {"count",window_count},
	// {"get_item_text",window_get_item_text},
	// {"get_item_data",window_get_item_data},
	// {"get_selected_item",window_selected_item},
	// {"get_selected_items",window_selected_items},
	// {"selected_count",window_selected_count},
	// {"set_selected_item",window_select_item},
	// {"on_select",window_on_select},
	// {"on_double_click",window_on_double_click},
	// {"on_key",window_on_key},
	// {"clear",window_clear},
	// {"autosize",window_autosize},
	// {"add_buttons",window_add_buttons},
	// {"add_tab",tabbar_add},
	// {"set_text",memo_set},
	// {"set_memo_colour",memo_set_colour},
	// {"set_list_colour",window_set_colour},
	{NULL, NULL},
};

static const struct luaL_reg ListView_f [] = 
{
  {"new", do_CreateListView},
  {NULL, NULL}
};

static const struct luaL_reg ListView_m [] = 
{
  { "Add_Column", do_ListViewAddColumn },
  { "Add_Item", do_ListViewAddItem },
  { "Set_Item", do_ListViewSetItem },
  { "Get_Text", do_ListViewGetText },
  { "Clear", do_ListViewClear },
  
  {"on_DblClick",do_SetOnDoubleClick},
  {NULL, NULL}
};

static const struct luaL_reg PageControl_f [] = 
{
  {"new", do_CreatePageControl},
  {NULL, NULL}
};

static const struct luaL_reg PageControl_m [] = 
{
	{ "Add_Page",	do_PageControlAddPage },
	
	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg Splitter_f [] = 
{
  {"new", do_CreateSplitter},
  {NULL, NULL}
};

static const struct luaL_reg Splitter_m [] = 
{
	{ "Set_Clients",	do_SplitterSetClients },
  {NULL, NULL}
};

static const struct luaL_reg Popup_f [] = 
{
  {"new", do_CreatePopup},
  {NULL, NULL}
};

static const struct luaL_reg Popup_m [] = 
{
	{ "Add_Item",	do_PopupAddItem },
  {NULL, NULL}
};

static const struct luaL_reg Button_f [] = 
{
  {"new", do_CreateButton},
  {NULL, NULL}
};

static const struct luaL_reg Button_m [] = 
{
  {"on_Click",do_SetOnClick},
  {NULL, NULL}
};

static const struct luaL_reg RadioGroup_f [] = 
{
  {"new", do_CreateRadioGroup},
  {NULL, NULL}
};

static const struct luaL_reg RadioGroup_m [] = 
{
	{ "Add_Item",	do_RadioGroupAddItem },
	{ "Get_Checked", do_RadioGroupGetChecked },

	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg CheckGroup_f [] = 
{
  {"new", do_CreateCheckGroup},
  {NULL, NULL}
};

static const struct luaL_reg CheckGroup_m [] = 
{
	{ "Add_Item",	do_CheckGroupAddItem },
	{ "Is_Checked", do_CheckGroupIsChecked },

	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg Edit_f [] = 
{
  {"new", do_CreateEdit},
  {NULL, NULL}
};

static const struct luaL_reg Edit_m [] = 
{
	{ "Get_Text", do_EditGetText },
  {NULL, NULL}
};

static const struct luaL_reg Memo_f [] = 
{
  {"new", do_CreateMemo},
  {NULL, NULL}
};

static const struct luaL_reg Memo_m [] = 
{
	{ "Get_Text", do_MemoGetText },
  {NULL, NULL}
};

void RegisterClass(lua_State *L,const char *name,const char *table,const luaL_reg *object_struct,const luaL_reg *method_struct)
{
    luaL_newmetatable(L, table);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    luaL_openlib(L, NULL, method_struct, 0); //first register Methods
    luaL_openlib(L, name, object_struct, 0); //now register object 
}

extern "C" 
{//__declspec(dllexport)
	LUALIB_API int luaopen_gui(lua_State *L)
	{
	  luaL_register(L,"gui",R);
	 
//    luaL_newmetatable(L, "gui.ListView");
//    lua_pushstring(L, "__index");
//    lua_pushvalue(L, -2);  /* pushes the metatable */
//    lua_settable(L, -3);  /* metatable.__index = metatable */
//    luaL_openlib(L, NULL, ListView_m, 0); //first register Methods
//    luaL_openlib(L, "ListView", ListView_f, 0); //now register object
    RegisterClass(L,"ListView","gui.ListView",ListView_f,ListView_m);
    RegisterClass(L,"PageControl","gui.PageControl",PageControl_f,PageControl_m);
    RegisterClass(L,"Splitter","gui.Splitter",Splitter_f,Splitter_m);
    RegisterClass(L,"Popup","gui.Popup",Popup_f,Popup_m);
    RegisterClass(L,"Button","gui.Button",Button_f,Button_m);
    RegisterClass(L,"RadioGroup","gui.RadioGroup",RadioGroup_f,RadioGroup_m);
    RegisterClass(L,"CheckGroup","gui.CheckGroup",CheckGroup_f,CheckGroup_m);
    RegisterClass(L,"Edit","gui.Popup",Edit_f,Edit_m);
    RegisterClass(L,"Memo","gui.Memo",Memo_f,Memo_m);

	  return 2;
	}
}
