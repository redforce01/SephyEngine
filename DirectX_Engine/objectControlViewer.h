#ifndef _OBJECTCONTROLVIEWER_H
#define _OBJECTCONTROLVIEWER_H

class ObjectControlViewer;

#include "systemUIDialog.h"
#include "systemUIEdit.h"
#include "mapTileData.h"
#include "freePositionButton.h"

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
	const std::string OBJECT_CONTROL_TEXTURE = "TEXTURE";
	const std::string OBJECT_CONTROL_LAYER = "LAYER";
	const std::string OBJECT_CONTROL_FREE_POSITION = "FREE POSITION";
	const std::string OBJECT_CONTROL_POS_X = "X";
	const std::string OBJECT_CONTROL_POS_Y = "Y";
	const std::string OBJECT_CONTROL_WIDTH = "WIDTH";
	const std::string OBJECT_CONTROL_HEIGHT = "HEIGH";
	const std::string OBJECT_CONTROL_COLLISION = "COLLISION TYPE";

	const UINT OBJECT_CONTROL_BOX_WIDTH = 20;
	const UINT OBJECT_CONTROL_BOX_HEIGHT = 15;

	const std::string OBJECT_CONTROL_COLLISION_BOX = "COLLISION_BOX";
	const std::string OBJECT_CONTROL_COLLISION_CIRCLE = "COLLISION_CIRCLE";
	const std::string OBJECT_CONTROL_COLLISION_ISOMETRIC = "COLLISION_ISOMETRIC";
	const std::string OBJECT_CONTROL_COLLISION_PIXEL = "COLLISION_PIXEL";


	const UINT EDIT_CONTROL_FIRST_POS_X = 10;
	const UINT EDIT_CONTROL_FIRST_POS_Y = 30;
	const UINT EDIT_CONTROL_WIDTH = 370;
	const UINT EDIT_CONTROL_HEIGHT = 25;
	const UINT EDIT_CONTROL_MARGIN = 4;
	const float EDIT_CONTROL_BOX_RATE = 0.3f;

	const UINT EDIT_CONTROL_TEXTURE_ID = 51;
	const UINT EDIT_CONTROL_LAYER_ID = 52;
	const UINT EDIT_CONTROL_POS_X_ID = 54;
	const UINT EDIT_CONTROL_POS_Y_ID = 55;
	const UINT EDIT_CONTROL_POS_WIDTH_ID = 56;
	const UINT EDIT_CONTROL_POS_HEIGHT_ID = 57;
	const UINT EDIT_CONTROL_COLLISION_ID = 58;

	const UINT COLLISION_KEY_HINT_POS_Y = 240;
	const std::string COLLISION_KEY_HINT = " ---------- Collision Key ----------";
	const std::string COLLISION_KEY_BOX = "Box";
	const std::string COLLISION_KEY_CIRCLE = "Circle";
	const std::string COLLISION_KEY_ISOMETRIC = "Isometric";
	const std::string COLLISION_KEY_PIXEL = "Pixel";

	const std::string FREEPOSITION_STATE_ON = "FREE MODE ON";
	const std::string FREEPOSITION_STATE_OFF = "FREE MODE ON";
	const UINT FREEPOSITION_BUTTON_ID = 53;
	const UINT FREEPOSITION_BUTTON_POS_X = objectControlViewerNS::WIDTH - 50;
	const UINT FREEPOSITION_BUTTON_POS_Y = 0;
	const UINT FREEPOSITION_BUTTON_WIDTH = 40;
	const UINT FREEPOSITION_BUTTON_HEIGHT = 40;
	const UINT FREEPOSITION_BUTTON_MARGIN = 0;
	const UINT FREEPOSITION_TEXT_RECT_WIDTH = 100;
	const UINT FREEPOSITION_TEXT_RECT_HEIGHT = 10;
}

class MapTileViewer;
class ObjectControlViewer : public SystemUIDialog
{
private:
	RECT m_rcTitle;
	RECT m_rcControl;
	RECT m_rcCollisionHint;

	// Object Control Viewer Text Variables
	bool m_bFreePosition;
	std::string m_textureName;
	int m_layer;
	int m_posX, m_posY;
	int m_width, m_height;
	OBJECT_COLLISION_TYPE m_collisionType;

private: // MapData
	MapTileData* m_SelectObjectData;
	MapTileViewer* m_pMapTileViewer;

private: // Button
	FreePositionButton* m_pFreePositionButton;
	RECT m_rcFreeText;

private: //Edit Controls
	SystemUIEdit* m_pTextureEdit;
	SystemUIEdit* m_pLayerEdit;
	//SystemUIEdit* m_pFreePositionEdit;	// Not Using...
	SystemUIEdit* m_pPosXEdit;
	SystemUIEdit* m_pPosYEdit;
	SystemUIEdit* m_pWidthEdit;
	SystemUIEdit* m_pHeightEdit;
	SystemUIEdit* m_pCollisionEdit;	
public:
	ObjectControlViewer();
	~ObjectControlViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;

	// ======================================================
	// Memeber Functions
	// ======================================================
	void makeObject();

	// Check Collision Type
	OBJECT_COLLISION_TYPE checkCollisionType();

	// ======================================================
	// Setter Functions
	// ======================================================
	void setSelectObjectData(MapTileData* pSelectObject)
	{ m_SelectObjectData = pSelectObject; }

	void setFreePositionMode(bool b)
	{
		m_bFreePosition = b;
	}

	// ======================================================
	// Getter Functions
	// ======================================================
	bool getFreePoisitionMode() const
	{
		return m_bFreePosition;
	}

	


	// Memory Link Function For Forward Pointer
	void setMemoryLinkMapTileViewer(MapTileViewer* pMapTileViewer)
	{ m_pMapTileViewer = pMapTileViewer; }
};

#endif // !_OBJECTCONTROLVIEWER_H
