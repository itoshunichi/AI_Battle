// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "AI";
const char GAME_TITLE[] = "AI_Test";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1280;               // width of game in pixels
const UINT GAME_HEIGHT = 720;               // height of game in pixels

//1列目のYの最小値
const float firstColumnMinY = 425;
//1列目のYの最大値
const float firstColumnMaxY = 550;
//2列目のYの最小値
const float seconsColumnMinY = 325;
//2列目のYの最大値
const float secondColumnMaxY = 425;
//3列目のYの最小値
const float thirdColumnMinY = 225;
//3列目のYの最大値
const float thirdColumnMaxY = 325;

const int STAGE_MASS_SIZE = 32;
const int STAGE_WIDTH = 40;
const int STAGE_HEIGH = 24;

// game
const double PI = 3.14159265;
const float FRAME_RATE = 400.0;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations
const float FULL_HEALTH = 100;



// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY = '`';         // ` key
const UCHAR ESC_KEY = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY = VK_MENU;     // Alt key
const UCHAR ENTER_KEY = VK_RETURN;   // Enter key

#endif
