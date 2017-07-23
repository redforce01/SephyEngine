#ifndef _RESOURCETREEVIEWER_H
#define _RESOURCETREEVIEWER_H

class ResourceTreeViewer;

#include <vector>
#include "systemUIDialog.h"
#include "resourceTreeContent.h"

constexpr int viewerChildWidth = 100;
constexpr int viewerChildHeight = 20;
constexpr int viewerChildMargin = 2;
constexpr int viewerChildTab = 5;


namespace treeViewerNS
{
	const UINT WIDTH = 300;						// width of treeViewer
	const UINT HEIGHT = 0;						// height of treeViewer			(g_fScreenHeight)
	const UINT X = 400 + WIDTH;	// Viewer location X  (512 == TileViewer Width) (g_fScreenWidth - (400 + Width))
	const UINT Y = 0;							// Viewer location Y
	const UINT MARGIN = 4;						// text margin from Viewer edge
	const char FONT[] = "Courier New";			// Viewer font
	const int FONT_HEIGHT = 14;					// height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 26, 32, 44);    // backdrop color
	const int MAX_LINES = 256;          // maximun number of lines in text buffer
	const std::string CUT_LINE = "---------------";
}


class ResourceTreeContent;
class ResourceTreeViewer : public SystemUIDialog
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

	virtual bool initialize(Graphics* g, Input* i) override;
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
