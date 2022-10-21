#ifndef TEST_TICTACTOE_H
#define TEST_TICTACTOE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "sudoku.hpp"
#include <string>

using namespace std;

extern "C" {
#include "sudoku.hpp"
}

TEST(player_win, test1)
{
    std::string output_text = "Вы не допустили ни одной ошибки, игра выиграна\n";

    testing::internal::CaptureStdout();

    int masking_cells = 0;
    int board[9][9];
    
    start(0, masking_cells, board);
    gameover(board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(generator, different)
{
    int board1[9][9];
    int board2[9][9];
    start(10, 0, board1);
    start(10, 0, board2);

    EXPECT_NE(board1, board2);
}

TEST(error, row)
{
    int board[9][9];
    start(0, 0, board);
    board[0][1] = 1;

    EXPECT_EQ(row_error(board), true);
}

TEST(error, line)
{
    int board[9][9];
    start(0, 0, board);
    board[1][0] = 1;

    EXPECT_EQ(line_error(board), true);
}

TEST(error, block)
{
    int board[9][9];
    start(0, 0, board);
    board[1][1] = 1;

    EXPECT_EQ(block_error(board), true);
}

TEST(handler, zero)
{
    std::string output_text = "Вы не допустили ни одной ошибки, игра выиграна\n";

    testing::internal::CaptureStdout();

    int masking_cells = 0;
    
    handler(masking_cells, cin);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());

}

TEST(swiple, littleRow)
{
    int board1[9][9];
    int board2[9][9];
    start(0, 0, board1);
    start(0, 0, board2);
    small_row_swipe(1, 0, board1);
    bool eq = true;
    
    for(int i = 0; i < 9; i++)
        if (board1[i][1] != board2[i][0] || board1[i][0] != board2[i][1])
            eq = false;
    
    EXPECT_EQ(eq, true);
}

TEST(swiple, littleLine)
{
    int board1[9][9];
    int board2[9][9];
    start(0, 0, board1);
    start(0, 0, board2);
    small_line_swipe(1, 0, board1);
    bool eq = true;
    
    for(int j = 0; j < 9; j++)
        if (board1[1][j] != board2[0][j] || board1[0][j] != board2[1][j])
            eq = false;
    
    EXPECT_EQ(eq, true);
}

TEST(swipe, bigRow)
{
    int board1[9][9];
    int board2[9][9];
    start(0, 0, board1);
    start(0, 0, board2);
    big_row_swipe(1, 0, board1);
    bool eq = true;
    
    for (int b = 0; b < 3; b++)
        for(int i = 0; i < 9; i++)
            if (board1[i][b+3] != board2[i][b] || board1[i][b] != board2[i][b+3])
                eq = false;
    
    EXPECT_EQ(eq, true);
}

TEST(swipe, bigLine)
{
    int board1[9][9];
    int board2[9][9];
    start(0, 0, board1);
    start(0, 0, board2);
    big_line_swipe(1, 0, board1);
    bool eq = true;
    
    for (int b = 0; b < 3; b++)
        for(int j = 0; j < 9; j++)
            if (board1[b+3][j] != board2[b][j] || board1[b][j] != board2[b+3][j])
                eq = false;
    
    EXPECT_EQ(eq, true);
}

TEST(move, falsecoordinate)
{
    std::string output_text = "Введённые данные некоректны, значение столбца и строки должно быть от 1 до 9\n";

    testing::internal::CaptureStdout();
    
    int board[9][9];
    start(0, 0, board);
    
    make_move(0, 0, 1, board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(move, notemptyplace)
{
    std::string output_text = "В этой ячейке уже есть значение, выберите ячейку со значением ноль\n";

    testing::internal::CaptureStdout();
    
    int board[9][9];
    start(0, 0, board);
    
    make_move(1, 1, 1, board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(move, wrongvalue)
{
    std::string output_text = "Значение может быть только от 1 до 9\n";

    testing::internal::CaptureStdout();
    
    int board[9][9];
    start(0, 0, board);
    board[0][0] = 0;
    make_move(1, 1, 0, board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(move, ok)
{
    int board[9][9];
    start(0, 0, board);
    board[0][0] = 0;
    make_move(1, 1, 1, board);
    

    EXPECT_EQ(board[0][0], 1);
}

TEST(print, zero)
{
    std::string output_text = 
"000 000 000 \n000 000 000 \n000 000 000 \n\n000 000 000 \n000 000 000 \n000 000 000 \n\n000 000 000 \n000 000 000 \n000 000 000 \n\n";

    testing::internal::CaptureStdout();
    
    int board[9][9];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = 0;
        }
    
    board_print(board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(masking, hungred)
{
    std::string output_text = "Невозможно замаскировать столько клеток, максимум 81\n";
    
    testing::internal::CaptureStdout();
        
    int board[9][9];
    start(0, 100, board);
    
    std::string text = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(text.c_str(), output_text.c_str());
}

TEST(masking, positive)
{
    int board[9][9];
    start(0, 0, board);
    mask(10, board);
    int k = 0;
    
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if(board[i][j] == 0)
                k++;
    

    EXPECT_EQ(k, 10);
}

TEST(input, positive)
{
    int board[9][9];
    start(0, 0, board);
    board[0][0] = 0;
    std::string test_input = "1\n1\n1\n";
    stringstream fake_input(test_input);
    player_turn(fake_input, board, 1);

    EXPECT_EQ(board[0][0], 1);
}

TEST(hunting, positive)
{
    int board[9][9];
    start(0,0,board);
    board[0][0] = 0;
    board[0][1] = 0;
    
    hunter(board);
    
    EXPECT_EQ(board[0][2], 0);
}
#endif
