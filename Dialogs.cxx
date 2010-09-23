#include <gtk/gtk.h>

#include "Dialogs.h"
/*
void PageSwitched (GtkNotebook *notebook, GtkNotebookPage *page, guint page_num, gpointer user_data)
{
  CPageControl *pc=(CPageControl*)user_data;
  pc->OnPageSwitch(page_num);
  //g_print("Page switched to Page #%d\n",page_num);
}
*/

/*
==================== Open =====================
GtkWidget *dialog;
dialog = gtk_file_chooser_dialog_new ("Open File",
				      parent_window,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    open_file (filename);
    g_free (filename);
  }
gtk_widget_destroy (dialog);


// =================== Save ===============
GtkWidget *dialog;
dialog = gtk_file_chooser_dialog_new ("Save File",
				      parent_window,
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				      NULL);
gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
if (user_edited_a_new_document)
  {
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), default_folder_for_saving);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
  }
else
  gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog), filename_for_existing_document);
if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
    save_to_file (filename);
    g_free (filename);
  }
gtk_widget_destroy (dialog);


//==================== Message ============================
GtkResponseType message_dialog(GtkWindow *parent, const gchar *title, const gchar *message, GtkMessageType type)
{
  GtkWidget *dialog;
  GtkResponseType response;
  GtkButtonsType buttons;

  if (type == GTK_MESSAGE_QUESTION) 
    buttons = GTK_BUTTONS_YES_NO;
  else 
    buttons = GTK_BUTTONS_OK;

  dialog = gtk_message_dialog_new (parent, GTK_DIALOG_DESTROY_WITH_PARENT, type, buttons, "%s", message);

  gtk_window_set_title(GTK_WINDOW(dialog), title);

  response = GtkResponseType(gtk_dialog_run (GTK_DIALOG (dialog)));
  gtk_widget_destroy (dialog);   
       
  return response;
}

const gchar *text="Testmessage";
message_dialog(GTK_WINDOW(gtk_widget_get_toplevel(item)),"Info",text,GTK_MESSAGE_INFO);
*/
/*
//GtkMessageType:
GTK_MESSAGE_INFO
GTK_MESSAGE_QUESTION,
GTK_MESSAGE_ERROR
GTK_MESSAGE_WARNING

GTK_BUTTONS_YES_NO
GTK_BUTTONS_OK
*/
/*
CSplitter::CSplitter(GtkWidget *parent,bool vertical)
{
  GtkWidget *Paned;
  if (vertical)
    Paned=gtk_vpaned_new(); 
  else
    Paned=gtk_hpaned_new ();
  
  //g_object_set(Paned,"min-position",10, NULL); //not writable
  //g_signal_connect(ListView, "row-activated", (GCallback) RowActivated, this);
  //gtk_widget_show(Paned);
  //int key=g_object_get_data (G_OBJECT(w),"ClassPointer");
  //g_object_set_data(G_OBJECT(Paned),"ClassPointer",this);
  
  SetWidget(Paned);
  SetParent(parent);
}

CSplitter::~CSplitter()
{
  // if (GTK_IS_WIDGET(GetWidget())) //if control is not freed before (window destroyed)
    // gtk_widget_destroy(GetWidget());
}

void CSplitter::SetClients(GtkWidget *Child1,GtkWidget *Child2)
{
  gtk_paned_add1(GTK_PANED(GetWidget()),Child1);
  gtk_paned_add2(GTK_PANED(GetWidget()),Child2);
}
*/
