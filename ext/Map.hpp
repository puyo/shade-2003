// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.
  
#ifndef MAP_HPP
#define MAP_HPP

#include "External.hpp"

class Map {

	public:

	Map();

	uint width() const;
	uint height() const;
	VALUE tile(uint x, uint y) const;

	void set_tile(uint x, uint y, VALUE t);

	static void scroll_viewport(int dx, int dy);
	static void set_viewport_offset(int x, int y);
	static void set_viewport_size(uint s, uint vw, uint vh);
	static void centre_viewport(const Map& map);

	void alloc(VALUE self, uint width, uint height);
	void dealloc();

	void draw() const;

	private:
	VALUE tiles;
	uint map_width;
	uint map_height;
};
	
#endif
