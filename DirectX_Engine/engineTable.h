#ifndef _ENGINETABLE_H
#define _ENGINETABLE_H

class EngineTable;

#include <string>

class EngineTable
{
private:
	int tableRow;
	int tableColum;

public:
	EngineTable();
	EngineTable(int x, int y);
	~EngineTable();

	void drawTable();
};

#endif // !_ENGINETABLE_H
