#include "stdafx.h"
#include "saveLoadViewer.h"


SaveLoadViewer::SaveLoadViewer()
{
	m_ViewerType = VIEWER_TYPE::VIEWER_TYPE_NONE;
}


SaveLoadViewer::~SaveLoadViewer()
{
}

bool SaveLoadViewer::initialize(Graphics * g, Input * i)
{
	return false;
}

void SaveLoadViewer::update(float frameTime)
{
}

void SaveLoadViewer::render()
{
}

void SaveLoadViewer::callLoadViewer()
{
}

void SaveLoadViewer::callSaveViewer()
{
}
