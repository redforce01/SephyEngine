#include "stdafx.h"
#include "objectControlViewer.h"


ObjectControlViewer::ObjectControlViewer()
{
	fontColor = objectControlViewerNS::FONT_COLOR;
	backColor = objectControlViewerNS::BACK_COLOR;
	m_SelectObjectData = nullptr;

	m_layer = 0;
	m_bFreePosition = false;
	m_posX = m_posY = 0;
	m_width = m_height = 0;
	m_collisionType = OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC;
}


ObjectControlViewer::~ObjectControlViewer()
{
}

bool ObjectControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		m_rcTitle = RectMake(objectControlViewerNS::X + objectControlViewerNS::MARGIN, objectControlViewerNS::Y + objectControlViewerNS::MARGIN,
			objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2), objectControlViewerNS::FONT_HEIGHT + objectControlViewerNS::MARGIN);
		m_rcControl = RectMake(
			objectControlViewerNS::X + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT,
			objectControlViewerNS::Y + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT + objectControlNS::OBJECT_CONTROL_BOX_HEIGHT,
			objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2),
			objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

		success = m_dxFont.initialize(g, objectControlViewerNS::FONT_HEIGHT, false, false, objectControlViewerNS::FONT);
		if (success == false)
			throw("Object Control Viewer DxFont initialized Failed");

		success = SystemUIDialog::initializeDialog(g, i, objectControlViewerNS::X, objectControlViewerNS::Y, objectControlViewerNS::WIDTH, objectControlViewerNS::HEIGHT, objectControlViewerNS::MARGIN);
		if (success == false)
			throw("Object Control Viewer SystemUIDialog initialized Failed");
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
}

void ObjectControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	// Print Object Control Title
	m_dxFont.print(objectControlNS::OBJECT_CONTROL_TITLE, m_rcTitle, DT_LEFT | DT_VCENTER);	
	
	m_rcControl = RectMake(
		objectControlViewerNS::X + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT,
		objectControlViewerNS::Y + objectControlViewerNS::MARGIN + objectControlViewerNS::FONT_HEIGHT + objectControlNS::OBJECT_CONTROL_BOX_HEIGHT,
		objectControlViewerNS::WIDTH - (objectControlViewerNS::MARGIN * 2),
		objectControlNS::OBJECT_CONTROL_BOX_HEIGHT);

	std::string strData;

	// Print Object Control Texture
	strData = objectControlNS::OBJECT_CONTROL_TEXTURE;
	if (m_SelectObjectData != nullptr)
		strData += m_SelectObjectData->getTextureName();
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control Layer
	strData = objectControlNS::OBJECT_CONTROL_LAYER;
	if (m_SelectObjectData != nullptr)
		strData += std::to_string(m_layer);
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control Free Position
	strData = objectControlNS::OBJECT_CONTROL_CUSTOM_POS;
	if (m_bFreePosition)
		strData += "on";
	else
		strData += "off";
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control PosX
	strData = objectControlNS::OBJECT_CONTROL_POS_X;
	strData += std::to_string(m_posX);
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control PosY
	strData = objectControlNS::OBJECT_CONTROL_POS_Y;
	strData += std::to_string(m_posY);
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control Width
	strData = objectControlNS::OBJECT_CONTROL_WIDTH;
	strData += std::to_string(m_width);
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control Height
	strData = objectControlNS::OBJECT_CONTROL_HEIGHT;
	strData += std::to_string(m_height);
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;

	// Print Object Control Collision type
	strData = objectControlNS::OBJECT_CONTROL_COLLISION;
	switch (m_collisionType)
	{
	case OBJECT_COLLISION_TYPE::COLLISION_BOX:
		strData += objectControlNS::OBJECT_CONTROL_COLLISION_BOX;
		break;
	case OBJECT_COLLISION_TYPE::COLLISION_CIRCLE:
		strData += objectControlNS::OBJECT_CONTROL_COLLISION_CIRCLE;
		break;
	case OBJECT_COLLISION_TYPE::COLLISION_ISOMETRIC:
		strData += objectControlNS::OBJECT_CONTROL_COLLISION_ISOMETRIC;
		break;
	case OBJECT_COLLISION_TYPE::COLLISION_PIXEL:
		strData += objectControlNS::OBJECT_CONTROL_COLLISION_PIXEL;
		break;
	}
	m_dxFont.print(strData, m_rcControl, DT_LEFT);
	m_rcControl.top += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;
	m_rcControl.bottom += objectControlNS::OBJECT_CONTROL_BOX_HEIGHT;


	m_pGraphics->spriteEnd();
}
