#include <gtk/gtk.h>

#include "Dialogs.h"
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

*/

GtkWidget *CFileOpenDialog::CreateDialog(GtkWidget *parent,const char *title)
{
  return gtk_file_chooser_dialog_new (title, GTK_WINDOW(parent), GTK_FILE_CHOOSER_ACTION_OPEN,
            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
            GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
            NULL);
}

CFileOpenDialog::CFileOpenDialog(GtkWidget *parent,const char *title)
{
  GtkWidget *dialog = CreateDialog(parent,title);

  SetWidget(dialog);
}

CFileOpenDialog::~CFileOpenDialog()
{
  g_free (filename);
  gtk_widget_destroy (GetWidget());
}

int CFileOpenDialog::RunDialog()
{
  return (gtk_dialog_run (GTK_DIALOG (GetWidget())));
}

void CFileOpenDialog::SetFileName(const char *f)
{
  gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (GetWidget()), f);
}

char *CFileOpenDialog::GetFileName()
{
  filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (GetWidget()));
  return filename;
}

/*
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

*/

GtkWidget *CFileSaveDialog::CreateDialog(GtkWidget *parent,const char *title)
{
  return gtk_file_chooser_dialog_new (title, GTK_WINDOW(parent), GTK_FILE_CHOOSER_ACTION_SAVE,
            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
            GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
            NULL);
}

CFileSaveDialog::CFileSaveDialog(GtkWidget *parent,const char *title)
:CFileOpenDialog(parent,title)
{
//  GtkWidget *dialog = CreateDialog(parent,title);
//  SetWidget(dialog);
}

CFileSaveDialog::~CFileSaveDialog()
{
  //filename and dialog are freed in CFileOpenDialog
}

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

