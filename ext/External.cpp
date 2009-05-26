
// $Id$

/*
Shade: A science-fiction computer roleplaying game.
Copyright (C) 2002  Greg McIntyre

Shade is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.

Shade is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Pictorial Consequences; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include "External.hpp"

#include "Display.hpp"


void init() {
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	SDL_EnableKeyRepeat(120, 20);

	SDL_EnableUNICODE(SDL_ENABLE);
}

void draw_map(VALUE map_value, VALUE tile_size_value, VALUE x1_value, VALUE y1_value, VALUE w_value, VALUE h_value) {

	// Return if v isn't a Map.
	const char *class_name = rb_class2name(CLASS_OF(map_value));
	if (strcasecmp(class_name, "Map") != 0) {
		printf("drawMap: Expected Map. Got %s.\n", class_name);
		return;
	}

	// Convert params.
	int tile_size = NUM2INT(tile_size_value);
	int x1 = NUM2INT(x1_value);
	int y1 = NUM2INT(y1_value);
	int w = NUM2INT(w_value);
	int h = NUM2INT(h_value);

	int i, j;
	for (j = x1; j != h; ++j) {
		for (i = y1; i != w; ++i) {
			unsigned char code = NUM2CHR(rb_gv_get("code"));
			uint colour = NUM2UINT(rb_gv_get("colour"));

			Display::set_colour(colour);
			Display::draw_glyph(tile_size*i, tile_size*j, code);
		}
	}
}
