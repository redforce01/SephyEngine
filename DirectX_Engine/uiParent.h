#ifndef _UIPARENT_H
#define _UIPARENT_H
#define WIN32_LEAN_AND_MEAN

class UIParent;

#include "image.h"
#include <vector>

struct UIStruct
{
	TextureManager*		texture;
	RECT				rect;
	bool				bNinePatch;
	std::vector<RECT>	vecNineRect;
};

class UIParent : public Image
{
protected:
	UIStruct mainStruct;
	
public:
	UIParent();
	~UIParent();

	virtual void update(float frameTime) PURE;
	virtual void render() PURE;

	virtual void release();
	virtual void releaseAll();
	virtual void resetAll();

	RECT getMainRect() { return mainStruct.rect; }
	void setMainRect(RECT rc) { mainStruct.rect = rc; }
};

#endif // !_UIPARENT_H
