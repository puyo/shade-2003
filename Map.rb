# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'Tile'
require 'Debug'
require 'External'

class Map < External::Map

	def allocate(width, height)
		Debug.print "Allocating #{width}x#{height} map..."
		@blank = Empty.new(self)
		alloc(self, width, height)
	end

	def free
		dealloc
	end

	def set_unit(x, y, unit)
		t = tile(x, y)
		t.unit = unit
		unit.location = t
	end

	def make_demo
		puts "Making demo map..."
		
		allocate(50, 50)

		# Walls
		for i in 5..10
			t = Wall::new(self)
			set_tile(i, 5, t)
			t.colour = 0x808080
		end
		for i in 5..10
			t = Wall::new(self)
			set_tile(5, i, t)
			t.colour = 0x808080
		end

		# Door
		t = Door::new(self)
		set_tile(5, 7, t)
		t.colour = 0xFF8040
	end

	# Attempt moving a unit from one tile to another.
	# If there are any problems, do nothing.
	def move_unit(unit, tile_old, tile_new)
		if tile_new and not tile_new.unit and tile_new.passable
			tile_old.unit = nil
			tile_new.unit = unit
			unit.location = tile_new
		end
	end

	def new_tile(type)
		return eval(type).new(self)
	end
end
