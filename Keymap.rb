# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

class Keymap < Hash
end

$keymap = Keymap.new
$keymap['left'] = 'left'
$keymap['right'] = 'left'
$keymap['up'] = 'up'
$keymap['down'] = 'down'
