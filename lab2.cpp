#include <iostream>
#include <stack>
#include <sstream>
#include <vector>

namespace SomeCalc {

	bool check_brackets(std::string& str) {
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
		return brackets.empty() ? true : false;
	}

	bool is_digit(char c) {
		return (c >= '0') && (c <= '9');
	}

	bool is_operator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '~';
	}

	int op_priority(char c) {
		switch (c)
		{
		case '+':
		case '-': return 1;

		case '*':
		case '/': return 2;

		case '~': return 3;


		default: return 0;
		}
	}

	void proccess_operation(std::stack<double>& st, char op) {
		if (st.empty()) throw std::exception("eval:proccess_operation: недостаточно операндов. ошибка при чтении данных");

		if (op == '~') {
			double right = st.top(); st.pop();
			st.push(-right);
			return;
		}
		double right = st.top(); st.pop();
		double left = st.top(); st.pop();
		switch (op) {
		case '+':
			st.push(left + right); break;
		case '-':
			st.push(left - right); break;
		case '*':
			st.push(left * right); break;
		case '/':
			if (right == 0) throw std::exception("eval:proccess_operation: деление на ноль");
			st.push(left / right);
			break;
		}
	}

	double eval(std::string& input) {

		bool NUM_READ = false;
		std::stack<double> nums;
		std::stack<char> ops;
		std::string operand;

		if (input.empty()) throw std::exception("eval: пустая строка");
		if (!check_brackets(input)) throw std::exception("eval: cкобки расставлены неверно");



		for (char& c : input) {
			if (!isdigit(c) && !is_operator(c) && (c != '(') && (c != ')') && (c != ' '))
				throw std::exception("eval: в строке лишние символы");

			if (is_digit(c)) {
				if (!NUM_READ) NUM_READ = true;
				operand.push_back(c);
				continue;
			}

			if (NUM_READ) {
				NUM_READ = false;
				nums.push(atoi(operand.c_str()));
				operand.clear();
			}

			if (c == '(') ops.push('(');
			else if (c == ')') {
				if (ops.top() == '(') throw std::exception("eval: Пустые скобки");

				while (ops.top() != '(')
				{
					proccess_operation(nums, ops.top());
					ops.pop();
				}
				ops.pop();
			}

			if (is_operator(c)) {
				while (!ops.empty() && (op_priority(ops.top()) >= op_priority(c))) {
					proccess_operation(nums, ops.top());
					ops.pop();
				}
				ops.push(c);
			}
		}
		if (NUM_READ) {
			NUM_READ = false;
			nums.push(atoi(operand.c_str()));
			operand.clear();
		}

		while (!ops.empty()) {
			proccess_operation(nums, ops.top());
			ops.pop();
		}
		return nums.top();
	}
}


int main() {
	setlocale(LC_ALL, "RUS");
	std::string ex;
	double res;
	while (true)
	{
		std::cout << "Введите выражение: ";
		std::getline(std::cin, ex);

		if (ex == "exit") return 0;
		try
		{
			res = SomeCalc::eval(ex);
		}
		catch (const std::exception& e)
		{
			std::cout << "error: " << e.what() << std::endl;
			continue;
		}

		printf("Результат: %f \n", res);
	}
}
