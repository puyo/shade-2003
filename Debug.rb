# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.

class Debug

	class << self

		def print(*stuff)
			puts stuff
		end
		
		def p(*stuff)
			puts stuff
		end

	end
end
