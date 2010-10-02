#include <gtk/gtk.h>

#include "TextControls.h"
/*
void button_clicked(GtkWidget *button, gpointer   user_data)
{
  CButton *b=(CButton*)user_data;
  b->OnClick();
}
*/
CEdit::CEdit(GtkWidget *parent,const char* label)
{
  GtkWidget *hBox=gtk_hbox_new(false,2);
  GtkWidget *lbl=gtk_label_new(label);
  gtk_widget_show(lbl);
  GtkWidget *Edit=gtk_entry_new();
  gtk_widget_show(Edit);
  gtk_box_pack_start(GTK_BOX(hBox),lbl,true,true,1);
  gtk_box_pack_end(GTK_BOX(hBox),Edit,true,true,1);
  //gtk_widget_set_usize(hBox,-1,50);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Edit),"ClassPointer",this);
  //g_signal_connect(Edit, "clicked", (GCallback) button_clicked, this);
  
  
  
  SetWidget(hBox);
  SetParent(parent);
}

CEdit::~CEdit()
{

}

void CEdit::SetText(const char* text)
{
  GtkWidget *Edit=GetItemFromContainer(GTK_CONTAINER(GetWidget()),1);
  gtk_entry_set_text(GTK_ENTRY(Edit), text);
}

const char* CEdit::GetText()
{
  GtkWidget *Edit=GetItemFromContainer(GTK_CONTAINER(GetWidget()),1);
  return gtk_entry_get_text(GTK_ENTRY(Edit));
}


CMemo::CMemo(GtkWidget *parent)
{
  GtkWidget *Memo= gtk_text_view_new ();
  
  GtkWidget *ScrollBox=gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(ScrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(ScrollBox),Memo);
  gtk_widget_show(ScrollBox);
  gtk_widget_show(Memo);
  
  SetWidget(ScrollBox);
  SetParent(parent);
  //gtk_widget_set_size_request (Memo,-1,200);
}

CMemo::~CMemo()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}
