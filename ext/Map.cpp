// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.

#include "Map.hpp"
#include "Display.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

int map_offset_x = 0;
int map_offset_y = 0;

uint tile_size;
uint viewport_width;
uint viewport_height;

Map::Map() {
	tiles = Qnil;
	rb_define_variable("tiles", &tiles);
}

uint Map::width() const {
	return map_width;
}

uint Map::height() const {
	return map_height;
}

void Map::scroll_viewport(int dx, int dy) {
	map_offset_x += dx;
	map_offset_y += dy;
}

void Map::set_viewport_offset(int x, int y) {
	map_offset_x = x;
	map_offset_y = y;
}

void Map::set_viewport_size(uint s, uint vw, uint vh) {
	tile_size = s;
	viewport_width = vw;
	viewport_height = vh;
}

void Map::centre_viewport(const Map& map) {
	map_offset_x = ((signed)map.width() - (signed)viewport_width)/2;
	map_offset_y = ((signed)map.height() - (signed)viewport_height)/2;
}

void Map::alloc(VALUE self, uint w, uint h) {
	map_width = w;
	map_height = h;
	uint mapSize = map_width * map_height;
	tiles = rb_ary_new2(mapSize);

	VALUE ground = rb_str_new2("Ground");
	for (uint j = 0; j != map_height; ++j) {
		for (uint i = 0; i != map_width; ++i) {
			VALUE t = rb_funcall(self, rb_intern("new_tile"), 1, ground);
			set_tile(i, j, t);
		}
		//printf(".");
		fflush(stdout);
	}
	//printf("\n");
}

void Map::dealloc() {
	tiles = Qnil;
}

void Map::set_tile(uint x, uint y, VALUE t) {
	if (x >= map_width || y >= map_height) {
		return;
	}
	rb_iv_set(t, "@x", INT2NUM(x));
	rb_iv_set(t, "@y", INT2NUM(y));
	rb_ary_store(tiles, y*map_width + x, t);
}

VALUE Map::tile(uint x, uint y) const {
	if (x >= map_width || y >= map_height) {
		return Qnil;
	}
	return rb_ary_entry(tiles, y*map_width + x);
}

void Map::draw() const {
   	int i, j;
	int maxX = map_offset_x + viewport_width;
	int maxY = map_offset_y + viewport_height;

	Display::lock();

	for (j = map_offset_y; j < maxY; ++j) {
		for (i = map_offset_x; i < maxX; ++i) {
			VALUE t = tile(i, j);
			
			if (t == Qnil)
				continue;

			unsigned char code;
			uint colour;

			VALUE u = rb_iv_get(t, "@unit");

			if (u != Qnil) {
				// Draw the unit.
				code = NUM2CHR(rb_iv_get(u, "@code"));
				colour = NUM2UINT(rb_iv_get(u, "@colour"));
			} else {
				VALUE items = rb_iv_get(t, "@items");
				if (RARRAY_LEN(items) > 0) {
					// Draw an item.
					code = 'i';
					colour = 0x800000;
				} else {
					// Draw the tile.
					code = NUM2CHR(rb_iv_get(t, "@code"));
					colour = NUM2UINT(rb_iv_get(t, "@colour"));
				}
			}
			Display::set_colour(colour);
			Display::draw_glyph(tile_size*(i - map_offset_x), tile_size*(j - map_offset_y), code);
		}
	}

	Display::unlock();
}
