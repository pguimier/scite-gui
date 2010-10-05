#ifndef LUACONTROL_H
#define LUACONTROL_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

#include "Control.h"

enum
{
	evClick=0,//without parameter
	evDoubleClick,//parameter: new index
	evChange,//used for Pagecontrol-switch; new index
	evMouseDown,//parameters: mouse-button and position
	evMouseUp,//parameters: mouse-button and position
	
	evMax
};

bool function_ref(lua_State* L, int idx, int* pr); //get function pointer -- idx=param-number pr=pointer to int which holds the function-ref
void dispatch_ref(lua_State* L,int idx, int ival); //call function

class LuaControl
{
  protected:
    lua_State* L;
    int events[evMax];//array for holding lua-function-pointer
    //int ControlType;
  public:
    LuaControl(lua_State *l);
    virtual ~LuaControl();
    void removeEvent(int EventID);
    void SetEvent(int EventID,int ref);
    int GetEvent(int EventID);
    lua_State *GetLuaState(){return L;};
    //void SetControlType(int ct);
    //int GetControlType() {return ControlType;}
};
#endif

