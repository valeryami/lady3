#include <iostream>
#include <stdlib.h>
#include <string>
typedef char* str;
using namespace std;
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
int choice;
int row,column;
char turn = 'X';
bool draw = false;

void player_turn(int select){

    switch(select){
        case 1: row=0; column=0; break;
        case 2: row=0; column=1; break;
        case 3: row=0; column=2; break;
        case 4: row=1; column=0; break;
        case 5: row=1; column=1; break;
        case 6: row=1; column=2; break;
        case 7: row=2; column=0; break;
        case 8: row=2; column=1; break;
        case 9: row=2; column=2; break;
        default:
            cout<<"Невозможный ход";
    }

    if(turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'X';
        turn = 'O';
    }else if(turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O'){
        board[row][column] = 'O';
        turn = 'X';
    }
    else {
        return;
    }
}

bool gameover(){

    for(int i=0; i<3; i++)
    if((((board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) || ((board[0][i] == board[1][i]) && (board[0][i] == board[2][i]))) && (board[i][0] == 'X' || board[i][0] == 'O' || board[0][i] == 'X' || board[0][i] == 'O')) {
        return false;
    }

    if((((board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) || ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]))) && (board[0][0] == 'X' || board[0][0] == 'O' || board[0][2] == 'X' || board[0][2] == 'O')) {
        return false;
    }

    for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    if(board[i][j] != 'X' && board[i][j] != 'O')
    return true;

    draw = true;
    return false;
}

void tictactoe(int select[], int size)
{
    turn = 'X';
    draw = false;
    int i=0;
    while(gameover() && i<size) {
        player_turn(select[i]);
        i++;
    }
    if(turn == 'O' && draw == false && gameover() == false){
        cout << "Игрок Х выиграл игру!!!";
    }
    else if(turn == 'X' && draw == false && gameover() == false){
        cout << "Игрок О выиграл игру!!!";
    }
    else if (draw)
        cout << "Ничья!!!";
    else if (size >1)
        cout << "Невозможно выявить победителя";
    for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
    board[i][j] = i*3+j;
}
