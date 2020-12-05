#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::vector<bool> seatsFound(8*128);

	std::string line;
	std::ifstream input("input.txt");
	int lines = 0;
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
		seatsFound[col + 8*row] = true;
		lines++;
	}
	//std::cout << "Counted " << lines << " other boarding passes" << std::endl;

	int highestID = 0;
	for(int i = 1; i < seatsFound.size() - 1; i++) {
		if (seatsFound[i]) {
			highestID = std::max(highestID, i);
		} else if (!seatsFound[i] && seatsFound[i-1] && seatsFound[i+1]) {
			std::cout << "Your seat is row " << i/8 << " col " << i%8 << " id " << i << std::endl;
		}
	}
	//std::cout << highestID << std::endl;
	return 0;
}
