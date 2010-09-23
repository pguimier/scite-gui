#include <gtk/gtk.h>

#include "TextControls.h"
/*
void button_clicked(GtkWidget *button, gpointer   user_data)
{
  CButton *b=(CButton*)user_data;
  b->OnClick();
}
*/
CEdit::CEdit(GtkWidget *parent)
{
  GtkWidget *Edit=gtk_entry_new();
  
  //gtk_widget_show(Edit);

  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Edit),"ClassPointer",this);
  //g_signal_connect(Edit, "clicked", (GCallback) button_clicked, this);
  
  SetWidget(Edit);
  SetParent(parent);
}

CEdit::~CEdit()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CEdit::SetText(const char* text)
{
  gtk_entry_set_text(GTK_ENTRY(GetWidget()), text);
}

const char* CEdit::GetText()
{
  return gtk_entry_get_text(GTK_ENTRY(GetWidget()));
}

/*
void CButton::OnClick()
{
  g_print("button clicked\n");
}
*/

CMemo::CMemo(GtkWidget *parent)
{
  GtkWidget *Memo= gtk_text_view_new ();
  SetWidget(Memo);
  SetParent(parent);
}

CMemo::~CMemo()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}