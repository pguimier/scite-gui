#include <gtk/gtk.h>

#include "Menu.h"

void menuitem_clicked(gpointer user_data,GtkWidget *menuitem)
{
//  g_print("menuitem: %x, User_data: %x\n",int(menuitem),int(user_data));
  CPopupMenu *m=(CPopupMenu*)user_data;
//  g_print("casting %x to CPopupmenu done,call m->GetWidget\n",int(user_data));
  int Key=int(g_object_get_data (G_OBJECT(menuitem),"ID"));
//  g_print("call OnCLick\n");
  m->OnClick(menuitem,Key);
}

gboolean view_menu(GtkWidget *wid,GdkEventButton *event,GtkWidget *menu)
{
  if((event->button == 3) && (event->type == GDK_BUTTON_PRESS))
  {
    gtk_menu_popup(GTK_MENU(menu),NULL,NULL,NULL,NULL,event->button,event->time);
    return TRUE;
  }
  return FALSE;
} 

CPopupMenu::CPopupMenu(GtkWidget *parent)
{
  GtkWidget *Menu=gtk_menu_new();

  SetWidget(Menu);
  //http://library.gnome.org/devel/gtk/stable/gtk-migrating-checklist.html#checklist-popup-menu
  gtk_menu_attach_to_widget (GTK_MENU (Menu), parent, NULL);
  g_signal_connect(G_OBJECT(parent),"button-press-event",G_CALLBACK(view_menu),(gpointer)Menu);
}

CPopupMenu::~CPopupMenu()
{
}

void CPopupMenu::AddMenuItem(const char*caption,int ID)
{
  //gtk_widget_set_sensitive(menuitem_edit, FALSE); //disable
  GtkWidget *menuitem;
  if (!strcmp(caption,""))
  {
    menuitem=gtk_separator_menu_item_new();
  } else
  {
    menuitem=gtk_menu_item_new_with_label(caption);
    g_object_set_data(G_OBJECT(menuitem),"ID",gpointer(ID));
    g_object_set_data(G_OBJECT(menuitem),"Class",this);
//    g_print("CPopupMenu-ClassPointer (this): %x\n",int(this));
    g_signal_connect_swapped(G_OBJECT(menuitem),"activate",G_CALLBACK(menuitem_clicked),this);
  }
  gtk_menu_shell_append(GTK_MENU_SHELL(GetWidget()),menuitem);
  gtk_widget_show (menuitem);
}

void CPopupMenu::OnClick(GtkWidget *Menuitem,int ID)
{
  g_print("Menuitem (%x) clicked\n",ID);
}

