// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.

#include "Display.hpp"
#include "PNG.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>

#define FONT_NOT_LOADED  -1
#define NO_FONT  -1
#define FONT_ASCII_OFFSET  32
#define BPP  16

// Typedefs.

class Glyph {
    public:
        byte *bitmap;
        byte width;
        byte height;

        Glyph(byte width, byte height) : bitmap(NULL), width(width), height(height) {
            //printf("Glyph(%d, %d)\n", width, height);
            bitmap = new byte[width*height];
        }

        ~Glyph() {
            //printf("~Glyph()\n");
            if (bitmap != NULL) {
                delete[] bitmap;
                bitmap = NULL;
            }
        }
};


class Font {
    public:
        std::vector<Glyph *> glyphs;
        byte height;
        bool proportional;

        const Glyph& ascii_glyph(unsigned char code) const throw (std::out_of_range) {
            uint index = code - FONT_ASCII_OFFSET;
            if (index >= glyphs.size()) {
                printf("Font dropout: %d ('%c')\n", code, code);
                return *(*glyphs.end());
            }
            return *glyphs[index];
        }
};


class Colour {
    public:
        byte r, g, b, a;
        Colour() : r(r), g(g), b(b), a(a) {}
        Colour(byte r, byte g, byte b, byte a=0xFF) : r(r), g(g), b(b) {
            this->a = a;
        }
        Colour(byte *v) {
            set(v);
        }
        void set(byte *v) {
            r = v[0];
            g = v[1];
            b = v[2];
            a = v[3];
        }
        bool operator==(const Colour& col) const {
            return (r == col.r) && (g == col.g) && (b == col.b);
        }
        bool operator!=(const Colour& col) const {
            return (r != col.r) || (g != col.g) || (b != col.b);
        }
};


// Global variables.

SDL_Surface *screen;
std::vector<Font> fonts;
int current_font = -1;
bool opened = false;
Uint32 colour;
Uint32 clear_colour;

static void putpixel(int x, int y, Uint32 pixel) {
    int bpp = screen->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
    switch(bpp) {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

// Methods.

void Display::open(const char *title, uint width, uint height) {
    set_size(width, height);
    SDL_WM_SetCaption(title, title);
}


void Display::close() {
    SDL_Quit();
}


void Display::refresh() {
    //printf("Display::refresh\n");
    SDL_Flip(screen);
}


void Display::set_size(uint width, uint height) {

    // Init SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        exit(1);
    }

    // Get video capabilities.
    const SDL_VideoInfo* info = SDL_GetVideoInfo();    
    if (!info) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        exit(1);
    }    

    uint video_flags =
        SDL_DOUBLEBUF | // Enable double buffering
        SDL_HWPALETTE | // Store the palette in hardware
        SDL_RESIZABLE;  // Enable window resizing

    // Enable storing surfaces in memory if possible
    if (info->hw_available) {
        video_flags |= SDL_HWSURFACE;
    } else {
        video_flags |= SDL_SWSURFACE;
    }

    // Enable hardware blits if possible
    if (info->blit_hw) {
        video_flags |= SDL_HWACCEL;
    }

    // Open window or set video mode.
    screen = SDL_SetVideoMode(width, height, BPP, video_flags);
    if (screen == NULL) {
        fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());
        exit(1);
    }

    if (opened) {
        screen->w = width;
        screen->h = height;
    }

    clear();
    opened = true;
}


uint Display::width() {
    return screen->w;
}


uint Display::height() {
    return screen->h;
}


Glyph *make_glyph(const PNG& png, const Colour& fg, const Colour& bg, Font& font, uint x, uint y) throw (std::out_of_range) {

    //printf("make_glyph(%d, %d)\n", x, y);
    //printf("make_glyph: bg = (%d, %d, %d)\n", bg.r, bg.g, bg.b);

    // Measure the width by reading until bg.
    int glyph_width = 0;
    Colour current;

    while (true) {
        if (x + glyph_width > png.width()) {
            break;
        }
        current.set(png.get(x + glyph_width, y));
        //printf("make_glyph: current = (%d, %d, %d)\n", current.r, current.g, current.b);
        if (current == bg) {
            break;
        }
        ++glyph_width;
    }

    //printf("makeGlyph: width = %d\n", glyph_width);

    if (glyph_width == 0) {
        throw std::out_of_range("Ran out of font image while reading glyph.");
    }

    printf("Allocating glyph...\n");

    Glyph *result = new Glyph(glyph_width, font.height);

    printf("Reading bitmap...\n");

    // Interpret PNG pixels as bitmap.
    for (uint j = 0; j != result->height; ++j) {
        for (uint i = 0; i != result->width; ++i) {
            // Get the next pixel.
            current.set(png.get(x + i, y + j));

            if (current != fg) {
                // Use different alpha intensities of white.
                // Take the alpha intensity to be the average
                // intensity of the RGB colour components.
                byte intensity = (current.r + current.g + current.b)/3;
                result->bitmap[j*result->width + i] = intensity;
                ///printf("%03d", intensity);
            } else {
                result->bitmap[j*result->width + i] = 0;
                //printf("---");
            }
        }
        //printf("\n");
    }
    return result;
}


