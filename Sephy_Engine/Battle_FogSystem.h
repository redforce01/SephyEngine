#ifndef _BATTLE_FOGSYSTEM_H
#define _BATTLE_FOGSYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CBattle_FogSystem;

#include <vector>
#include "systemBase.h"
#include "Battle_FogCell.h"

namespace battleFogSystemNS
{
	const std::string ERROR_MESSAGE = "Battle Fog System Initialize Failed";
	const std::string FOG_RESOURCE_FOLDER_NAME = "54_Battle_Texture_Fog";
}

class CBattle_UnitSystem;
class CBattle_FogSystem : public SystemBase
{
private:
	CBattle_UnitSystem* m_pBattleUnitSystem;
public:
	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}
private:
	std::vector<CBattle_FogCell*> m_vFog;
	UINT m_nFogCellX;
	UINT m_nFogCellY;

public:
	CBattle_FogSystem();
	~CBattle_FogSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//================================================
	// Member Functions
	//================================================

	void moveX(float distance);
	void moveY(float distance);

	void setupAllFog(float mapTotalWidth, float mapTotalHeight);


	//================================================
	// Getter Functions
	//================================================

	std::vector<CBattle_FogCell*> getAllFogCell() const
	{
		return m_vFog;
	}

	UINT getFogCellSizeX() const
	{
		return m_nFogCellX;
	}
	UINT getFogCellSizeY() const
	{
		return m_nFogCellY;
	}
};

#endif // !_BATTLE_FOGSYSTEM_H