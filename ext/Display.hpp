// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.
  
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "External.hpp"

class Display {
	public:

	static void open(const char *title, uint width, uint height);
	static void close();

	static uint width();
	static uint height();

	static int load_font(const char *filename);
	static bool font_loaded(uint fontID);
	static bool font_proportional(uint fontID);
	static uint text_width(uint fontID, const char *string);
	static uint text_height(uint fontID);

	static void set_colour(unsigned int value);
	static void set_clear_colour(unsigned int value);
	static void set_font(uint fontID);

	static void clear();
	static void refresh();
	static void set_size(uint width, uint height);

	static void draw_string(int x, int y, const char *string);
	static uint draw_glyph(int x, int y, unsigned char ch);
	static const char *draw_paragraph(int x, int y, uint width, uint height, const char *string);

	static void toggle_full_screen();

	static void lock();
	static void unlock();
};

#endif
