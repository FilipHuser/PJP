#include <iostream>

#define MAX_EXPRESSION_SIZE 128 

bool isOperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c =='/') { return true; }

    return false;
}

int main(int argc , char* argv[])
{
    int N{0};

    std::cin >> N;

    if (N <= 0) { return 1; }

    char expression[N][MAX_EXPRESSION_SIZE];

    for(int i{0}; i < N; i++)
    {
        std::cin >> expression[i];
    }


    for(int i{0}; i < N; i++)
    {
        std::cout << expression[i] << std::endl;
    }


    return 0;
}