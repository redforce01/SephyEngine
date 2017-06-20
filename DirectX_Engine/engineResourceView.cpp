#include "stdafx.h"
#include "engineResourceView.h"

namespace engineResourceViewNS
{
	const char * WINDOW_CLASSNAME = "resourceView";
	const char * WINDOW_VIEWNAME = "Resources";
	const DWORD WINDOW_DWSTYLE = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_THICKFRAME | WS_CAPTION;
}

EngineResourceView::EngineResourceView() : EngineWindow()
{
	treeImages = nullptr;
	hTree = nullptr;
}


EngineResourceView::~EngineResourceView()
{
}

bool EngineResourceView::initialize(EngineInput * input, HWND hParent, HMENU hMenu, int startX, int startY, int width, int height)
{
	bool success = false;

	engineViewWS.className = engineResourceViewNS::WINDOW_CLASSNAME;
	engineViewWS.titleName = engineResourceViewNS::WINDOW_VIEWNAME;
	engineViewWS.viewName = engineResourceViewNS::WINDOW_VIEWNAME;
	engineViewWS.startX = startX;
	engineViewWS.startY = startY;
	engineViewWS.width = width;
	engineViewWS.height = height;
	engineViewWS.dwstyle = engineResourceViewNS::WINDOW_DWSTYLE;
	engineViewWS.hParent = hParent;
	engineViewWS.hMenu = hMenu;

	success = createWindowClass(engineResourceViewNS::WINDOW_CLASSNAME, input, true, g_wcx, this);
	success = createNewWindow(engineViewWS, false);
	
	return success;
}

LRESULT EngineResourceView::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	TVINSERTSTRUCT TI;
	HTREEITEM resources, folder, item;
	//treeImages = ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_PNG1), 32, 1, RGB(255, 255, 255));
	//SendMessage(hWndThis, TVM_SETIMAGELIST, (WPARAM)TVSIL_NORMAL, (LPARAM)treeImages);
	RECT rc;
	GetClientRect(hWnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;


	TVITEMEX TvEx;
	TCHAR Cap[30];
	stFile* pParam;

	switch (Msg)
	{
	case WM_CREATE:
		hTree = CreateWindow(WC_TREEVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES,
			0, 0, w, h, hWnd, NULL, GetModuleHandle(NULL), NULL);

		TI.hParent = 0;
		TI.hInsertAfter = TVI_ROOT;
		TI.item.mask = TVIF_TEXT | /*TVIF_IMAGE |*/ TVIF_SELECTEDIMAGE;
		//TI.item.iImage = 0;
		//TI.item.iSelectedImage = 2;
		TI.item.pszText = "Resources";
		resources = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);

		for (auto iter : FILEMANAGER->getAllFile())
		{
			TI.hParent = resources;
			//TI.item.iImage = 0;
			TI.item.pszText = (LPSTR)iter.first.c_str();
			folder = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);


			for (auto iter2 = iter.second->begin();
				iter2 != iter.second->end(); iter2++)
			{
				TI.hParent = folder;
				//TI.item.iImage = 3;
				TI.item.pszText = (LPSTR)(*iter2)->fileName.c_str();
				item = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&TI);
			}
		}
		return 0;
	case WM_SIZE:
		MoveWindow(hTree, 0, 0, w, h, true);
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMTREEVIEW ntv;
		hdr = (LPNMHDR)lParam;
		ntv = (LPNMTREEVIEW)lParam;
		if (hdr->hwndFrom == hTree)
		{
			switch (hdr->code)
			{
			case TVN_SELCHANGED:
				TvEx.mask = TVIF_PARAM | TVIF_TEXT;
				TvEx.hItem = ntv->itemNew.hItem;
				TvEx.pszText = Cap;
				TvEx.cchTextMax = 30;
				TreeView_GetItem(hTree, &TvEx);
				pParam = (stFile*)TvEx.lParam;
				break;
			case TVN_SELCHANGING:
				TvEx.mask = TVIF_TEXT;
				TvEx.pszText = Cap;
				TvEx.cchTextMax = 30;
				TvEx.hItem = ntv->itemNew.hItem;
				TreeView_GetItem(hTree, &TvEx);
				break;
			case TVN_DELETEITEM:
				pParam = (stFile*)ntv->itemOld.lParam;
				free(pParam);
				break;
			}
		}
		
		return 0;
	case WM_LBUTTONDOWN:
		HTREEITEM hNow;
		hNow = TreeView_GetSelection(hTree);
		if (hNow == nullptr) {}
		else
		{
			TvEx.mask = TVIF_TEXT;
			TvEx.pszText = Cap;
			TvEx.cchTextMax = 30;
			TvEx.hItem = hNow;
			TreeView_GetItem(hTree, &TvEx);
		}		
		return 0;
	case WM_RBUTTONDOWN:
		hNow = TreeView_GetSelection(hTree);
		if (hNow = nullptr) {}
		else
		{
			TvEx.mask = TVIF_TEXT;
			TvEx.pszText = Cap;
			TvEx.cchTextMax = 30;
			TvEx.hItem = hNow;
			TreeView_GetItem(hTree, &TvEx);
		}
		return 0;
	case WM_ACTIVATE:

		return 0;
	}
	
	return pEngineInput->messageHandler(hWnd, Msg, wParam, lParam);
}