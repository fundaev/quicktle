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

TEST_DIR       = ./test
TEST_SRCS      = $(TEST_DIR)/test_tlefunc.h $(TEST_DIR)/test_tlenode.h $(TEST_DIR)/test_tlestream.h $(TEST_DIR)/main.cpp
INCPATH        += -I$(TEST_DIR) -I$(GTEST_DIR)/src -I$(GTEST_DIR)/include -I./include/
CXXFLAGS       += -Wall $(INCPATH) 
LIBS           += -lpthread
TARGET         = tletest
GTEST_HEADERS  = $(GTEST_DIR)/*.h $(GTEST_DIR)/internal/*.h
GTEST_SRCS     = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
TLELIB_DIR     = ./include/tlelib
VPATH          = $(TLELIB_DIR) $(TEST_DIR)
TLELIB_HEADERS = $(TLELIB_DIR)/*.h
TLELIB_SRCS    = $(TLELIB_DIR)/*.cpp
OBJECTS        = $(GTEST_DIR)/src/gtest-all.o tlenode.o tlestream.o tlefunc.o main.o
PACK_FILES     = include/ test/ samples/ Makefile Doxyfile COPYING.LESSER COPYING README
PACK_NAME      = tlelib_1_0_0.zip

.PHONY: purge clean


build-test: $(TEST_SRCS) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(INCPATH) $(LIBS) $(OBJECTS) -o $(TARGET)

main.o: $(TEST_SRCS)
tlenode.o: $(TLELIB_DIR)/tlenode.cpp $(TLELIB_DIR)/tlenode.h $(TLELIB_DIR)/tleexception.h
tlestream.o: $(TLELIB_DIR)/tlestream.cpp $(TLELIB_DIR)/tlestream.h $(TLELIB_DIR)/tlenode.h
tlefunc.o: $(TLELIB_DIR)/tlefunc.cpp $(TLELIB_DIR)/tlefunc.h

pack: clean-all
	zip -r $(PACK_NAME) $(PACK_FILES)

purge:
	rm -f *.o

clean: purge
	rm -f $(TARGET)

clean-all: clean
	rm -f samples/*.o samples/sample_*
