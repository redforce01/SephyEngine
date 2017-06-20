#include "stdafx.h"
#include "ResourceTreeViewer.h"


ResourceTreeViewer::ResourceTreeViewer()
{
}


ResourceTreeViewer::~ResourceTreeViewer()
{
}

bool ResourceTreeViewer::initialize(Graphics* g, Input* i)
{
	bool success = false;

	int resX, resY;
	resX = resY = 0;

	try
	{
		auto total = FILEMANAGER->getAllFile();
		for (auto iter : total)
		{
			resX = 5;
			File* folder = new File();
			folder->initialize(g, i, CONTENTSTYPE::CONTENTS_FOLDER, iter.first, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
			addTreeRes(folder);
			resX += viewerChildTab;
			resY += viewerChildHeight;

			for (auto fileIter = iter.second->begin(); fileIter != iter.second->end(); fileIter++)
			{
				File* file = new File();
				file->initialize(g, i, CONTENTSTYPE::CONTENTS_FILE, (*fileIter)->fileName, resX, resY, viewerChildWidth, viewerChildHeight, viewerChildMargin);
				addTreeRes(file);
				resY += viewerChildHeight;
			}
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
	//resFiles.emplace(pChild->getViewName(), pChild);

	return true;
}
