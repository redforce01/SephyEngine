#include "stdafx.h"
#include "logViewer.h"


LogViewer::LogViewer()
{
	m_rcLogBox = { 0, };
	m_rcTitle = { 0, };
}


LogViewer::~LogViewer()
{
}

bool LogViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{
		m_rcTitle = RectMake(logViewerNS::X + 4, g_fScreenHeight - logViewerNS::Y + 4, logViewerNS::WIDTH - 4, logViewerNS::LOG_HEIGHT);
		m_rcLogBox = RectMake(logViewerNS::X + 5, g_fScreenHeight- logViewerNS::Y + logViewerNS::LOG_HEIGHT, logViewerNS::WIDTH - (5 * 2), logViewerNS::LOG_HEIGHT);

		success = m_dxFont.initialize(g, logViewerNS::FONT_HEIGHT, false, false, logViewerNS::FONT);
		if (success == false)
			throw("LogViewer Font Initialized Failed");

		success = SystemUIDialog::initializeDialog(g, i,
			logViewerNS::X,
			g_fScreenHeight - logViewerNS::Y,
			logViewerNS::WIDTH,
			logViewerNS::HEIGHT,
			logViewerNS::MARGIN);
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "LogViewer Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void LogViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);

	if (getMouseOver() == false)
		return;
}

void LogViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();
	m_dxFont.print(logViewerNS::LOGBOX_TITLE, m_rcTitle, DT_LEFT);
	m_rcLogBox = RectMake(logViewerNS::X + 5, g_fScreenHeight - logViewerNS::Y + logViewerNS::LOG_HEIGHT, logViewerNS::WIDTH - (5 * 2), logViewerNS::LOG_HEIGHT);
	for (auto iter : m_arrLog)
	{
		m_dxFont.print(iter, m_rcLogBox, DT_LEFT);
		m_rcLogBox.top += logViewerNS::LOG_HEIGHT;
		m_rcLogBox.bottom += logViewerNS::LOG_HEIGHT;
		if (m_rcLogBox.bottom > m_rcBoundingBox.bottom)
			break;
	}

	m_pGraphics->spriteEnd();
}
