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
	int a = 0, b = 0, c = 0;
	for (int i = 0; i < values.size() - 1 && a == b; i++) {
		for (int j = i + 1; j < values.size() && a == b; j++) {
			for (int k = j + 1; k < values.size() && a == b; k++) {
				if (values[i] + values[j] + values[k] == 2020) {
					a = values[i];
					b = values[j];
					c = values[k];
				}
			}
		}
	}

	//Output answer
	std::cout << a * b * c << std::endl;
	return 0;
}
