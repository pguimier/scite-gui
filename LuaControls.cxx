
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

#include "LuaControls.h"

void free_children(GtkContainer *c)
{
  GList *List = gtk_container_get_children (c);

  for (int i=g_list_length(List)-1;i>=0;i--)
  {
    GtkWidget *w = GTK_WIDGET(g_list_nth( List, i )->data);
    //first get pointer to class
    /*
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
			    g_print("LuaPagecontrol freed...\n");
			  }break;
			}
    }*/
    gtk_widget_destroy(w);
  }
}

void luapagecontrol_destroy(GtkWidget *widget, gpointer user_data)
{
  //free PageControlClass when deleting GUI-Element

  //void *pt=g_object_get_data (G_OBJECT(widget),"ClassPointer");
  g_print("Free LuaPageControl...\n");
  LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(user_data);
  //g_print("user_data: %x, pt: %x\n",int(user_data),int(pt));
  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(pt);
  //g_print("cast ok...now freeing\n");
  delete(PageControl); //Segmentation fault with this-pointer
  g_print("free ok...\n");
}

void luacontrol_destroy(GtkWidget *widget, gpointer user_data)
{
  //free ControlClass when deleting GUI-Element

  //void *pt=g_object_get_data (G_OBJECT(widget),"ClassPointer");
  g_print("Free LuaControl...\n");
  LuaControl *Control=reinterpret_cast<LuaControl*>(user_data);
  //g_print("user_data: %x, pt: %x\n",int(user_data),int(pt));
  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(pt);
  //g_print("cast ok...now freeing\n");
  delete(Control); //Segmentation fault with this-pointer
  g_print("free ok...\n");
}

LuaPageControl::LuaPageControl(lua_State *l,GtkWidget *parent)
  :LuaControl(l), CPageControl(parent)
{
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  SetControlType(lcPageControl);
  //g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luapagecontrol_destroy), this);
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

LuaListView::LuaListView(lua_State *l,GtkWidget *parent)
  :LuaControl(l), CListView(parent)
{
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  SetControlType(lcListView);
  //g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luapagecontrol_destroy), this);
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}
/*
LuaSplitter::LuaSplitter(lua_State *l,GtkWidget *parent,bool vertical)
  :LuaControl(l), CSplitter(parent,vertical)
{
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  SetControlType(lcSplitter);
  //g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luapagecontrol_destroy), this);
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

LuaButton::LuaButton(lua_State *l,GtkWidget *parent,const char *caption)
  :LuaControl(l), CButton(parent,caption)
{
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  SetControlType(lcButton);
  //g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luapagecontrol_destroy), this);
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}
*/
