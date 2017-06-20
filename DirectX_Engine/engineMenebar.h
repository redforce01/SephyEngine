#ifndef _ENGINEMENUBAR_H
#define _ENGINEMENUBAR_H

class EngineMenuBar;

#include "cSingletonBase.h"
#include <string>
#include <vector>
#include <map>
#include "engineError.h"

namespace engineMenubarNS
{
	const UINT default_Menubar_FILE = 0;
	const UINT default_Menubar_EDIT = 1;
	const UINT default_Menubar_OBJECT = 2;
	const UINT default_Menubar_WINDOW = 3;
	const UINT default_Menubar_HELP = 4;

	const UINT default_Menu_QUIT = 101;
}

class EngineMenuBar : public cSingletonBase<EngineMenuBar>
{
private:
	typedef std::vector<HMENU> MenuList;
	typedef std::map<std::string, MenuList> MAP_MENU;

protected:
	MAP_MENU map_EngineMenu;

public:
	EngineMenuBar();
	~EngineMenuBar();

	bool initialize();
};

#define ENGINE_MENUBAR_MANAGER EngineMenuBar::GetInstance()

#endif // !_ENGINEMENUBAR_H