#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CButton:public GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    virtual void SetWidget(GtkWidget *w);
  public:
    CButton(GtkWidget *parent,const char*caption);
    virtual ~CButton();
    void SetCaption(const char*caption);

    void OnClick();
};
