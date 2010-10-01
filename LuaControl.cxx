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

//http://efreedom.com/Question/1-1416797/Reference-Lua-Function-C-CPlusPlus
//http://efreedom.com/Question/1-2688040/Callback-Lua-Function-C-Function
// show a message on the SciTE output window
void OutputMessage(lua_State *L)
{
	if (lua_isstring(L,-1)) {
		size_t len;
		const char *msg = lua_tolstring(L,-1,&len);
		char *buff = new char[len+2];
		strncpy(buff,msg,len);
		buff[len] = '\n';
		buff[len+1] = '\0';
		lua_pop(L,1);
		if (lua_checkstack(L,3)) {
			lua_getglobal(L,"output");
			lua_getfield(L,-1,"AddText");
			lua_insert(L,-2);
			lua_pushstring(L,buff);
			lua_pcall(L,2,0,0);
		}
		delete[] buff;
	}
}

bool function_ref(lua_State* L, int idx, int* pr) //get function pointer -- idx=param-number (temporary pointer to function) pr=pointer to int which holds the function-ref
{
	if (*pr != 0) 
	{
		luaL_unref(L,LUA_REGISTRYINDEX,*pr);
	}
	lua_pushvalue(L,idx); //push value on index idx to the top of stack
	*pr = luaL_ref(L,LUA_REGISTRYINDEX); //getting a unique id from function pointer on top of stack which stays active until luaL_unref is called
	return true;
}

void dispatch_ref(lua_State* L,int idx, int ival) //call function ival=param for Lua-Function
{
	if (idx != 0) 
	{
		lua_rawgeti(L,LUA_REGISTRYINDEX,idx);
		lua_pushnumber(L,ival); //param for lua function
		
    int res=lua_pcall(L,1,0,0);
    g_print("lua_pcall-result: %d\n",res);
		if (res != 0) OutputMessage(L);// lua_error(L);
	}
}

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

void LuaControl::SetEvent(int EventID,int ref)
{
  //call function_ref to get pointer and set it to new adress
  removeEvent(EventID);
	//lua_pushvalue(L,idx);
	events[EventID]=ref; //luaL_ref(L,LUA_REGISTRYINDEX);
}

int LuaControl::GetEvent(int EventID)
{
  return events[EventID];
}
/*
void LuaControl::SetControlType(int ct)
{
  ControlType=ct;
}
*/
