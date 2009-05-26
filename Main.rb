# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

require 'External'
require 'Display'
require 'Events'
require 'Game'

# Execution starts here!

puts "Loading..."

External::init
Display::open('Shade', 640, 480)
Game::demo
