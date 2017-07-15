#pragma once

#include "systemUIDialog.h"

namespace worldresourceNS
{
	const UINT num = 4;

	const UINT x = 10;	//Viewer location
	const UINT y = 10;

	const std::string img_name = "ExitButton";	//resource img * 4
	const UINT img_width = 36;
	const UINT img_height = 36;

	const UINT save_width = 172;
	const UINT save_height = 32;	//y position + 2

	const UINT increase_width = 80;
	const UINT increase_height = 30;	//y position + 1

	const UINT distance_x = 11;
	const UINT distance_y = 8;

	const UINT MARGIN = 4;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE_save = 24;
	const int FONT_SIZE_increase = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Resource_UI : public SystemUIDialog
{
private:
	std::map<std::string, std::string> m_saveMessage;
	std::map<std::string, std::string> m_increaseMessage;

	RECT rect_save[worldresourceNS::num];
	RECT rect_increase[worldresourceNS::num];

	TextDX dxfont_save;
	TextDX dxfont_increase;

	Graphics*	m_pGraphics;
	Input*		m_pInput;

	Image* img_resource[worldresourceNS::num];

	void resource_initialize(int index, std::string img);

public:
	CWorld_Resource_UI();
	~CWorld_Resource_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() ;

	//rect_save = true , rect_increase = false
	void addMessage(std::string key, std::string message, bool is_save)
	{
		if (is_save)
			m_saveMessage.emplace(key, message);
		else m_increaseMessage.emplace(key, message);
	}
	void setMessage(std::string key, std::string message, bool is_save)
	{
		if (is_save)
			m_saveMessage.find(key)->second = message;
		else m_increaseMessage.find(key)->second = message;
	}
	void removeMessage(std::string key)
	{
		m_saveMessage.erase(key);
		m_increaseMessage.erase(key);
	}
};

