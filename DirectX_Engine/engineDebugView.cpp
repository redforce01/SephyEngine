#include "stdafx.h"
#include "engineDebugView.h"


EngineDebugView::EngineDebugView()
{
	initialized = false;
	visible = false;
	strViewName = "None";

	pGraphics = nullptr;
	pInput = nullptr;

	posX = posY = 0;
	width = height = 0;

	vertexBuffer = nullptr;

	messageMax = 0;
	rows = 0;
	scrollAmount = 0;
}


EngineDebugView::~EngineDebugView()
{
	onLostDevice();					// call onLostDevice() for every graphics item
}

bool EngineDebugView::initialize(
	std::string viewName, Graphics * g, Input * i,
	float x, float y, float w, float h,
	float margin, int msgMax)
{
	bool success = false;

	if (g == nullptr || i == nullptr)
		return false;

	try
	{
		strViewName = viewName;
		pGraphics = g;
		pInput = i;

		posX = x;
		posY = y;
		width = w;
		height = h;
		marginSize = margin;

		messageMax = 1;

		viewRect = RectMake(posX, posY, width, height);
		textRect = RectMake(posX + margin, posY + margin, width - margin, height - margin);
		
		// top left
		vtx[0].x = x;
		vtx[0].y = y;
		vtx[0].z = 0.0f;
		vtx[0].rhw = 1.0f;
		vtx[0].color = backColor;

		// top right
		vtx[1].x = x + w;
		vtx[1].y = y;
		vtx[1].z = 0.0f;
		vtx[1].rhw = 1.0f;
		vtx[1].color = backColor;

		// bottom right
		vtx[2].x = x + w;
		vtx[2].y = y + h;
		vtx[2].z = 0.0f;
		vtx[2].rhw = 1.0f;
		vtx[2].color = backColor;

		// bottom left
		vtx[3].x = x;
		vtx[3].y = y + h;
		vtx[3].z = 0.0f;
		vtx[3].rhw = 1.0f;
		vtx[3].color = backColor;

		pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);

		// initialize DirectX font
		if (dxFont.initialize(pGraphics, consoleNS::FONT_HEIGHT, false,
			false, consoleNS::FONT) == false)
			return false;      // if failed
		dxFont.setFontColor(fontColor);
		success = initialized = true;
	}
	catch (...)
	{
		return false;
	}

	return success;
}

void EngineDebugView::update(float frameTime)
{
	
}

void EngineDebugView::render()
{
	draw();
}

void EngineDebugView::draw()
{
	if (!visible || pGraphics == nullptr || !initialized)
		return;

	pGraphics->drawQuad(vertexBuffer);       // draw backdrop
	if (message.size() == 0)
		return;

	pGraphics->spriteBegin();                // Begin drawing sprites

											// display text on console
	textRect.left = 0;
	textRect.top = 0;

	// sets textRect bottom to height of 1 row
	dxFont.print("|", textRect, DT_CALCRECT);
	int rowHeight = textRect.bottom + 2;    // height of 1 row (+2 is row spacing)
	if (rowHeight <= 0)                      // this should never be true
		rowHeight = 20;                     // force a workable result

											// number of rows that will fit on console
	rows = (height - 2 * marginSize) / rowHeight;
	rows -= 2;                              // room for input prompt at bottom
	if (rows <= 0)                          // this should never be true
		rows = 5;                           // force a workable result

											// set text display rect for one row
	textRect.left = (long)(posX + marginSize);
	textRect.right = (long)(textRect.right + width - marginSize);
	// -2*rowHeight is room for input prompt
	textRect.bottom = (long)(posY + height - 2 * marginSize - 2 * rowHeight);
	
	auto iter = message.begin();
	// for all rows (max text.size()) from bottom to top
	for (int r = scrollAmount; r < rows + scrollAmount && r < (int)(message.size()); r++)
	{
		// set text display rect top for this row
		textRect.top = textRect.bottom - rowHeight;
		// display one row of text
		dxFont.print(message.find(iter->first)->second, textRect, DT_LEFT);
		// adjust text display rect bottom for next row
		textRect.bottom -= rowHeight;
		iter++;
	}

	// display command prompt and current command string
	// set text display rect for prompt
	textRect.bottom = (long)(posY + height - marginSize);
	textRect.top = textRect.bottom - rowHeight;
	std::string prompt = ">";                   // build prompt string
	prompt += pInput->getTextIn();
	dxFont.print(prompt, textRect, DT_LEFT);      // display prompt and command

	pGraphics->spriteEnd();                      // End drawing sprites
}

void EngineDebugView::showHide()
{
	if (!initialized)
		return;
	visible = !visible;
}

void EngineDebugView::showHide(bool flag)
{
	if (!initialized)
		return;
	visible = flag;
}

void EngineDebugView::addMessage(const std::string &key, const std::string &str)
{
	if (!initialized)
		return;
	message.emplace(key, str);                  // add str to deque of text
	if (message.size() > consoleNS::MAX_LINES)
	{
		auto iter = message.begin();
		message.erase(iter);					// delete oldest line
	}
}

//=============================================================================
// called when graphics device is lost
//=============================================================================
void EngineDebugView::onLostDevice()
{
	if (!initialized)
		return;
	dxFont.onLostDevice();
	SAFE_RELEASE(vertexBuffer);
}

//=============================================================================
// called when graphics device is reset
//=============================================================================
void EngineDebugView::onResetDevice()
{
	if (!initialized)
		return;
	pGraphics->createVertexBuffer(vtx, sizeof vtx, vertexBuffer);
	dxFont.onResetDevice();
}
