#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits.h>

struct num {
	long v = 0;
	bool valid = false;
};

int main() {
	std::vector<num> numbers;
	
	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		num n;
//		std::cout << line << std::endl;
		n.v = std::stol(line);
		numbers.push_back(n);
	}

	for (int i = 25; i < numbers.size(); i++) {
		for (int j = i-25; j < i; j++) {
			for (int k = i-24; k < i; k++) {
				if (numbers[j].v + numbers[k].v == numbers[i].v) {
					numbers[i].valid = true;
				}
			}
		}
	}

	long weak = 0;
	for (int i = 25; i < numbers.size(); i++) {
		if (numbers[i].valid == false) {
			std::cout << numbers[i].v << std::endl;
			weak = numbers[i].v;
			break;
		}
	}

	for (int i = 0; i < numbers.size(); i++) {
		long running = 0;
		long smallest = LONG_MAX;
		long largest = LONG_MIN;
		for (int j = i; j < numbers.size() && running < weak; j++) {
			long n = numbers[j].v;
			running += n;
			smallest = std::min(smallest, n);
			largest = std::max(largest, n);
		}
		if (running == weak) { //Got it
			std::cout << smallest << ", " << largest << std::endl;
			std::cout << smallest + largest << std::endl;
			break;
		}
	}

	return 0;
}
