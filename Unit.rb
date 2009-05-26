# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'GameObject'

class Unit < GameObject
	attr_accessor :location

	def x
		location.x
	end

	def y
		location.y
	end
	
	def hostile(unit)
		# For now, all units are peaceful.
		return false
	end

	def default_action(tile)
		if tile
			# Determine tile contents, then perform default action for
			# tile's contents.

			if tile.unit
				# There's a unit!
				if tile.unit.hostile(self)
					default_action_hostile_unit(tile.unit)
				else
					default_action_peaceful_unit(tile.unit)
				end
			elsif tile.class == Door
				if not tile.passable
					default_action_closed_door(tile)
				else
					default_action_ground(tile)
				end
			elsif tile.class == Sign
				default_action_sign(tile)
			elsif tile.class == Terminal
				default_action_terminal(tile)
			elsif tile.class == Wall
				default_action_wall(tile)
			elsif tile.class == Water
				default_action_water(tile)
			elsif tile.class == Ladder
				if tile.direction == Ladder::Up
					default_action_ladder_up(tile)
				else
					default_action_ladder_down(tile)
				end
			elsif tile.items.size > 0
				default_action_items(tile)
			else
				default_action_ground(tile)
			end
		end
	end

	def default_action_ground(tile)
		location.parent.move_unit(self, location, tile)
	end

	def default_action_hostile_unit(tile)
	end

	def default_action_peaceful_unit(tile)
	end

	def default_action_closed_door(tile)
		tile.open
	end

	def default_action_water(tile)
	end

	def default_action_wall(tile)
	end
end
