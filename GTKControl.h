#ifndef GTK_CONTROL_H
#define GTK_CONTROL_H


#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

#include "Control.h"

GtkWidget* GetItemFromContainer(GtkContainer *c,int p);
int GetIndexFromContainer(GtkContainer *c,GtkWidget *item);

class GtkControl:public CControl
{
  private:
    GtkWidget *widget;
    int fWidth;
    int fHeight;
  protected:
  public:
    GtkControl();
    virtual ~GtkControl();
    void SetWidget(GtkWidget *w);
    GtkWidget *GetWidget() {return widget;};
    void SetParent(GtkWidget *Parent);
    void CheckSize(int width,int height);
    void OnResize(int width,int height);
};
#endif
