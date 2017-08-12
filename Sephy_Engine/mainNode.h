#ifndef _MAINNODE_H			// Prevent multiple definitions if this 
#define _MAINNODE_H			// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class MainNode;

namespace mainNodeNS
{
	const float maxFrameLimit = 60.0f;
}

class MainNode
{
private:
	bool initializedMgr = false;

public:
	MainNode();
	~MainNode();

	HRESULT initialize();
	void release();
	void update();
	void render();

	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif