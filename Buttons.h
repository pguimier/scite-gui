#include <gtk/gtk.h>

#include "GTKControl.h"

//http://library.gnome.org/devel/gtk/unstable/GtkNotebook.html
class CButton:public GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
    virtual GtkWidget *CreateButtonWidget(const char*caption);
  public:
    CButton(GtkWidget *parent,const char*caption);
    virtual ~CButton();
    void SetCaption(const char*caption);

    void OnClick();
};

class CCheckBox:public CButton//GtkControl
{
  private:
    //GtkWidget *Button;
  protected:
    //virtual void SetWidget(GtkWidget *w);
    virtual GtkWidget *CreateButtonWidget(const char*caption);
  public:
    CCheckBox(GtkWidget *parent,const char*caption);
    virtual ~CCheckBox();
    //void SetCaption(const char*caption); //derived from CButton
    bool GetChecked();
    void SetChecked(bool checked);
    //void OnClick();
};

class CRadioGroup:public GtkControl
{
  private:
    GtkWidget *GroupMaster;
    int radiocount;
    int selectedindex;
  protected:
    //virtual void SetWidget(GtkWidget *w);
  public:
    CRadioGroup(GtkWidget *parent,const char*caption_of_first);
    virtual ~CRadioGroup();
    //void SetCaption(const char*caption); //derived from CButton
    void AddRadio(const char* caption);
    int GetChecked();
    void SetChecked(int checked);
    void CheckSelected();
    void OnChange();
};
