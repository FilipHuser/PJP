#include <iostream>
#include <string>
#include <vector>
#include <limits>

#define MAX_EXPRESSION_SIZE 32

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

std::string trimWhiteSpaces(std::string s)
{
    std::string output;

    for (auto &c : s)
    {
        if (c != ' ')
        {
            output += c;
        }
    }

    return output;
}

int eval(std::string expression)
{
    int result = -1;
    // Add logic to evaluate the expression based on operators
    // For simplicity, this example assumes a single operator expression
    size_t operatorPos = expression.find_first_of("+-*/");
    if (operatorPos != std::string::npos)
    {
        int operand1 = std::stoi(expression.substr(0, operatorPos));
        int operand2 = std::stoi(expression.substr(operatorPos + 1));

        char op = expression[operatorPos];

        switch (op)
        {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            // Add check for division by zero if needed
            result = operand1 / operand2;
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    int N{0};

    std::cin >> N;

    if (N <= 0)
    {
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> expressions;
    std::string expression;

    for (int i{0}; i < N; i++)
    {
        std::getline(std::cin, expression);
        expressions.push_back(expression);
    }

    for(auto& exp : expressions)
    {
        std::cout << eval(trimWhiteSpaces(exp)) << std::endl;
    }

    return 0;
}
