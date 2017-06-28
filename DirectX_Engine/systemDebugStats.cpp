#include "stdafx.h"
#include "systemDebugStats.h"


SystemDebugStats::SystemDebugStats()
{
	fontColor = debugStatsNS::FONT_COLOR;
	backColor = debugStatsNS::BACK_COLOR;
}


SystemDebugStats::~SystemDebugStats()
{
}

bool SystemDebugStats::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initialize(g, i, debugStatsNS::X, debugStatsNS::Y, debugStatsNS::WIDTH, debugStatsNS::HEIGHT, debugStatsNS::MARGIN);

		m_rcText = RectMake(
			debugStatsNS::X + debugStatsNS::MARGIN,
			debugStatsNS::Y + debugStatsNS::MARGIN,
			debugStatsNS::WIDTH - debugStatsNS::MARGIN,
			debugStatsNS::HEIGHT - debugStatsNS::MARGIN);

		dxFont.initialize(g, debugStatsNS::FONT_SIZE, false, false, debugStatsNS::FONT);

	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "SystemDebugStats Initialized Failed", "Error", MB_OK);
	}

	return success;
}

void SystemDebugStats::update(float frameTime)
{
	SystemUIDialog::update(frameTime);
}

void SystemDebugStats::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	pGraphics->spriteBegin();
	m_rcText.left = debugStatsNS::X + debugStatsNS::MARGIN;
	m_rcText.top = debugStatsNS::Y + debugStatsNS::MARGIN;
	m_rcText.right = m_rcText.left + debugStatsNS::WIDTH;
	m_rcText.bottom = m_rcText.top + debugStatsNS::TEXT_HEIGHT;

	for (auto iter : m_mapMessage)
	{
		dxFont.print(iter.second, m_rcText, DT_LEFT);
		m_rcText.top += debugStatsNS::TEXT_HEIGHT;
		m_rcText.bottom += debugStatsNS::TEXT_HEIGHT;
	}
	pGraphics->spriteEnd();
}