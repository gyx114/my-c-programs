# 六子棋游戏 Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/six_chess.exe

SOURCES = main.c game.c board.c ai.c file_io.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

all: dirs $(TARGET)

dirs:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(BINDIR) mkdir $(BINDIR)
	@if not exist data mkdir data

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run