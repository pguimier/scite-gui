#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CWindow:public GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CWindow(const char*caption);
    virtual ~CWindow();
    void AddControl(GtkWidget *c);
};

class CBox:public GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CBox(GtkWidget *parent,bool vertical);
    virtual ~CBox();
    void AddControl(GtkWidget *c);
};

