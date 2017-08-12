#ifndef _CAMERASYSTEM_H
#define _CAMERASYSTEM_H

class CameraSystem;

#include "systemBase.h"

namespace CameraSystemNS
{
	const UCHAR CAMERA_MOVE_LEFT_KEY = 'A';
	const UCHAR CAMERA_MOVE_RIGHT_KEY = 'D';
	const UCHAR CAMERA_MOVE_UP_KEY = 'W';
	const UCHAR CAMERA_MOVE_DOWN_KEY = 'S';

	const UCHAR CAMERA_ZOOM_IN_KEY = VK_PRIOR;
	const UCHAR CAMERA_ZOOM_OUT_KEY = VK_NEXT;
	const UCHAR CAMERA_BOOST_KEY = VK_SHIFT;
	const UINT CAMERA_SPEED = 10;
	const UINT CAMERA_BOOST = 2;
	const float CAMERA_ZOOM_RATE = 0.1f;
	const UINT CAMERA_MOVE_LIMIT = 100;
}

class MinimapViewer;
class MapSystem;
class CameraSystem : public SystemBase
{
private:
	float cameraX, cameraY;
	float cameraSpeed;
	float cameraAngle;
	float cameraZoomRate;		// 0 ~ 1 [Wheel zDelta 10.0f = scale 0.1f] 
	float cameraZoomSpeed;

	MapSystem* m_pMapSystem;
	MinimapViewer* m_pMinimap;
	Input* m_pInput;
	bool m_bCameraBoost;
public:
	CameraSystem();
	~CameraSystem();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void zoomIn();
	void zoomOut();

	void setCameraSpeed(float speed){ cameraSpeed = speed; }
	void setCameraPos(float x, float y);
	void setcameraAngle(float angle) { cameraAngle = angle; }
	
	float getCameraX() { return cameraX; }
	float getCameraY() { return cameraY; }
	float getCameraSpeed() { return cameraSpeed; }
	float getCameraAngle() { return cameraAngle; }
	float getCameraZoomRate() { return cameraZoomRate; }
	float getCameraZoomSpeed() { return cameraZoomSpeed; }

	void setMemoryLinkMapSystem(MapSystem* pMapSys) { m_pMapSystem = pMapSys; }
	void setMemoryLinkMinimap(MinimapViewer* pMinimap) { m_pMinimap = pMinimap; }
};

#endif // !_CAMERASYSTEM_H
