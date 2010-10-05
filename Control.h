#ifndef CONTROL_H
#define CONTROL_H

enum WindowTypes
{
	cPageControl=0,
  cListView,
	cSplitter,
	cButton,
  cCheckBox,
  cRadioGroup,
  cCheckGroup,
	cPopupMenu,
	cEdit,
	cMemo,
  cWindow,
  cBox,
  cMessageBox,
  cFileOpenDialog,
  cFileSaveDialog,
  
	cMax
};

class Control
{
  private:
    int fType;
  protected:
  public:
    Control();
    virtual ~Control();
    void SetType(int T);
    int GetType();
};
#endif
