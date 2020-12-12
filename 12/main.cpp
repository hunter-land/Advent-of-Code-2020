#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

int main () {
	int dir = 0;
	float x = 0, y = 0;
	float wx = 10, wy = 1;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		char c = line[0];
		int n = std::stoi(line.substr(1));
		switch (c) {
			case 'S':
				n *= -1;
			case 'N':
				//y += n;
				wy += n;
			break;
			case 'W':
				n *= -1;
			case 'E':
				//x += n;
				wx += n;
			break;
			case 'F':
				//x += std::cos(dir * M_PI / 180.) * n;
				//y += std::sin(dir * M_PI / 180.) * n;

				x += wx * n;
				y += wy * n;
			break;
			case 'R':
				n *= -1;
			case 'L':
				//dir += n;
				{ //Rotate waypoint
					float s = std::sin(n * M_PI / 180.);
					float c = std::cos(n * M_PI / 180.);
					float wxn = wx * c - wy * s;
					float wyn = wx * s + wy * c;
					wx = wxn;
					wy = wyn;
				}
			break;
		}
	}

	std::cout << "|" << x << "| + |" << y << "| = " << std::abs(x) + std::abs(y) << std::endl;

	return 0;
}
