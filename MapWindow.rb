# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'GUI'

class MapWindow < Window

	def initialize(map, font, x, y, width, height)
		@map = map
		@font = font
		@size = Display.text_height(@font)
		Map::set_viewport_size(@size, width/@size, height/@size)
		Map::set_viewport_offset(x, y)
		super('Map', x, y, width, height)
	end

	def draw_contents
		Display::set_font(@font)
		@map.draw
	end
end
