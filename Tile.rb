# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.
#

require 'GameObject'
require 'Unit'
require 'Inventory'

# A single grid space on a tile map.
class Tile < GameObject

	CLEAR_CODE = ?.
	CLEAR_COLOUR = 0xFFFFFF
	
	attr_accessor :unit
	attr_accessor :parent
	attr_accessor :x
	attr_accessor :y
	attr_accessor :items

	attr :passable
	attr :blocks_vision

	def initialize(parent, colour=CLEAR_COLOUR, code=CLEAR_CODE)
		super(colour, code)
		@parent = parent
		@unit = nil
		@items = Inventory.new
		@passable = false
		@blocks_vision = false
	end

	def clear
		code = CLEAR_CODE
		colour = CLEAR_COLOUR
	end

	def adjacent_location(dx, dy)
		return @parent.tile(x + dx, y + dy)
	end
end

# An empty tile. An empty tile is fallen through when stepped upon.
class Empty < Tile
	def initialize(parent)
		super(parent, CLEAR_COLOUR, ?\ )
		@passable = false
		@blocks_vision = false
	end
end

# Normal ground.
class Ground < Tile
	def initialize(parent)
		super(parent, CLEAR_COLOUR, ?.)
		@passable = true
		@blocks_vision = false
	end
end

# A normal wall.
class Wall < Tile
	def initialize(parent)
		super(parent, CLEAR_COLOUR, ?#)
		@passable = false
		@blocks_vision = true
	end
end

# A typical door with no lock.
class Door < Tile
	def initialize(parent)
		@open_code = ?/
		@closed_code = ?+
		@open = false
		@passable = open
		@blocks_vision = (not open)
		super(parent, CLEAR_COLOUR, @closed_code)
	end

	def open
		@passable = true
		@blocks_vision = false
		@code = @open_code
	end

	def close
		@passable = false
		@blocks_vision = true
		@code = @closed_code
	end
end

class Water < Tile
end

class Sign < Tile
end

class Ladder < Tile
end

class Terminal < Tile
end

