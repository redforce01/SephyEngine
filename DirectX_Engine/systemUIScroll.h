#ifndef _SYSTEMUISCROLL_H
#define _SYSTEMUISCROLL_H

class SystemUIScroll;

#include "systemUIControl.h"
#include "image.h"

enum class SCROLL_TYPE
{
	SCROLL_TYPE_HORIZONTAL,
	SCROLL_TYPE_VERTICAL
};

namespace systemUIScrollNS
{
	const float SCROLL_BUTTON_RATE = (1 / 20);
	const COLOR_ARGB TRACK_COLOR = SETCOLOR_ARGB(192, 91, 91, 91);
}

class SystemUIScroll : public SystemUIControl
{
protected:
	enum class ARROWSTATE
	{
		CLEAR,
		CLICKED_UP,
		CLICKED_DOWN,
		HELD_UP,
		HELD_DOWN
	};

protected:
	SCROLL_TYPE m_type;		// scroll type (vertical / horizontal)
	bool m_bShowThumb;
	bool m_bDrag;
	RECT m_rcUpButton;		// rect up button
	RECT m_rcDownButton;	// rect down button 
	RECT m_rcTrack;			// rect scoll
	RECT m_rcThumb;			// Thumb rect in scroll
	int m_nPosition;		// Position of the first displayed item
	int m_nPageSize;		// Display Scroll Page Size In Displayed View
	int m_nStart;			// First item
	int m_nEnd;				// The index after the last item
	POINT m_LastMouse;		// Last mouse position
	ARROWSTATE m_Arrow;		// State of the arrows

	Image* m_UpButton;
	Image* m_DownButton;
	Image* m_Thumb;
public:
	SystemUIScroll();
	virtual ~SystemUIScroll();

	virtual bool initScroll(Graphics* g, Input* i, int controlID, SystemUIDialog* pDialog, SCROLL_TYPE type,
		int scrollX, int scrollY, int scrollWidth, int scrollHeight);
	virtual void update(float frameTime) override;
	virtual void render() override;

	void capture();
	void updateThumb();
	// =========================================
	// Getter Functions
	// =========================================
	float getTrackPos() const
	{
		return m_nPosition;
	}
	// =========================================
	// Setter Functions
	// =========================================
	void setTrackRange(int start, int end)
	{
		m_nStart = start, m_nEnd = end;
		// Cap(); UpdateThumbRect();
	}
	void setTrackPos(float nPosition)
	{
		m_nPosition = nPosition;
		// Cap(); UpdateThumbRect();
	}
};

#endif // !_SYSTEMUISCROLL_H
