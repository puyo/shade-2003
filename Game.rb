# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'Map'
require 'Party'
require 'MapWindow'
require 'MessageWindow'
require 'PartyWindow'
require 'Options'

# A Shade game in the sense of 'New Game' or 'Load Game'.
class Game
	
	# Run the Shade demo.
	def Game::demo
		@map = Map::new
		@map.make_demo

		puts 'Loading fonts...'
		verdana = Display::load_font('fonts/verdana-14.png')
		fixed = Display::load_font('fonts/fixed-8.png')
		map_font = fixed

		@player = Player::new(0x00FF00, ?@)
		@party = Party::new(@player)

		@map.set_unit(7, 7, @player)

		@map_window = MapWindow::new(@map, map_font, 0, 0, Display::width, Display::height*3/4)
		@message_window = MessageWindow::new(fixed, 0, Display::height*2/3, Display::width, Display::height - Display::height*2/3 - 1)

		Game::loop
	end

	# The main game input/drawing loop. Does not return.
	def Game::loop
		@map_window.draw
#		@message_window.draw

		while true
			Display::refresh
			Events::wait

			case Events::type
			when Events::EVENT_EXIT
				exit
			when Events::EVENT_KEY_DOWN

				case Events::keyString
				when 'escape'
					exit
				when 'right ctrl' # Ignore these...
				when 'left ctrl'
				when 'right alt'
				when 'left alt'
				when 'right shift'
				when 'left shift'
				when 'f12'
					Display::toggle_full_screen
				when 'control c'
					Map::centre_viewport(@map)
				when 'control o'
					Map::set_viewport_offset(0, 0)
				when 'control ' + Options::Keymap['left']
					Map::scroll_viewport(-1, 0)
				when 'control ' + Options::Keymap['right']
					Map::scroll_viewport(+1, 0)
				when 'control ' + Options::Keymap['up']
					Map::scroll_viewport(0, -1)
				when 'control ' + Options::Keymap['down']
					Map::scroll_viewport(0, +1)
				when Options::Keymap['left']
					@player.default_action(@player.location.adjacent_location(-1, +0))
				when Options::Keymap['right']
					@player.default_action(@player.location.adjacent_location(+1, +0))
				when Options::Keymap['up']
					@player.default_action(@player.location.adjacent_location(+0, -1))
				when Options::Keymap['down']
					@player.default_action(@player.location.adjacent_location(+0, +1))
				when Options::Keymap['up left']
					@player.default_action(@player.location.adjacent_location(-1, -1))
				when Options::Keymap['up right']
					@player.default_action(@player.location.adjacent_location(+1, -1))
				when Options::Keymap['down left']
					@player.default_action(@player.location.adjacent_location(-1, +1))
				when Options::Keymap['down right']
					@player.default_action(@player.location.adjacent_location(+1, +1))
				else
					# @message_window << "Unrecognised key '#{Events::keyString}'"
				end

				@map_window.draw
#				@message_window.draw
			end
		end
	end
end
