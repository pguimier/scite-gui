/*

*/

#define LUA_CORE

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

//#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>

void *SidebarHandle=NULL;

#include "LuaControls.h"
#include "LuaEvents.h"
#include "LuaObjects.h"

int GetControlFromLuaPtr(void *LuaPointer)
{
  LuaClass *lc=reinterpret_cast<LuaClass*>(LuaPointer);
  CControl *Ctl=reinterpret_cast<CControl*>(lc->Ctl);
  return Ctl->GetControl();
}

static int do_InitSidebar(lua_State *L) //gui.InitSidebar(scite.GetSidebarHandle())
{
  if (SidebarHandle)
    free_children(GTK_CONTAINER(SidebarHandle));
  SidebarHandle=lua_touserdata(L,1);

  return 1;
}

//creating controls
static int do_CreatePageControl(lua_State *L) //pagecontrol=PageControl.new(parent) --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  
//  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaPageControl *PageControl=new LuaPageControl(L,iParent);
  //lua_pushlightuserdata(L,PageControl);//put pointer of Pagecontrol to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,PageControl);
}

static int do_CreateListView(lua_State *L) //lv=ListView.new(parent) --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  
//  g_print("Adding Listview to Parent 0x%x...\n",int(iParent));

  LuaListView *Listview=new LuaListView(L,iParent);
//  g_print("Listview-Widget: %x\n",int(Listview->GetWidget()));
  //lua_pushlightuserdata(L,Listview);//put pointer of Listview to stack
  return PushObject(L,Listview);
  //return 1;//return 1 value (handle)
}

static int do_CreateSplitter(lua_State *L) //spl=Splitter.new(parent,bool vertical) --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  bool vertical=lua_toboolean(L,2);
  
//  g_print("Adding Pagecontrol to Parent 0x%x...\n",int(iParent));

  LuaSplitter *Splitter=new LuaSplitter(L,iParent,vertical);
  //lua_pushlightuserdata(L,Splitter); //put pointer of Splitter to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Splitter);
}

static int do_CreateButton(lua_State *L) //btn=Button.new(parent,"caption") --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  const char *caption=luaL_checkstring(L,2);
  
//  g_print("Adding Button to Parent 0x%x...\n",int(iParent));

  LuaButton *Button=new LuaButton(L,iParent,caption);
  
  //lua_pushlightuserdata(L,Button); //put pointer of Button to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Button);
}

static int do_CreatePopup(lua_State *L) //popup=Popup.new(parent)
{
  void *iParent=lua_touserdata(L,1);
//  GtkWidget *P=reinterpret_cast<GtkControl*>(iParent)->GetWidget();
  //LuaClass *lc=reinterpret_cast<LuaClass*>(iParent);
  //GtkControl *Control=reinterpret_cast<GtkControl*>(lc->Ctl);
  //int P=int(Control->GetWidget());
  //CControl *Ctl=reinterpret_cast<CControl*>(lc->Ctl);
  //int P=int(Ctl->GetControl());
  int P=GetControlFromLuaPtr(iParent);
  
//  g_print("Adding Popup to Parent 0x%x...\n",int(P));

  LuaPopupMenu *Popup=new LuaPopupMenu(L,P);
  
//  g_print("Popup-Widget: %x\n",int(Popup->GetWidget()));
  //lua_pushlightuserdata(L,Popup); //put pointer of Popup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Popup);
}

static int do_CreateRadioGroup(lua_State *L) //rg=RadioGroup.new(parent,"caption") --parent can be 0
{
  int iParent=int (lua_touserdata(L,1));
  const char *caption=luaL_checkstring(L,2);
  
//  g_print("Adding RadioGroup to Parent 0x%x...\n",int(iParent));

  LuaRadioGroup *Radiogroup=new LuaRadioGroup(L,iParent,caption);
  
//  g_print("RadioGroup-Widget: %x\n",int(Radiogroup->GetWidget()));
  //lua_pushlightuserdata(L,Radiogroup); //put pointer of RadioGroup to stack
  //return 1;//return 1 value (handle)
  
  return PushObject(L,Radiogroup);
}

