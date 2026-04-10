#ifndef FILE_IO_H
#define FILE_IO_H

#include "game.h"

// 函数声明
int save_game(const GameRecord *record, const char *filename);
int load_games(GameRecord *records, int max_records, const char *filename);
void replay_game(const GameRecord *record);
void display_saved_games(const char *filename);

#endif