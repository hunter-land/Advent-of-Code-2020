#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct inst {
	std::string command = "nop";
	int value = 0;
	bool visited = false;
};

bool reachesEnd(size_t i, std::vector<inst> insts);

int main() {
	//int acc = 0;
	std::vector<inst> instructions;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		inst in;
		in.command = line.substr(0, line.find(' '));
		in.value = std::stoi(line.substr(line.find(' ') + 1));
		instructions.push_back(in);
	}

	int acc = 0;
	size_t i = 0;
	bool changedInst = false;
	while (instructions[i].visited == false && i < instructions.size()) {
		instructions[i].visited = true;
		if (instructions[i].command == "acc") {
			acc += instructions[i].value;
		} else if (instructions[i].command == "jmp") {
			if (!changedInst && reachesEnd(i + 1, instructions)) {
				std::cout << i << " swapped (jmp -> nop)" << std::endl;
				changedInst = true;
			} else {
				i += instructions[i].value;
				i--;
			}
		} else if (instructions[i].command == "nop") {
			if (!changedInst && reachesEnd(i + instructions[i].value - 1, instructions)) {
				std::cout << i << " swapped (nop -> jmp " << instructions[i].value << ")" << std::endl;
				changedInst = true;
				i += instructions[i].value;
				i--;
			} else {}
		}
		i++;
	}

	if (i == instructions.size()) {
		std::cout << "Passed sanity" << std::endl;
	}
	std::cout << acc << std::endl;
	return 0;
}

bool reachesEnd(size_t i, std::vector<inst> insts) {
	while (insts[i].visited == false && i < insts.size()) {
		insts[i].visited = true;
		if (insts[i].command == "jmp") {
			i += insts[i].value;
			i--;
		}
		i++;
	}
	return i == insts.size();
}
