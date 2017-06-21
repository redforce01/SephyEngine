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
	bool selectable;
public:
	ResourceTreeContent();
	~ResourceTreeContent();

	// Contents initialize
	bool initialize(Graphics* g, Input* i, TextDX* font,
		CONTENTSTYPE type, std::string msg,
		float x, float y, float w, float h, float m);

	// Contents Draw
	void draw();

	// For TreeViewer Move Update
	void changePos(float x, float y);

	// Not Working...
	// need to fix
	void setupRect();
	
	// This Function Return Content - Message(std::string)
	inline std::string getMessage() { return message; }

	// This function Return Content RECT
	inline RECT getContentRect() { return rcContent; }
};

#endif // !_RESOURCETREECONTENT_H
