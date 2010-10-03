#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/stable/GtkEntry.html
class CEdit:public GtkControl
{
  private:
  protected:
    GtkWidget *GetEdit();
  public:
    CEdit(GtkWidget *parent,const char* label);
    virtual ~CEdit();
    void SetText(const char* text);
    const char* GetText();
    //void OnClick();
};

//http://library.gnome.org/devel/gtk/stable/TextWidget.html
//http://www.bravegnu.org/gtktext/index.htm
class CMemo:public GtkControl
{
  private:

  protected:
    GtkWidget *GetMemo();
  public:
    CMemo(GtkWidget *parent);
    virtual ~CMemo();
    void SetText(const char *Text);
    char *GetText();
    // void SetText(const char* text);
    // const char* GetText();
    //void OnClick();
};
