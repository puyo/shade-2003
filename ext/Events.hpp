// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.
  
#ifndef EVENT_HPP
#define EVENT_HPP

#include "External.hpp"
#include "Display.hpp"

class Events {
	public:

	enum event_t {
		EVENT_RESIZE = SDL_VIDEORESIZE,
		EVENT_EXIT = SDL_QUIT,
		EVENT_KEY_DOWN = SDL_KEYDOWN,
		EVENT_KEY_UP = SDL_KEYUP,
		EVENT_MOUSE_DOWN = SDL_MOUSEBUTTONDOWN,
		EVENT_MOUSE_UP = SDL_MOUSEBUTTONUP,
		EVENT_MOUSE_MOTION = SDL_MOUSEMOTION,
	};

	enum button_t {
		BUTTON_LEFT = SDL_BUTTON_LEFT,
		BUTTON_RIGHT = SDL_BUTTON_RIGHT,
		BUTTON_MIDDLE = SDL_BUTTON_MIDDLE,
	};

	enum key_t {
		KEY_ESCAPE = SDLK_ESCAPE,

		KEY_F1 = SDLK_F1,
		KEY_F2 = SDLK_F2,
		KEY_F3 = SDLK_F3,
		KEY_F4 = SDLK_F4,

		KEY_F5 = SDLK_F5,
		KEY_F6 = SDLK_F6,
		KEY_F7 = SDLK_F7,
		KEY_F8 = SDLK_F8,

		KEY_F9 = SDLK_F9,
		KEY_F10 = SDLK_F10,
		KEY_F11 = SDLK_F11,
		KEY_F12 = SDLK_F12,

		KEY_PRINTSCREEN = SDLK_PRINT,
		KEY_SCROLL_LOCK = SDLK_SCROLLOCK,
		KEY_PAUSE = SDLK_PAUSE,

		KEY_TILDE = SDLK_BACKQUOTE,
		KEY_1 = SDLK_1,
		KEY_2 = SDLK_2,
		KEY_3 = SDLK_3,
		KEY_4 = SDLK_4,
		KEY_5 = SDLK_5,
		KEY_6 = SDLK_6,
		KEY_7 = SDLK_7,
		KEY_8 = SDLK_8,
		KEY_9 = SDLK_9,
		KEY_0 = SDLK_0,
		KEY_MINUS = SDLK_MINUS,
		KEY_EQUALS = SDLK_EQUALS,
		KEY_BACKSPACE = SDLK_BACKSPACE,

		KEY_INSERT = SDLK_INSERT,
		KEY_HOME = SDLK_HOME,
		KEY_PAGE_UP = SDLK_PAGEUP,

		KEY_NUMLOCK = SDLK_NUMLOCK,
		KEY_KP_DIVIDE = SDLK_KP_DIVIDE,
		KEY_KP_MULTIPLY = SDLK_KP_MULTIPLY,
		KEY_KP_MINUS = SDLK_KP_MINUS,

		KEY_TAB = SDLK_TAB,
		KEY_Q = SDLK_q,
		KEY_W = SDLK_w,
		KEY_E = SDLK_e,
		KEY_R = SDLK_r,
		KEY_T = SDLK_t,
		KEY_Y = SDLK_y,
		KEY_U = SDLK_u,
		KEY_I = SDLK_i,
		KEY_O = SDLK_o,
		KEY_P = SDLK_p,
		KEY_LEFTBRACKET = SDLK_LEFTBRACKET,
		KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET,
		KEY_BACKSLASH = SDLK_BACKSLASH,
		
		KEY_DELETE = SDLK_DELETE,
		KEY_END = SDLK_END,
		KEY_PAGE_DOWN = SDLK_PAGEDOWN,

		KEY_KP_7 = SDLK_KP7,
		KEY_KP_8 = SDLK_KP8,
		KEY_KP_9 = SDLK_KP9,
		KEY_KP_PLUS = SDLK_KP_PLUS,

		KEY_CAPSLOCK = SDLK_CAPSLOCK,
		KEY_A = SDLK_a,
		KEY_S = SDLK_s,
		KEY_D = SDLK_d,
		KEY_F = SDLK_f,
		KEY_G = SDLK_g,
		KEY_H = SDLK_h,
		KEY_J = SDLK_j,
		KEY_K = SDLK_k,
		KEY_L = SDLK_l,
		KEY_SEMICOLON = SDLK_SEMICOLON,
		KEY_QUOTE = SDLK_QUOTE,
		KEY_ENTER = SDLK_RETURN,

		KEY_KP_4 = SDLK_KP4,
		KEY_KP_5 = SDLK_KP5,
		KEY_KP_6 = SDLK_KP6,

		KEY_LEFT_SHIFT = SDLK_LSHIFT,
		KEY_Z = SDLK_z,
		KEY_X = SDLK_x,
		KEY_C = SDLK_c,
		KEY_V = SDLK_v,
		KEY_B = SDLK_b,
		KEY_N = SDLK_n,
		KEY_M = SDLK_m,
		KEY_COMMA = SDLK_COMMA,
		KEY_PERIOD = SDLK_PERIOD,
		KEY_SLASH = SDLK_SLASH,
		KEY_RIGHT_SHIFT = SDLK_RSHIFT,
		
		KEY_UP = SDLK_UP,
		
		KEY_KP_1 = SDLK_KP1,
		KEY_KP_2 = SDLK_KP2,
		KEY_KP_3 = SDLK_KP3,
		KEY_KP_ENTER = SDLK_KP_ENTER,

		KEY_LEFT_CTRL = SDLK_LCTRL,
		KEY_LEFT_ALT = SDLK_LALT,
		KEY_SPACE = SDLK_SPACE,
		KEY_RIGHT_ALT = SDLK_RALT,
		KEY_RIGHT_CTRL = SDLK_RCTRL,

		KEY_LEFT = SDLK_LEFT,
		KEY_DOWN = SDLK_DOWN,
		KEY_RIGHT = SDLK_RIGHT,

		KEY_KP_0 = SDLK_KP0,
		KEY_KP_PERIOD = SDLK_KP_PERIOD,
	};

	static void wait();
	static int type();
	static SDL_Event *event();

	static int mousePositionX();
	static int mousePositionY();
	static int mouseOffsetX();
	static int mouseOffsetY();
	static bool mouseButton(uint num);
	static uint mouseButtons();

	static int key();
	static const char *keyName(int code);
	static const char *keyString();
	static int keyCode();
	static bool keyCtrl();
	static bool keyAlt();
	static bool keyShift();
};

#endif
