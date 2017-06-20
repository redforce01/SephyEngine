#include "stdafx.h"
#include "ResourceTreeViewer.h"


ResourceTreeViewer::ResourceTreeViewer()
{



	fontColor = treeViewerNS::FONT_COLOR;
	backColor = treeViewerNS::BACK_COLOR;
	vertexBuffer = nullptr;

	initialized = false;
	visible = false;
}


ResourceTreeViewer::~ResourceTreeViewer()
{
}

bool ResourceTreeViewer::initialize(Graphics* g, Input* i)
{
	bool success = false;

	try
	{
		pGraphics = g;
		pInput = i;

		// top left
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// top right
		vtx[1].x = x + treeViewerNS::WIDTH;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// bottom right
		vtx[2].x = x + treeViewerNS::WIDTH;
		vtx[2].y = y + treeViewerNS::HEIGHT;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// bottom left
		vtx[3].x = x;
		vtx[3].y = y + treeViewerNS::HEIGHT;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

		// initialize DirectX font
		if (dxFont.initialize(pGraphics, treeViewerNS::FONT_HEIGHT, false,
			false, consoleNS::FONT) == false)
			return false;      // if failed
		dxFont.setFontColor(fontColor);
		
		int resX, resY;
		resX = 0;
		resY = 5;
		auto total = FILEMANAGER->getAllFile();
		for (auto iter : total)
		{
			resX = 5;
			File* folder = new File();
			folder->initialize(g, i, &dxFont, CONTENTSTYPE::CONTENTS_FOLDER, iter.first, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
			addTreeRes(folder);
			resX += viewerChildTab;
			resY += viewerChildHeight;

			for (auto fileIter = iter.second->begin(); fileIter != iter.second->end(); fileIter++)
			{
				File* file = new File();
				file->initialize(g, i, &dxFont, CONTENTSTYPE::CONTENTS_FILE, (*fileIter)->fileName, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
				addTreeRes(file);
				resY += viewerChildHeight;
			}
		}

		success = initialized = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "ResourceViewer System Error", "Error", MB_OK);
	}
	
	return success;
}

void ResourceTreeViewer::update(float frameTime)
{

}

void ResourceTreeViewer::render()
{
	for (auto iter : resFiles)
	{
		iter.second->draw();
	}
}

bool ResourceTreeViewer::addTreeRes(File * pChild)
{
	//auto check = pChild->getViewName();
	//if (resFiles.find(check)->second == nullptr)
	//	return false;
	resFiles.emplace(pChild->getMessage(), pChild);

	return true;
}
