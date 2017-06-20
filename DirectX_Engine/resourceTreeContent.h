#ifndef _RESOURCETREECONTENT_H
#define _RESOURCETREECONTENT_H

class ResourceTreeContent;

#include <string>

enum class CONTENTSTYPE
{
	CONTENTS_FOLDER,
	CONTENTS_FILE,
	CONTENTS_UNKNOWN
};

class ResourceTreeContent
{
private:
	Graphics* pGraphics;
	Input* pInput;
	TextDX* pDxFont;
	
	CONTENTSTYPE contentType;
	std::string message;
	float posX, posY;
	float width, height;
	float margin;
	RECT rcText;
	RECT rcContent;

	bool initialized;
public:
	ResourceTreeContent();
	~ResourceTreeContent();

	bool initialize(Graphics* g, Input* i, TextDX* font,
		CONTENTSTYPE type, std::string msg,
		float x, float y, float w, float h, float m);
	void draw();

	void changePos(float x, float y);
	void setupRect();

	std::string getMessage() { return message; }
	RECT getContentRect() { return rcContent; }
};

#endif // !_RESOURCETREECONTENT_H
