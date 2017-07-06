#ifndef _OBJECTCONTROLVIEWER_H
#define _OBJECTCONTROLVIEWER_H

class ObjectControlViewer;

#include "systemUIDialog.h"
#include "mapTileData.h"

namespace objectControlViewerNS
{
	const UINT WIDTH = 400;				// width of treeViewer
	const UINT HEIGHT = 300;			// height of treeViewer
	const UINT X = WINSIZEX - WIDTH;	// Viewer location X
	const UINT Y = WINSIZEY - 300;		// Viewer location Y
	const UINT MARGIN = 4;              // text margin from Viewer edge
	const char FONT[] = "Courier New";  // Viewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color

}
enum class OBJECT_COLLISION_TYPE
{
	COLLISION_BOX, COLLISION_CIRCLE, COLLISION_ISOMETRIC, COLLISION_PIXEL
};

namespace objectControlNS
{
	const std::string OBJECT_CONTROL_TITLE = "OBJECT CONTROL";
	const std::string OBJECT_CONTROL_TEXTURE = "TEXTURE : ";
	const std::string OBJECT_CONTROL_LAYER = "LAYER : ";
	const std::string OBJECT_CONTROL_CUSTOM_POS = "FREE POSITION : ";
	const std::string OBJECT_CONTROL_POS_X = "X : ";
	const std::string OBJECT_CONTROL_POS_Y = "Y : ";
	const std::string OBJECT_CONTROL_WIDTH = "WIDTH : ";
	const std::string OBJECT_CONTROL_HEIGHT = "HEIGHT : ";
	const std::string OBJECT_CONTROL_COLLISION = "COLLISION TYPE : ";

	const UINT OBJECT_CONTROL_BOX_HEIGHT = 15;

	const std::string OBJECT_CONTROL_COLLISION_BOX = "COLLISION_BOX";
	const std::string OBJECT_CONTROL_COLLISION_CIRCLE = "COLLISION_CIRCLE";
	const std::string OBJECT_CONTROL_COLLISION_ISOMETRIC = "COLLISION_ISOMETRIC";
	const std::string OBJECT_CONTROL_COLLISION_PIXEL = "COLLISION_PIXEL";
}

class ObjectControlViewer : public SystemUIDialog
{
private:
	RECT m_rcTitle;
	RECT m_rcControl;

	std::string m_textureName;
	int m_layer;
	bool m_bFreePosition;
	int m_posX, m_posY;
	int m_width, m_height;
	OBJECT_COLLISION_TYPE m_collisionType;
private:
	MapTileData* m_SelectObjectData;

public:
	ObjectControlViewer();
	~ObjectControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ======================================================
	// Setter Functions
	// ======================================================
	void setSelectObjectData(MapTileData* pSelectObject)
	{
		m_SelectObjectData = pSelectObject;
	}
};

#endif // !_OBJECTCONTROLVIEWER_H
