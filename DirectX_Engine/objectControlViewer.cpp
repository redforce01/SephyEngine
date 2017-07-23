#include "stdafx.h"
#include "objectControlViewer.h"
#include "mapTileViewer.h"
#include "logViewer.h"
#include "mapSystem.h"

ObjectControlViewer::ObjectControlViewer()
{
	fontColor = objectControlViewerNS::FONT_COLOR;
	backColor = objectControlViewerNS::BACK_COLOR;

	m_pSelectObjectData = nullptr;	
	m_pMapTileViewer = nullptr;
	m_pLogViewer = nullptr;
	m_pMapSystem = nullptr;

	m_layer = 0;
	m_bFreePosition = true;
	m_posX = m_posY = 0;
	m_width = m_height = 0;
	m_collisionType = OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC;
}


ObjectControlViewer::~ObjectControlViewer()
{	
	SAFE_DELETE(m_pTextureEdit);
	SAFE_DELETE(m_pLayerEdit);
	//SAFE_DELETE(m_pFreePositionEdit);
	SAFE_DELETE(m_pPosXEdit);
	SAFE_DELETE(m_pPosYEdit);
	SAFE_DELETE(m_pWidthEdit);
	SAFE_DELETE(m_pHeightEdit);
	SAFE_DELETE(m_pCollisionEdit);
	SAFE_DELETE(m_pFreePositionButton);
	SAFE_DELETE(m_pMakeObjectButton);
}

bool ObjectControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		m_rcTitle = RectMake(g_fScreenWidth - objectControlViewerNS::X + objectControlViewerNS::MARGIN,
			g_fScreenHeight - objectControlViewerNS::Y + objectControlViewerNS::MARGIN,
			objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2), objectControlViewerNS::FONT_HEIGHT + objectControlViewerNS::MARGIN);
		m_rcControl = RectMake(
			g_fScreenWidth - objectControlViewerNS::X + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT,
			g_fScreenHeight - objectControlViewerNS::Y + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT + objectControlNS::OBJECT_CONTROL_BOX_HEIGHT,
			objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2),
			objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

		m_rcCollisionHint = RectMake(g_fScreenWidth - objectControlViewerNS::X + objectControlNS::OBJECT_CONTROL_BOX_WIDTH,
			g_fScreenHeight - objectControlViewerNS::Y + 250,
			objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2),	objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

		success = m_dxFont.initialize(g, objectControlViewerNS::FONT_HEIGHT, false, false, objectControlViewerNS::FONT);
		if (success == false)
			throw("Object Control Viewer DxFont initialized Failed");

		success = SystemUIDialog::initializeDialog(g, i, 			
			g_fScreenWidth - objectControlViewerNS::X,
			g_fScreenHeight - objectControlViewerNS::Y,
			objectControlViewerNS::WIDTH,
			objectControlViewerNS::HEIGHT,
			objectControlViewerNS::MARGIN);

		if (success == false)
			throw("Object Control Viewer SystemUIDialog initialized Failed");

