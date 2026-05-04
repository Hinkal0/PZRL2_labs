#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <queue>

bool isNumber(const std::string& token) {
	if (token.length() == 0) return false;
	size_t i = 0;
	if (token[0] == '-') {
			if (token.length() == 1) return false;
			++i;
	}
	for (; i < token.length(); i++) {
		if (!std::isdigit(token[i])) return false;
	}

	return true;
}

bool isOperator(const std::string& token) {
	return (token == "+") || (token == "-") || (token == "*") || (token == "/") || (token == "%");
}

int priority(const std::string& op) {
	if (op == "+" || op == "-") return 0;
	return 1;
}

int main() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream iss(line);
	std::stack<std::string> ops;
	std::string token;
	while (iss >> token) {
		if (isNumber(token)) {
			std::cout << token << ' ';
			continue;
		}
		if (isOperator(token)) {
			while (ops.size() && isOperator(ops.top()) && (priority(ops.top()) >= priority(token))) {
					std::cout << ops.top() << ' ';
					ops.pop();
			}
			ops.push(token);
			continue;
		}
		if (token == "(") {
			ops.push(token);
			continue;
		}
		if (token == ")") {
			if (!ops.size()) {
					throw std::runtime_error("Пропущена скобка");
			}
			while (ops.top() != "(") {
				std::cout << ops.top() << ' ';
				ops.pop();
				if (ops.size() == 0) {
						throw std::runtime_error("Пропущена скобка");
				}
			}
			ops.pop();
			continue;
		}
		throw std::runtime_error("Неизвестный токен");
	}

	while (ops.size()) {
		if (ops.top() == "(") {
				throw std::runtime_error("Пропущена скобка");
		}
		std::cout << ops.top() << ' ';
		ops.pop();
	}

	std::cout << std::endl;
}
