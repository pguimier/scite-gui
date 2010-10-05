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

class CControl
{
  private:
    int fType;
  protected:
  public:
    CControl();
    virtual ~CControl();
    void SetType(int T);
    int GetType();
};
#endif
