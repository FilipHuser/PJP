#include <iostream>
#include <stack>
#include <cctype>

int findPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // Assuming 0 precedence for other characters
}

bool isOpeningBracket(char ch) {
    return ch == '(';
}

bool isClosingBracket(char ch) {
    return ch == ')';
}

int charToDigit(char ch) {
    return ch - '0';
}

int applyOperator(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default:  // Handle invalid operator
            std::cerr << "Invalid operator: " << op << std::endl;
            return 0;  // Return a default value
    }
}

int main() {
    std::string trimmedExpression = "15-2";

    std::stack<char> operators;
    std::stack<int> values;

    for (int i = 0; i < trimmedExpression.length(); i++) {
        if (isOpeningBracket(trimmedExpression[i])) {
            operators.push(trimmedExpression[i]);
        } else if (isdigit(trimmedExpression[i])) {
            int x = 0;
            while (i < trimmedExpression.length() && isdigit(trimmedExpression[i])) {
                x = (x * 10) + charToDigit(trimmedExpression[i]);
                i++;
            }
            values.push(x);
            i--;
        } else if (isClosingBracket(trimmedExpression[i])) {
            while (!operators.empty() && operators.top() != '(') {
                int x = values.top();
                values.pop();
                int y = values.top();
                values.pop();
                char oprt = operators.top();
                operators.pop();
                values.push(applyOperator(y, x, oprt));
            }
            if (!operators.empty()) {
                operators.pop();  // Remove '('
            }
        } else {
            while (!operators.empty() && operators.top() != '(' && findPrecedence(operators.top()) >= findPrecedence(trimmedExpression[i])) {
                int x = values.top();
                values.pop();
                int y = values.top();
                values.pop();
                char oprt = operators.top();
                operators.pop();
                values.push(applyOperator(y, x, oprt));
            }
            operators.push(trimmedExpression[i]);
        }
    }

    while (!operators.empty()) {
        int x = values.top();
        values.pop();
        int y = values.top();
        values.pop();
        char oprt = operators.top();
        operators.pop();
        values.push(applyOperator(y, x, oprt));
    }

    std::cout << "Result: " << values.top() << std::endl;

    return 0;
}
