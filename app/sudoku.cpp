#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;


void board_print(int(*board)[9])
{
    for (int ki = 0; ki <= 6; ki += 3)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int kj = 0; kj <= 6; kj += 3)
            {
                for (int j = 0; j < 3; j++)
                    std::cout << board[ki + i][j + kj];
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool make_move(int i, int j, int k, int(*board)[9])
{
    if (i < 1 || i > 9 || j < 1 || j > 9)
    {
        cout << "Введённые данные некоректны, значение столбца и строки должно быть от 1 до 9" << endl;
        return false;
    }
    if (board[i - 1][j - 1] != 0)
    {
        cout << "В этой ячейке уже есть значение, выберите ячейку со значением ноль" << endl;
        return false;
    }
    if (k < 1 || k > 9)
    {
        cout << "Значение может быть только от 1 до 9" << endl;
        return false;
    }

    board[i - 1][j - 1] = k;
    board_print(board);

    return true;
}

void player_turn(istream &input_text, int(*board)[9], int t)
{
    
    int i;
    int j;
    int k;

    for (; t > 0; t--)
        do
        {
            cout << "Введите номер столбца, в котором хотите ввести значение" << endl;
            input_text >> j;
            cout << "Введите номер  строки, в котором хотите ввести значение" << endl;
            input_text >> i;
            cout << "Введите значение от 1 до 9" << endl;
            input_text >> k;
        } while (!make_move(i, j, k, board));
}

bool row_error(int(*board)[9]) {
    for (int j = 0; j < 9; j++)
    {
        int use[9] = { 1,2,3,4,5,6,7,8,9 };
        for (int i = 0; i < 9; i++)
        {
            if (use[board[i][j] - 1] == 0)
                return true;
            use[board[i][j] - 1] = 0;
        }
    }
    return false;
}

bool line_error(int(*board)[9]) {
    for (int i = 0; i < 9; i++)
    {
        int use[9] = { 1,2,3,4,5,6,7,8,9 };
        for (int j = 0; j < 9; j++)
        {
            if (use[board[i][j] - 1] == 0)
                return true;
            use[board[i][j] - 1] = 0;
        }
    }
    return false;
}

bool block_error(int(*board)[9]) {
    for (int ki = 0; ki <= 6; ki += 3)
    {
        for (int kj = 0; kj <= 6; kj += 3)
        {
            int use[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (use[board[ki + i][kj + j] - 1] == 0)
                        return true;
                    use[board[ki + i][kj + j] - 1] = 0;
                }
            }
        }
    }
    return false;
}

void gameover(int(*board)[9])
{
    if (row_error(board) || line_error(board) || block_error(board))
        cout << "Вы допустили ошибку, игра проиграна" << endl;
    else
        cout << "Вы не допустили ни одной ошибки, игра выиграна" << endl;
}

void small_line_swipe(int i1, int i2, int(*board)[9])
{
    int tmp = 0;
    for (int j = 0; j < 9; j++)
    {
        tmp = board[i1][j];
        board[i1][j] = board[i2][j];
        board[i2][j] = tmp;
    }
}

void big_line_swipe(int b1, int b2, int(*board)[9])
{
    for (int i = 0; i < 3; i++)
        small_line_swipe(i + b1 * 3, i + b2 * 3, board);
}


void small_row_swipe(int j1, int j2, int(*board)[9])
{
    int tmp = 0;
    for (int i = 0; i < 9; i++)
    {
        tmp = board[i][j1];
        board[i][j1] = board[i][j2];
        board[i][j2] = tmp;
    }
}

void big_row_swipe(int b1, int b2, int(*board)[9])
{
    for (int j = 0; j < 3; j++)
        small_row_swipe(j + b1 * 3, j + b2 * 3, board);
}

void hunter(int (*board)[9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] != 0)
            {
                board[i][j] = 0;
                return;
            }
}

void mask(int cells, int(*board)[9])
{
    for (int k = 0; k < cells; k++)
    {
        int i = rand() % 9;
        int j = rand() % 9;
        if (board[i][j] == 0)
            hunter(board);
        else
            board[i][j] = 0;
    }
}

void start(int swipe, int masking_cells, int board[9][9])
{
    if (masking_cells > 81)
    {
        cout << "Невозможно замаскировать столько клеток, максимум 81" << endl;
        return;
    }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
        }
    for (int k = 0; k < swipe; k++)
    {
        int i1 = rand() % 3;
        int i2 = rand() % 3;
        int j1 = rand() % 3;
        int j2 = rand() % 3;
        int b;
        int block1 = 0;
        int block2 = 0;

        b = (rand() % 3) * 3;
        while (i1 == i2)
            i2 = rand() % 3;
        small_line_swipe(i1 + b, i2 + b, board);

        b = (rand() % 3) * 3;
        while (j1 == j2)
            j2 = rand() % 3;
        small_row_swipe(j1 + b, j2 + b, board);

        block1 = (rand() % 3);
        block2 = (rand() % 3);
        while (block1 == block2)
            block2 = rand() % 3;
        big_line_swipe(block1, block2, board);

        block1 = (rand() % 3);
        block2 = (rand() % 3);
        while (block1 == block2)
            block2 = rand() % 3;
        big_row_swipe(block1, block2, board);
    }
    mask(masking_cells, board);
}

void handler(int masking_cells, istream &inpute)
{
    int board[9][9];
    start(10, masking_cells, board);

    player_turn(inpute, board, masking_cells);
    
    gameover(board);
}
