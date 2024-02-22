#include <iostream>

int main(int argc , char* argv[])
{
    char* buffer = new char;

    buffer[0] = 'a';
    buffer[1] = 'h';
    buffer[2] = 'o';
    buffer[3] = 'j';


    for (int i{0}; i < 4; i++)
    {
        printf("%c" , buffer[i]);
    }

    return 0;
}