
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

GtkWidget *GetWidgetFromWrapPointer(void *p)
{
  WinWrap *wrp=(WinWrap*)p;
  GtkWidget *W=NULL;
  g_print("GetWidgetFromWrapPointer\n");
  switch (wrp->wc)
  {
    case lcPageControl:
    {
      g_print("PageControl\n");
      LuaPageControl *LC=reinterpret_cast<LuaPageControl*>(wrp->window);
      W= LC->GetWidget();
    };break;
    case lcListView:
    {
      g_print("Listview\n");
      LuaListView *LC=reinterpret_cast<LuaListView*>(wrp->window);
      W= LC->GetWidget();
    };break;
    case lcSplitter:
    {
      g_print("Splitter\n");
      LuaSplitter *LC=reinterpret_cast<LuaSplitter*>(wrp->window);
      W= LC->GetWidget();
    };break;
    case lcButton:
    {
      g_print("Button\n");
      LuaButton *LC=reinterpret_cast<LuaButton*>(wrp->window);
      W= LC->GetWidget();
    };break;
  }
  return W;
}

void luacontrol_destroy(GtkWidget *widget, gpointer user_data)
{
  //free ControlClass when deleting GUI-Element
  g_print("Free LuaControl...\n");
  int wc=int(g_object_get_data (G_OBJECT(widget),"WindowClass"));
  switch (wc)
  {
    case lcPageControl: {LuaPageControl *Control=reinterpret_cast<LuaPageControl*>(user_data);delete(Control);}break;
    case lcListView: {LuaListView *Control=reinterpret_cast<LuaListView*>(user_data);delete(Control);}break;
    case lcSplitter: {LuaSplitter *Control=reinterpret_cast<LuaSplitter*>(user_data);delete(Control);}break;
    case lcButton: {LuaButton *Control=reinterpret_cast<LuaButton*>(user_data);delete(Control);}break;
  }
  //g_print("user_data: %x, pt: %x\n",int(user_data),int(pt));
  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(pt);
  //g_print("cast ok...now freeing\n");
  
  g_print("free ok...\n");
}

LuaPageControl::LuaPageControl(lua_State *l,GtkWidget *parent)
  :LuaControl(l), CPageControl(parent)
{
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassPointer",this);
  //g_object_set_data(G_OBJECT(this->GetWidget()),"ClassType",reinterpret_cast<void*>(Type_LuaPageControl));
  g_object_set_data(G_OBJECT(this->GetWidget()),"WindowClass",reinterpret_cast<void*>(lcPageControl)); //for Destroy
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

LuaListView::LuaListView(lua_State *l,GtkWidget *parent)
  :LuaControl(l), CListView(parent)
{
  g_object_set_data(G_OBJECT(this->GetWidget()),"WindowClass",reinterpret_cast<void*>(lcListView)); //for Destroy
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

LuaSplitter::LuaSplitter(lua_State *l,GtkWidget *parent,bool vertical)
  :LuaControl(l), CSplitter(parent,vertical)
{
  g_object_set_data(G_OBJECT(this->GetWidget()),"WindowClass",reinterpret_cast<void*>(lcSplitter)); //for Destroy
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

LuaButton::LuaButton(lua_State *l,GtkWidget *parent,const char *caption)
  :LuaControl(l), CButton(parent,caption)
{
  g_object_set_data(G_OBJECT(this->GetWidget()),"WindowClass",reinterpret_cast<void*>(lcButton)); //for Destroy
  g_signal_connect (this->GetWidget(), "destroy",G_CALLBACK (luacontrol_destroy), this);
}

