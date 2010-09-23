#ifndef GTK_CONTROL_H
#define GTK_CONTROL_H

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>
GtkWidget* GetItemFromContainer(GtkContainer *c,int p);

class GtkControl
{
  private:
    GtkWidget *widget;
  protected:
  public:
    GtkControl();
    virtual ~GtkControl();
    //virtual GtkWidget *GetWidget()={0};
    void SetWidget(GtkWidget *w);
    GtkWidget *GetWidget() {return widget;};
    void SetParent(GtkWidget *Parent);
};
#endif
