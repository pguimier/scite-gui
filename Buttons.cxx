#include <gtk/gtk.h>

#include "Buttons.h"

void button_clicked(GtkWidget *button, gpointer   user_data)
{
  CButton *b=(CButton*)user_data;
  b->OnClick();
}

GtkWidget *CButton::CreateButtonWidget(const char*caption)
{
  return gtk_button_new_with_label (caption);
}

CButton::CButton(GtkWidget *parent,const char*caption)
{
  GtkWidget *Button=CreateButtonWidget(caption);
  
  //gtk_widget_show(Button);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Button),"ClassPointer",this);
  g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Button);
  SetParent(parent);
}

CButton::~CButton()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CButton::SetCaption(const char*caption)
{
  gtk_button_set_label(GTK_BUTTON(GetWidget()), caption);
}

void CButton::OnClick()
{
  g_print("button clicked\n");
}

//Checkbox
GtkWidget *CCheckBox::CreateButtonWidget(const char*caption)
{
  return gtk_check_button_new_with_label (caption);
}

CCheckBox::CCheckBox(GtkWidget *parent,const char*caption)
  :CButton(parent,caption)
{/*
  GtkWidget *Checkbox=gtk_check_button_new_with_label (caption);
  
  //gtk_widget_show(Checkbox);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Checkbox),"ClassPointer",this);
  //g_signal_connect(Checkbox, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Checkbox);
  SetParent(parent);*/
}

CCheckBox::~CCheckBox()
{
}

bool CCheckBox::GetChecked()
{
  return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(GetWidget()));
}

void CCheckBox::SetChecked(bool checked)
{
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(GetWidget()),checked);
}

//Radiogroup
CRadioGroup::CRadioGroup(GtkWidget *parent,const char*caption_of_first)
{
  GtkWidget *Radiogroup=gtk_vbox_new(true,2); 
  GroupMaster=gtk_radio_button_new_with_label_from_widget(NULL, caption_of_first);
  gtk_container_add(GTK_CONTAINER(Radiogroup), GroupMaster);
  //gtk_widget_show(Radiogroup);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Radiogroup),"ClassPointer",this);
  //g_signal_connect(Checkbox, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Radiogroup);
  SetParent(parent);
}

CRadioGroup::~CRadioGroup()
{

}

int CRadioGroup::GetChecked()
{
  //return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(GetWidget()));
  GList *List = gtk_container_get_children (GTK_CONTAINER(GetWidget()));

  int l=g_list_length(List);
  GtkWidget *w;
  for (int i=0; i<l;i++)
  {
    w = GTK_WIDGET(g_list_nth( List, i )->data);
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(w))) return i;
  };
  return -1;
}

void CRadioGroup::SetChecked(int checked)
{
  //gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(GetWidget()),checked);
  GtkWidget *r=GetItemFromContainer(GTK_CONTAINER(GetWidget()),checked);
  if (r) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(GetWidget()),true);
}

void CRadioGroup::AddRadio(const char* caption)
{
  GtkWidget *radio=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(GroupMaster), caption);
  gtk_container_add(GTK_CONTAINER(GetWidget()), radio); 
}
