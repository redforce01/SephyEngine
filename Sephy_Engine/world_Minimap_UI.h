#pragma once

#include "systemUIDialog.h"

namespace worldminimapNS
{
	const UINT width = 210;	//map size
	const UINT height = 210;
	const UINT x = 230;	//map position g_fScreenWidth - 230;
	const UINT y = 230;	//g_fScreenHeight - 230;

	const UINT cam_width = 20;	//cam size -> wmap size / 210
	const UINT cam_height = 9;
}
 
class CWorld_Minimap_UI : public SystemUIDialog
{
private:

public:
	CWorld_Minimap_UI();
	~CWorld_Minimap_UI();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

