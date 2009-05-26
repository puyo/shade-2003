# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'GUI'

class PartyWindow < Window

	def initialize(party, font, x, y, width, height)
		@party = party
		@font = font
		super('Party', x, y, width, height, 5, 5, 5, 5)
	end

	def draw_contents
		Display::set_colour 0xFFFFFF
		Display::set_font(@font)

		x = @party.player.location.x
		y = @party.player.location.y

		Display::draw_string(0, 0, x.to_s + ',' + y.to_s)
	end
end
