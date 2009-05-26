# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'Display'

class Widget

	attr_accessor :parent
	attr_accessor :name

	# Position
	attr_accessor :x
	attr_accessor :y

	# Size
	attr_accessor :width
	attr_accessor :height

	def draw
		draw_contents
	end

	# Draw the contents of this window. This must be defined by all
	# inheriting classes. When drawing, (0,0) represents the
	# top-left-most drawable point inside the window, according to the
	# padding values.
	def draw_contents
	end
end

class ContainerWidget < Widget

	attr :children

	def initialize
		@children = []
	end

	def <<(child)
		@children << child
	end

	# Draw all children widgets.
	def draw_contents
		for c in @children
			c.draw
		end
	end
end

class Window < ContainerWidget

	# Padding.
	attr :pleft
	attr :pright
	attr :ptop
	attr :pbottom

	# Create a width by height window which will be drawn at
	# (x,y). The title may or may not be displayed depending
	# on the decoration. The default decoration does not
	# display the title.
	#
	# p<direction> is the padding in that direction.
	# Padding determines where the window contents is from the
	# position given here. It should include the size of the
	# decorations so that they are not drawn over.
	def initialize(name, x, y, width, height, pleft=0, pright=0, ptop=0, pbottom=0)
		@name = name
		@x = x
		@y = y
		@width = width
		@height = height
		@pleft = pleft
		@pright = pright
		@ptop = ptop
		@pbottom = pbottom
		super()
	end

	# Decorate and draw the contents of a window.
	def draw
		# Clear.
		Display::set_colour 0x000000
		decorate
		draw_contents
	end

	# Draw a plain rectangle around the border of the
	# window. Disable this by redefining this method with a
	# null op.
	def decorate
		Display::set_colour 0xFFFFFF
	end
end

