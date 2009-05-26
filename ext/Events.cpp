// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.

#include "Events.hpp"

// Global variables.

SDL_Event e;
char result[128];


// Methods.

bool printable(int code) {
	return (code >= (int)' ' && code <= (int)'~');
}

void Events::wait() {
	while (SDL_WaitEvent(&e) >= 0) { // Wait for next SDL event.
		// Throw away pending keyboard events, or SDL seems to crash(?).
		// (This seems to be a nice enough input loop).
		if (e.type == SDL_VIDEORESIZE) {
			Display::set_size(e.resize.w, e.resize.h);
		}
		SDL_PeepEvents(NULL, 1000, SDL_GETEVENT, SDL_KEYUP | SDL_KEYDOWN);
		return;
	}
}

int Events::type() {
	return (int)e.type;
}

SDL_Event *Events::event() {
	return &e;
}

int Events::key() {
	return (int)e.key.keysym.sym;
}

int Events::mousePositionX() { return e.motion.x; }
int Events::mousePositionY() { return e.motion.y; }
int Events::mouseOffsetX() { return e.motion.xrel; }
int Events::mouseOffsetY() { return e.motion.yrel; }
bool Events::mouseButton(uint num) { return e.button.state & SDL_BUTTON(num); }
uint Events::mouseButtons() { return e.button.state; }

const char *Events::keyName(int code) {
	return SDL_GetKeyName((SDLKey)code);
}

const char *Events::keyString() {
	result[0] = '\0';
	if (
		key() != KEY_LEFT_SHIFT &&
		key() != KEY_RIGHT_SHIFT &&
		key() != KEY_LEFT_ALT &&
		key() != KEY_RIGHT_ALT &&
		key() != KEY_LEFT_CTRL &&
		key() != KEY_RIGHT_CTRL
		) {
		if (keyCtrl()) {
			strcat(result, "control ");
		}
		if (keyAlt()) {
			strcat(result, "alt ");
		}
		if (keyShift()) {
			strcat(result, "shift ");
		}
	}
	strcat(result, keyName(key()));
	return result;
}

int Events::keyCode() {
	return (int)e.key.keysym.unicode;
}

bool Events::keyCtrl() {
	return e.key.keysym.mod & KMOD_CTRL;
}

bool Events::keyAlt() {
	return e.key.keysym.mod & KMOD_ALT;
}

bool Events::keyShift() {
	return e.key.keysym.mod & KMOD_SHIFT;
}
