#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CEdit:public GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CEdit(GtkWidget *parent);
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
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CMemo(GtkWidget *parent);
    virtual ~CMemo();
    // void SetText(const char* text);
    // const char* GetText();
    //void OnClick();
};
