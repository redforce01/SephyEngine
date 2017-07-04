#ifndef _LOGVIEWER_H
#define _LOGVIEWER_H

class LogViewer;

#include "systemUIDialog.h"


class LogViewer : public SystemUIDialog
{
private:
	std::deque<std::string> m_arrLog;


public:
	LogViewer();
	~LogViewer();

	virtual bool initialize(Graphics* g, Input* i) override;
	virtual void update(float frameTime) override;
	virtual void render() override;
};

#endif // !_LOGVIEWER_H
