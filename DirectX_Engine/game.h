#ifndef _GAME_H                 // Prevent multiple definitions if this 
#define _GAME_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Game;

#include <Mmsystem.h>
#include "graphics.h"
#include "input.h"
#include "constants.h"
#include "textDX.h"
#include "console.h"
#include "gameError.h"
#include "messageDialog.h"
#include "inputDialog.h"

#include "gameObjectManager.h"

namespace gameNS
{
    const char FONT[] = "Courier New";  // font
    const int POINT_SIZE = 14;          // point size
    const COLOR_ARGB FONT_COLOR = SETCOLOR_ARGB(255,255,255,255);    // white

	const std::string command_help = "help";
	const std::string command_timer = "timer";
	const std::string command_fps = "fps";
}

class Game
{
protected:
    // common game properties
    Graphics *graphics;             // pointer to Graphics
    Input   *input;                 // pointer to Input
    Console *console;               // pointer to Console
    MessageDialog *messageDialog;   // pointer to MessageDialog
    InputDialog *inputDialog;       // pointer to InputDialog
    HWND    hwnd;                   // window handle
    HRESULT hr;                     // standard return type
    LARGE_INTEGER timeStart;        // Performance Counter start value
    LARGE_INTEGER timeEnd;          // Performance Counter end value
    LARGE_INTEGER timerFreq;        // Performance Counter frequency
    float   frameTime;              // time required for last frame
    float   fps;                    // frames per second
    TextDX  dxFont;                 // DirectX font for fps
    bool    fpsOn;                  // true to display fps
    DWORD   sleepTime;              // number of milli-seconds to sleep between frames
    bool    paused;                 // true if game is paused
    bool    initialized;
	bool	started;
    std::string  command;           // command from console

	bool timerOn;
	GameObjectManager gameObjMgr;
public:
    // Constructor
    Game();
    // Destructor
    virtual ~Game();

    // Member functions

    // Window message handler
    LRESULT messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

    // Initialize the game
    // Pre: hwnd is handle to window
    virtual void initialize(HWND hwnd);

    // Call run repeatedly by the main message loop in WinMain
    virtual void run(HWND);

    // Call when the graphics device was lost.
    // Release all reserved video memory so graphics device may be reset.
    virtual void releaseAll();

    // Recreate all surfaces and reset all entities.
    virtual void resetAll();

    // Delete all reserved memory.
    virtual void deleteAll();

    // Process console commands.
    virtual void consoleCommand();

    // Do network communications.
    virtual void communicate(float frameTime) {}

    // Render game items.
    virtual void renderGame();

    // Handle lost graphics device
    virtual void handleLostGraphicsDevice();

    // Set display mode (fullscreen, window or toggle)
    void setDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

    // Return pointer to Graphics.
    Graphics* getGraphics() {return graphics;}

    // Return pointer to Input.
    Input* getInput()       {return input;}

	// Return HWND to Child
	HWND getHwnd()			{ return hwnd; }

    // Exit the game
    void exitGame()         {PostMessage(hwnd, WM_DESTROY, 0, 0);}
	
    // Pure virtual function declarations
    // These functions MUST be written in any class that inherits from Game

    // Update game items.
    virtual void update() = 0;

	// release game items.
	virtual void release() = 0;

    // Perform AI calculations.
    virtual void ai() = 0;

    // Check for collisions.
    virtual void collisions() = 0;

    // Render graphics.
    // Call graphics->spriteBegin();
    //   draw sprites
    // Call graphics->spriteEnd();
    //   draw non-sprites
    virtual void render() = 0;

	float getTimeDelta() { return this->frameTime; }

	void setInitialized(bool b) { this->initialized = b; }

	bool getInitializd() { return this->initialized; }
};

#endif
