#include <iostream>
#include <string>
#include <stack>

bool check_brackets(const std::string& str) {
    std::stack<char> brackets;
    for (char c: str) {
        if (c == '(' || c == '[' || c == '{') {
            brackets.push(c);
            continue;
        }

        if (c == ')' || c == ']' || c == '}') {

            if (brackets.empty()) return false;
            if (c == ']' && brackets.top() != '[') return false;
            if (c == ')' && brackets.top() != '(') return false;
            if (c == '}' && brackets.top() != '{') return false;
            brackets.pop();
        }

    }
    if (brackets.empty()) return true;
    else return false;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    std::string str;
    std::cout << "Введите строку: ";
    std::cin >> str;

    if (check_brackets(str)) {
        std::cout << "Строка существует\n";
    } else {
        std::cout << "Строка не существует\n";
    }
    
    return 0;
}
