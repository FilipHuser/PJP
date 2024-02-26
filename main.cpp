#include <iostream>
#include <string>
#include <vector>
#include <stack>

int applyOperator(int x , int y , char oprt)
{
    int result{0};

    switch (oprt)
    {
        case '*':
            return x*y;
        break;

        case '/':
            return x/y;
        break;

        case '+':
            return x+y;
        break;

        case '-':
            return x-y;
        break;
    }

    return -1; //error
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isOpeningBracket(char c)
{
    return (c == '(');
}

bool isClosingBracket(char c)
{
    return (c == ')');
}

int charToDigit(char c)
{
    return c - '0';
}

int findPrecedence(char oprt)
{
    if (oprt == '+' || oprt == '-') { return 1; }
    if (oprt == '*' || oprt == '/') { return 2; }

    return 0;
}

std::string trimWhiteSpaces(std::string s)
{
    std::string output;

    for (auto &c : s)
    {
        if (c != ' ' && c != '\t')
        {
            output += c;
        }
    }

    return output;
}


int eval(const std::string &expression)
{
    std::string trimmedExpression = trimWhiteSpaces(expression);

    std::stack<int> values;
    std::stack<char> operators;


    for(int i{0}; i < trimmedExpression.length(); i++)
    {
        if (isOpeningBracket(trimmedExpression[i]))
        {
            operators.push(trimmedExpression[i]);

        } else if(isdigit(trimmedExpression[i]))
        {
            values.push(charToDigit(trimmedExpression[i]));

        } else if (isClosingBracket(trimmedExpression[i])) // prvni ')' -> zacnu zpracovavat prvni '()'
        {
            while(!operators.empty() && operators.top() != '(')
            {
                int x = values.top();

                values.pop();

                int y = values.top();

                values.pop();

                char oprt = operators.top();

                operators.pop();

                values.push(applyOperator(x , y , oprt));
            }

            if (!operators.empty()) { operators.pop(); } // zbavuju se '('

        } else { //je operator

            while(!operators.empty() && findPrecedence(operators.top() >= findPrecedence(trimmedExpression[i])))
            {
                int x = values.top();

                values.pop();

                int y = values.top();

                values.pop();

                char oprt = operators.top();
                operators.pop();

                values.push(applyOperator(y , x , oprt));
            }

            operators.push(trimmedExpression[i]);

        }
    }

    while(!operators.empty())
    {
        int x = values.top();

        values.pop();

        int y = values.top();

        values.pop();

        char oprt = operators.top();

        operators.pop();

        values.push(applyOperator(x , y , oprt));
    }


  

    return values.top();
}

int main()
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

    for (auto &exp : expressions)
    {
        //eval(exp);
        std::cout << eval(exp) << std::endl;
    }

    return 0;
}
