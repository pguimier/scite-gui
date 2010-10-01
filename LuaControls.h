#ifndef LUA_CONTROLS_H
#define LUA_CONTROLS_H

#include "LuaControl.h"
#include "PageControl.h"
#include "ListView.h"
#include "Splitter.h"
#include "Buttons.h"
#include "Menu.h"

enum WindowClasses
{
	lcPageControl=0,
  lcListView,
	lcSplitter,
	lcButton,
	lcPopupMenu,
  lcRadioGroup,
  
	lcMax
};

//code taken from gui_ext.cpp by Steve Donovan
//extern const char* WINDOW_CLASS = "WINDOW*";
extern const char WINDOW_CLASS[];

struct WinWrap {
  int wc;
	void *window;
	void *data;
};

static int wrap_window(lua_State* L, void *win, int WindowClass) 
{
	WinWrap *wrp = (WinWrap*)lua_newuserdata(L,sizeof(WinWrap));
	wrp->window = win;
  wrp->wc=WindowClass;
	wrp->data = NULL;
	//luaL_getmetatable(L,WINDOW_CLASS);
//	lua_setmetatable(L,-2);
	return 1;
}

void free_children(GtkContainer *c);
GtkWidget *GetWidgetFromWrapPointer(void *p);

class LuaPageControl:/*public LuaControl,*/public CPageControl
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaPageControl(lua_State *l,GtkWidget *parent);
    virtual ~LuaPageControl() {};
    virtual void OnPageSwitch(int page_num);
};

class LuaListView:/*public LuaControl,*/public CListView
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaListView(lua_State *l,GtkWidget *parent);
    virtual ~LuaListView() {};
    virtual void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
};

class LuaSplitter:/*public LuaControl,*/public CSplitter
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaSplitter(lua_State *l,GtkWidget *parent,bool vertical);
    virtual ~LuaSplitter() {};
};

class LuaButton:/*public LuaControl,*/public CButton
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaButton(lua_State *l,GtkWidget *parent,const char *caption);
    virtual ~LuaButton() {};
};

class LuaPopupMenu:/*public LuaControl,*/public CPopupMenu
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaPopupMenu(lua_State *l,GtkWidget *parent);
    virtual ~LuaPopupMenu() {};
    virtual void AddMenuItem(const char*caption,int ref);
    virtual void OnClick(GtkWidget *Menuitem,int ID);
};

class LuaRadioGroup:/*public LuaControl,*/public CRadioGroup
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaRadioGroup(lua_State *l,GtkWidget *parent,const char *caption_of_first);
    virtual ~LuaRadioGroup() {};
};


#endif
