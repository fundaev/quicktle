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

TESTDIR        = ./test
TEST_SRCS      = $(TESTDIR)/test_tlefunc.h $(TESTDIR)/test_tlenode.h $(TESTDIR)/test_tlestream.h $(TESTDIR)/main.cpp
INCPATH        +=  -I$(TESTDIR) -I$(GTEST_DIR)/src -I$(GTEST_DIR)/include -I./include/
CXXFLAGS       +=  -Wall $(INCPATH) 
LIBS           += -lpthread
TARGET         = tletest
GTEST_HEADERS  = $(GTEST_DIR)/*.h $(GTEST_DIR)/internal/*.h
GTEST_SRCS     = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
TLELIB_DIR     = ./include/tlelib
TLELIB_HEADERS = $(TLELIB_DIR)/*.h
TLELIB_SRCS    = $(TLELIB_DIR)/*.cpp
OBJECTS        = $(GTEST_DIR)/src/gtest-all.o tlenode.o tlestream.o tlefunc.o main.o

.PHONY: purge clean


build-test: $(OBJECTS) $(TEST_SRCS)
	$(CXX) $(LDFLAGS) $(INCPATH) $(LIBS) $(OBJECTS) -o $(TARGET)

main.o: $(TESTDIR)/main.cpp $(TESTDIR)/test_tlenode.h $(TESTDIR)/test_tlefunc.h
	$(CXX) -c $(CXXFLAGS) $(TESTDIR)/main.cpp

tlenode.o: $(TLELIB_DIR)/tlenode.cpp $(TLELIB_DIR)/tlenode.h $(TLELIB_DIR)/tleexception.h
	$(CXX) -c $(CXXFLAGS) $(TLELIB_DIR)/tlenode.cpp

tlestream.o: $(TLELIB_DIR)/tlestream.cpp $(TLELIB_DIR)/tlestream.h $(TLELIB_DIR)/tlenode.h
	$(CXX) -c $(CXXFLAGS) $(TLELIB_DIR)/tlestream.cpp

tlefunc.o: $(TLELIB_DIR)/tlefunc.cpp $(TLELIB_DIR)/tlefunc.h
	$(CXX) -c $(CXXFLAGS) $(TLELIB_DIR)/tlefunc.cpp

purge:
	rm -f *.o

clean: purge
	rm -f $(TARGET)
