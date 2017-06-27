#include "stdafx.h"
#include "controlViewer.h"


ControlViewer::ControlViewer()
{
	fontColor = toolControlViewerNS::FONT_COLOR;
	backColor = toolControlViewerNS::BACK_COLOR;
}


ControlViewer::~ControlViewer()
{
}

bool ControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		success = SystemUIDialog::initialize(g, i, toolControlViewerNS::X, toolControlViewerNS::Y, toolControlViewerNS::WIDTH, toolControlViewerNS::HEIGHT, toolControlViewerNS::MARGIN);


		m_pSaveButton = new Control_SaveButton;
		m_pSaveButton->initialize(g, i, toolControlViewerNS::controlIDSave, this, 0, 0, 40, 40, 2);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "ToolControl Viewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void ControlViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	m_pSaveButton->update(frameTime);
}

void ControlViewer::render()
{
	SystemUIDialog::render();

	m_pSaveButton->render();
}
