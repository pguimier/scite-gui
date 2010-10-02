#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/stable/GtkWindow.html
//http://library.gnome.org/devel/gtk/stable/GtkBox.html
class CWindow:public GtkControl
{
  private:

  protected:

  public:
    CWindow(const char*caption);
    virtual ~CWindow();
    void AddControl(GtkWidget *c);
};

class CBox:public GtkControl
{
  private:

  protected:

  public:
    CBox(GtkWidget *parent,bool vertical);
    virtual ~CBox();
    void AddControl(GtkWidget *c);
};