static int do_CreateCheckGroup(lua_State *L) //cg=CheckGroup.new(parent,"caption") --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  const char *caption=luaL_checkstring(L,2);
  
  //g_print("Adding CheckGroup to Parent 0x%x...\n",int(iParent));

  LuaCheckGroup *Checkgroup=new LuaCheckGroup(L,iParent,caption);
  
  //g_print("CheckGroup-Widget: %x\n",int(Checkgroup->GetWidget()));
  //lua_pushlightuserdata(L,Checkgroup); //put pointer of CheckGroup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Checkgroup);
}

static int do_CreateEdit(lua_State *L) //edit=Edit.new(parent,"label") --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  const char *label=luaL_checkstring(L,2);
  //g_print("Adding Edit to Parent 0x%x...\n",int(iParent));

  LuaEdit *Edit=new LuaEdit(L,iParent,label);
  
  //g_print("Edit-Widget: %x\n",int(Edit->GetWidget()));
  //lua_pushlightuserdata(L,Edit); //put pointer of RadioGroup to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Edit);
}

static int do_CreateMemo(lua_State *L) //memo=Memo.new(parent) --parent can be 0
{
  int iParent=int(lua_touserdata(L,1));
  
  //g_print("Adding Memo to Parent 0x%x...\n",int(iParent));

  LuaMemo *Memo=new LuaMemo(L,iParent);
  
  //g_print("Memo-Widget: %x\n",int(Memo->GetWidget()));
  //lua_pushlightuserdata(L,Memo); //put pointer of Memo to stack
  //return 1;//return 1 value (handle)
  return PushObject(L,Memo);
}


//window Methods

static int do_PageControlAddPage(lua_State *L) //tab=pagecontrol:Add_Page("caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  //LuaPageControl *PageControl=reinterpret_cast<LuaPageControl*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaPageControl *Control=reinterpret_cast<LuaPageControl*>(lc->Ctl);

  void *vbox=Control->AddPage(caption,-1);
  lua_pushlightuserdata(L,vbox);//put pointer of vbox on stack
  return 1;//return 1 value (handle to vbox)
}

static int do_ListViewAddColumn(lua_State *L) //listview:Add_Column("caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
  Listview->AddColumn(caption);
  return 0;//return no value
}

static int do_ListViewAddItem(lua_State *L) //row=listview:Add_Item("caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);//iLuaControl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  int row=Listview->AddNewItem(caption);
  lua_pushinteger(L,row);//put rownumber on stack
  return 1;//return 1 value (row)
}

static int do_ListViewSetItem(lua_State *L) //listview:Set_Item(row,col,"caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  const char *caption=luaL_checkstring(L,4);
  //int ArgumentCount = lua_gettop(L);

  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  Listview->SetValue(row,col,caption);
  return 0;
}

static int do_ListViewGetText(lua_State *L) //listview:Get_Text(row,col) returns string
{
  void *iLuaControl=lua_touserdata(L,1);
  int row=luaL_checkinteger(L,2);
  int col=luaL_checkinteger(L,3);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  Listview->GetText(row,col); //LuaListView pushes value to Stack
  return 1;
}

static int do_ListViewClear(lua_State *L) //listview:Clear()
{
  void *iLuaControl=lua_touserdata(L,1);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaListView *Listview=reinterpret_cast<LuaListView*>(lc->Ctl);
//  LuaListView *Listview=reinterpret_cast<LuaListView*>(iLuaControl);
  g_print("clear listview\n");
  Listview->Clear();
  return 0;
}

