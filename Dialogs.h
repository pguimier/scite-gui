#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/stable/GtkFileChooserDialog.html

class CFileOpenDialog:public GtkControl
{
  private:
    char *filename;
  protected:
    //virtual void SetWidget(GtkWidget *w);
    virtual GtkWidget *CreateDialog(GtkWidget *parent,const char *title);
    //virtual void SetFileName(const char *f);
  public:
    CFileOpenDialog(GtkWidget *parent,const char *title);
    virtual ~CFileOpenDialog();
    virtual int RunDialog();
    char *GetFileName();
    virtual void SetFileName(const char *f);

    //void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);

}; 

class CFileSaveDialog:public CFileOpenDialog
{
  private:
    
  protected:
    //virtual void SetWidget(GtkWidget *w);
    virtual GtkWidget *CreateDialog(GtkWidget *parent,const char *title);
  public:
    CFileSaveDialog(GtkWidget *parent,const char *title);
    virtual ~CFileSaveDialog();
    //virtual void SetFileName(const char *f);

    //void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);

}; 

GtkResponseType message_dialog(GtkWindow *parent, const gchar *title, const gchar *message, GtkMessageType type);

/*
//GtkMessageType:
GTK_MESSAGE_INFO
GTK_MESSAGE_QUESTION,
GTK_MESSAGE_ERROR
GTK_MESSAGE_WARNING

GTK_BUTTONS_YES_NO
GTK_BUTTONS_OK

//GtkResponseType:
 -11	RESPONSE_HELP	 Returned by Help buttons in GTK+ dialogs.
 -10	RESPONSE_APPLY	Returned by Apply buttons in GTK+ dialogs.
 -9	RESPONSE_NO	Returned by No buttons in GTK+ dialogs.
 -8	RESPONSE_YES	Returned by Yes buttons in GTK+ dialogs.
 -7	RESPONSE_CLOSE	Returned by Close buttons in GTK+ dialogs.
 -6	RESPONSE_CANCEL	Returned by Cancel buttons in GTK+ dialogs.
 -5	RESPONSE_OK	Returned by OK buttons in GTK+ dialogs.
 -4	RESPONSE_DELETE_EVENT	Returned if the dialog is deleted. 
 -3	RESPONSE_ACCEPT	 Generic response id, not used by GTK+ dialogs.
 -2	RESPONSE_REJECT	Generic response id, not used by GTK+ dialogs.
 -1	RESPONSE_NONE	Returned if an action widget has no response id, or if the dialog gets programmatically hidden or destroyed. 
 
example:
const gchar *text="Testmessage";
message_dialog(GTK_WINDOW(gtk_widget_get_toplevel(item)),"Info",text,GTK_MESSAGE_INFO);

*/

