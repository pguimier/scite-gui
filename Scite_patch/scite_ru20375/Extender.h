// SciTE - Scintilla based Text Editor
/** @file Extender.h
 ** SciTE extension interface.
 **/
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef EXTENDER_H
#define EXTENDER_H

#include "Platform.h" //!-add-[OnKey]
#include "Scintilla.h"
class Accessor;

class ExtensionAPI {
public:
	virtual ~ExtensionAPI() {
	}
	enum Pane { paneEditor=1, paneOutput=2, paneFindOutput=3 };
	virtual sptr_t Send(Pane p, unsigned int msg, uptr_t wParam=0, sptr_t lParam=0)=0;
	virtual char *Range(Pane p, int start, int end)=0;
	virtual void Remove(Pane p, int start, int end)=0;
	virtual void Insert(Pane p, int pos, const char *s)=0;
	virtual void Trace(const char *s)=0;
	virtual char *Property(const char *key)=0;
	virtual void SetProperty(const char *key, const char *val)=0;
	virtual void UnsetProperty(const char *key)=0;
	virtual uptr_t GetInstance()=0;
	virtual void ShutDown()=0;
	virtual void Perform(const char *actions)=0;
	virtual void DoMenuCommand(int cmdID)=0;
	virtual void UpdateStatusBar(bool bUpdateSlowData)=0;
	virtual void CheckMenus()=0; //!-add-[CheckMenus]
	virtual bool ShowParametersDialog(const char *msg)=0; //!-add-[ParametersDialogFromLua]
	virtual bool InsertAbbreviation(const char *data, int expandedLength)=0; //!-add-[AbbrevRefactoring]
	virtual char *GetTranslation(const char *s, bool retainIfNotFound = true)=0; //!-add-[LocalizationFromLua]
};

/**
 * Methods in extensions return true if they have completely handled and event and
 * false if default processing is to continue.
 */
class Extension {
public:
	virtual ~Extension() {}

	virtual bool Initialise(ExtensionAPI *host_)=0;
	virtual bool Finalise()=0;
	virtual bool Clear()=0;
	virtual bool Load(const char *filename)=0;

	virtual bool InitBuffer(int) { return false; }
	virtual bool ActivateBuffer(int) { return false; }
	virtual bool RemoveBuffer(int) { return false; }

	virtual bool OnOpen(const char *) { return false; }
	virtual bool OnSwitchFile(const char *) { return false; }
	virtual bool OnBeforeSave(const char *) { return false; }
	virtual bool OnSave(const char *) { return false; }
	virtual bool OnChar(char) { return false; }
	virtual bool OnExecute(const char *) { return false; }
	virtual bool OnSavePointReached() { return false; }
	virtual bool OnSavePointLeft() { return false; }
	virtual bool OnStyle(unsigned int, int, int, Accessor *) {
		return false;
	}
//!	virtual bool OnDoubleClick() { return false; }
	virtual bool OnDoubleClick(int) { return false; } //!-add-[OnDoubleClick]
	virtual bool OnClick(int) { return false; } //!-add-[OnClick]
	virtual bool OnMouseButtonUp(int) { return false; } //!-add-[OnMouseButtonUp]
	virtual bool OnUpdateUI() { return false; }
	virtual bool OnMarginClick() { return false; }
	virtual bool OnMacro(const char *, const char *) { return false; }
	virtual bool OnUserListSelection(int, const char *) { return false; }
	virtual bool OnMenuCommand(int, int) { return false; } //!-add-[OnMenuCommand]
	virtual const char *OnSendEditor(unsigned int, unsigned int, const char *) { return 0; } //!-add-[OnSendEditor]
	virtual const char *OnSendEditor(unsigned int, unsigned int, long) { return 0; } //!-add-[OnSendEditor]

	virtual bool SendProperty(const char *) { return false; }

//!-start-[OnKey]
#if PLAT_WIN
	virtual bool OnKey(int, int, char) { return false; }
#else
//!-end-[OnKey]
	virtual bool OnKey(int, int) { return false; }
#endif //!-add-[OnKey]
	virtual bool OnDwellStart(int, const char *) { return false; }
	virtual bool OnClose(const char *) { return false; }
};

#endif
