#include <gtk/gtk.h>

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CPageControl
{
  private:
    GtkWidget *PageControl;
  protected:
  public:
    CPageControl(GtkWidget *parent);
    ~CPageControl();
    GtkWidget *AddPage(const char *caption,int position=-1);
    void RemovePage(int page_num);
    GtkWidget *GetPage(int page_num);
    GtkWidget *GetWidget();
    int GetPageCount();

    void OnPageSwitch(int page_num);
};
