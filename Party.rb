# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'Player'
require 'Ally'

class Party

	attr :player
	attr :allies

	def initialize(player)
		@player = player
		@allies = []
	end

	def add_ally(ally)
		@allies << ally
	end

	def removeAlly(ally)
		@allies -= ally
	end
end
