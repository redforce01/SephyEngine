#include "stdafx.h"
#include "logViewer.h"


LogViewer::LogViewer()
{
}


LogViewer::~LogViewer()
{
}

bool LogViewer::initialize(Graphics * g, Input * i)
{


	return false;
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


}
