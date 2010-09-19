#include "LuaControl.h"
#include "PageControl.h"
#include "ListView.h"
//#include "Splitter.h"
//#include "Buttons.h"

void free_children(GtkContainer *c);

// enum ControlTypes
// {
  // Type_LuaPageControl=1
// };

class LuaPageControl:public LuaControl,public CPageControl
{
  private:
  
  protected:
  
  public:
    LuaPageControl(lua_State *l,GtkWidget *parent);
    virtual ~LuaPageControl() {};
};

class LuaListView:public LuaControl,public CListView
{
  private:
  
  protected:
  
  public:
    LuaListView(lua_State *l,GtkWidget *parent);
    virtual ~LuaListView() {};
};
/*
class LuaSplitter:public LuaControl,public CSplitter
{
  private:
  
  protected:
  
  public:
    LuaSplitter(lua_State *l,GtkWidget *parent,bool vertical);
    virtual ~LuaSplitter() {};
};

class LuaButton:public LuaControl,public CButton
{
  private:
  
  protected:
  
  public:
    LuaButton(lua_State *l,GtkWidget *parent,const char *caption);
    virtual ~LuaButton() {};
};
*/
