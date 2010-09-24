#include <gtk/gtk.h>

#include "Container.h"

CWindow::CWindow(const char*caption)
{
  GtkWidget *Window=gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  //gtk_widget_show(Button);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Button),"ClassPointer",this);
  //g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), this);
  
  SetWidget(Window);
  //SetParent(parent);
}

CWindow::~CWindow()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CWindow::AddControl(GtkWidget *c)
{
  gtk_container_add(GTK_CONTAINER(GetWidget()),c);
}

//================ CBox ======================
CBox::CBox(GtkWidget *parent,bool vertical)
{
  GtkWidget *Box;
  
  if (vertical)
    Box=gtk_vbox_new(true,2);
  else
    Box=gtk_hbox_new(true,2);
  
  //gtk_widget_show(Button);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Button),"ClassPointer",this);
  //g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Box);
  SetParent(parent);
}

CBox::~CBox()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CBox::AddControl(GtkWidget *c)
{
  gtk_box_pack_start(GTK_BOX(GetWidget()),c, TRUE, TRUE, 0);
}