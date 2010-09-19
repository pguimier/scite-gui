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

static int do_InitSidebar(lua_State *L)
{
  SidebarHandle=lua_touserdata(L,1);
  g_print("Sidebar-Handle: 0x%x (PageControl-Class)\n",int(SidebarHandle));
  
  free_children(GTK_CONTAINER(SidebarHandle));

  return 1;
}

static int do_CreatePageControl(lua_State *L)
{
  void *iParent=lua_touserdata(L,1);
  
  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaPageControl *PageControl=new LuaPageControl(L,GTK_WIDGET(iParent));
  
  lua_pushlightuserdata(L,PageControl);//put pointer of Pagecontrol to stack
  return 1;//return 1 value (handle)
}

static int do_CreateListView(lua_State *L)
{
  void *iParent=lua_touserdata(L,1);
  
  g_print("Adding Listview to Parent 0x%x...\n",int(iParent));

  LuaListView *Listview=new LuaListView(L,GTK_WIDGET(iParent));
  
  lua_pushlightuserdata(L,Listview);//put pointer of Listview to stack
  return 1;//return 1 value (handle)
}

/*
static int do_CreateSplitter(lua_State *L)
{
  void *iParent=lua_touserdata(L,1);
  bool vertical=lua_toboolean(L,2);
  
  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaSplitter *Splitter=new LuaSplitter(L,GTK_WIDGET(iParent),vertical);
  
  lua_pushlightuserdata(L,Splitter); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)
}

static int do_CreateButton(lua_State *L)
{
  void *iParent=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
  
  g_print("Adding Button to Parent 0x%x...\n",int(iParent));

  LuaButton *Button=new LuaButton(L,GTK_WIDGET(iParent),caption);
  
  lua_pushlightuserdata(L,Button); //put pointer of Splitter to stack
  return 1;//return 1 value (handle)
}
*/
static int do_PageControlAddPage(lua_State *L)
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(iLuaControl);
 
  void *vbox=PageControl->AddPage(caption,-1);
  
  lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
  return 1;//return 1 value (handle)
}

static int do_ListViewAddColumn(lua_State *L)
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
 
  //void *vbox=PageControl->AddPage(caption,-1);
  Listview->AddColumn(caption);
  //lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
  return 0;//return 1 value (handle)
}

static int do_ListViewAddItem(lua_State *L)
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
 
  //void *vbox=PageControl->AddPage(caption,-1);
  GtkTreeIter iter=Listview->AddItem(caption);
  int row=Listview->GetRowFromIter(iter);
  //lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
  lua_pushinteger(L,row);//put pointer of vbox on stack
  return 1;//return 1 value (handle)
}

static int do_ListViewSetItem(lua_State *L)
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  const char *caption=luaL_checkstring(L,4);

  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  //int ArgumentCount = lua_gettop(L);
  
  Listview->SetValue(row,col,caption);
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
	{ "New_Pagecontrol",	do_CreatePageControl },
	{ "New_Listview",	do_CreateListView },
//	{ "New_Splitter",	do_CreateSplitter },
//  { "New_Button", do_CreateButton },
	{ NULL,			NULL	}
};
/*
//code taken from gui_ext.cpp by Steve Donovan
struct WinWrap {
	TWin *window;
	void *data;
};
const char* WINDOW_CLASS = "WINDOW*";

static int wrap_window(lua_State* L, TWin* win) //MEMLEAK? or maybe automatically freed
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
*/
static int window_on_select(lua_State *L)
{
	// LuaControl* lc = dynamic_cast<LuaControl*>(window_arg(L,1));
	// lc->set_select(2);
	return 0;
}

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
