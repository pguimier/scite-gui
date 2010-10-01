#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CListView:public GtkControl
{
  private:
    GtkListStore *store;
    int fColCount;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CListView(GtkWidget *parent/*,int cols=1*/);
    virtual ~CListView();
    bool SetValue(int row,int col,const char *value);
    GtkTreeIter AddItem(const char *caption);
    int GetRowFromIter(GtkTreeIter &iter);
    int AddColumn(const char *caption);
    virtual void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
};