#pragma region OBJECT_CONTROL_VIEWER_EDIT_CONTROL_INITIALIZE
		
		m_pTextureEdit = new SystemUIEdit;
		m_pTextureEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_TEXTURE_ID, true, "TextureName...", objectControlNS::OBJECT_CONTROL_TEXTURE, false, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);
		m_pLayerEdit = new SystemUIEdit;
		m_pLayerEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_LAYER_ID, true, "Object Layer (Number Only)", objectControlNS::OBJECT_CONTROL_LAYER, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);

		//m_pFreePositionEdit = new SystemUIEdit;
		//m_pFreePositionEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_FREEPOSITION_ID, true, "0 == none free / 1 == free", objectControlNS::OBJECT_CONTROL_FREE_POSITION, true, this,
		//	objectControlNS::EDIT_CONTROL_BOX_RATE,
		//	objectControlNS::EDIT_CONTROL_FIRST_POS_X,
		//	objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 2,
		//	objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);


		m_pPosXEdit = new SystemUIEdit;
		m_pPosXEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_POS_X_ID, false, "", objectControlNS::OBJECT_CONTROL_POS_X, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 2,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);
		m_pPosXEdit->setEditText("0");

		m_pPosYEdit = new SystemUIEdit;
		m_pPosYEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_POS_Y_ID, false, "", objectControlNS::OBJECT_CONTROL_POS_Y, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 3,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);
		m_pPosYEdit->setEditText("0");

		m_pWidthEdit = new SystemUIEdit;
		m_pWidthEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_POS_WIDTH_ID, false, "", objectControlNS::OBJECT_CONTROL_WIDTH, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 4,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);
		m_pWidthEdit->setEditText("0");

		m_pHeightEdit = new SystemUIEdit;
		m_pHeightEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_POS_HEIGHT_ID, false, "", objectControlNS::OBJECT_CONTROL_HEIGHT, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 5,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);
		m_pHeightEdit->setEditText("0");

		m_pCollisionEdit = new SystemUIEdit;
		m_pCollisionEdit->initEdit(g, i, objectControlNS::EDIT_CONTROL_COLLISION_ID, true, "Collision Type...", objectControlNS::OBJECT_CONTROL_COLLISION, true, this,
			objectControlNS::EDIT_CONTROL_BOX_RATE,
			objectControlNS::EDIT_CONTROL_FIRST_POS_X,
			objectControlNS::EDIT_CONTROL_FIRST_POS_Y + objectControlNS::EDIT_CONTROL_HEIGHT * 6,
			objectControlNS::EDIT_CONTROL_WIDTH, objectControlNS::EDIT_CONTROL_HEIGHT, objectControlNS::EDIT_CONTROL_MARGIN);

#pragma endregion

#pragma region OBJECT_CONTROL_VIEWER_BUTTON_INITIALIZE

		m_pFreePositionButton = new FreePositionButton;
		m_pFreePositionButton->initialize(g, i, objectControlNS::FREEPOSITION_BUTTON_ID, this,
			objectControlNS::FREEPOSITION_BUTTON_POS_X, objectControlNS::FREEPOSITION_BUTTON_POS_Y,
			objectControlNS::FREEPOSITION_BUTTON_WIDTH, objectControlNS::FREEPOSITION_BUTTON_HEIGHT,
			objectControlNS::FREEPOSITION_BUTTON_MARGIN);
		m_pFreePositionButton->setMemoryLinkObjectControlViewer(this);

		int left = m_pFreePositionButton->GetControlRECT().left - objectControlNS::FREEPOSITION_TEXT_RECT_WIDTH;
		int top = m_pFreePositionButton->GetControlRECT().top + objectControlNS::FREEPOSITION_TEXT_RECT_HEIGHT;
		m_rcFreeText = RectMake(left, top,
			objectControlNS::FREEPOSITION_TEXT_RECT_WIDTH,
			objectControlNS::FREEPOSITION_TEXT_RECT_HEIGHT);

		m_pMakeObjectButton = new MakeObjectButton;
		m_pMakeObjectButton->initialize(g, i, objectControlNS::MAKE_OBJECT_BUTTON_ID, this,
			objectControlNS::MAKE_OBJECT_BUTTON_POS_X, objectControlNS::MAKE_OBJECT_BUTTON_POS_Y,
			objectControlNS::MAKE_OBJECT_BUTTON_WIDTH, objectControlNS::MAKE_OBJECT_BUTTON_HEIGHT,
			objectControlNS::MAKE_OBJECT_BUTTON_MARGIN);
		m_pMakeObjectButton->setMemoryLinkObjectControlViewer(this);

		left = m_pMakeObjectButton->GetControlRECT().left - objectControlNS::MAKE_OBJECT_TEXT_RECT_WIDTH;
		top = m_pMakeObjectButton->GetControlRECT().top + objectControlNS::MAKE_OBJECT_TEXT_RECT_HEIGHT;
		m_rcMakeText = RectMake(left, top,
			objectControlNS::MAKE_OBJECT_TEXT_RECT_WIDTH,
			objectControlNS::MAKE_OBJECT_TEXT_RECT_HEIGHT);
		m_strMakeButtonTitle = objectControlNS::MAKE_OBJECT_TEXT;

