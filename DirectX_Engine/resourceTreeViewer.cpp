#include "stdafx.h"
#include "ResourceTreeViewer.h"


ResourceTreeViewer::ResourceTreeViewer() : SystemUIDialog()
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
		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - treeViewerNS::X,
			treeViewerNS::Y,
			treeViewerNS::WIDTH,
			g_fScreenHeight,
			treeViewerNS::MARGIN);

		// initialize DirectX font
		if (m_dxFont.initialize(m_pGraphics, treeViewerNS::FONT_HEIGHT, false,
			false, treeViewerNS::FONT) == false)
			return false;      // if failed
		m_dxFont.setFontColor(fontColor);
		
		int resX, resY;
		resX = m_x + m_margin;
		resY = m_y + m_margin;
		auto total = FILEMANAGER->getAllFile();
		for (auto iter : total)
		{
			resX = m_x + m_margin;
			File* folder = new File();
			folder->initialize(g, i, &m_dxFont, CONTENTSTYPE::CONTENTS_FOLDER, iter.first, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
			addTreeRes(folder);
			resX += viewerChildTab;
			resY += viewerChildHeight;

			for (auto fileIter = iter.second->begin(); fileIter != iter.second->end(); fileIter++)
			{
				File* file = new File();
				file->initialize(g, i, &m_dxFont, CONTENTSTYPE::CONTENTS_FILE, (*fileIter)->fileName, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
				addTreeRes(file);
				resY += viewerChildHeight;
			}

			resX = m_x;
			File* cutline = new File();
			cutline->initialize(g, i, &m_dxFont, CONTENTSTYPE::CONTENTS_UNKNOWN, treeViewerNS::CUT_LINE, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
			addTreeRes(cutline);
			resY += viewerChildHeight;
		}

		success = true;
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, "ResourceViewer System Error", "Error", MB_OK);
	}
	
	return success;
}

void ResourceTreeViewer::update(float frameTime)
{
	SystemUIDialog::update(frameTime);


}

void ResourceTreeViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	m_pGraphics->spriteBegin();

	if (resFiles.size() <= 0)
		return;
	for (auto iter : resFiles)
	{
		if (iter->getContentRect().bottom > m_height)
			break;

		iter->draw();
	}

	m_pGraphics->spriteEnd();
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
		if (PtInRect(&iter->getContentRect(), PointMake(m_pInput->getMouseX(), m_pInput->getMouseY())))
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
