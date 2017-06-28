#include "stdafx.h"
#include "engineBootSystem.h"

EngineBootSystem* pBootSystem;
EngineBootSystem::EngineBootSystem()
{
	m_bEngineBooted = false;
	pBootSystem = this;
}

EngineBootSystem::~EngineBootSystem()
{
	if (bootThread.joinable())
		bootThread.join();
}

void EngineBootSystem::EngineBoot()
{
	FILEMANAGER->initialize();
	pBootSystem->m_bEngineBooted = true;
}

void EngineBootSystem::BootSystemInitialize(HINSTANCE hInst, int nCmdShow)
{
	CreateMainWindow(m_hWnd, hInst, nCmdShow);


	bootThread = std::thread();
	EngineBoot();
}

bool EngineBootSystem::CreateMainWindow(HWND &hWnd, HINSTANCE hInstance, int nCmdShow)
{

	return false;
}

LRESULT EngineBootSystem::EngineProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
