#ifndef _CAMERASYSTEM_H
#define _CAMERASYSTEM_H

class CameraSystem;

namespace CameraSystemNS
{
	const UCHAR CAMERA_MOVE_LEFT_KEY = 'A';
	const UCHAR CAMERA_MOVE_RIGHT_KEY = 'D';
	const UCHAR CAMERA_MOVE_UP_KEY = 'W';
	const UCHAR CAMERA_MOVE_DOWN_KEY = 'S';

	const UCHAR CAMERA_ZOOM_IN_KEY = VK_PRIOR;
	const UCHAR CAMERA_ZOOM_OUT_KEY = VK_NEXT;
}

class MapSystem;
class CameraSystem
{
private:
	float cameraX, cameraY;
	float cameraSpeed;
	float cameraAngle;
	float cameraZoomRate;		// 0 ~ 1 [Wheel zDelta 10.0f = scale 0.1f] 
	float cameraZoomSpeed;

	MapSystem* pMapSystem;

public:
	CameraSystem();
	~CameraSystem();

	bool initialize();
	void update(Input* input);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void zoomIn();
	void zoomOut();

	void setCameraSpeed(float speed) { cameraSpeed = speed; }
	void setCameraPos(float x, float y) { cameraX = x, cameraY = y; }
	void setcameraAngle(float angle) { cameraAngle = angle; }
	
	float getCameraX() { return cameraX; }
	float getCameraY() { return cameraY; }
	float getCameraSpeed() { return cameraSpeed; }
	float getCameraAngle() { return cameraAngle; }
	float getCameraZoomRate() { return cameraZoomRate; }
	float getCameraZoomSpeed() { return cameraZoomSpeed; }

	void setMemoryLinkMapSystem(MapSystem* pMapSys) { pMapSystem = pMapSys; }
};

#endif // !_CAMERASYSTEM_H
