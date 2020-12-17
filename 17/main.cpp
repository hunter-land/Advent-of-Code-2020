#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct point {
	int x, y, z, w;
	bool active = false;
};
bool operator==(const point& l, const point& r) {
	return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
}
bool getPoint(int x, int y, int z, int w, std::vector<point>& points) {
	point p;
	p.x = x;
	p.y = y;
	p.z = z;
	p.w = w;
	auto it = std::find(points.begin(), points.end(), p);
	if (it != points.end()) {
		//std::cout << x << ", " << y << ", " << z << ", " << w << (it->active ? " active" : " inactive") << std::endl;
		return (*it).active;
	}
	return false;
}
void setPoint(int x, int y, int z, int w, bool active, std::vector<point>& points) {
	point p;
	p.x = x;
	p.y = y;
	p.z = z;
	p.w = w;
	auto it = std::find(points.begin(), points.end(), p);
	if (it != points.end()) {
		it->active = active;
	} else {
		p.active = active;
		points.push_back(p);
	}
}

int main() {
	std::vector<point> points;

	std::ifstream input("input.txt");
	std::string line;
	int y = 0;
	while (std::getline(input, line)) {
		int a = 0;
		for (int i = 0; i < line.size(); i++) {
			point p;
			p.x = i;
			p.y = y;
			p.z = 0;
			p.w = 0;
			bool b = line[i] == '#';
			p.active = b;
			a += b;
			points.push_back(p);
		}
		std::cout << "(y = " << y << ", a = " << a << "): " << line << std::endl;
		y++;
	}
	y += 2;

	//std::cout << a << std::endl;
	std::cin >> line;

	//Per iteration:
	//If active && 2 or 3 active adjacent:
	//	Remain active
	//else
	//	Become inactive
	//If inactive && 3 active adjacent:
	//	Become active
	//else
	//	Remain inactive

	std::vector<point> lastPoints = points;
	int max = y;
	for(int i = 0; i < 6; i++, max++) {
		int activeThisCycle = 0;
		for (int x = -max; x <= max; x++) {
			for (int y = -max; y <= max; y++) {
				for (int z = -max; z <= max; z++) {
					for (int w = -max; w <= max; w++) {
						int adjacentActive = 0;
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								for (int dz = -1; dz <= 1; dz++) {
									for (int dw = -1; dw <= 1; dw++) {
										adjacentActive += getPoint(x + dx, y + dy, z + dz, w + dw, lastPoints);
									}
								}
							}
						}
						bool active = getPoint(x, y, z, w, lastPoints);
						adjacentActive -= active;
						activeThisCycle += active;

						if (active) {
							if (adjacentActive == 2 || adjacentActive == 3) {
								//Remain active
							} else {
								//Become inactive
								setPoint(x, y, z, w, false, points);
							}
						} else {
							if (adjacentActive == 3) {
								//Become active
								setPoint(x, y, z, w, true, points);
							} else {
								//Remain inactive
								//setPoint(x, y, z, false);
							}
						}
					}
				}
			}
		}
		std::cout << "#" << i << ": " << activeThisCycle << " active cubes." << std::endl;
		lastPoints = points;
		//std::cin >> line;
	}

	int activeCubes = 0;
	for (point &p : points) {
		activeCubes += p.active;
	}
	std::cout << activeCubes << std::endl;

	return 0;
}
