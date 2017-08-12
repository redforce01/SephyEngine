#ifndef _UNITTOOL_CAMERASYSTEM_H
#define _UNITTOOL_CAMERASYSTEM_H
#define WIN32_LEAN_AND_MEAN

class CUnitTool_CameraSystem;

#include "systemBase.h"

namespace unitToolCameraSystemNS
{
	const std::string ERROR_MESSAGE = "UnitTool CameraSystem Initialize Failed";
	const float CAMERA_NORMAL_SPEED = 10.f;
	const float CAMERA_BOOST_SPEED = CAMERA_NORMAL_SPEED * 3.0f;
	const UCHAR CAMERA_BOOST_KEY = VK_SHIFT;

	const UCHAR CAMERA_MOVE_LEFT_KEY	= 'A';
	const UCHAR CAMERA_MOVE_RIGHT_KEY	= 'D';
	const UCHAR CAMERA_MOVE_UP_KEY		= 'W';
	const UCHAR CAMERA_MOVE_DOWN_KEY	= 'S';
}

class CUnitTool_UnitControlSystem;
class CUnitTool_MapSystem;
class CUnitTool_CameraSystem : public SystemBase
{
private: // Forward Declarations
	CUnitTool_MapSystem* m_pMapSystem;
	CUnitTool_UnitControlSystem* m_pUnitControlSystem;
public:
	void setMemoryLinkMapSystem(CUnitTool_MapSystem* pMapSystem)
	{
		m_pMapSystem = pMapSystem;
	}
	void setMemoryLinkUnitControlSystem(CUnitTool_UnitControlSystem* pUnitControlSystem)
	{
		m_pUnitControlSystem = pUnitControlSystem;
	}

private: // Camera Variables
	float m_fCameraX, m_fCameraY;
	float m_fCameraSpeed;
	float m_fCameraMinX, m_fCameraMinY;
	float m_fCameraMaxX, m_fCameraMaxY;
	
public:
	CUnitTool_CameraSystem();
	~CUnitTool_CameraSystem();

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
};

#endif // !_UNITTOOL_CAMERASYSTEM_H
