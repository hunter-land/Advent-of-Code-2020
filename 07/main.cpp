#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct rule {
	std::string color = "";
	std::vector<std::string> carriedIn; //This color can be carried in these colors
	std::vector<std::string> carries; //What color this bag carries
	std::vector<int> carriesN; //How many of each color does this bag carry
	bool visited = false;
};
bool operator==(const rule& l, const rule& r) {
	return l.color == r.color;
}
bool operator==(const std::string l, const rule& r) {
	return l == r.color;
}
bool operator==(const rule& l, const std::string r) {
	return l.color == r;
}
int howManyBags(std::string color, std::vector<rule> &ruleset);

int main() {
	std::vector<rule> rules;

	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) { //Color A contain Y Color B, Z Color C
		std::string a = line.substr(0, line.find(" bags contain ")); //X
		line = line.substr(a.size() + 14); //Remove " bags contain "
		line = line.substr(0, line.size() - 1); //Remove '.'
		
		std::stringstream rest(line);
		std::string seg;
		while (std::getline(rest, seg, ',')) {
			//std::cout << seg << '\t';
			if (seg[0] == ' ') {
				seg = seg.substr(1);
			}
			seg = seg.substr(0, seg.size() - 4);
			if (seg[seg.size() - 1] == ' ') {
				seg = seg.substr(0, seg.size() - 1);
			}
			//std::cout << seg << '\t';

			//int tally = 0;
			//std::cout << seg;

			if ((line[0] != 'n' || line[1] != 'o' || line[2] != ' ') &&
			(seg[0] != 'n' || seg[1] != 'o' || seg[2] != ' ')) {
				//std::cout << seg << std::endl;
				int n = std::stoi(seg.substr(0, seg.find(' ')));
				seg = seg.substr(seg.find(' ') + 1);
				size_t i = std::distance(rules.begin(), std::find(rules.begin(), rules.end(), seg));
				if (i >= rules.size()) {
					rule r;
					r.color = seg;
					i = rules.size();
					rules.push_back(r);
				}
				auto it = std::find(rules[i].carriedIn.begin(), rules[i].carriedIn.end(), a);
				if (it == rules[i].carriedIn.end()) {
					rules[i].carriedIn.push_back(a);
				} else {
					//We already know `a` carrys `seg` colored bags
				}

				//New section for the reverse
				i = std::distance(rules.begin(), std::find(rules.begin(), rules.end(), a));
				if (i >= rules.size()) {
					rule r;
					r.color = a;
					i = rules.size();
					rules.push_back(r);
				}
				it = std::find(rules[i].carries.begin(), rules[i].carries.end(), seg);
				if (it == rules[i].carries.end()) {
					rules[i].carries.push_back(seg);
					rules[i].carriesN.push_back(n);
				}
			}
		}
		//std::cout << std::endl;
	}

	std::vector<rule*> toProcess;
	std::vector<std::string> bagToCarryMine;
	rule* root = &(*std::find(rules.begin(), rules.end(), std::string("shiny gold")));
	toProcess.push_back(root);
	while (toProcess.size() > 0) {
		rule* r = toProcess[0];
		toProcess.erase(toProcess.begin());

		for (std::string &color : r->carriedIn) {
			auto it = std::find(rules.begin(), rules.end(), color);
			//std::cout << color << " -> " << r->color << std::endl;
			if (it != rules.end()) {
				if (it->visited == false) {
			//		std::cout << color << " -> " << r->color << std::endl;
					toProcess.push_back(&(*it));
					//bagToCarryMine.push_back(color);
				}
			}
			if (std::find(bagToCarryMine.begin(), bagToCarryMine.end(), color) == bagToCarryMine.end()) {
				bagToCarryMine.push_back(color);
			}
		}
		r->visited = true;
	}

	int mustCarry = howManyBags("shiny gold", rules);

	std::cout << bagToCarryMine.size() << std::endl;
	std::cout << mustCarry << std::endl;
	return 0;
}

int howManyBags(std::string color, std::vector<rule> &ruleset) {
	int n = 0;
	auto it = std::find(ruleset.begin(), ruleset.end(), color);
	if (it == ruleset.end()) {
		return 0;
	}
	rule* r = &(*it);

	for (int i = 0; i < r->carries.size(); i++) {
		int x = r->carriesN[i]; //How many of bag at index do we need
		n += x; //This many of bag `x`
		n += x * howManyBags(r->carries[i], ruleset); //Bag x carries this many bags, times the number of bag x
	}
	return n;
}
