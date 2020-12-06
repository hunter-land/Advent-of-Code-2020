#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<std::vector<char>> groupResp;
	std::vector<std::vector<int>> groupRespTotals;

	std::ifstream input("input.txt");
	std::string line;
	std::vector<char> answers;
	std::vector<int> times;
	int n = 0;
	while (std::getline(input, line)) {
		if (line == "") {
			groupResp.push_back(answers);
			times.push_back(n);
			n = 0;
			groupRespTotals.push_back(times);
			answers.resize(0);
			times.resize(0);
		} else {
			n++;
			for (char c : line) {
				size_t i = std::distance(answers.begin(), std::find(answers.begin(), answers.end(), c));
				if (i >= answers.size()) {
					answers.push_back(c);
					times.push_back(1);
				} else {
					times[i]++;
				}
			}
		}
	}
	groupResp.push_back(answers);
	times.push_back(n);
	groupRespTotals.push_back(times);

	int total = 0;
	for (int i = 0; i < groupResp.size(); i++) {
		//auto end = std::unique(resp.begin(), resp.end());
		//int size = std::distance(resp.begin(), end);
		
		//std::cout << std::string(resp.begin(), resp.end()) << std::endl;
		//total += resp.size();
		
		for (int j = 0; j < groupRespTotals[i].size()-1; j++) {
			std::cout << groupResp[i][j] << " appears " << groupRespTotals[i][j] << " times." << std::endl;
			if (groupRespTotals[i][j] == groupRespTotals[i][groupRespTotals[i].size()-1]) {
				total++;
			}
		}
	}

	std::cout << total << std::endl;
	return 0;
}
