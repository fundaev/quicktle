CXXFLAGS       += -Wall -I../include
TARGETS        = sample_1
TLELIB_DIR     = ../include/tlelib
VPATH          = $(TLELIB_DIR)
TLELIB_OBJECTS = tlenode.o tlestream.o tlefunc.o

.PHONY: purge clean sample1

all: $(TARGETS)

sample1/main.o: sample1/main.cpp
tlenode.o: $(TLELIB_DIR)/tlenode.cpp $(TLELIB_DIR)/tlenode.h $(TLELIB_DIR)/tleexception.h
tlestream.o: $(TLELIB_DIR)/tlestream.cpp $(TLELIB_DIR)/tlestream.h $(TLELIB_DIR)/tlenode.h
tlefunc.o: $(TLELIB_DIR)/tlefunc.cpp $(TLELIB_DIR)/tlefunc.h

sample_1: $(TLELIB_OBJECTS) sample1/main.o
	$(CXX) $(LDFLAGS) sample1/main.o $(TLELIB_OBJECTS) -o sample_1

purge:
	rm -f *.o

clean: purge
	rm -f $(TARGETS)
