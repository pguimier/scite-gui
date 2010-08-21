#define LUA_CORE

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

#include "LuaControl.h"

/*
class LuaControl
{
protected:
	lua_State* L;
	int events[evMax];//array for holding lua-function-pointer
public:
	LuaControl(lua_State *l): L(l) 
	{
	  for (int i=0;i<evMax;i++) {events[i]=0;}
	}
	~LuaControl()
	{
	  for (int i=0;i<evMax;i++) {removeEvent(i);}//free memory of all events
	}
	void removeEvent(int EventID)
	{
	  if (events[EventID]!=0) 
	  {
	    luaL_unref(L,LUA_REGISTRYINDEX,events[EventID]);
	    events[EventID]=0;
	  }
	}
	void setEvent(int EventID,int idx)
	{
	  //call function_ref to get pointer and set it to new adress
	  removeEvent(EventID);
		lua_pushvalue(L,idx);
		events[EventID]= luaL_ref(L,LUA_REGISTRYINDEX);
	}
};
*/
LuaControl::LuaControl(lua_State *l): L(l)
{
  for (int i=0;i<evMax;i++) {events[i]=0;}
}

LuaControl::~LuaControl()
{
  for (int i=0;i<evMax;i++) {removeEvent(i);}//free memory of all events
}

void LuaControl::removeEvent(int EventID)
{
  if (events[EventID]!=0) 
  {
    luaL_unref(L,LUA_REGISTRYINDEX,events[EventID]);
    events[EventID]=0;
  }
}

void LuaControl::setEvent(int EventID,int idx)
{
  //call function_ref to get pointer and set it to new adress
  removeEvent(EventID);
	lua_pushvalue(L,idx);
	events[EventID]= luaL_ref(L,LUA_REGISTRYINDEX);
}

