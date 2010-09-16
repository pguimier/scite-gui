#include <gtk/gtk.h>

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CListView
{
  private:
    GtkWidget *ListView;
    GtkListStore *store;
    int fColCount;
  protected:
  public:
    CListView(GtkWidget *parent,int cols=1);
    ~CListView();
    bool SetValue(int row,int col,const char *value);
    GtkTreeIter AddItem(const char *caption);
    int AddColumn(const char *caption);
    void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
};
