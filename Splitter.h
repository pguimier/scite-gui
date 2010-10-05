#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/stable/GtkPaned.html
class CSplitter:public GtkControl
{
  private:
    void setPanedProperties(GtkWidget *child,bool resize,bool shrink);
  protected:

  public:
    CSplitter(GtkWidget *parent,bool vertical);
    ~CSplitter();
    virtual void SetClients(GtkWidget *Child1,GtkWidget *Child2);
    void SetStaticChild(int c);
    void SetSplitterPosition(int p,bool SecondChild=false);
};
