#include "stdafx.h"
#include "mapTileViewer.h"


MapTileViewer::MapTileViewer()
{
	fontColor = mapTileViewerNS::FONT_COLOR;
	backColor = mapTileViewerNS::BACK_COLOR;
}


MapTileViewer::~MapTileViewer()
{
}

bool MapTileViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;

	try
	{

		success = SystemUIDialog::initialize(g, i, mapTileViewerNS::X, mapTileViewerNS::Y, mapTileViewerNS::WIDTH, mapTileViewerNS::HEIGHT, mapTileViewerNS::MARGIN);
	}
	catch (...)
	{

	}

	return success;
}

void MapTileViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);
}

void MapTileViewer::render()
{
	SystemUIDialog::render();

	pGraphics->spriteBegin();




	pGraphics->spriteEnd();
}
