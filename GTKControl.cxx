#include <gtk/gtk.h>

#include "GTKControl.h"

void my_getsize(GtkWidget *widget, GtkAllocation *allocation, void *data) {
    printf("width = %d, height = %d\n", allocation->width, allocation->height);
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
GtkControl::GtkControl()
{

}

GtkControl::~GtkControl()
{

}

void GtkControl::SetWidget(GtkWidget *w)
{
  widget=w;
  g_signal_connect(widget, "size-allocate", G_CALLBACK(my_getsize), this);
}
