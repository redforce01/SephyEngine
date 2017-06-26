#ifndef _SYSTEMUICONTROL_H
#define _SYSTEMUICONTROL_H
#define WIN32_LEAN_AND_MEAN

class SystemUIControl;


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
	bool m_bHasIcon;
	SystemUIDialog* m_pDialog;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;
	COLOR_ARGB  backColor;
//====================================
// Protected Variables
//====================================
protected:
	virtual void UpdateRects()
	{
		m_rcBoundingBox = RectMake(m_x, m_y, m_width, m_height);
	}
	Graphics* m_pGraphics;
	Input* m_pInput;
	Image* m_pIcon;
	TextDX dxFont;
	int m_nControlID;
	RECT m_rcBoundingBox;
	UINT m_nHotkey;
	bool m_bEnabled;
	SYSTEM_UI_TYPES m_Type;
	SYSTEM_UI_CONTROL_STATE m_State;
	void* m_Object;
//====================================
// Function Pointer
//====================================
protected:
	typedef void(*CALLBACK_FUNCTION_)(void);
	typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);
	CALLBACK_FUNCTION_			m_CallbackFunction;
	CALLBACK_FUNCTION_PARAMETER m_CallbackFunctionParameter;
public:
	SystemUIControl();
	~SystemUIControl();

	virtual bool initialize(int controlID, SYSTEM_UI_TYPES type,
		int x, int y, int w, int h, int m);
	virtual void update(float frameTime);
	virtual void render();

	// =================================================================
	// Member Functions
	// =================================================================
	bool vertexSetUp(int x, int y, int w, int h);
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
	int GetID() const
	{
		return m_nControlID;
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
	UINT GetHotKey()
	{
		return m_nHotkey;
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
	virtual void SetEnabled(bool bEnabled)
	{
		m_bEnabled = bEnabled;
	}
	virtual bool GetEnabled()
	{
		return m_bEnabled;
	}
	virtual void SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
	}
	virtual bool GetVisible()
	{
		return m_bVisible;
	}
};

#endif // !_SYSTEMUICONTROL_H