#include "stdafx.h"
#include "windowFrame.h"


WindowFrame::WindowFrame()
{
	initialized = false;                // set true when successfully initialized
	graphics = NULL;
	visible = false;                    // not visible
	x = 0;								// starting position
	y = 0;
	height = 0;
	width = 0;
	hWndParent = NULL;
	hWndChild = NULL;
	borderColor;
	backColor;
}


WindowFrame::~WindowFrame()
{
}

bool WindowFrame::initialize(Graphics * g, Input * in, HWND hWnd, float startX, float startY, UINT windowWidth, UINT windowHeight, std::string windowName)
{
	Game::initialize(hWnd);

	x = startX, y = startY;
	height = windowWidth;
	width = windowHeight;
	text = windowName;

	try {
		graphics = g;                   // the graphics object
		input = in;                     // the input object
		hWndParent = hWnd;

		// initialize DirectX font
		if (createMainWindow(hWnd) == false)
			return false;               // if failed
	}
	catch (...) {
		return false;
	}
	
	initialized = true;
	return true;
}

void WindowFrame::update()
{
}

void WindowFrame::ai()
{
}

void WindowFrame::collisions()
{
}

void WindowFrame::render()
{
}

bool WindowFrame::createMainWindow(HWND hWnd)
{
	int			x, y, cx, cy;
	WNDCLASS	wc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WindowFrame::WndProcChild;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = text.c_str();

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClass(&wc) == 0)    // if error
		return false;

	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	cx = width;
	cy = height;
	x = 0;
	y = 0;

	HWND		hParentWnd = NULL;
	HINSTANCE	hInst = NULL;

	hParentWnd = hWnd;
	hInst = GetModuleHandle(NULL);

	hWndChild = CreateWindow(
		text.c_str(),
		text.c_str(),
		//WS_OVERLAPPEDWINDOW,
		WS_POPUP |				// �˾� �����츦 �����.WS_CHILD�� �Բ� �� �� ����.
		WS_THICKFRAME |			// ũ�� ������ ������ �β��� ��輱�� ������.		
		WS_CLIPSIBLINGS |		// ���ϵ峢�� ��ȣ ��ģ ������ �׸��� �������� ���ܵȴ�.
		WS_CLIPCHILDREN |		// ���ϵ尡 ��ġ�� ������ �׸��� �������� ���ܵȴ�.
		WS_VISIBLE,				// �����츦 ������ ���� ȭ�鿡 ����Ѵ�.
		x, y, cx, cy,
		hParentWnd, NULL, hInst, NULL);

	ShowWindow(hWndChild, SW_SHOWNORMAL);

	return true;
}

LRESULT WindowFrame::WndProcChild(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}