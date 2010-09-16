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

#include "LuaControl.h"
#include "PageControl.h"

class LuaPageControl:public LuaControl,public CPageControl
{
  private:
  
  protected:
  
  public:
    LuaPageControl(lua_State *l,GtkWidget *parent): LuaControl(l), CPageControl(parent)
    {}
    ~LuaPageControl() {};
};


void free_children(GtkContainer *c)
{
  GList *List = gtk_container_get_children (c);

  for (int i=g_list_length(List)-1;i>=0;i--)
  {
    GtkWidget *w = GTK_WIDGET(g_list_nth( List, i )->data);
    //first get pointer to class
    void *pt=g_object_get_data (G_OBJECT(w),"ClassPointer");
    if (pt) g_print("pointer set ;)");
    gtk_widget_destroy(w);
  }
}

static int do_InitSidebar(lua_State *L)
{
  SidebarHandle=lua_touserdata(L,1);
  g_print("Sidebar-Handle: 0x%x (PageControl-Class)\n",int(SidebarHandle));
  
  free_children(GTK_CONTAINER(SidebarHandle));

  return 1;
}

static int do_CreatePageControl(lua_State *L)
{
  gpointer iParent=lua_touserdata(L,1);
  
  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaPageControl *PageControl=new LuaPageControl(L,GTK_WIDGET(iParent));
  /*
  GtkWidget *button=gtk_button_new_with_label("Test");
  gtk_widget_show(button);
  gtk_box_pack_start(GTK_BOX(iParent),button, TRUE, TRUE, 0);
  
  button=gtk_button_new_with_label("Test2");
  gtk_widget_show(button);
  gtk_box_pack_start(GTK_BOX(iParent),button, TRUE, TRUE, 0);
  */
  lua_pushlightuserdata(L,PageControl);//put pointer of Pagecontrol to stack
  return 1;//return 1 value (handle)
}

static int do_PageControlAddPage(lua_State *L)
{
  gpointer iPageControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
 
  g_print("Adding Page To Pagecontrol (0x%x) with label '%s'...\n",iPageControl,caption);

  LuaPageControl* PageControl=reinterpret_cast<LuaPageControl*>(iPageControl);
 
  GtkWidget *vbox=PageControl->AddPage(caption,-1);
  
  lua_pushlightuserdata(L,&vbox);//put pointer of vbox on stack
  return 1;//return 1 value (handle)
}

static const luaL_reg R[] =
{
  { "InitSidebar", do_InitSidebar},
	{ "Pagecontrol_Add_Page",	do_PageControlAddPage },
	{ "New_Pagecontrol",	do_CreatePageControl },
	{ NULL,			NULL	}
};

static int window_on_select(lua_State *L)
{
  return 1;
}

static const struct luaL_reg window_methods[] = {
	{"on_select",window_on_select},
	{NULL, NULL},
};

extern "C" {//__declspec(dllexport)
LUALIB_API int luaopen_gui(lua_State *L)
{
 luaL_register(L,"gui",R);
 
	/*luaL_newmetatable(L, WINDOW_CLASS);  // create metatable for window objects
	lua_pushvalue(L, -1);  // push metatable
	lua_setfield(L, -2, "__index");  // metatable.__index = metatable
	luaL_register(L, NULL, window_methods);
 */
 return 1;
}
}
