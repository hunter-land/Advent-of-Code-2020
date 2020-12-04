#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int main() {
	std::vector<int> values;
	std::ifstream instream("input.txt");

	//Import all integers to vector
	std::string line;
	while (std::getline(instream, line)) {
		values.push_back(std::stoi(line));
	}

	//Find which two add to 2020
	int a = 0, b = 0;
	for (int i = 0; i < values.size() - 1 && a == b; i++) {
		for (int j = i + 1; j < values.size() && a == b; j++) {
			if (values[i] + values[j] == 2020) {
				a = values[i];
				b = values[j];
			}
		}
	}

	//Output answer
	std::cout << a * b << std::endl;
	return 0;
}
