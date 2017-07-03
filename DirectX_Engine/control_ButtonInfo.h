#pragma once
namespace controlButtonNS
{
	const int BUTTON_WIDTH = 40;
	const int BUTTON_HEIGHT = 40;
	const int BUTTON_MARGIN = 2;
	const int BUTTON_POS_MARGIN = 10;
	const int BUTTON_BASIC_X = 0;
	const int BUTTON_BASIC_Y = 0;

	const int BUTTON_SAVE_ID	= 1;
	const int BUTTON_LOAD_ID	= 2;
	const int BUTTON_RESET_ID	= 3;
	const int BUTTON_PERFORM_ID = 4;
	const int BUTTON_DEBUG_ID	= 5;
	const int BUTTON_EXIT_ID	= 6;

	const int BUTTON_SAVE_POS_X		= 0;
	const int BUTTON_LOAD_POS_X		= BUTTON_SAVE_POS_X + BUTTON_WIDTH;
	const int BUTTON_RESET_POS_X	= BUTTON_LOAD_POS_X + BUTTON_WIDTH;
	const int BUTTON_PERFORM_POS_X	= BUTTON_RESET_POS_X + BUTTON_WIDTH;
	const int BUTTON_DEBUG_POS_X	= BUTTON_PERFORM_POS_X + BUTTON_WIDTH;
	const int BUTTON_EXIT_POS_X		= BUTTON_DEBUG_POS_X + BUTTON_WIDTH;
}