CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -ID:/c_libs/SDL3/x86_64-w64-mingw32/include -Iinclude
LIBS = -LD:/c_libs/SDL3/x86_64-w64-mingw32/lib -lSDL3 -lm
TARGET = six-chess
TARGET_DIR = bin

SRCS = src/main.c src/board.c src/game.c src/ai.c src/file_io.c src/graphics.c
OBJS = $(SRCS:.c=.o)

$(TARGET_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(TARGET_DIR)
	$(CC) -o $@ $^ $(LIBS)
	copy "D:\c_libs\SDL3\x86_64-w64-mingw32\bin\SDL3.dll" $(TARGET_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) $(TARGET_DIR)\$(TARGET).exe $(TARGET_DIR)\SDL3.dll 2>nul

run: $(TARGET_DIR)/$(TARGET)
	.\$(TARGET_DIR)\$(TARGET)

.PHONY: clean run