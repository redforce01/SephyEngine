#ifndef _SAVELOADVIEWER_H
#define _SAVELOADVIEWER_H

class SaveLoadViewer;

#include "systemUIDialog.h"

enum class VIEWER_TYPE
{
	VIEWER_TYPE_NONE,
	VIEWER_TYPE_SAVE,
	VIEWER_TYPE_LOAD
};

class SaveLoadViewer : public SystemUIDialog
{
private:
	VIEWER_TYPE m_ViewerType;
	
	SystemUIDialog* m_pSaveDialog;
	SystemUIDialog* m_pLoadDialog;
public:
	SaveLoadViewer();
	~SaveLoadViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void callLoadViewer();
	void callSaveViewer();
};

#endif // !_SAVELOADVIEWER_H