#pragma endregion
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "Object Control Viewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void ObjectControlViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);

	if (m_pSelectObjectData)
	{
		m_pTextureEdit->setEditText(m_pSelectObjectData->getTextureName());
		m_textureName = m_pSelectObjectData->getTextureName();
	}
	
	if (m_bFreePosition)
		m_strFreeButtonTitle = objectControlNS::FREEPOSITION_STATE_ON;
	else
		m_strFreeButtonTitle = objectControlNS::FREEPOSITION_STATE_OFF;


	m_pTextureEdit->update(frameTime);
	m_pLayerEdit->update(frameTime);
	//m_pFreePositionEdit->update(frameTime);
	m_pPosXEdit->update(frameTime);
	m_pPosYEdit->update(frameTime);
	m_pWidthEdit->update(frameTime);
	m_pHeightEdit->update(frameTime);
	m_pCollisionEdit->update(frameTime);

	m_pFreePositionButton->update(frameTime);
	m_pMakeObjectButton->update(frameTime);
}

void ObjectControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	// =========================================
	// EditControls Render
	m_pTextureEdit->render();
	m_pTextureEdit->render();
	m_pLayerEdit->render();
	//m_pFreePositionEdit->render();
	m_pPosXEdit->render();
	m_pPosYEdit->render();
	m_pWidthEdit->render();
	m_pHeightEdit->render();
	m_pCollisionEdit->render();
	// =========================================


	// =========================================
	// Button Control Render
	m_pFreePositionButton->render();
	m_pMakeObjectButton->render();
	// =========================================


	// =========================================
	// Sprite Begin
	m_pGraphics->spriteBegin();

	// Print Object Control Title
	m_dxFont.print(objectControlNS::OBJECT_CONTROL_TITLE, m_rcTitle, DT_LEFT | DT_VCENTER);

	m_rcCollisionHint = RectMake(g_fScreenWidth - objectControlViewerNS::X + objectControlNS::OBJECT_CONTROL_BOX_WIDTH, 
		g_fScreenHeight - objectControlViewerNS::Y + objectControlNS::COLLISION_KEY_HINT_POS_Y,
		objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2), objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

	std::string collisionHint = objectControlNS::COLLISION_KEY_HINT;
	std::string collisionHintA = objectControlNS::COLLISION_KEY_BOX + ", " + objectControlNS::COLLISION_KEY_CIRCLE;
	std::string collisionHintB = objectControlNS::COLLISION_KEY_ISOMETRIC + ", " + objectControlNS::COLLISION_KEY_PIXEL;
	
	m_dxFont.print(collisionHint, m_rcCollisionHint, DT_LEFT | DT_VCENTER);
	m_rcCollisionHint.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcCollisionHint.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_dxFont.print(collisionHintA, m_rcCollisionHint, DT_LEFT | DT_VCENTER);
	m_rcCollisionHint.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcCollisionHint.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_dxFont.print(collisionHintB, m_rcCollisionHint, DT_LEFT | DT_VCENTER);
	m_rcCollisionHint.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcCollisionHint.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	
	m_dxFont.print(m_strFreeButtonTitle, m_rcFreeText, DT_LEFT | DT_VCENTER);	
	m_dxFont.print(m_strMakeButtonTitle, m_rcMakeText, DT_LEFT | DT_VCENTER);

	m_pGraphics->spriteEnd();
	// Sprite End
	// =========================================

