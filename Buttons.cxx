#include <gtk/gtk.h>

#include "Buttons.h"

void button_clicked(GtkWidget *button, gpointer   user_data)
{
  CButton *b=(CButton*)user_data;
  b->OnClick();
}

void radio_toggled(GtkWidget *radio, gpointer   user_data)
{
  CRadioGroup *rg=(CRadioGroup*)user_data;
  rg->CheckSelected();
}

void checkbox_toggled(GtkWidget *checkbox, gpointer   user_data)
{
  CCheckGroup *rg=(CCheckGroup*)user_data;
  rg->OnChange(checkbox);
}

GtkWidget *CButton::CreateButtonWidget(const char*caption)
{
  return gtk_button_new_with_label (caption);
}

CButton::CButton(GtkWidget *parent,const char*caption)
{
  GtkWidget *Button=CreateButtonWidget(caption);

  g_signal_connect(Button, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Button);
  SetParent(parent);
}

CButton::~CButton()
{

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
{
  GtkWidget *Checkbox=gtk_check_button_new_with_label (caption);

  //g_signal_connect(Checkbox, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Checkbox);
  SetParent(parent);
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
  radiocount=0;
  GtkWidget *Radiogroup=gtk_vbox_new(true,2);
  gtk_widget_show(Radiogroup);
  GroupMaster=gtk_radio_button_new_with_label_from_widget(NULL, caption_of_first);
  gtk_container_add(GTK_CONTAINER(Radiogroup), GroupMaster);
  gtk_widget_show(GroupMaster);
  //gtk_widget_show(Radiogroup);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  g_object_set_data(G_OBJECT(Radiogroup),"ClassPointer",this);
  g_object_set_data(G_OBJECT(GroupMaster),"ID",gpointer(radiocount++));
  g_signal_connect(GroupMaster, "toggled", (GCallback) radio_toggled, this);
//  g_print("CRadioGroup set Widget [%x]/Parent [%x]\n",int(Radiogroup),int(parent));
  SetWidget(Radiogroup);
  SetParent(parent);
  //gtk_widget_set_size_request (Radiogroup,0,0);
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
  if (r) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(r),true);
}

void CRadioGroup::AddRadio(const char* caption)
{
  GtkWidget *radio=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(GroupMaster), caption);
  gtk_container_add(GTK_CONTAINER(GetWidget()), radio); 
  g_object_set_data(G_OBJECT(radio),"ID",gpointer(radiocount++));
  g_signal_connect(radio, "toggled", (GCallback) radio_toggled, this);
  gtk_widget_show(radio);
}

void CRadioGroup::CheckSelected()
{
  //g_print("Radiogroup changed [%d]\n",GetChecked());
  if (selectedindex!=GetChecked())
  {
    selectedindex=GetChecked();
    OnChange(selectedindex);
  }
}

void CRadioGroup::OnChange(int selected)
{
  g_print("Radiogroup changed [%d]\n",selected);
}

//Checkgroup
CCheckGroup::CCheckGroup(GtkWidget *parent,const char*caption_of_first)
{
  checkcount=0;
  GtkWidget *Checkgroup=gtk_vbox_new(true,2);
  gtk_widget_show(Checkgroup);
  g_object_set_data(G_OBJECT(Checkgroup),"ClassPointer",this);
  SetWidget(Checkgroup);
  
  AddCheckBox(caption_of_first);
//  g_print("CRadioGroup set Widget [%x]/Parent [%x]\n",int(Radiogroup),int(parent));
  SetParent(parent);
  //gtk_widget_set_size_request (Radiogroup,0,0);
}

CCheckGroup::~CCheckGroup()
{

}

bool CCheckGroup::GetChecked(int index)
{
  //return gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(GetWidget()));

  GList *List = gtk_container_get_children (GTK_CONTAINER(GetWidget()));

  int l=g_list_length(List);
  if (index >=0 && index<l)
  {
    GtkWidget *w;
    w = GTK_WIDGET(g_list_nth( List, index )->data);
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(w))) return index;
  }
  return -1;
}

void CCheckGroup::SetChecked(int index,bool checked)
{
  //gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(GetWidget()),item);
  GtkWidget *r=GetItemFromContainer(GTK_CONTAINER(GetWidget()),index);
  if (r) gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(r),checked);
}

void CCheckGroup::AddCheckBox(const char* caption)
{
  GtkWidget *checkbox=gtk_check_button_new_with_label(caption);
  gtk_container_add(GTK_CONTAINER(GetWidget()), checkbox); 
  g_object_set_data(G_OBJECT(checkbox),"ID",gpointer(checkcount++));
  g_signal_connect(checkbox, "toggled", (GCallback) checkbox_toggled, this);
  gtk_widget_show(checkbox);
}
/*
void CCheckGroup::CheckSelected()
{
  //g_print("Radiogroup changed [%d]\n",GetChecked());
  if (selectedindex!=GetChecked())
  {
    selectedindex=GetChecked();
    OnChange();
  }
}
*/
void CCheckGroup::OnChange(GtkWidget *checkbox)
{
  g_print("Checkgroup changed\n");
}

