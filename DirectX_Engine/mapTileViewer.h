#ifndef _MAPTILEVIEWER_H
#define _MAPTILEVIEWER_H

class MapTileViewer;

#include "systemUIWindow.h"


class MapTileViewer : public SystemUIWindow
{
private:
	

public:
	MapTileViewer();
	~MapTileViewer();

	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_MAPTILEVIEWER_H
