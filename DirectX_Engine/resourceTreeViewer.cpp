#include "stdafx.h"
#include "ResourceTreeViewer.h"


ResourceTreeViewer::ResourceTreeViewer() : SystemUIWindow()
{
	nSelectFile = 0;
	pSelectFile = nullptr;

	fontColor = treeViewerNS::FONT_COLOR;
	backColor = treeViewerNS::BACK_COLOR;
}


ResourceTreeViewer::~ResourceTreeViewer()
{
	for (auto iter : resFiles)
	{
		if (iter)
			SAFE_DELETE(iter);
		iter = nullptr;
	}
}

bool ResourceTreeViewer::initialize(Graphics* g, Input* i)
{
	bool success = false;

	try
	{
		success = SystemUIWindow::initialize(g, i, treeViewerNS::X, treeViewerNS::Y, treeViewerNS::WIDTH, treeViewerNS::HEIGHT, treeViewerNS::MARGIN);

		// initialize DirectX font
		if (dxFont.initialize(pGraphics, treeViewerNS::FONT_HEIGHT, false,
			false, treeViewerNS::FONT) == false)
			return false;      // if failed
		dxFont.setFontColor(fontColor);
		
		int resX, resY;
		resX = x + margin;
		resY = y + margin;
		auto total = FILEMANAGER->getAllFile();
		for (auto iter : total)
		{
			resX = x + margin;
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

			resX = x;
			File* cutline = new File();
			cutline->initialize(g, i, &dxFont, CONTENTSTYPE::CONTENTS_UNKNOWN, treeViewerNS::CUT_LINE, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
			addTreeRes(cutline);
			resY += viewerChildHeight;
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
	pGraphics->drawQuad(vertexBuffer);

	if (resFiles.size() <= 0)
		return;
	
	pGraphics->spriteBegin();
	for (auto iter : resFiles)
	{
		if (iter->getContentRect().bottom > height)
			break;

		iter->draw();
	}
	pGraphics->spriteEnd();
}

bool ResourceTreeViewer::addTreeRes(File * pChild)
{
	if (pChild == nullptr)
		return false;

	resFiles.emplace_back(pChild);
	return true;
}

bool ResourceTreeViewer::checkTreeClicked()
{
	nSelectFile = 0;
	for (auto iter : resFiles)
	{
		if (PtInRect(&iter->getContentRect(), PointMake(pInput->getMouseX(), pInput->getMouseY())))
			return true;
		nSelectFile++;
	}

	return false;
}

bool ResourceTreeViewer::checkMapClicked()
{
	return false;
}

bool ResourceTreeViewer::setSelectFile()
{
	if (resFiles.size() < nSelectFile)
		return false;

	pSelectFile = resFiles[nSelectFile];
	return true;
}
