#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/stable/GtkTreeView.html
//http://library.gnome.org/devel/gtk/stable/GtkListStore.html

class CListView:public GtkControl
{
  private:
    GtkListStore *store;
    int fColCount;
  protected:

  public:
    CListView(GtkWidget *parent/*,int cols=1*/);
    virtual ~CListView();
    bool SetValue(int row,int col,const char *value);
    void GetText(int row,int col,char** caption);
    virtual GtkTreeIter AddItem(const char *caption);
    int GetRowFromIter(GtkTreeIter &iter);
    int AddColumn(const char *caption);
    void Clear();
    void RemoveRow(int row);
    
    virtual void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
};
