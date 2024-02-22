#include <iostream>

#define BUFF_SIZE 255



int main(int argc , char* argv[])
{
    char buff[BUFF_SIZE];

    while(1)
    {
        std::cin >> buff;




        if(!std::strcmp(buff , "quit")) { break; }


        std::cout << buff << std::endl;
    }



    return 0;
}