#include <gtk/gtk.h>

#include "Buttons.h"

void button_clicked(GtkButton *button, gpointer   user_data)
{
  CButton *b=(CButton*)user_data;
  b->OnClick();
}

CButton::CButton(GtkWidget *parent,const char*caption)
{
  GtkWidget *Button=gtk_button_new_with_label (caption);
  
  gtk_widget_show(Button);
  /*
  if (GTK_IS_BOX(parent))
  {
    //g_print("box-parent (%x)\n",int(parent));
    gtk_box_pack_start(GTK_BOX(parent),Button, TRUE, TRUE, 0);
  }else if (GTK_IS_CONTAINER(parent))
  {
    //g_print("container-parent (%x)\n",int(parent));
    gtk_container_add(GTK_CONTAINER(parent),Button);
  }else g_print("unknown parent (Button)");
  */
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  g_object_set_data(G_OBJECT(Button),"ClassPointer",this);
  g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Button);
  SetParent(parent);
}

CButton::~CButton()
{
  if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    gtk_widget_destroy(GetWidget());
}

void CButton::SetCaption(const char*caption)
{
  gtk_button_set_label(GTK_BUTTON(GetWidget()), caption);
}

void CButton::OnClick()
{
  g_print("button clicked\n");
}
