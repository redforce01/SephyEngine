#pragma once
#include "systemBase.h"
class testingUI : public SystemBase
{
private:
	RECT m_rcUI;
	bool m_hasFocus;

public:
	testingUI();
	~testingUI();

	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;


	bool ContainFocus() const
	{
		return m_hasFocus;
	}
};

