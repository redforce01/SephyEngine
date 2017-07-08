#ifndef _SYSTEMUIBUTTON_H
#define _SYSTEMUIBUTTON_H

class SystemUIButton;

#include "systemUIControl.h"

class SystemUIButton : public SystemUIControl
{
private:
	bool m_bHasIcon;
	bool m_bHasMessage;
	std::string m_strMessage;

protected:
	Image* m_pIcon;

// CALLBACK Function & void Pointer
protected:
	void* m_pObject;
	typedef void(*CALLBACK_FUNCTION_)(void);
	typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);
	CALLBACK_FUNCTION_			m_CallbackFunction;
	CALLBACK_FUNCTION_PARAMETER m_CallbackFunctionParameter;
public:
	SystemUIButton();
	virtual ~SystemUIButton();

	virtual bool initButton(Graphics* g, Input* i, int controlID, CALLBACK_FUNCTION_ cbFunction,
		int x, int y, int w, int h, int m);
	virtual bool initButton(Graphics* g, Input* i, int controlID, CALLBACK_FUNCTION_ cbFunction, SystemUIDialog* pParent,
		int x, int y, int w, int h, int m);
	virtual bool initButton(Graphics* g, Input* i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void* obj,
		int x, int y, int w, int h, int m);
	virtual bool initButton(Graphics* g, Input* i, int controlID, CALLBACK_FUNCTION_PARAMETER cbfParam, void* obj, SystemUIDialog* pParent,
		int x, int y, int w, int h, int m);

	virtual bool initialize(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, int x, int y, int w, int h, int m) PURE;
	virtual void update(float frameTime) override;
	virtual void render() override;

public:
	void SetMessage(std::string message)
	{
		m_strMessage = message;
		m_bHasMessage = true;
	}
	void SetIcon(Image* icon);

	Image* GetIcon() const
	{
		return m_pIcon;
	}
};

#endif // !_SYSTEMUIBUTTON_H
