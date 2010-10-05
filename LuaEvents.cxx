#include "LuaEvents.h"

int get_function_ref(lua_State *L)
{
  int ref=0;
  if (!lua_isfunction(L, -1)) //Judging wheather it is a function object the top element of the stack (last param)
	{
		g_print("Top Parameter is not a function!\n");
	}else	ref = luaL_ref(L, LUA_REGISTRYINDEX); //fetch the function reference value
	return ref;
}

int Set_Event(void *iControl,int evType,int functionref)
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

