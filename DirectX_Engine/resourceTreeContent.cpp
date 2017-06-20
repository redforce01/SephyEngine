#include "stdafx.h"
#include "resourceTreeContent.h"


ResourceTreeContent::ResourceTreeContent()
{
	pGraphics = nullptr;
	pInput = nullptr;
	contentType = CONTENTSTYPE::CONTENTS_UNKNOWN;
	posX = posY = 0;
	width = height = 0;
	margin = 0;

	visible = false;
	initialized = false;
}


ResourceTreeContent::~ResourceTreeContent()
{
}

bool ResourceTreeContent::initialize(Graphics * g, Input * i, CONTENTSTYPE type, std::string msg, float x, float y, float w, float h, float m)
{
	bool success = false;

	try
	{
		if (g == nullptr || i == nullptr)
			return false;

		pGraphics = g;
		pInput = i;
		contentType = type;
		message = msg;
		posX = x, posY = y;
		width = w, height = h;
		margin = m;

		rcText = RectMake(x + m, y + m, w - m, h - m);
		rcContent = RectMake(x, y, w, h);
		
		success = initialized = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "ResourceTreeView Content Initialize Failed", "Error", MB_OK);
	}

	return success;
}

void ResourceTreeContent::draw()
{
	pGraphics->spriteBegin();
	
	setupRect();
	dxFont.print(message, rcText, DT_LEFT);

	pGraphics->spriteEnd();
}

void ResourceTreeContent::changePos(float x, float y)
{
	posX = x;
	posY = y;

	setupRect();
}

void ResourceTreeContent::setupRect()
{
	int rowHeight = rcText.bottom + 2;
	if (rowHeight <= 0)
		rowHeight = 20;

	rcText.left = (long)(posX + margin);
	rcText.right = (long)(rcText.right + width - margin);
	rcText.top = rcText.bottom - rowHeight;
	rcText.bottom = (long)(posY + height - 2 * margin - 2 * rowHeight);
}

void ResourceTreeContent::setShowHide()
{
	if (!initialized)
		return;
	visible = !visible;
}

void ResourceTreeContent::setShowHide(bool flag)
{
	if (!initialized)
		return;
	visible = flag;
}
