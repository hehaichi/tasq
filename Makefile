CXX=g++
CXXFLAGS=-std=c++11 -I. -L /usr/lib/x86-64-linux-gnu/boost/
BIN_DIR=bin
OBJ_DIR=build

LIBS=-lboost_system -lboost_filesystem -lboost_thread

SRC_DIR=src
_DEPS = daemon.h
DEPS = $(patsubst %,$(SRC_DIR)/%,$(_DEPS))

_OBJ = daemon.o 
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))




$(BIN_DIR)/daemon: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o