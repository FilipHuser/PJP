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

bool isValid(std::string expression)
{
    for (int i{0}; i < expression.length(); i++)
    {
        if (i == 0 && isOperator(expression[i])) { return false; }

        if(i < expression.length() - 1)
        {
            if (isOperator(expression[i]) && isOperator(expression[i + 1]))
            {
                return false;
            }
        }

    }

    return true;
}

std::string eval(std::string expression)
{
    std::string trimmedExpression = trimWhiteSpaces(expression);

    std::stack<int> values;
    std::stack<char> operators;

    if (!isValid(expression)) { return "ERROR"; }


    for(int i{0}; i < trimmedExpression.length(); i++)
    {
        if (isOpeningBracket(trimmedExpression[i])) // '('
        {
            operators.push(trimmedExpression[i]);

        } else if(isdigit(trimmedExpression[i])) // cislo
        {
            int x{0};
             
            // There may be more than one
            // digits in number.
            while(i < trimmedExpression.length() && isdigit(trimmedExpression[i]))
            {
                x = (x*10) + charToDigit(trimmedExpression[i]);
                i++;
            }
            values.push(x);
            i--;

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

                values.push(applyOperator(y , x , oprt));
            }

            if (!operators.empty()) { operators.pop(); } // zbavuju se '('

        } else { //je operator

            while(!operators.empty() && operators.top() != '(' && findPrecedence(operators.top()) >= findPrecedence(trimmedExpression[i])) //dokud prvni operator ma stejnou nebo vetsi prednost 
            {
                int x = values.top();

                values.pop();

                int y = values.top();

                values.pop();

                char oprt = operators.top();
                operators.pop();

                values.push(applyOperator(y , x , oprt));
            }

            // + - * /
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

        values.push(applyOperator(y , x , oprt));
    }


    return std::to_string(values.top());
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
        std::cout << eval(exp) << std::endl;
    }

    return 0;
}