#pragma region NOT USING CODE

	//m_rcControl = RectMake(
	//	objectControlViewerNS::X + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT,
	//	objectControlViewerNS::Y + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT + objectControlNS::OBJECT_CONTROL_BOX_HEIGHT,
	//	objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2),
	//	objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

	//std::string strData;
	//// Print Object Control Texture
	//strData = objectControlNS::OBJECT_CONTROL_TEXTURE;
	//if (m_SelectObjectData != nullptr)
	//	strData += m_SelectObjectData->getTextureName();
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control Layer
	//strData = objectControlNS::OBJECT_CONTROL_LAYER;
	//if (m_SelectObjectData != nullptr)
	//	strData += std::to_string(m_layer);
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control Free Position
	//strData = objectControlNS::OBJECT_CONTROL_CUSTOM_POS;
	//if (m_bFreePosition)
	//	strData += "on";
	//else
	//	strData += "off";
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control PosX
	//strData = objectControlNS::OBJECT_CONTROL_POS_X;
	//strData += std::to_string(m_posX);
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control PosY
	//strData = objectControlNS::OBJECT_CONTROL_POS_Y;
	//strData += std::to_string(m_posY);
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control Width
	//strData = objectControlNS::OBJECT_CONTROL_WIDTH;
	//strData += std::to_string(m_width);
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control Height
	//strData = objectControlNS::OBJECT_CONTROL_HEIGHT;
	//strData += std::to_string(m_height);
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	//// Print Object Control Collision type
	//strData = objectControlNS::OBJECT_CONTROL_COLLISION;
	//switch (m_collisionType)
	//{
	//case OBJECT_COLLISION_TYPE::COLLISION_BOX:
	//	strData += objectControlNS::OBJECT_CONTROL_COLLISION_BOX;
	//	break;
	//case OBJECT_COLLISION_TYPE::COLLISION_CIRCLE:
	//	strData += objectControlNS::OBJECT_CONTROL_COLLISION_CIRCLE;
	//	break;
	//case OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC:
	//	strData += objectControlNS::OBJECT_CONTROL_COLLISION_ISOMETRIC;
	//	break;
	//case OBJECT_COLLISION_TYPE::COLLISION_PIXEL:
	//	strData += objectControlNS::OBJECT_CONTROL_COLLISION_PIXEL;
	//	break;
	//}
	//m_dxFont.print(strData, m_rcControl, DT_LEFT);
	//m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	//m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

#pragma endregion

}

bool ObjectControlViewer::makeObject()
{
	bool success = false;
	try
	{
		if (m_pSelectObjectData == nullptr)
			return false;

		m_layer = (m_pLayerEdit->getEditText().size() != 0 ?
			std::stoi(m_pLayerEdit->getEditText()) : 0);
		m_posX = (m_pPosXEdit->getEditText().size() != 0 ?
			std::stoi(m_pPosXEdit->getEditText()) : 0);		
		m_posY = (m_pPosYEdit->getEditText().size() != 0 ?
			std::stoi(m_pPosYEdit->getEditText()) : 0);	
		m_width = (m_pWidthEdit->getEditText().size() != 0 ?
			std::stoi(m_pWidthEdit->getEditText()) : 0);		
		m_height = (m_pHeightEdit->getEditText().size() != 0 ?
			std::stoi(m_pHeightEdit->getEditText()) : 0);
		m_collisionType = checkCollisionType();
		
		m_pSelectObjectData->setPosition(m_posX, m_posY);
		m_pSelectObjectData->setWidth(m_width);
		m_pSelectObjectData->setHeight(m_height);		
		m_pSelectObjectData->setLayer(m_layer);
		m_pSelectObjectData->setObjectable(true);
		m_pSelectObjectData->setTextureName(m_textureName);
		m_pSelectObjectData->setCollisionType(m_collisionType);

		if (m_bFreePosition)
			m_pSelectObjectData->setFreePosition(true);
		else
			m_pSelectObjectData->setFreePosition(false);

		m_pLogViewer->addLog(objectControlNS::MAKE_OBJECT_RESULT_LOG_SUCCESS);
		return true;
	}
	catch (...)
	{
		m_pLogViewer->addLog(objectControlNS::MAKE_OBJECT_RESULT_LOG_FAIL);
		return false;
	}
}

OBJECT_COLLISION_TYPE ObjectControlViewer::checkCollisionType()
{	
	std::string strEnter = m_pCollisionEdit->getEditText();
	
	if (strEnter.compare(objectControlNS::COLLISION_KEY_BOX) == 0)
	{
		return OBJECT_COLLISION_TYPE::COLLISION_BOX;
	}
	else if (strEnter.compare(objectControlNS::COLLISION_KEY_CIRCLE) == 0)
	{
		return OBJECT_COLLISION_TYPE::COLLISION_CIRCLE;
	}
	else if (strEnter.compare(objectControlNS::COLLISION_KEY_ISOMETRIC) == 0)
	{
		return OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC;
	}
	else if (strEnter.compare(objectControlNS::COLLISION_KEY_PIXEL) == 0)
	{
		return OBJECT_COLLISION_TYPE::COLLISION_PIXEL;
	}
	return OBJECT_COLLISION_TYPE::COLLISION_BOX;
}
