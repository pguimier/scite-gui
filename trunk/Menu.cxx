#include <gtk/gtk.h>

#include "Menu.h"

void menuitem_clicked(GtkWidget *menuitem, gpointer   user_data)
{
  CPopupMenu *m=(CPopupMenu*)user_data;
  int Key=int(g_object_get_data (G_OBJECT(m->GetWidget()),"ID"));
  m->OnClick(menuitem,Key);
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

CPopupMenu::CPopupMenu(GtkWidget *parent)
{
  GtkWidget *Menu=gtk_menu_new();

  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Menu),"ClassPointer",this);
  //g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Menu);
  //SetParent(parent);
  //http://library.gnome.org/devel/gtk/stable/gtk-migrating-checklist.html#checklist-popup-menu
  gtk_menu_attach_to_widget (GTK_MENU (Menu), parent, NULL);
}

CPopupMenu::~CPopupMenu()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CPopupMenu::AddMenuItem(const char*caption,int ID)
{
  //gtk_widget_set_sensitive(menuitem_edit, FALSE); //disable
  GtkWidget *menuitem;
  if (strcmp(caption,""))
  {
    menuitem=gtk_separator_menu_item_new();
  } else
  {
    menuitem=gtk_menu_item_new_with_label(caption);
    g_object_set_data(G_OBJECT(menuitem),"ID",gpointer(ID));
    g_signal_connect_swapped(G_OBJECT(menuitem),"activate",G_CALLBACK(menuitem_clicked),this);
  }
  gtk_menu_shell_append(GTK_MENU_SHELL(GetWidget()),menuitem);
  gtk_widget_show (menuitem);
}

void CPopupMenu::OnClick(GtkWidget *Menuitem,int ID)
{
  g_print("button clicked\n");
}