# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'GUI'

# Window at the bottom of the main screen which displays text messages to the user.
# TODO: Scrollback (page up, page down).
class MessageWindow < Window

	attr :max

	def initialize(font, x, y, width, height, max=100)
		@font = font
		@font_height = Display::text_height(@font)
		@messages = []
		@max = max
		super('Messages', x, y, width, height, 5, 5, 5, 5)
	end

	# Add a message.
	def <<(message)
		@messages << message
		# If there are too many, throw the oldest one away.
		while @messages.size > @max
			@messages.shift
		end
	end

	# Clear all messages.
	def clear
		@messages = []
	end

	def draw
		Display::set_font @font
		Display::set_colour 0xFF0000

		# TODO: Replace with 'draw_paragraph's

		y = @y + height - @font_height - @pbottom - @ptop
		@messages.reverse.each { |m|
			Display::draw_string(0, y, m)
			y -= @font_height
			return if y < -@font_height
		}
	end
end
