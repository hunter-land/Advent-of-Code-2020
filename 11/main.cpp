#include <iostream>
#include <fstream>
#include <vector>
#include <string>



int main() {
	std::vector<std::vector<char>> seats;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		seats.resize(seats.size() + 1);
		for (char c : line) {
			seats[seats.size() - 1].push_back(c);
		}
	}

	//std::cout << seats[0].size() << "x" << seats.size() << std::endl;

	int seatDifferences = 0;
	do {
		std::vector<std::vector<char>> seatsprev = seats;
		seatDifferences = 0;
		for (int y = 0; y < seatsprev.size(); y++) {
			for (int x = 0; x < seatsprev[y].size(); x++) {
				int adjacent = 0;
				//Count all adjacent, including diags
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						int ay = y + j;
						int ax = x + i;

						for (int k = 1; true; k++) {
							ay = y + j * k;
							ax = x + i * k;
							//std::cout << "Checking " << ax << "," << ay << " from " << x << "," << y <<std::endl;
							if (ay >= 0 && ay < seatsprev.size() &&
							    ax >= 0 && ax < seatsprev[ay].size()) {
								if (seatsprev[ay][ax] == '#' && !(ay == y && ax == x)) {
									adjacent++;
									//std::cout << "Adjacent " << ax << ", " << ay << " occupied (" << adjacent << ")" << std::endl;
									break;
								} else if (seatsprev[ay][ax] == 'L' && !(ay == y && ax == x)) {
									//std::cout << "Adjacent " << ax << ", " << ay << " empty (" << seatsprev[ay][ax] << ")" << std::endl;
									break; //Empty in this direction
								} else if (ay == y && ax == x) {
									break;
								}
							} else {
								break;
							}
						}
					}
				}
				//std::cin >> line;
				//std::cout << adjacent << std::endl;
				switch (seatsprev[y][x]) {
					case '#':
					if (adjacent >= 5) {
						seats[y][x] = 'L';
						seatDifferences++;
					}
					break;
					case 'L':
					if (adjacent == 0) {
						seats[y][x] = '#';
						seatDifferences++;
					}
					break;
				}
			}
		}
		std::cout << seatDifferences << " changed" <<std::endl;

		//Print out current seating arrangement
		//std::cout << seats.size() << "x" << seats[0].size() << std::endl;
/*		for (int i = 0; i < seats.size(); i++) {
			for (int j = 0; j < seats[i].size(); j++) {
//				std::cout << i << ", " << j << std::endl;
				std::cout << seats[i][j];
			}
			std::cout << std::endl;
		}
		std::cin >> line;*/

	} while (seatDifferences > 0);

	int occupied = 0;
	for (std::vector<char>& row : seats) {
		for (char c : row) {
			occupied += c == '#';
		}
	}

	std::cout << occupied << std::endl;

	return 0;
}
