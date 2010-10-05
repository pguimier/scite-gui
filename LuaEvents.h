#ifndef LUA_EVENTS_H
#define LUA_EVENTS_H
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "LuaControls.h"
#include "LuaObjects.h"

int get_function_ref(lua_State *L);
int Set_Event(void *iControl,int evType,int functionref);

#endif
