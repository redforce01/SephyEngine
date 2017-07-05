#ifndef _ENGINEBOOTSYSTEM_H
#define _ENGINEBOOTSYSTEM_H

class EngineBootSystem;

#include <thread>
#include <vector>

class EngineBootSystem
{
private:
	bool m_bEngineBooted;
	HWND m_hWnd;

	std::thread bootThread;

public:
	EngineBootSystem();
	~EngineBootSystem();

	void BootSystemInitialize(HINSTANCE hInst, int nCmdShow);
	bool CreateMainWindow(HWND &, HINSTANCE, int);
	LRESULT EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	
	static void EngineBoot();

	bool GetBootFinish() const
	{ return m_bEngineBooted; }
};

#endif // !_ENGINEBOOTSYSTEM_H