static int do_SplitterSetClients(lua_State *L) //splitter:Set_Clients(Child1,Child2)
{
  void *iLuaControl=lua_touserdata(L,1);
  void *iChild1=lua_touserdata(L,2);
  void *iChild2=lua_touserdata(L,3);

//  LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaSplitter *Splitter=reinterpret_cast<LuaSplitter*>(lc->Ctl);
  /*
  LuaClass *lc_c1=reinterpret_cast<LuaClass*>(iChild1);
  GtkWidget *C1=reinterpret_cast<GtkControl*>(lc_c1->Ctl)->GetWidget();
  LuaClass *lc_c2=reinterpret_cast<LuaClass*>(iChild2);
  GtkWidget *C2=reinterpret_cast<GtkControl*>(lc_c2->Ctl)->GetWidget();
  */
  int C1=GetControlFromLuaPtr(iChild1);
  int C2=GetControlFromLuaPtr(iChild2);
  Splitter->SetClients(C1,C2);
  Splitter->SetStaticChild(0);

  return 0;
}

static int do_PopupAddItem(lua_State *L) //popup:Add_Item(caption,function)
{
  //int ArgumentCount = lua_gettop(L);
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);
//  g_print("adding MenuItem %s to Popupmenu %x\n",caption,int(iLuaControl));

//  LuaPopupMenu *Popup=reinterpret_cast<LuaPopupMenu*>(iLuaControl);
//  g_print("PopupClass:%x\n",int(Popup));
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaPopupMenu *Popup=reinterpret_cast<LuaPopupMenu*>(lc->Ctl);
  
  int ref;
  if (strcmp(caption,"")) //do not try to get reference for Separator-Elements
    ref=get_function_ref(L);
  lua_pop(L, 3); // clean the stack, removing 3 Elements

  Popup->AddMenuItem(caption,ref);
    
  return 0;
}

static int do_RadioGroupAddItem(lua_State *L) //radiogroup:Add_Item("caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

//  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(lc->Ctl);
  Radiogroup->AddRadio(caption);
  return 0;
}

static int do_RadioGroupGetChecked(lua_State *L) //radiogroup:Get_Checked() returns integer
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaRadioGroup *Radiogroup=reinterpret_cast<LuaRadioGroup*>(lc->Ctl);
  lua_pushinteger(L,Radiogroup->GetChecked());
  return 1;
}

static int do_CheckGroupAddItem(lua_State *L) //checkgroup:Add_Item("caption")
{
  void *iLuaControl=lua_touserdata(L,1);
  const char *caption=luaL_checkstring(L,2);

//  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(lc->Ctl);
  Checkgroup->AddCheckBox(caption);
  return 0;
}

static int do_CheckGroupIsChecked(lua_State *L) //checkgroup:Is_Checked(int ItemIndex) returns bool
{
  void *iLuaControl=lua_touserdata(L,1);
  int index=luaL_checkinteger(L,2);

//  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaCheckGroup *Checkgroup=reinterpret_cast<LuaCheckGroup*>(lc->Ctl);
  lua_pushboolean(L,Checkgroup->GetChecked(index));
  return 1;
}

static int do_EditGetText(lua_State *L) //edit:Get_Text() returns string
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaEdit *Edit=reinterpret_cast<LuaEdit*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaEdit *Edit=reinterpret_cast<LuaEdit*>(lc->Ctl);
  Edit->GetText(); //LuaEdit pushes value to Stack
  return 1;
}

static int do_MemoGetText(lua_State *L) //memo:Get_Text() returns string
{
  void *iLuaControl=lua_touserdata(L,1);
//  LuaMemo *Memo=reinterpret_cast<LuaMemo*>(iLuaControl);
  LuaClass *lc=reinterpret_cast<LuaClass*>(iLuaControl);
  LuaMemo *Memo=reinterpret_cast<LuaMemo*>(lc->Ctl);
  Memo->GetText(); //LuaMemo pushes value to Stack
  return 1;
}


static int do_ShowError(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_ERROR);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowInfo(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_INFO);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowWarning(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  int ret=MessageDialog(caption, message, MESSAGE_WARNING);
  lua_pushinteger(L,ret);
  return 1;
}

static int do_ShowQuestion(lua_State *L) //
{
  const char *caption=luaL_checkstring(L,1);
  const char *message=luaL_checkstring(L,2);
  bool ret=(MessageDialog(caption, message, MESSAGE_QUESTION)==1);
  lua_pushboolean(L,ret);
  return 1;
}

/*
//function taken from gui_ext.cpp by Steve Donovan
static wchar_t** table_to_str_array(lua_State *L, int idx, int* psz = NULL)
{
	if (! lua_istable(L,idx)) 
  {
		throw_error(L,L"table argument expected");
	}
    wchar_t** p = new wchar_t*[100];
    int i = 0;
    lua_pushnil(L); // first key
    while (lua_next(L, idx) != 0) 
    {
      // `key' is at index -2 and `value' at index -1 
		 p[i++] = _wcsdup(StringFromUTF8(lua_tostring(L,-1)));
         lua_pop(L, 1);  // removes `value'; keeps `key' for next iteration
    }
    p[i] = NULL;  // conventional way of indicating end of string array
    if (psz) *psz = i;
    return p;
}
*/

//TODO: removing redundant code

static int do_SetOnClick(lua_State *L)//without parameter
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evClick,ref);
  return 0;
}

static int do_SetOnDoubleClick(lua_State *L)//parameter: new index
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evDoubleClick,ref);
  return 0;
}

static int do_SetOnChange(lua_State *L)//used for Pagecontrol-switch; new index
{
  void *iLuaControl=lua_touserdata(L,1);
      
  int ref=get_function_ref(L);
  lua_pop(L, 2); // clean the stack, removing 2 Elements
  Set_Event(iLuaControl,evChange,ref);
  return 0;
}


static const luaL_reg R[] =
{
  { "InitSidebar", do_InitSidebar},
/*
	{ "Pagecontrol_Add_Page",	do_PageControlAddPage },
	{ "Listview_Add_Column", do_ListViewAddColumn },
	{ "Listview_Add_Item", do_ListViewAddItem },
	{ "Listview_Set_Item", do_ListViewSetItem },
	{ "Listview_Get_Text", do_ListViewGetText },
	{ "Listview_Clear", do_ListViewClear },
	{ "Splitter_Set_Clients", do_SplitterSetClients },
  { "Popup_Add_Item", do_PopupAddItem },
	{ "Radiogroup_Add_Item", do_RadioGroupAddItem },
	{ "Radiogroup_Get_Checked", do_RadioGroupGetChecked },
	{ "Checkgroup_Add_Item", do_CheckGroupAddItem },
	{ "Checkgroup_Is_Checked", do_CheckGroupIsChecked },
	{ "Edit_Get_Text", do_EditGetText },
	{ "Memo_Get_Text", do_MemoGetText },
	{ "New_Pagecontrol",	do_CreatePageControl },
	{ "New_Listview",	do_CreateListView },
	{ "New_Splitter",	do_CreateSplitter },
  { "New_Button", do_CreateButton },
  { "New_Popup", do_CreatePopup },
  { "New_Radiogroup", do_CreateRadioGroup },
  { "New_Checkgroup", do_CreateCheckGroup },
  { "New_Edit", do_CreateEdit },
  { "New_Memo", do_CreateMemo },
*/
  { "Show_Error", do_ShowError },
  { "Show_Info", do_ShowInfo },
  { "Show_Warning", do_ShowWarning },
  { "Show_Question", do_ShowQuestion },

	{ NULL,			NULL	}
};

static const struct luaL_reg ListView_f [] = 
{
  {"new", do_CreateListView},
  {NULL, NULL}
};

static const struct luaL_reg ListView_m [] = 
{
  { "Add_Column", do_ListViewAddColumn },
  { "Add_Item", do_ListViewAddItem },
  { "Set_Item", do_ListViewSetItem },
  { "Get_Text", do_ListViewGetText },
  { "Clear", do_ListViewClear },
  
  {"on_DblClick",do_SetOnDoubleClick},
  {NULL, NULL}
};

