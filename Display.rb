# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'External'

class Display < External::Display
	class << self

		attr :width
		attr :height
		
		# Open the display with resolution width by height pixels. 
		# If the display is running in a windowed environment (such as
		# running in an X window), this opens a new window with a title
		# bar containing the title provided. Otherwise this sets the
		# screen resolution directly at a depth sufficient to work in RGBA
		# (and hence only supported screen resolutions should be passed).
		def open(title, width, height)
			@width = width
			@height = height
			@handlers = []
			
			External::Display.open(title, width, height)
		end
	end
end

