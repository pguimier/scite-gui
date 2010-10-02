#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CPageControl:public GtkControl
{
  private:
  protected:
    //void SetWidget(GtkWidget *w);
  public:
    CPageControl(GtkWidget *parent);
    virtual ~CPageControl();
    GtkWidget *AddPage(const char *caption,int position=-1);
    void RemovePage(int page_num);
    GtkWidget *GetPage(int page_num);
    //GtkWidget *GetWidget();
    int GetPageCount();

    virtual void OnPageSwitch(int page_num);
};