static const struct luaL_reg PageControl_f [] = 
{
  {"new", do_CreatePageControl},
  {NULL, NULL}
};

static const struct luaL_reg PageControl_m [] = 
{
	{ "Add_Page",	do_PageControlAddPage },
	
	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg Splitter_f [] = 
{
  {"new", do_CreateSplitter},
  {NULL, NULL}
};

static const struct luaL_reg Splitter_m [] = 
{
	{ "Set_Clients",	do_SplitterSetClients },
  {NULL, NULL}
};

static const struct luaL_reg Popup_f [] = 
{
  {"new", do_CreatePopup},
  {NULL, NULL}
};

static const struct luaL_reg Popup_m [] = 
{
	{ "Add_Item",	do_PopupAddItem },
  {NULL, NULL}
};

static const struct luaL_reg Button_f [] = 
{
  {"new", do_CreateButton},
  {NULL, NULL}
};

static const struct luaL_reg Button_m [] = 
{
  {"on_Click",do_SetOnClick},
  {NULL, NULL}
};

static const struct luaL_reg RadioGroup_f [] = 
{
  {"new", do_CreateRadioGroup},
  {NULL, NULL}
};

static const struct luaL_reg RadioGroup_m [] = 
{
	{ "Add_Item",	do_RadioGroupAddItem },
	{ "Get_Checked", do_RadioGroupGetChecked },

	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg CheckGroup_f [] = 
{
  {"new", do_CreateCheckGroup},
  {NULL, NULL}
};

static const struct luaL_reg CheckGroup_m [] = 
{
	{ "Add_Item",	do_CheckGroupAddItem },
	{ "Is_Checked", do_CheckGroupIsChecked },

	{"on_Change", do_SetOnChange},
  {NULL, NULL}
};

static const struct luaL_reg Edit_f [] = 
{
  {"new", do_CreateEdit},
  {NULL, NULL}
};

static const struct luaL_reg Edit_m [] = 
{
	{ "Get_Text", do_EditGetText },
  {NULL, NULL}
};

static const struct luaL_reg Memo_f [] = 
{
  {"new", do_CreateMemo},
  {NULL, NULL}
};

static const struct luaL_reg Memo_m [] = 
{
	{ "Get_Text", do_MemoGetText },
  {NULL, NULL}
};

extern "C" 
{//__declspec(dllexport)
	LUALIB_API int luaopen_gui(lua_State *L)
	{
	  luaL_register(L,"gui",R);
	 
//    luaL_newmetatable(L, "gui.ListView");
//    lua_pushstring(L, "__index");
//    lua_pushvalue(L, -2);  /* pushes the metatable */
//    lua_settable(L, -3);  /* metatable.__index = metatable */
//    luaL_openlib(L, NULL, ListView_m, 0); //first register Methods
//    luaL_openlib(L, "ListView", ListView_f, 0); //now register object
    RegisterClass(L,"ListView","gui.ListView",ListView_f,ListView_m);
    RegisterClass(L,"PageControl","gui.PageControl",PageControl_f,PageControl_m);
    RegisterClass(L,"Splitter","gui.Splitter",Splitter_f,Splitter_m);
    RegisterClass(L,"Popup","gui.Popup",Popup_f,Popup_m);
    RegisterClass(L,"Button","gui.Button",Button_f,Button_m);
    RegisterClass(L,"RadioGroup","gui.RadioGroup",RadioGroup_f,RadioGroup_m);
    RegisterClass(L,"CheckGroup","gui.CheckGroup",CheckGroup_f,CheckGroup_m);
    RegisterClass(L,"Edit","gui.Edit",Edit_f,Edit_m);
    RegisterClass(L,"Memo","gui.Memo",Memo_f,Memo_m);

	  return 2;
	}
}
