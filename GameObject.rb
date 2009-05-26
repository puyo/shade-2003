# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

class GameObject
	attr :id
	attr :name
	attr_accessor :code
	attr_accessor :colour

	def initialize(colour, code)
		@colour = colour
		@code = code
	end
end
