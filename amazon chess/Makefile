CXX = D:/msys2/mingw64/bin/g++.exe

CXXFLAGS = -std=c++11 -O2 -Wall -Wextra

LDFLAGS = -static -static-libgcc -static-libstdc++ -lgdi32 -lole32 -luuid -leasyxw -lstdc++ -mwindows

TARGET = amazon_chess.exe

SRC = amazons.cpp

LIB_DIR = ./lib

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -L$(LIB_DIR) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
