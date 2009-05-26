// $Id$
//
// Shade: A science-fiction computer roleplaying game.
// Copyright (C) 2002  Greg McIntyre
// 
// Shade is licensed under the GNU General Public License as published
// by the Free Software Foundation. For more information, please refer
// to gpl.txt.

#ifndef EXTERNAL_HPP
#define EXTERNAL_HPP

#include <SDL.h>
#include <cstdlib>
#include <cstdio>

#ifndef byte
#define byte  unsigned char
#endif
#ifndef uint
#define uint  unsigned int
#endif

#include "ruby.h"

void init();

#endif
