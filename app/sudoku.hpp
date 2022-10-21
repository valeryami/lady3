#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <istream>

void player_turn(std::istream &input_text, int(*board)[9], int t);

void hunter(int (*board)[9]);

void board_print(int(*board)[9]);

void handler(int masking_cells, std::istream &inpute);

void gameover(int(*board)[9]);

void start(int swipe, int masking_cells, int board[9][9]);

void mask(int cells, int(*board)[9]);

void big_row_swipe(int b1, int b2, int(*board)[9]);

void small_row_swipe(int j1, int j2, int(*board)[9]);

void big_line_swipe(int b1, int b2, int(*board)[9]);

void small_line_swipe(int i1, int i2, int(*board)[9]);

bool block_error(int(*board)[9]);

bool line_error(int(*board)[9]);

bool row_error(int(*board)[9]);

void player_turn(int(*board)[9]);

bool make_move(int i, int j, int k, int(*board)[9]);

#endif
