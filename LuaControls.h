#ifndef LUA_CONTROLS_H
#define LUA_CONTROLS_H

#include "LuaControl.h"
#include "PageControl.h"
#include "ListView.h"
#include "Splitter.h"
#include "Buttons.h"
#include "Menu.h"
#include "TextControls.h"
#include "Dialogs.h"
/*
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
*/
//code taken from gui_ext.cpp by Steve Donovan
//extern const char* WINDOW_CLASS = "WINDOW*";
extern const char WINDOW_CLASS[];
/*
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
*/
void free_children(GtkContainer *c);
//GtkWidget *GetWidgetFromWrapPointer(void *p);

enum MessageType
{
  MESSAGE_INFO,
  MESSAGE_WARNING,
  MESSAGE_QUESTION,
  MESSAGE_ERROR
};

int MessageDialog(const char *title, const char *message, MessageType type);

class LuaPageControl:/*public LuaControl,*/public CPageControl
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaPageControl(lua_State *l,int parent);
    virtual ~LuaPageControl() {};
    virtual void OnPageSwitch(int page_num);
};

class LuaListView:/*public LuaControl,*/public CListView
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaListView(lua_State *l,int parent);
    virtual ~LuaListView() {};
    virtual void OnRowActivated(GtkTreePath *path,GtkTreeViewColumn  *col);
    virtual int AddNewItem(const char *caption);
    void GetText(int row,int col);
};

class LuaSplitter:/*public LuaControl,*/public CSplitter
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaSplitter(lua_State *l,int parent,bool vertical);
    virtual ~LuaSplitter() {};
    virtual void SetClients(int Child1,int Child2);
};

class LuaButton:/*public LuaControl,*/public CButton
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaButton(lua_State *l,int parent,const char *caption);
    virtual ~LuaButton() {};
    virtual void OnClick();
};

class LuaPopupMenu:/*public LuaControl,*/public CPopupMenu
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaPopupMenu(lua_State *l,int parent);
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
    LuaRadioGroup(lua_State *l,int parent,const char *caption_of_first);
    virtual ~LuaRadioGroup() {};
    virtual void OnChange(int selected);
};

class LuaCheckGroup:/*public LuaControl,*/public CCheckGroup
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaCheckGroup(lua_State *l,int parent,const char *caption_of_first);
    virtual ~LuaCheckGroup() {};
    virtual void OnChange(GtkWidget *changed_item);
};

class LuaEdit:/*public LuaControl,*/public CEdit
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaEdit(lua_State *l,int parent,const char *label);
    virtual ~LuaEdit() {};
    void GetText();
    //virtual void OnChange(GtkWidget *changed_item);
};

class LuaMemo:/*public LuaControl,*/public CMemo
{
  private:
  
  protected:
  
  public:
    LuaControl Lua;
    LuaMemo(lua_State *l,int parent);
    virtual ~LuaMemo() {};
    void GetText();
    //virtual void OnChange(GtkWidget *changed_item);
};

#endif

