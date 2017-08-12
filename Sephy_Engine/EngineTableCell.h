#ifndef _ENGINETABLECELL_H
#define _ENGINETABLECELL_H

class EngineTableCell;

#include <string>

class EngineTableCell
{
private:
	std::string strCell;
	
public:
	EngineTableCell();
	~EngineTableCell();

	void drawCell(HDC hDC);
	void setString(std::string str) { strCell = str; }
	std::string getString() { return strCell; }
};

#endif // !_ENGINETABLECELL_H
