# $Id$
#
# Shade: A science-fiction computer roleplaying game.
# Copyright (C) 2002  Greg McIntyre
# 
# Shade is licensed under the GNU General Public License as published
# by the Free Software Foundation. For more information, please refer
# to gpl.txt.


###############
# Libraries.
###############

# RUBY_DIR = /usr/lib/ruby/1.8/i486-linux/

# # Libraries used.
# OTHER_LIBS = ruby SDL png

# # Directories where libraries are installed.
# OTHER_LIB_DIRS = $(SRC_DIRS) $(RUBY_DIR) /usr/lib

# # Directories where header files are installed.
# OTHER_INC_DIRS = . $(RUBY_DIR) /usr/include/SDL

###############
# Compiler options.
###############

# CC_FLAGS = $(CC_OPTIONS) $(INC)
# LD_FLAGS = $(LD_OPTIONS) $(LIB_DIRS) $(LIBS)



LD = g++

CXXFLAGS = -Wall -O2
CXXFLAGS += -fpic
#CXXFLAGS += -I$(RUBY_DIR)
CXXFLAGS += `PKG_CONFIG_PATH="${PKG_CONFIG_PATH}:/usr/local/opt/ruby@2.3/lib/pkgconfig" pkg-config sdl ruby-2.3 libpng --cflags`

LDFLAGS = -shared
LDFLAGS += `PKG_CONFIG_PATH="/usr/local/opt/ruby@2.3/lib/pkgconfig" pkg-config sdl ruby-2.3 libpng --libs`
#LDFLAGS += -L$(RUBY_DIR) -lruby1.8
LDFLAGS += -lpng


###############
# Targets.
###############

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HDRS = $(wildcard *.hpp)
WRAPPER_INTERFACES = $(wildcard *.ipp)
WRAPPER_OBJS = $(WRAPPER_INTERFACES:.ipp=_wrap.o)

TARGET = External.so


all: $(TARGET)

$(TARGET): $(WRAPPER_OBJS) $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

# C++

%_wrap.cpp: %.ipp $(HDRS)
	swig -c++ -ruby -o $@ $<

# C

%_wrap.c: %.i
	swig -ruby -o $@ $<

clean:
	/bin/rm -fv *.o *_wrap.c *_wrap.cpp *~ $(TARGET)
