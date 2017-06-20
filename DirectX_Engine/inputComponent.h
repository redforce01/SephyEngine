#ifndef _INPUTCOMPONENT_H
#define _INPUTCOMPONENT_H

class InputComponent;

#include "componentBase.h"

namespace inputComponentNS
{
	const UCHAR LEFT_MOVE = VK_LEFT | 'A';
	const UCHAR RIGHT_MOVE = VK_RIGHT | 'D';
	const UCHAR UP_MOVE = VK_UP | 'W';
	const UCHAR DOWN_MOVE = VK_DOWN | 'S';
}

class Input;
class InputComponent : public ComponentBase
{
private:
	Input* input;

public:
	InputComponent();
	~InputComponent();

	virtual const goc_id_type& componentID() const
	{ return goc_id_type("InputComponent"); }

	virtual void start() override;
	virtual void update(float frameTime) override;
	virtual void HandleMessage(GOCMessage message);
};

#endif // !_INPUTCOMPONENT_H
