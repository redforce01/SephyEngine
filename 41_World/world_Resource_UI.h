#pragma once

#include "systemUIDialog.h"
#include "world_Resource_Detail.h"

namespace worldresourceNS
{
	const UINT num = 4;

	const UINT x = 10;	//Viewer location
	const UINT y = 10;

	const std::string MONEY = "Money";	//resource img * 4
	const std::string IRON = "Iron";
	const std::string FUEL = "Fuel";
	const std::string RESEARCH = "Research";
	const UINT icon_width = 24;
	const UINT icon_height = 24;

	const std::string img_name = "Resource";
	const UINT img_width = 183;
	const UINT img_height = 24;
	
	const std::string img_save = "Score";
	const UINT num_save_width = 9;		//Score -> Image Size
	const UINT num_save_height = 13;
	const UINT save_width = 60;
	const UINT save_height = 15;	//y position + 2

	const std::string img_increase = "AW";
	const UINT num_increase_width = 7;		//NumT -> Image Size
	const UINT num_increase_height = 11;
	const UINT increase_width = 50;
	const UINT increase_height = 15;	//y position + 1

	const UINT distance_x = 15;
	const UINT distance_y = 9;

	const UINT MARGIN = 10;					// text margin from Viewer edge

	const char FONT[] = "Courier New";		// Viewer font
	const int FONT_SIZE = 16;
//	const int FONT_SIZE_increase = 14;
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
}

class CWorld_Player;
class CWorld_Resource_UI : public SystemUIDialog
{
private:
	//std::map<std::string, std::string> m_saveMessage;
	//std::map<std::string, std::string> m_increaseMessage;
	CWorld_Resource_Detail* resource_detail;
	CWorld_Player* player;

	Image* img_resource[worldresourceNS::num];
	RECT rect_save[worldresourceNS::num];
	RECT rect_increase[worldresourceNS::num];

	int increase_resource[worldresourceNS::num];
	int decrease_resource[worldresourceNS::num];

	TextDX m_dxfont;
	//TextDX dxfont_increase;

	Graphics*	m_pGraphics;
	Input*		m_pInput;

	Image* icon_resource[worldresourceNS::num];

	std::vector<Image*> list_number;

	void resource_initialize(int index, std::string img);
	void calcu_resource();

public:
	void SetLoadLinkPlayer(CWorld_Player* _player) { player = _player; }

	CWorld_Resource_UI();
	~CWorld_Resource_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() ;

	void replace_number_img(RECT rect, UINT _resource, bool big);
	RECT get_rect_increase(UINT _index) { return rect_increase[_index]; }
	//rect_save = true , rect_increase = false
	//void addMessage(std::string key, std::string message, bool is_save)
	//{
	//	if (is_save)
	//		m_saveMessage.emplace(key, message);
	//	else m_increaseMessage.emplace(key, message);
	//}
	//void setMessage(std::string key, std::string message, bool is_save)
	//{
	//	if (is_save)
	//		m_saveMessage.find(key)->second = message;
	//	else m_increaseMessage.find(key)->second = message;
	//}
	//void removeMessage(std::string key)
	//{
	//	m_saveMessage.erase(key);
	//	m_increaseMessage.erase(key);
	//}
};

