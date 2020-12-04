#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
	std::vector<std::vector<char>> map;

	std::ifstream input("map.txt");
	std::string line;
	while (std::getline(input, line)) {
		map.push_back(std::vector<char>(line.begin(), line.end()));
	}

	//int row = 0, col = 0;
	int dx = 3, dy = 1;
	int trees = 0;
	for (int row = dy, col = dx; row < map.size(); row += dy, col += dx) {
		if (map[row % map.size()][col % map[0].size()] == '#') {
			trees++;
		}
	}

	std::cout << trees << std::endl;
	return 0;
}
