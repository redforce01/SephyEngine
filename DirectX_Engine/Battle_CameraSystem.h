#ifndef _BATTLE_CAMERASYSTEM_H
#define _BATTLE_CAMERASYSTEM_H

class CBattle_CameraSystem;

#include "systemBase.h"

namespace battleCameraSystemNS
{
	const std::string ERROR_MESSAGE = "Battle CameraSystem Initialize Failed";
	const float CAMERA_NORMAL_SPEED = 10.f;
	const float CAMERA_BOOST_SPEED = 20.0f;
	const UCHAR CAMERA_BOOST_KEY = VK_SHIFT;

	const UCHAR CAMERA_MOVE_LEFT_KEY = VK_LEFT;
	const UCHAR CAMERA_MOVE_RIGHT_KEY = VK_RIGHT;
	const UCHAR CAMERA_MOVE_UP_KEY = VK_UP;
	const UCHAR CAMERA_MOVE_DOWN_KEY = VK_DOWN;
}

class CBattle_MapSystem;
class CBattle_MiniMapSystem;
class CBattle_CameraSystem : public SystemBase
{
private: // Camera Variables
	float m_fCameraX, m_fCameraY;
	float m_fCameraSpeed;
	float m_fCameraMinX, m_fCameraMinY;
	float m_fCameraMaxX, m_fCameraMaxY;

	bool m_bCameraBoost;

private: // Forward Pointer Variables
	CBattle_MapSystem*		m_pBattleMapSystem;
	CBattle_MiniMapSystem*	m_pBattleMinimapSystem;

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
};

#endif // !_BATTLE_CAMERASYSTEM_H
