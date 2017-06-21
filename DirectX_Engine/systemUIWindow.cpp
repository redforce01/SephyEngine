#include "stdafx.h"
#include "systemUIWindow.h"


SystemUIWindow::SystemUIWindow()
{
	x = y = 0;
	width = height = 0;
	margin = 0;
	vertexBuffer = nullptr;

	initialized = false;
	visible = false;
}


SystemUIWindow::~SystemUIWindow()
{
}

bool SystemUIWindow::initialize(Graphics * g, Input * i, int x, int y, int w, int h, int m)
{

	try
	{
		if (g == nullptr || i == nullptr)
			return false;

		pGraphics = g;
		pInput = i;
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		this->margin = m;

		// top left
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// top right
		vtx[1].x = x + w;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// bottom right
		vtx[2].x = x + w;
		vtx[2].y = y + h;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// bottom left
		vtx[3].x = x;
		vtx[3].y = y + h;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
		rcWindow = RectMake(x, y, w, h);
	}
	catch (...)
	{

	}


	return false;
}
