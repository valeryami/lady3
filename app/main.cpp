#include "myfunc.hpp"
#include <iostream>
using namespace std;

int main()
{
    int select[] = {10};
    
    int size = sizeof(select)/4;
    
    tictactoe(select, size);
}
