#ifndef _SYSTEMUIEDIT_H
#define _SYSTEMUIEDIT_H

class SystemUIEdit;

#include "systemUIControl.h"

namespace systemUIEditNS
{
	const char FONT[] = "Courier New";			// Viewer font
	const int FONT_HEIGHT = 14;					// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text

	const UINT EDIT_MARGIN = 4;
	const std::string EDIT_CURSOR = "|";
}

class SystemUIEdit : public SystemUIControl
{
private:
	std::string m_strEditTitle;
	std::string m_strEditText;
	std::string m_strHint;
	bool m_bShowHint;
	bool m_bEditable;

	// EditBox Size Variables
private:
	float m_fEditBoxRate; // the Rate between TitleBox and EditBox in rcBoundingBox (must value : 0.0 ~ 1.0)
	
public:
	SystemUIEdit();
	virtual ~SystemUIEdit();

	virtual bool initEdit(Graphics* g, Input* i, int controlID, bool bUseHint,
		std::string strHint, std::string strTitle, bool bEditable, float fBoxRate,
		int x, int y, int w, int h, int m);
	virtual bool initEdit(Graphics* g, Input* i, int controlID, bool bUseHint,
		std::string strHint, std::string strTitle, bool bEditable, SystemUIDialog* pParent, float fBoxRate,
		int x, int y, int w, int h, int m);
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ===============================================
	// Memeber Functions
	// ===============================================
	void clearInputText()
	{
		m_pInput->clearTextIn();
	}

	// ===============================================
	// Setter Functions
	// ===============================================
	void setEditText(std::string str)
	{
		m_strEditText = str;
	}
	void setEditable(bool b)
	{
		m_bEditable = b;
	}

	// ===============================================
	// Getter Functions
	// ===============================================
	std::string getEditText() const
	{
		return m_strEditText;
	}
	bool getEditable() const
	{
		return m_bEditable;
	}
};

#endif // !_SYSTEMUIEDIT_H
