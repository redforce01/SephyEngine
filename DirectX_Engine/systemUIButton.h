#ifndef _SYSTEMUIBUTTON_H
#define _SYSTEMUIBUTTON_H

class SystemUIButton;

#include "systemUIControl.h"


class SystemUIButton : public SystemUIControl
{
public:
	SystemUIButton();
	~SystemUIButton();

	bool initialize();

};

#endif // !_SYSTEMUIBUTTON_H
