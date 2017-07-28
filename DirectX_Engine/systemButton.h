#ifndef _SYSTEM_BUTTON_H
#define _SYSTEM_BUTTON_H
#define WIN32_LEAN_AND_MEAN

class SystemButton;

#include "image.h"
#include <functional>

namespace systemButtonNS
{
	const std::string FRAME_UP_KEY			= "N";
	const std::string FRAME_DOWN_KEY		= "P";
	const std::string FRAME_OVERLAB_KEY		= "O";
	const std::string FRAME_DEACTIVE_KEY	= "D";

	const std::string ERROR_MESSAGE = "System Button Initialize Failed";
}

enum class SYSTEM_UI_BUTTON
{ BUTTON_STATE_DEACTIVE, BUTTON_STATE_DOWN, BUTTON_STATE_UP, BUTTON_STATE_OVERLAB };

class SystemButton : public Image
{
protected:
	Graphics*	m_pGraphics;
	Input*		m_pInput;
	std::string m_strButtonKey;
	float		m_x, m_y;
	float		m_width, m_height;
	RECT		m_rcButton;

protected:
	bool		m_bUseKey;
	bool		m_bInitialized;
	bool		m_bActive;

protected:
	std::function<void()> m_function;
	SYSTEM_UI_BUTTON m_enButtonState;
private:
	std::string m_strButtonUpKey;
	std::string m_strButtonDownKey;
	std::string m_strButtonOverKey;
	std::string m_strButtonDeactiveKey;
public:
	SystemButton();
	virtual ~SystemButton();

	virtual bool initialize(Graphics* g, Input* i, std::string imageName, bool bUseKey = false);
	virtual bool initialize(Graphics* g, Input* i, float x, float y, std::string imageName, bool bUseKey = false);
	virtual void update(float frameTime);
	virtual void render();

	//==================================================
	// Member Functions
	//==================================================
	
private:
	void setupButtonRect()
	{
		m_rcButton = RectMake(m_x, m_y, m_width, m_height);
	}

	//==================================================
	// Setter Functions
	//==================================================
public:
	void setActive(bool b)
	{
		m_bActive = b;
	}
	
	void setButtonWidth(float width)
	{
		m_width = width;
		setupButtonRect();
	}

	void setButtonHeight(float height)
	{
		m_height = height;
		setupButtonRect();
	}

	void setButtonPos(float x, float y)
	{
		m_x = x, m_y = y;
		setupButtonRect();
	}
	
	void setRegistFunction(std::function<void()> pFunction)
	{
		m_function = pFunction;
	}

	//==================================================
	// Setter Functions
	//==================================================

	bool getActive() const
	{
		return m_bActive;
	}

	float getButtonWidth() const
	{
		return m_width;
	}

	float getButtonHeight() const
	{
		return m_height;
	}

	float getButtonX() const
	{
		return m_x;
	}

	float getButtonY() const
	{
		return m_y;
	}

	RECT getButtonRect() const
	{
		return m_rcButton;
	}
};

#endif // !_SYSTEM_BUTTON_H
