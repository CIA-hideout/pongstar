#ifndef _CONSTANTS_H
#define _CONSTANTS_H
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr) { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr) { if (ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if (ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr) { if (ptr) { (ptr)->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr) { if (ptr) { (ptr)->onResetDevice(); } }
// Color which should be transparent
#define TRANSCOLOR SETCOLOR_ARGB(0,255,0,255)

//-----------------------------------------------
// Constants
//-----------------------------------------------
// Window
const char CLASS_NAME[] = "Pongstar";
const char GAME_TITLE[] = "Pongstar";
const bool FULLSCREEN = false;
const UINT GAME_WIDTH = 1280;
const UINT GAME_HEIGHT = 720;

// Game
const double PI = 3.14159265;
const float FRAME_RATE = 500.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

const int WALL_PADDING = 10;
const int TOP_WALL = WALL_PADDING;
const int BOTTOM_WALL = GAME_HEIGHT - WALL_PADDING;
const int LEFT_WALL = WALL_PADDING;
const int RIGHT_WALL = GAME_WIDTH - WALL_PADDING;
const int LEFT_SHIELD = 70;
const int RIGHT_SHIELD = GAME_WIDTH - 70;

// Key Mappings
const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;
const UCHAR SPACE_KEY = VK_SPACE;
const UCHAR UP_KEY = VK_UP;
const UCHAR DOWN_KEY = VK_DOWN;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;

// Sprites
const char BALL_IMAGE[] = "sprites\\Ball.png";
const char BORDER_IMAGE[] = "sprites\\Border.png";
const char PADDLE_IMAGE[] = "sprites\\Paddle.png";
const char BUMPER_IMAGE[] = "sprites\\Bumper.png";
const char PICKUP_IMAGE[] = "sprites\\Pickups.png";
const char DIVIDER_IMAGE[] = "sprites\\Divider.png";

// Screens
const char INSTRUCTIONS[] = "resources\\screens\\Instructions.png";

const int HUD_Y_POS = 12;

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";
// XGS_FILE must be location of .xgs file.
const char XGS_FILE[] = "audio\\Win\\pongstar.xgs";

// audio cues
const char HIT_BUMPER_CUE[] = "hit-bumper";
const char HIT_PADDLE_CUE[] = "hit-paddle";
const char HIT_WALL_CUE[] = "hit-wall";

const char ENLARGE_CUE[] = "enlarge";
const char SHRINK_CUE[] = "shrink";
const char BOOST_CUE[] = "boost";
const char SLOW_CUE[] = "slow";
const char MULTIPLY_CUE[] = "multiply";
const char SHIELD_CUE[] = "shield";
const char MAGNET_CUE[] = "magnet";

#endif
