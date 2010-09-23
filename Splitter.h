#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CSplitter:public GtkControl
{
  private:
    //GtkWidget *Paned;
    void setPanedProperties(GtkWidget *child,bool resize,bool shrink);
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CSplitter(GtkWidget *parent,bool vertical);
    ~CSplitter();
    void SetClients(GtkWidget *Child1,GtkWidget *Child2);
    void SetStaticChild(int c);
    void SetSplitterPosition(int p,bool SecondChild=false);
    /*
    void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
    */
};
