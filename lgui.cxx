/*
SidebarTest
*/
/* lua_pushinteger(L,sbx);
 lua_pushnil(L);
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

void *SidebarHandle;

/*
bool function_ref(lua_State* L, int idx, int* pr) //get function pointer
{
	if (*pr != 0) {
		luaL_unref(L,LUA_REGISTRYINDEX,*pr);
	}
	lua_pushvalue(L,idx);
	*pr = luaL_ref(L,LUA_REGISTRYINDEX);
	return true;
}

void dispatch_ref(lua_State* L,int idx, int ival) //call function
{
	if (idx != 0) {
		lua_rawgeti(L,LUA_REGISTRYINDEX,idx);
		lua_pushnumber(L,ival);
		
		if (lua_pcall(L,1,0,0)) {
			OutputMessage(L);
		}
	}
}

*/

#include "LuaControls.h"

static int do_InitSidebar(lua_State *L) //gui.InitSidebar(scite.GetSidebarHandle())
{
  SidebarHandle=lua_touserdata(L,1);
  g_print("Sidebar-Handle: 0x%x (PageControl-Class)\n",int(SidebarHandle));
  
  free_children(GTK_CONTAINER(SidebarHandle));

  return 1;
}

//creating controls
static int do_CreatePageControl(lua_State *L) //pagecontrol=gui.New_Pagecontrol(parent) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  
  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaPageControl *PageControl=new LuaPageControl(L,GTK_WIDGET(iParent));
  
/*  lua_pushlightuserdata(L,PageControl);//put pointer of Pagecontrol to stack
  return 1;//return 1 value (handle)*/
  return wrap_window(L,PageControl, lcPageControl);
}

static int do_CreateListView(lua_State *L) //lv=gui.New_Listview(parent) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  
  g_print("Adding Listview to Parent 0x%x...\n",int(iParent));

  LuaListView *Listview=new LuaListView(L,GTK_WIDGET(iParent));
  g_print("Listview-Widget: %x\n",int(Listview->GetWidget()));
  /*lua_pushlightuserdata(L,Listview);//put pointer of Listview to stack
  return 1;//return 1 value (handle)*/
  return wrap_window(L,Listview, lcListView);
}

static int do_CreateSplitter(lua_State *L) //spl=gui.New_Splitter(parent,bool vertical) --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  bool vertical=lua_toboolean(L,2);
  
  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaSplitter *Splitter=new LuaSplitter(L,GTK_WIDGET(iParent),vertical);
/*  lua_pushlightuserdata(L,Splitter); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)  */
  return wrap_window(L,Splitter, lcSplitter);
}

static int do_CreateButton(lua_State *L) //btn=gui.New_Button(parent,"caption") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
  g_print("Adding Button to Parent 0x%x...\n",int(iParent));

  LuaButton *Button=new LuaButton(L,GTK_WIDGET(iParent),caption);
  
  g_print("Button-Widget: %x\n",int(Button->GetWidget()));
  /*lua_pushlightuserdata(L,Button); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)*/
  return wrap_window(L,Button, lcButton);
}

static int do_CreatePopup(lua_State *L) //popup=gui.New_Popup(parent)
{
  void *iParent=lua_touserdata(L,1);
  GtkWidget *P=GetWidgetFromWrapPointer(iParent);
  
  g_print("Adding Popup to Parent 0x%x...\n",int(P));

  LuaPopupMenu *Popup=new LuaPopupMenu(L,GTK_WIDGET(P));
  
  g_print("Popup-Widget: %x\n",int(Popup->GetWidget()));
  /*lua_pushlightuserdata(L,Button); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)*/
  return wrap_window(L,Popup, lcPopupMenu);
}

static int do_CreateRadioGroup(lua_State *L) //btn=gui.New_RadioGroup(parent,"caption") --parent can be 0
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
  g_print("Adding RadioGroup to Parent 0x%x...\n",int(iParent));

  LuaRadioGroup *Radiogroup=new LuaRadioGroup(L,GTK_WIDGET(iParent),caption);
  
  g_print("RadioGroup-Widget: %x\n",int(Radiogroup->GetWidget()));
  /*lua_pushlightuserdata(L,Button); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)*/
  return wrap_window(L,Radiogroup, lcRadioGroup);
}


//window Methods

static int do_PageControlAddPage(lua_State *L) //tab=gui.Pagecontrol_Add_Page(pagecontrol,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(iLuaControl);
   if (wrp->wc==lcPageControl)
  {
    LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(wrp->window);
    void *vbox=PageControl->AddPage(caption,-1);
    lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
    return 1;//return 1 value (handle)
  } else g_print("Not a PageControl (AddPage)!\n");
  return 0;
}

static int do_ListViewAddColumn(lua_State *L) //gui.Listview_Add_Column(Listview,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  g_print("Listview->AddColumn\n");
  
  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  if (wrp->wc==lcListView)
  {
    g_print("Listview:CastToLuaListview\n");
    LuaListView *Listview=reinterpret_cast<LuaListView*>(wrp->window);
    Listview->AddColumn(caption);
  } else g_print("Not a Listview (AddColumn)!\n");
  return 0;//return 1 value (handle)
}

