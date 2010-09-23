#include <gtk/gtk.h>

#include "Menu.h"

void menuitem_clicked(GtkWidget *menuitem, gpointer   user_data)
{
  CPopupMenu *m=(CPopupMenu*)user_data;
  int Key=int(g_object_get_data (G_OBJECT(w),"ID"));
  m->OnClick(menuitem,key);
}
/*
static void menuitem_activate(GtkWidget *w)
{
  int Key=int(g_object_get_data (G_OBJECT(w),"ID"));
    printf ("%d\n",Key);
    switch (Key)
    {
      case IDM_OPEN:g_print ("open a file\n");
      case IDM_CLOSE:g_print ("exit program\n");
    } 
    if ((Key>=IDM_RECENT) & (Key<IDM_RECENT+IDM_RECENT_MAX))
    {
      g_print ("open recent file\n");
    }
}

*/
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
    
CPopupMenu::CPopupMenu(GtkWidget *parent)
{
  GtkWidget *Menu=gtk_menu_new();

  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  g_object_set_data(G_OBJECT(Menu),"ClassPointer",this);
  //g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Menu);
  SetParent(parent);
}

CPopupMenu::~CPopupMenu()
{
  if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    gtk_widget_destroy(GetWidget());
}

void CPopupMenu::AddMenuItem(const char*caption,int ID)
{
  //gtk_widget_set_sensitive(menuitem_edit, FALSE); //disable
  GtkWidget *menuitem=gtk_menu_item_new_with_label(caption);
  gtk_menu_shell_append(GTK_MENU_SHELL(GetWidget()),menuitem);
  g_signal_connect_swapped(G_OBJECT(menuitem),"activate",G_CALLBACK(menuitem_clicked),this);
  gtk_widget_show (menuitem);
  g_object_set_data(G_OBJECT(menuitem),"ID",gpointer(ID));
}

void CPopupMenu::OnClick(GtkWidget *Menuitem,int ID)
{
  g_print("button clicked\n");
}
