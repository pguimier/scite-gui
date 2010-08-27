
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

#include "LuaControls.h"

gboolean luapagecontrol_destroy(GtkWidget *widget,GdkEvent  *event, gpointer user_data)
{
  //free PageControlClass when deleting UI - not run yet :(
//  g_print("Free LuaPageControl...\n");
//  LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(user_data);
//  delete(PageControl);
}

LuaPageControl::LuaPageControl(lua_State *l,GtkWidget *parent)
  :LuaControl(l), CPageControl(parent)
{
  g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luapagecontrol_destroy), this);
}


void free_children(GtkContainer *c)
{
  GList *List = gtk_container_get_children (c);

  for (int i=g_list_length(List)-1;i>=0;i--)
  {
    GtkWidget *w = GTK_WIDGET(g_list_nth( List, i )->data);
    //first get pointer to class
    void *pt=g_object_get_data (G_OBJECT(w),"ClassPointer");
    if (pt) 
    {
      g_print("pointer set ;)\n");
      int control_type=int(g_object_get_data (G_OBJECT(w),"ClassType"));
      switch (control_type)
      {
        case Type_LuaPageControl:
        {
          g_print("free LuaPagecontrol\n");
			    LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(pt);
			    delete(PageControl);
			  }break;
			}
    }
    gtk_widget_destroy(w);
  }
}

