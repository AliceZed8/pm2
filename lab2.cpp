#include <iostream>
#include <stack>
#include <sstream>

bool __isDigit(char c) {
	return (c >= '0') && (c <= '9');
}

bool __isOperator(char c) {
	return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

int __Priority(char c) {
	switch (c)
	{
	case '(':
	case ')':
		return 1;

	case '+':
	case '-':
		return 2;

	case '*':
	case '/':
		return 3;

	}
}

bool check_brackets(const std::string& str) {
	std::stack<char> brackets;
	for (char c : str) {
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

double cpp_eval(std::string& input) {
	std::stack<char> st;
	std::string output;
	std::string number;

	if (!check_brackets(input)) throw std::exception("Скобки расставлены неправильно");



	bool NUM_READ = false;
	for (char &c : input) {
		//Reading Number
		if (__isDigit(c)) {
			if (!NUM_READ) NUM_READ = true;
			number.push_back(c);
			continue;
		}

		//Other symbol or operator
		if ((c == ' ') || (c == '(') || (c == ')') || __isOperator(c)) {

			//Stop reading a number
			if (NUM_READ) {
				NUM_READ = false;
				number.push_back(' ');
				output += number;
				number.clear();
			}

			if (__isOperator(c)) {
				if (st.empty() || (__Priority(st.top()) < __Priority(c))) {
					st.push(c);
					continue;
				}

				while (!st.empty() && (__Priority(st.top()) >= __Priority(c))) {
					if (st.top() == '+') output += "+ ";
					if (st.top() == '-') output += "- ";
					if (st.top() == '*') output += "* ";
					if (st.top() == '/') output += "/ ";
					st.pop();
				}

				if (!st.empty() && (__Priority(st.top()) < __Priority(c))) {
					st.push(c);
					continue;
				}

			}

			if (c == '(') {
				st.push(c);
				continue;
			}

			if (c == ')') {
				while (st.top() != '(') {
					if (st.top() == '+') output += "+ ";
					if (st.top() == '-') output += "- ";
					if (st.top() == '*') output += "* ";
					if (st.top() == '/') output += "/ ";
					st.pop();
				}

				st.pop();
			}
		}
		if (c == '=') {
			if (NUM_READ) {
				NUM_READ = false;
				number.push_back(' ');
				output += number;
				number.clear();
			}
			break;
		}

	}
	while (!st.empty()) {
		if (st.top() == '+') output += "+ ";
		if (st.top() == '-') output += "- ";
		if (st.top() == '*') output += "* ";
		if (st.top() == '/') output += "/ ";
		st.pop();
	}

	std::cout << output << std::endl;
	std::stringstream stream(output);
	std::stack<double> nums;
	double num1, num2, result;

	std::string buf;
	try {
		while (!stream.eof()) {
			stream >> buf;

			if (__isDigit(buf[0])) {
				nums.push(atof(buf.c_str()));
				buf.clear();
				continue;
			}

			if (__isOperator(buf[0])) {
				if (nums.size() < 2) throw std::exception("Ошибка 1");

				num1 = nums.top();
				nums.pop();
				num2 = nums.top();
				nums.pop();

				if (buf[0] == '+') nums.push(num1 + num2);
				if (buf[0] == '-') nums.push(num2 - num1);
				if (buf[0] == '*') nums.push(num2 * num1);
				if (buf[0] == '/') {
					if (num1 == 0) throw std::exception("Деление на ноль!!!");
					nums.push(num2 / num1);
				}
				buf.clear();
			}
		}
	}
	catch (const std::exception& e) { throw; }

	if (nums.size() != 1) {
		throw std::exception("Ошибка 1");
	}

	return nums.top();

}


int main() {
	setlocale(LC_ALL, "RUS");
	
	std::string ex;
	double res;

	while (true)
	{
		std::cout << "Введите выражение: " ;
		std::getline(std::cin, ex);

		if (ex == "exit") return 0;

		try
		{
			res = cpp_eval(ex);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}

		printf("Результат: %f \n", res);
	}
}
