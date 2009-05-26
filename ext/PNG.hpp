// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.

#ifdef uint
#undef uint
#endif

#include <png.h>
#include <cstdio>
#include <stdexcept>

// Very simple OO libpng wrapper.
class PNG {
	private:
	png_struct *png;
	png_info *info;
	png_info *end_info;
	png_byte **data;
	
	public:

	PNG() : png(NULL), info(NULL), end_info(NULL) {
		data = NULL;
	}
	PNG(const char *filename) : png(NULL), info(NULL), end_info(NULL) {
		load(filename);
	}

	unsigned int height() const {
		return loaded() ? info->height : 0;
	}

	unsigned int width() const {
		return loaded() ? info->width : 0;
	}

	bool loaded() const {
		return data != NULL;
	}

	png_byte *operator[](unsigned int index) const throw (std::out_of_range) {
		if (index >= height()) {
			char msg[80];
			sprintf(msg, "Invalid row in PNG image: %u", index);
			throw std::out_of_range(msg);
		}
		return data[index];
	}

	png_byte *get(unsigned int x, unsigned int y) const throw (std::out_of_range) {
		if (x >= width() || y >= height()) {
			char msg[80];
			sprintf(msg, "Invalid position in PNG image: (%u, %u)", x, y);
			throw std::out_of_range(msg);
		}
		return &data[y][x*4];
	}

	void load(const char *filename) {
		FILE *fp = fopen(filename, "rb");

		if (!fp) {
			return;
		}

		// Read header bytes.
		const int number = 8;
		png_byte header[number];
		size_t bytes = fread(header, 1, number, fp);

		// Verify this is a PNG.
		const bool is_png = !png_sig_cmp(header, 0, number);
		if (!is_png) {
			return;
		}

		// Allocate libpng structures.
		png = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
		if (!png) {
			return;
		}
		
		info = png_create_info_struct(png);
		if (!info) {
			png_destroy_read_struct(&png, (png_infopp)NULL, (png_infopp)NULL);
			return;
		}
		
		end_info = png_create_info_struct(png);
		if (!end_info) {
			png_destroy_read_struct(&png, &info, (png_infopp)NULL);
			return;
		}

		// Read PNG into structures.
		png_init_io(png, fp);
		png_set_sig_bytes(png, number);
		png_read_png(png, info, PNG_TRANSFORM_EXPAND, NULL);
		data = png_get_rows(png, info);
	}

	void free() {
		png_destroy_read_struct(&png, &info, &end_info);
		data = NULL;
	}
};
