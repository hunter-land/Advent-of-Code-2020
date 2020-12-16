#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

int main() {
	size_t i = 0;
	std::map<int, std::pair<int, int>> nums;// = {{0,{0,0}}, {3,{1,1}}, {6,{2,2}}};

	std::ifstream input("input.txt");
	std::string line;
	std::getline(input, line);
	while (line.find(',') != std::string::npos) {
		nums[std::stoi(line.substr(0, line.find(',')))] = {i, i};
		line = line.substr(line.find(',') + 1);
		i++;
	}
	int last = std::stoi(line);
	nums[last] = {i, i};
	i++;

	//If [i-1] is first appearance of, say '0'
	//else say distance from most recent ([i-1]) to 2nd most recent

	for (; i < 30000000; i++) {

		//Was this said previously?
		//If so, dist = (i - nums[last])
		//Otherwise dist = 0;

		int dist = 0;
		if (nums.find(last) != nums.end()) {
			dist = nums[last].second - nums[last].first;
		}

		if (nums.find(dist) != nums.end()) {
			nums[dist].first = nums[dist].second;
			nums[dist].second = i;
		} else {
			nums[dist] = {i, i};
		}

		last = dist;

		if (i == 30000000 - 1 || i == 2020 - 1) {
			std::cout << dist << std::endl;
		}
	}

	return 0;
}
