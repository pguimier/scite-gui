#ifndef LUAOBJECTS_H
#define LUAOBJECTS_H
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "Control.h"

struct LuaClass
{
  CControl *Ctl;
  int CT;
};


void RegisterClass(lua_State *L,const char *name,const char *table,const luaL_reg *object_struct,const luaL_reg *method_struct);
int PushObject(lua_State* L,CControl *c);

#endif
