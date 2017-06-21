#ifndef _RESOURCETREEVIEWER_H
#define _RESOURCETREEVIEWER_H

class ResourceTreeViewer;

#include <vector>
#include "systemUIWindow.h"
#include "resourceTreeContent.h"

constexpr int viewerChildWidth = 100;
constexpr int viewerChildHeight = 20;
constexpr int viewerChildMargin = 2;
constexpr int viewerChildTab = 5;


namespace treeViewerNS
{
	const UINT WIDTH = 300;             // width of treeViewer
	const UINT HEIGHT = 800;            // height of treeViewer
	const UINT X = WINSIZEX - 400;      // treeViewer location
	const UINT Y = 5;
	const UINT MARGIN = 4;              // text margin from treeViewer edge
	const char FONT[] = "Courier New";  // treeViewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 97, 97, 97);    // backdrop color
	const int MAX_LINES = 256;          // maximun number of lines in text buffer
	const std::string CUT_LINE = "---------------";
}


class ResourceTreeContent;
class ResourceTreeViewer : public SystemUIWindow
{
	typedef ResourceTreeContent File;
	typedef std::vector<File*> TREE_FILES;
private:
	TREE_FILES resFiles;
	int nSelectFile;
	File* pSelectFile;

public:
	ResourceTreeViewer();
	~ResourceTreeViewer();

	bool initialize(Graphics* g, Input* i);
	virtual void update(float frameTime) override;
	virtual void render() override;

	bool addTreeRes(File* pChild);

	bool checkTreeClicked();
	bool checkMapClicked();

	bool setSelectFile();

	inline std::string getSelectFile()
	{
		if (pSelectFile == nullptr)
			return nullptr;
		
		return pSelectFile->getMessage();
	}
};

#endif // !_RESOURCETREEVIEWER_H
