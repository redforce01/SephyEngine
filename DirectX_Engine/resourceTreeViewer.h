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

class ResourceTreeContent;
class ResourceTreeViewer
{
	typedef ResourceTreeContent File;
	typedef std::map<std::string, File*> MAP_FILES;
private:
	MAP_FILES resFiles;
	
	VertexC vtx[4];
	LP_VERTEXBUFFER vertexBuffer;

public:
	ResourceTreeViewer();
	~ResourceTreeViewer();


	bool initialize(Graphics* g, Input* i);
	void update(float frameTime);
	void render();

	bool addTreeRes(File* pChild);


};

#endif // !_RESOURCETREEVIEWER_H