static int do_ListViewAddItem(lua_State *L) //row=gui.Listview_Add_Item(Listview,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  if (wrp->wc==lcListView)
  {
    LuaListView *Listview=reinterpret_cast<LuaListView*>(wrp->window);
    GtkTreeIter iter=Listview->AddItem(caption);
    int row=Listview->GetRowFromIter(iter);
    lua_pushinteger(L,row);//put pointer of vbox on stack
    return 1;//return 1 value (handle)
  } else g_print("Not a Listview (AddItem)!\n");
  return 0;
}

static int do_ListViewSetItem(lua_State *L) //gui.Listview_Set_Item(listview,row,col,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  const char *caption=luaL_checkstring(L,4);
  //int ArgumentCount = lua_gettop(L);

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  if (wrp->wc==lcListView)
  {
    LuaListView *Listview=reinterpret_cast<LuaListView*>(wrp->window);
    Listview->SetValue(row,col,caption);
  } else g_print("Not a Listview (SetItem)!\n");
  return 0;
}

static int do_SplitterSetClients(lua_State *L) //gui.Splitter_Set_Clients(Splitter,Child1,Child2)
{
  //int ArgumentCount = lua_gettop(L);
  void *iLuaControl=lua_touserdata(L,1);
  void *iChild1=lua_touserdata(L,2);
  void *iChild2=lua_touserdata(L,3);

  g_print("adding Child1: %x and Child2: %x to Splitter %x\n",int(iChild1),int(iChild2),int(iLuaControl));

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(iLuaControl);
  if (wrp->wc==lcSplitter)
  {
    LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(wrp->window);
    GtkWidget *C1=GetWidgetFromWrapPointer(iChild1);
    GtkWidget *C2=GetWidgetFromWrapPointer(iChild2);
    Splitter->SetClients(C1,C2);
    Splitter->SetStaticChild(0);
  } else g_print("Not a Splitter (SetClients)!\n");
  return 0;
}

int get_function_ref(lua_State *L)
{
  int ref=0;
  if (!lua_isfunction(L, -1)) //Judging wheather it is a function object the top element of the stack (last param)
	{
		g_print("PopupMenuAddItem: 3rd Parameter is not a function!\n");
	}else	ref = luaL_ref(L, LUA_REGISTRYINDEX); //fetch the function reference value
	return ref;
}

static int do_PopupAddItem(lua_State *L) //gui.Popup_Add_Item(Popup,caption,function)
{
  //int ArgumentCount = lua_gettop(L);
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  //int id=luaL_checkinteger(L,3);
  //lua_pop(L,2); //pop the first 2 elements from stack so that function-pointer is on top
  g_print("adding MenuItem %s to Popupmenu %x\n",caption,int(iLuaControl));

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(iLuaControl);
  if (wrp->wc==lcPopupMenu)
  {
    LuaPopupMenu *Popup=reinterpret_cast<LuaPopupMenu*>(wrp->window);
    //Popup->AddMenuItem(caption,id);
    g_print("PopupClass:%x\n",int(Popup));
    
    int ref=get_function_ref(L);
    lua_pop(L, 3); // clean the stack, removing 3 Elements

    Popup->AddMenuItem(caption,ref);
    
  } else g_print("Not a PopupMenu (AddItem)!\n");
  return 0;
}

static int do_RadioGroupAddItem(lua_State *L) //row=gui.Listview_Add_Item(Listview,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  WinWrap *wrp=(WinWrap*)iLuaControl;
  //LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  if (wrp->wc==lcRadioGroup)
  {
    LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(wrp->window);
    Radiogroup->AddRadio(caption);
  } else g_print("Not a RadioGroup (AddItem)!\n");
  return 0;
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

static const luaL_reg R[] =
{
  { "InitSidebar", do_InitSidebar},
	{ "Pagecontrol_Add_Page",	do_PageControlAddPage },
	{ "Listview_Add_Column", do_ListViewAddColumn },
	{ "Listview_Add_Item", do_ListViewAddItem },
	{ "Listview_Set_Item", do_ListViewSetItem },
	{ "Splitter_Set_Clients", do_SplitterSetClients },
  { "Popup_Add_Item", do_PopupAddItem },
	{ "Radiogroup_Add_Item", do_RadioGroupAddItem },
	{ "New_Pagecontrol",	do_CreatePageControl },
	{ "New_Listview",	do_CreateListView },
	{ "New_Splitter",	do_CreateSplitter },
  { "New_Button", do_CreateButton },
  { "New_Popup", do_CreatePopup },
  { "New_Radiogroup", do_CreateRadioGroup },
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

extern "C" 
{//__declspec(dllexport)
	LUALIB_API int luaopen_gui(lua_State *L)
	{
	  luaL_register(L,"gui",R);
	 
		/*
    //i have to get this WINDOW_CLASS with WinWrap working
    //code taken from gui_ext.cpp by Steve Donovan
    luaL_openlib (L, "gui", gui, 0);
    luaL_newmetatable(L, WINDOW_CLASS);  // create metatable for window objects
    lua_pushvalue(L, -1);  // push metatable
    lua_setfield(L, -2, "__index");  // metatable.__index = metatable
    luaL_register(L, NULL, window_methods);
	 */
	  return 1;
	}
}
