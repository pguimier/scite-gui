#include "LuaControl.h"
#include "PageControl.h"

void free_children(GtkContainer *c);

enum ControlTypes
{
  Type_LuaPageControl=1
};

class LuaPageControl:public LuaControl,public CPageControl
{
  private:
  
  protected:
  
  public:
    LuaPageControl(lua_State *l,GtkWidget *parent);
    ~LuaPageControl() {};
};
