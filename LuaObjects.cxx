#include "LuaObjects.h"

void RegisterClass(lua_State *L,const char *name,const char *table,const luaL_reg *object_struct,const luaL_reg *method_struct)
{
    luaL_newmetatable(L, table);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */
    luaL_openlib(L, NULL, method_struct, 0); //first register Methods
    luaL_openlib(L, name, object_struct, 0); //now register object 
}

int PushObject(lua_State* L,CControl *c)
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