bool skip_bg_pixels(PNG& png, Colour& bg, uint *x, uint y) {
    Colour current;
    while (true) {
        if (*x >= png.width()) {
            return true;
        }
        current.set(png.get(*x, y));
        if (current != bg) {
            return false;
        }
        ++(*x);
    }
}


int Display::load_font(const char *filename) {
    PNG png(filename);
    if (!png.loaded()) {
        return FONT_NOT_LOADED;
    }

    Font& font = *(new Font);

    Colour fg;
    Colour bg;		
    try {
        // Measure fg/bg colours and height of font.
        // fg is always pixel at (0, 0).
        // bg is the next different pixel, reading across.
        int font_height = 0;
        fg.set(png.get(0, 0));
        while (true) {
            bg.set(png.get(0, font_height));
            if (bg != fg) {
                break;
            }
            ++font_height;
        }

        font.height = font_height;
        font.proportional = false;

        uint last_width = 0;
        uint glyph_offset_x = 0;
        uint glyph_offset_y = 0;
        while (true) {

            // Skip pixels until not bg colour. If end of file, quit.
            bool endOfRow = skip_bg_pixels(png, bg, &glyph_offset_x, glyph_offset_y);
            if (endOfRow) {
                // Increment the y offset past this row.
                glyph_offset_y += font.height + 1;
                // Can we fit another row?
                if (glyph_offset_y + font.height >= png.height()) {
                    // No, let's quit.
                    break;
                }
                // Start at the left hand side again.
                glyph_offset_x = 0;
            }

            printf("Making glyph...\n");

            // Make new glyph.
            Glyph *g = make_glyph(png, fg, bg, font, glyph_offset_x, glyph_offset_y);

            // Increment the x offset past this character.
            glyph_offset_x += g->width;

            // Note whether this font is proportional.
            if (!font.proportional) {
                // Check for differences in widths.
                if (last_width > 0 && g->width != last_width) {
                    font.proportional = true;
                }
                last_width = g->width;
            }

            printf("Storing glyph...\n");

            // Store the glyph.
            font.glyphs.push_back(g);

            printf("Glyph stored.\n");
        }

    } catch (std::out_of_range e) {
        fprintf(stderr, "[%s]\n", e.what());
        exit(1);
    }

    png.free();

    // Add the font to our list.
    fonts.push_back(font);

    return fonts.size() - 1;
}


bool Display::font_loaded(uint id) {
    // If there is 1 font loaded, it has ID 0 & size == 1.
    // If there are 2 fonts loaded, 0, 1 & size == 2.
    // ...
    return (fonts.size() - 1) >= id;
}


bool Display::font_proportional(uint id) {
    return fonts[id].proportional;
}


uint Display::text_width(uint id, const char *string) {
    Font& font = fonts[id];
    uint result = 0;
    try {
        for (int i = 0; string[i]; ++i) {
            const Glyph& g = font.ascii_glyph(string[i]);
            result += g.width;
        }
    } catch (std::out_of_range e) {
        fprintf(stderr, "[%s]\n", e.what());
        exit(1);
    }
    return result;
}


uint Display::text_height(uint fontID) {
    return fonts[fontID].height;
}


void Display::set_colour(unsigned int value) {
    colour = SDL_MapRGB(screen->format,
            (value >> 16) & 0xFF,
            (value >> 8) & 0xFF,
            (value) & 0xFF
            );
}


void Display::set_clear_colour(unsigned int value) {
    clear_colour = SDL_MapRGB(screen->format,
            (value >> 16) & 0xFF,
            (value >> 8) & 0xFF,
            (value) & 0xFF
            );
}


void Display::set_font(uint fontID) {
    current_font = fontID;
}


void Display::clear() {
    SDL_FillRect(screen, NULL, clear_colour);
}


void Display::draw_string(int x, int y, const char *string) {
    uint offset = 0;
    uint width = 0;
    for (uint i = 0; string[i]; ++i) {
        width = draw_glyph(x + offset, y, string[i]);
        offset += width;
    }
}


uint Display::draw_glyph(int x, int y, unsigned char ch) {

    try {
        if (current_font == NO_FONT) {
            throw std::out_of_range("Current font not set.");
            return 0;
        }

        const Glyph& g = fonts[current_font].ascii_glyph(ch);

        for (int j = 0; j != g.height; ++j) {
            for (int i = 0; i != g.width; ++i) {
                if (g.bitmap[j*g.width + i]) {
                    putpixel(x + i, y + j, colour);
                    //printf("%05d", colour);
                } else {
                    putpixel(x + i, y + j, 0);
                    //printf(".....");
                }
            }
            //printf("\n");
        }
        //printf("\n");
        return g.width;

    } catch (std::out_of_range e) {
        fprintf(stderr, "[%s]\n", e.what());
        return 0;
    }
}


const char *Display::draw_paragraph(int x, int y, uint width, uint height, const char *string) {
    return NULL;
}


void Display::toggle_full_screen() {
    SDL_WM_ToggleFullScreen(screen);
    refresh();
}


void Display::lock() {
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }
}


void Display::unlock() {
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
}
