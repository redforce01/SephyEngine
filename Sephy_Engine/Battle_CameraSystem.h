#ifndef _BATTLE_CAMERASYSTEM_H
#define _BATTLE_CAMERASYSTEM_H

class CBattle_CameraSystem;

#include "systemBase.h"
#include "Battle_MinimapView.h"

namespace battleCameraSystemNS
{
	const std::string ERROR_MESSAGE = "Battle CameraSystem Initialize Failed";
	const float CAMERA_NORMAL_SPEED = 10.f;
	const float CAMERA_BOOST_SPEED = CAMERA_NORMAL_SPEED * 3.0f;
	const UCHAR CAMERA_BOOST_KEY = VK_SHIFT;

	const UCHAR CAMERA_MOVE_LEFT_KEY = 'A';
	const UCHAR CAMERA_MOVE_RIGHT_KEY = 'D';
	const UCHAR CAMERA_MOVE_UP_KEY = 'W';
	const UCHAR CAMERA_MOVE_DOWN_KEY = 'S';
}

class CBattle_FogSystem;
class CBattle_UnitSystem;
class CBattle_MapSystem;
class CBattle_MiniMapSystem;
class CBattle_CameraSystem : public SystemBase
{
private: // Camera Variables
	float m_fCameraX, m_fCameraY;
	float m_fCameraSpeed;
	float m_fCameraMinX, m_fCameraMinY;
	float m_fCameraMaxX, m_fCameraMaxY;
private: // Forward Pointer Variables
	CBattle_MapSystem*		m_pBattleMapSystem;
	CBattle_MiniMapSystem*	m_pBattleMinimapSystem;
	CBattle_UnitSystem*		m_pBattleUnitSystem;
	CBattle_FogSystem*		m_pBattleFogSystem;
private:
	CBattle_MinimapView* m_pBattleMinimapView;

public:
	CBattle_CameraSystem();
	~CBattle_CameraSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	//===============================================
	// Member Functions
	//===============================================
		
	void moveLeft();	// Camera Move Left
	void moveRight();	// Camera Move Right
	void moveUp();		// Camera Move Up
	void moveDown();	// Camera Move Down

	//===============================================
	// Setter Functions
	//===============================================
	// Set Camera Speed 
	void setCameraSpeed(float speed)
	{
		m_fCameraSpeed = speed;
	}
	// Set Camera Position(x, y)
	void setCameraPos(float x, float y);

	// Set Camera Min X, Y
	void setCameraMinPos(float minX, float minY)
	{
		m_fCameraMinX = minX, m_fCameraMinY = minY;
	}
	// Set Camera Max X, Y
	void setCameraMaxPos(float maxX, float maxY)
	{
		m_fCameraMaxX = maxX, m_fCameraMaxY = maxY;
	}


	//===============================================
	// Getter Functions
	//===============================================
	// Get Camera Speed
	float getCameraSpeed(float speed) const
	{
		return m_fCameraSpeed;
	}
	// Get Camera Position(x, y)
	POINT getCameraPos() const
	{
		return PointMake(m_fCameraX, m_fCameraY);
	}
	float getCameraX() const
	{
		return m_fCameraX;
	}
	float getCameraY() const
	{
		return m_fCameraY;
	}
	CBattle_MinimapView* getBattleMinimapViewer() const
	{
		return m_pBattleMinimapView;
	}
	
	//===============================================
	// Memory Link Functions
	//===============================================
	void setMemoryLinkBattleMapSystem(CBattle_MapSystem* pBattleMapSystem)
	{
		m_pBattleMapSystem = pBattleMapSystem;
	}
	void setMemoryLinkBattleMinimapSystem(CBattle_MiniMapSystem* pBattleMinimapSystem)
	{
		m_pBattleMinimapSystem = pBattleMinimapSystem;
	}
	void setMemoryLinkBattleUnitSystem(CBattle_UnitSystem* pBattleUnitSystem)
	{
		m_pBattleUnitSystem = pBattleUnitSystem;
	}
	void setMemoryLinkBattleFogSystem(CBattle_FogSystem* pBattleFogSystem)
	{
		m_pBattleFogSystem = pBattleFogSystem;
	}
};

#endif // !_BATTLE_CAMERASYSTEM_H
