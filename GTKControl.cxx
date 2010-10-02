#include <gtk/gtk.h>

#include "GTKControl.h"

GtkWidget* GetItemFromContainer(GtkContainer *c,int p)
{
  GtkWidget *res=0;
  GList *List = gtk_container_get_children (c);

  int l=g_list_length(List);
  if (p>=0 && p<l)
  {
    res = GTK_WIDGET(g_list_nth( List, p )->data);
  } else g_print("invalid index");
  return res;
}

int GetIndexFromContainer(GtkContainer *c,GtkWidget *item)
{
  GList *List = gtk_container_get_children (c);
  int i=-1;
  int l=g_list_length(List);
  for (int p=0;p<l;p++)
  {
    if (GTK_WIDGET(g_list_nth( List, p )->data) == item) i=p;
  }
  return i;
}

void my_getsize(GtkWidget *widget, GtkAllocation *allocation, void *user_data) 
{
    GtkControl *gc=(GtkControl*)user_data;
    //gc->OnResize(allocation->width, allocation->height);
    gc->CheckSize(allocation->width, allocation->height); //check first if size has really changed
    //printf("width = %d, height = %d\n", allocation->width, allocation->height);
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
  if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    gtk_widget_destroy(GetWidget());
}

void GtkControl::SetWidget(GtkWidget *w)
{
  widget=w;
  g_object_set_data(G_OBJECT(widget),"ClassPointer",this);
  g_signal_connect(widget, "size-allocate", G_CALLBACK(my_getsize), this);
  gtk_widget_show(widget); //maybe this should not be done for menu-widget
}

void GtkControl::SetParent(GtkWidget *parent)
{
  if (parent)
  {
    if (GTK_IS_BOX(parent))
    {
      //g_print("box-parent (%x)\n",int(parent));
      gtk_box_pack_start(GTK_BOX(parent),widget, TRUE, TRUE, 0);
    }else if (GTK_IS_CONTAINER(parent))
    {
      //g_print("container-parent (%x)\n",int(parent));
      gtk_container_add(GTK_CONTAINER(parent),widget);
    }else g_print("unknown parent");
  }
}

void GtkControl::CheckSize(int width,int height)
{
  //int wc=int(g_object_get_data (G_OBJECT(widget),"WindowClass"));

  //g_print("[%d] Width: %d, Height: %d\n",wc,width,height);
  if ((width!=fWidth)||(height!=fHeight))
  {
    fWidth=width;
    fHeight=height;
    OnResize(width,height);
  }
}

void GtkControl::OnResize(int width,int height)
{
  int wc=int(g_object_get_data (G_OBJECT(widget),"WindowClass"));

  g_print("[%d] Width: %d, Height: %d\n",wc,width,height);
}

