#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::vector<std::vector<bool>> seatsFound(1 << 3);
	for (std::vector<bool> &row : seatsFound) {
		row.resize(1 << 7);
	}

	std::string line;
	std::ifstream input("input.txt");
	while (std::getline(input, line)) {
		int row = 0;
		for (int i = 0; i < 7; i++) {
			//if F keep 0
			row = row << 1;
			row |= (line[i] == 'B');
		}
		int col = 0;
		for (int i = 7; i < 7+3; i++) {
			//if L keep 0
			col = col << 1;
			col |= (line[i] == 'R');
		}
		//std::cout << row << ", " << col << std::endl;
		seatsFound[col][row] = true;
	}

	for (int col = 0; col < seatsFound.size(); col++) {
		for (int row = 0; row < seatsFound[col].size(); row++) {
			if (seatsFound[col][row] == false) {
				std::cout << "row " << row << ", column " << col << " is unclaimed and may be your seat." << std::endl;
			} else {
				//std::cout << row * 8 + col << std::endl;
			}
		}
	}
	return 0;
}
