#pragma once
namespace controlButtonNS
{
	const UINT BUTTON_WIDTH			= 40;
	const UINT BUTTON_HEIGHT		= 40;
	const UINT BUTTON_MARGIN		= 2;
	const UINT BUTTON_POS_MARGIN	= 10;
	const UINT BUTTON_BASIC_X		= 0;
	const UINT BUTTON_BASIC_Y		= 0;

	const UINT BUTTON_ID_START			= 0;
	const UINT BUTTON_SAVE_ID			= BUTTON_ID_START + 1;
	const UINT BUTTON_LOAD_ID			= BUTTON_SAVE_ID + 1;
	const UINT BUTTON_RESET_ID			= BUTTON_LOAD_ID + 1;
	const UINT BUTTON_PERFORM_ID		= BUTTON_RESET_ID + 1;
	const UINT BUTTON_DEBUG_ID			= BUTTON_PERFORM_ID + 1;
	const UINT BUTTON_DEBUG_CELL_ID		= BUTTON_DEBUG_ID + 1;
	const UINT BUTTON_DEBUG_OBJECT_ID	= BUTTON_DEBUG_CELL_ID + 1;
	const UINT BUTTON_DEBUG_EVENT_ID	= BUTTON_DEBUG_OBJECT_ID + 1;
	const UINT BUTTON_EXIT_ID			= BUTTON_DEBUG_EVENT_ID + 1;

	const UINT BUTTON_SAVE_POS_X				= 0;
	const UINT BUTTON_LOAD_POS_X				= BUTTON_SAVE_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_RESET_POS_X				= BUTTON_LOAD_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_PERFORM_POS_X				= BUTTON_RESET_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_DEBUG_POS_X				= BUTTON_PERFORM_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_DEBUG_CELL_POS_X			= BUTTON_DEBUG_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_DEBUG_OBJECT_POS_X		= BUTTON_DEBUG_CELL_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_DEBUG_EVENT_OBJECT_POS_X	= BUTTON_DEBUG_OBJECT_POS_X + BUTTON_WIDTH;
	const UINT BUTTON_EXIT_POS_X				= BUTTON_DEBUG_EVENT_OBJECT_POS_X + BUTTON_WIDTH;
}