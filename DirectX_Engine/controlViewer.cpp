#include "stdafx.h"
#include "controlViewer.h"


ControlViewer::ControlViewer()
{
	fontColor = toolControlViewerNS::FONT_COLOR;
	backColor = toolControlViewerNS::BACK_COLOR;

	m_pSaveButton = nullptr;
	m_pLoadButton = nullptr;
	m_pResetButton = nullptr;
	m_pDebugButton = nullptr;
	m_pDebugCellButton = nullptr;
	m_pDebugObjectButton = nullptr;
	m_pDebugEventObjectButton = nullptr;
	m_pPerformButton = nullptr;
	m_pExitButton = nullptr;
}


ControlViewer::~ControlViewer()
{
	SAFE_DELETE(m_pSaveButton);
	SAFE_DELETE(m_pLoadButton);
	SAFE_DELETE(m_pResetButton);
	SAFE_DELETE(m_pDebugButton);
	SAFE_DELETE(m_pDebugCellButton);
	SAFE_DELETE(m_pDebugObjectButton);
	SAFE_DELETE(m_pDebugEventObjectButton);
	SAFE_DELETE(m_pPerformButton);
	SAFE_DELETE(m_pExitButton);
}

bool ControlViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		success = SystemUIDialog::initializeDialog(g, i, toolControlViewerNS::X, toolControlViewerNS::Y, toolControlViewerNS::WIDTH, toolControlViewerNS::HEIGHT, toolControlViewerNS::MARGIN);


		m_pSaveButton = new Control_SaveButton;
		m_pSaveButton->initialize(g, i, controlButtonNS::BUTTON_SAVE_ID, this,
			controlButtonNS::BUTTON_SAVE_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pLoadButton = new Control_LoadButton;
		m_pLoadButton->initialize(g, i, controlButtonNS::BUTTON_LOAD_ID, this,
			controlButtonNS::BUTTON_LOAD_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pResetButton = new Control_ResetButton;
		m_pResetButton->initialize(g, i, controlButtonNS::BUTTON_RESET_ID, this,
			controlButtonNS::BUTTON_RESET_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pDebugButton = new Control_DebugButton;
		m_pDebugButton->initialize(g, i, controlButtonNS::BUTTON_DEBUG_ID, this,
			controlButtonNS::BUTTON_DEBUG_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pDebugCellButton = new Control_DebugCellButton;
		m_pDebugCellButton->initialize(g, i, controlButtonNS::BUTTON_DEBUG_CELL_ID, this,
			controlButtonNS::BUTTON_DEBUG_CELL_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pDebugObjectButton = new Control_DebugObjectButton;
		m_pDebugObjectButton->initialize(g, i, controlButtonNS::BUTTON_DEBUG_OBJECT_ID, this,
			controlButtonNS::BUTTON_DEBUG_OBJECT_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);
		
		m_pDebugEventObjectButton = new Control_DebugEventObjButton;
		m_pDebugEventObjectButton->initialize(g, i, controlButtonNS::BUTTON_DEBUG_EVENT_ID, this,
			controlButtonNS::BUTTON_DEBUG_EVENT_OBJECT_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pPerformButton = new Control_PerformButton;
		m_pPerformButton->initialize(g, i, controlButtonNS::BUTTON_PERFORM_ID, this,
			controlButtonNS::BUTTON_PERFORM_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);

		m_pExitButton = new Control_ExitButton;
		m_pExitButton->initialize(g, i, controlButtonNS::BUTTON_EXIT_ID, this,
			controlButtonNS::BUTTON_EXIT_POS_X,
			controlButtonNS::BUTTON_BASIC_Y,
			controlButtonNS::BUTTON_WIDTH,
			controlButtonNS::BUTTON_HEIGHT,
			controlButtonNS::BUTTON_MARGIN);
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

	if (m_bVisible == false)
		return;

	m_pSaveButton->update(frameTime);
	m_pLoadButton->update(frameTime);
	m_pResetButton->update(frameTime);
	m_pDebugButton->update(frameTime);
	m_pDebugCellButton->update(frameTime);
	m_pDebugObjectButton->update(frameTime);
	m_pDebugEventObjectButton->update(frameTime);
	m_pPerformButton->update(frameTime);
	m_pExitButton->update(frameTime);
}

void ControlViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pSaveButton->render();
	m_pLoadButton->render();
	m_pResetButton->render();
	m_pDebugButton->render();
	m_pDebugCellButton->render();
	m_pDebugObjectButton->render();
	m_pDebugEventObjectButton->render();
	m_pPerformButton->render();
	m_pExitButton->render();
}
