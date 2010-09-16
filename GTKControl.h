extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

class GtkControl
{
  private:
    GtkWidget *widget;
  protected:
    virtual void SetWidget(GtkWidget *w);
  public:
    GtkControl();
    ~GtkControl();
    //virtual GtkWidget *GetWidget()={0};
    GtkWidget *GetWidget() {return widget;};
};
