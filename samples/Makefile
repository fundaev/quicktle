#-----------------------------------------------------------------------------+
# TLELib                                                                      |
# Copyright 2011 Sergei V. Fundaev                                            |
#-----------------------------------------------------------------------------+
# This file is part of TLELib.                                                |
#                                                                             |
# TLELib is free software: you can redistribute it and/or modify              |
# it under the terms of the GNU Lesser General Public License as published by |
# the Free Software Foundation, either version 3 of the License, or           |
# (at your option) any later version.                                         |
#                                                                             |
# TLELib is distributed in the hope that it will be useful,                   |
# but WITHOUT ANY WARRANTY; without even the implied warranty of              |
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               |
# GNU Lesser General Public License for more details.                         |
#                                                                             |
# You should have received a copy of the GNU Lesser General Public License    |
# along with TLELib. If not, see <http://www.gnu.org/licenses/>.              |
#-----------------------------------------------------------------------------+

CXXFLAGS       += -Wall -I../include
TARGETS        = sample_1 sample_2 sample_3
TLELIB_DIR     = ../include/tlelib
VPATH          = $(TLELIB_DIR)
TLELIB_OBJECTS = tlenode.o tlestream.o tlefunc.o

.PHONY: purge clean $(TARGETS)

all: $(TARGETS)

sample1/main.o: sample1/main.cpp
sample2/main.o: sample2/main.cpp
sample3/main.o: sample3/main.cpp
tlenode.o: $(TLELIB_DIR)/tlenode.cpp $(TLELIB_DIR)/tlenode.h $(TLELIB_DIR)/tleexception.h
tlestream.o: $(TLELIB_DIR)/tlestream.cpp $(TLELIB_DIR)/tlestream.h $(TLELIB_DIR)/tlenode.h
tlefunc.o: $(TLELIB_DIR)/tlefunc.cpp $(TLELIB_DIR)/tlefunc.h

sample_1: $(TLELIB_OBJECTS) sample1/main.o
	$(CXX) $(LDFLAGS) sample1/main.o $(TLELIB_OBJECTS) -o sample_1

sample_2: $(TLELIB_OBJECTS) sample2/main.o
	$(CXX) $(LDFLAGS) sample2/main.o $(TLELIB_OBJECTS) -o sample_2

sample_3: $(TLELIB_OBJECTS) sample3/main.o
	$(CXX) $(LDFLAGS) sample3/main.o $(TLELIB_OBJECTS) -o sample_3

purge:
	rm -f *.o sample1/*.o sample2/*.o sample3/*.o

clean: purge
	rm -f $(TARGETS)
