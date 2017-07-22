#ifndef _SYSTEMUICONTROL_H
#define _SYSTEMUICONTROL_H
#define WIN32_LEAN_AND_MEAN

class SystemUIControl;

#include "graphics.h"
#include "input.h"

enum class SYSTEM_UI_TYPES
{
	UI_TYPE_BUTTON,
	UI_TYPE_STATIC,
	UI_TYPE_RADIOBUTTON,
	UI_TYPE_CHECKBOX,
	UI_TYPE_COMBOBOX,
	UI_TYPE_SLIDER,
	UI_TYPE_EDITBOX,
	UI_TYPE_ITEMEDITBOX,
	UI_TYPE_LISTBOX,
	UI_TYPE_SCROLLBAR
};

enum class SYSTEM_UI_CONTROL_STATE
{
	UI_CONTROL_STATE_NORMAL = 0,
	UI_CONTROL_STATE_DISABLED,
	UI_CONTROL_STATE_HIDDEN,
	UI_CONTROL_STATE_FOCUS,
	UI_CONTROL_STATE_MOUSEOVER,
	UI_CONTROL_STATE_PRESSED
};

class SystemUIDialog;
class SystemUIControl
{
//====================================
// Private Variables
//====================================
private:
	float m_x, m_y;
	float m_width, m_height;
	float m_margin;
	bool m_bInitialized;
	bool m_bVisible;
	bool m_bMouseOver;
	bool m_bHasFocus;
	bool m_bHasParent;
	bool m_bUseBackground;
	int m_nControlID;
//====================================
// Protected Variables
//====================================
protected:
	virtual void UpdateRects()
	{
		m_rcBoundingBox = RectMake(m_x, m_y, m_width, m_height);
	}
	SystemUIDialog* m_pDialog;
	Graphics* m_pGraphics;
	Input* m_pInput;
	TextDX m_dxFont;
	RECT m_rcBoundingBox;
	UINT m_nHotkey;
	bool m_bEnabled;
	SYSTEM_UI_TYPES m_Type;
	SYSTEM_UI_CONTROL_STATE m_State;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	COLOR_ARGB  backColor;
public:
	SystemUIControl();
	virtual ~SystemUIControl();

	virtual bool initControl(int controlID, SYSTEM_UI_TYPES type, bool bUseBack,
		int x, int y, int w, int h, int m);
	virtual bool initControl(int controlID, SYSTEM_UI_TYPES type, SystemUIDialog* pParent, bool bUseBack,
		int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

	// Vertex Setup Function
	bool vertexSetUp(int x, int y, int w, int h);
	
	// =================================================================
	// Setter Functions
	// =================================================================
	void SetState(SYSTEM_UI_CONTROL_STATE state)
	{
		m_State = state;
	}
	void SetHidden()
	{
		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_HIDDEN;
	}
	void SetNormal()
	{
		m_State = SYSTEM_UI_CONTROL_STATE::UI_CONTROL_STATE_NORMAL;
	}
	void SetID(int ID)
	{
		m_nControlID = ID;
	}
	void SetDxFont(TextDX font)
	{
		m_dxFont = font;
	}
	void SetLocation(int x, int y)
	{
		m_x = x; m_y = y; UpdateRects();
	}
	void SetSize(int width, int height)
	{
		m_width = width; m_height = height; UpdateRects();
	}
	void SetHotKey(UINT nHotKey)
	{
		m_nHotkey = nHotKey;
	}
	void SetFocus(bool b)
	{
		m_bHasFocus = b;
	}
	void SetFontStyle(DWORD dtStyle)
	{

	}
	// =================================================================
	// Getter Functions
	// =================================================================
	bool ContainsParent() const
	{
		return m_bHasParent;
	}
	float GetControlPosX() const
	{
		return m_x;
	}
	float GetControlPosY() const
	{
		return m_y;
	}
	POINT GetControlPt() const
	{
		return PointMake(m_x, m_y);
	}
	float GetControlMargin() const
	{
		return m_margin;
	}
	int GetID() const
	{
		return m_nControlID;
	}
	UINT GetHotKey() const
	{
		return m_nHotkey;
	}
	bool GetFocus() const
	{
		return m_bHasFocus;
	}
	RECT GetControlRECT() const
	{
		return m_rcBoundingBox;
	}
	// =================================================================
	// Virtual Functions
	// =================================================================
	virtual void OnFocusIn()
	{
		m_bHasFocus = true;
	}
	virtual void OnFocusOut()
	{
		m_bHasFocus = false;
	}
	virtual void OnMouseEnter()
	{
		m_bMouseOver = true;
	}
	virtual void OnMouseLeave()
	{
		m_bMouseOver = false;
	}
	virtual void OnHotKey() {}
	virtual bool ContainsPoint(POINT pt)
	{
		return PtInRect(&m_rcBoundingBox, pt);
	}

	// =================================================================
	// Virtual Setter Functions
	// =================================================================
	virtual void SetEnabled(bool bEnabled)
	{
		m_bEnabled = bEnabled;
	}
	virtual void SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}

	// =================================================================
	// Virtual Getter Functions
	// =================================================================
	virtual bool GetEnabled() const
	{
		return m_bEnabled;
	}
	virtual bool GetVisible() const
	{
		return m_bVisible;
	}
};

#endif // !_SYSTEMUICONTROL_H