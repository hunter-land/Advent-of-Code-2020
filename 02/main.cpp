#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct entry {
	int min = 0;
	int max = 0;
	char c = 0;
	std::string password;
};

int main() {
	std::vector<entry> entries;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		int dash = line.find('-');
		int space = line.find(' ');
		int colon = line.find(':');

		entry e;

		e.min = std::stoi(line.substr(0, dash));
		e.max = std::stoi(line.substr(dash + 1, space-dash));
		e.c = line.substr(colon - 1, 1)[0];
		e.password = line.substr(colon + 2);

		entries.push_back(e);

		//std::cout << e.min << "-" << e.max << " " << e.c << ": " << e.password << std::endl;
	}

	int validCount = 0;
	for (entry &e : entries) {
		int count = 0;
		for (char c : e.password) {
			count += c == e.c;
		}
//		if (count >= e.min && count <= e.max) {
//			validCount++;
//		}
		validCount += (e.password[e.min - 1] == e.c) != (e.password[e.max - 1] == e.c);

	}
	std::cout << validCount << std::endl;
	return 0;
}
