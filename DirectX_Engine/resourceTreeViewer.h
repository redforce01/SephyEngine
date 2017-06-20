#ifndef _RESOURCETREEVIEWER_H
#define _RESOURCETREEVIEWER_H

class ResourceTreeViewer;

#include <map>
#include "graphics.h"
#include "resourceTreeContent.h"

constexpr int viewerChildWidth = 100;
constexpr int viewerChildHeight = 20;
constexpr int viewerChildMargin = 2;
constexpr int viewerChildTab = 10;


namespace treeViewerNS
{
	const UINT WIDTH = 200;             // width of treeViewer
	const UINT HEIGHT = 500;            // height of treeViewer
	const UINT X = WINSIZEX - 250;      // treeViewer location
	const UINT Y = 5;
	const UINT MARGIN = 4;              // text margin from treeViewer edge
	const char FONT[] = "Courier New";  // treeViewer font
	const int FONT_HEIGHT = 14;         // height of the font in pixels
	const COLOR_ARGB FONT_COLOR = graphicsNS::WHITE;    // color of console text
	const COLOR_ARGB BACK_COLOR = SETCOLOR_ARGB(192, 97, 97, 97);    // backdrop color
	const int MAX_LINES = 256;          // maximun number of lines in text buffer
}


class ResourceTreeContent;
class ResourceTreeViewer
{
	typedef ResourceTreeContent File;
	typedef std::map<std::string, File*> MAP_FILES;
private:
	MAP_FILES resFiles;
	

private:
	Graphics* pGraphics;
	Input* pInput;

	float x, y;
	float width, height;
	TextDX dxFont;
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;

	COLOR_ARGB  fontColor;              // font color (a,r,g,b)
	COLOR_ARGB  backColor;              // background color (a,r,g,b)

	bool initialized;
	bool visible;
public:
	ResourceTreeViewer();
	~ResourceTreeViewer();

	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	bool addTreeRes(File* pChild);
};

#endif // !_RESOURCETREEVIEWER_H
