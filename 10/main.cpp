#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct adapter {
	int rating = 0;
	bool used = false;
	std::vector<adapter*> next;
	unsigned long combinations = 1;
};
bool operator<(const adapter& l, const adapter& r) {
	return l.rating < r.rating;
}

int main() {
	adapter a;
	a.rating = 0;
	std::vector<adapter> ratings = {a};
	int builtin = 0;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		int r = std::stoi(line);
		builtin = std::max(r, builtin);
		a.rating = r;
		ratings.push_back(a);
	}
	a.rating = builtin + 3;
	ratings.push_back(a);

	std::sort(ratings.begin(), ratings.end());
	int cur = 0; //Current joltage
	std::vector<long> diff;
	diff.resize(3);

	for (int i = 1; i < ratings.size(); i++) {
		int d = ratings[i].rating - ratings[i-1].rating;
		diff[d-1]++;

		for (int j = i + 1; j < i + 4 && j < ratings.size(); j++) {
			if (ratings[j].rating - ratings[i].rating <= 3) {
				ratings[i].next.push_back(&(ratings[j]));
			}
		}
		//std::cout << d << std::endl;
		//std::cout << diff[d-1] << std::endl;
	}
	
	for (int i = 1; i < 5; i++) {
		if (ratings[i].rating - ratings[0].rating <= 3) {
			ratings[0].next.push_back(&(ratings[i]));
		}
	}
	
	unsigned long combinations = 0;
	for (int i = ratings.size() - 2; i >= 0; i--) {
		//std::cout << "Adapter #" << i << " has " << ratings[i].next.size() << " next..." << std::endl;
		ratings[i].combinations = 0;
		for (int j = 0; j < ratings[i].next.size(); j++) {
			ratings[i].combinations += ratings[i].next[j]->combinations;
		}
		//std::cout << "With " << ratings[i].combinations << " using all of them" << std::endl;
	}
	combinations = ratings[0].combinations;

	std::cout << diff[0] << " * " << diff[2] << std::endl;
	std::cout << diff[0] * diff[2] << std::endl;

	std::cout << combinations << " combinations" << std::endl;
	return 0;
}
