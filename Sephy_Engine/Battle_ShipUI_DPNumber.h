#ifndef _BATTLE_SHIPUI_DPNUMBER_H
#define _BATTLE_SHIPUI_DPNUMBER_H
#define WIN32_LEAN_AND_MEAN

class CBattle_ShipUI_DPNumber;

#include <vector>
#include "image.h"

namespace battleShipUIDPNumberNS
{
	const std::string ERROR_MESSAGE = "Battle ShipUI DPNumber Interface Initialize Failed";
	const std::string DP_KEY_NORMAL = "N";
	const std::string DP_KEY_DANGER = "DP";
	const std::string DP_KEY_BLUE = "SP";

	const std::string DP_SLASH_FILENAME = "Slash";
	const float DANGER_RATE = 0.2f;
	const float NORMAL_RATE = 0.6f;
	const float BLUE_RATE = 0.2f;

	const UINT DP_IMAGE_SIZE = 7;
}

class CBattle_Ship;
class CBattle_ShipUI_DPNumber
{
private:
	CBattle_Ship* m_pMaster;
	std::vector<Image*> m_vCurrentDP;
	Image* m_Slash;
	std::vector<Image*> m_vMaxDP;

	float m_fCurrentDP;
	float m_fMaxDP;
public:
	CBattle_ShipUI_DPNumber();
	~CBattle_ShipUI_DPNumber();

	bool initialize(Graphics* g, CBattle_Ship* pMaster);
	void update(float frameTime);
	void draw();

	//====================================================
	// Member Functions
	//====================================================

	void setDPNumberPos(float startX, float startY);
	void setupDP(float currentDP, float maxDP);

	void moveX(float distance);
	void moveY(float distance);

private:
	void setupCurrentDP(float currentDP);
	void setupMaxDP(float maxDP);

};

#endif // !_BATTLE_SHIPUI_DPNUMBER_H
