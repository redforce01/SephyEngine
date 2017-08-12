#pragma once
#include "systemBase.h"



class CBattle_LogSystem : public SystemBase
{
private:
	std::vector<std::string> m_vLog;

public:
	CBattle_LogSystem();
	~CBattle_LogSystem();
	
	virtual bool initialize(Game* gamePtr) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

