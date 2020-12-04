#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct passport{
	int byr = 0;
	int iyr = 0;
	int eyr = 0;
	std::string hgt = "";
	std::string hcl = "";
	std::string ecl = "";
	size_t pid = 0;
	size_t cid = 0;
};

int main() {
	std::vector<passport> passports;

	std::ifstream input("input.txt");
	std::string line;
	passport p;
	while (std::getline(input, line)) {
		//std::cout << "\"" << line << "\"" << std::endl;
		if (line == "") { //Space between passports
			passports.push_back(p);
			p = passport();
		} else {
			std::istringstream linestream(line);
			std::string sub;
			while (std::getline(linestream, sub, ' ')) {
				int colon = sub.find(':');
				std::string field = sub.substr(0, colon);
				std::string value = sub.substr(colon + 1);
				if (field == "byr") {
					p.byr = std::stoi(value);
				} else if (field == "iyr") {
					p.iyr = std::stoi(value);
				} else if (field == "eyr") {
					p.eyr = std::stoi(value);
				} else if (field == "hgt") {
					p.hgt = value;
				} else if (field == "hcl") {
					p.hcl = value;
				} else if (field == "ecl") {
					p.ecl = value;
				} else if (field == "pid") {
					p.pid = std::stoi(value);
				} else if (field == "cid") {
					p.cid = std::stoi(value);
				} else {
					//Unknown field
				}
			}
		}
	}

	passport blankpassport;
	int validPassportCount = 0;
	for (passport &p : passports) {
		int validFieldCounts = 0;
		validFieldCounts += p.byr != blankpassport.byr;
		validFieldCounts += p.iyr != blankpassport.iyr;
		validFieldCounts += p.eyr != blankpassport.eyr;
		validFieldCounts += p.hgt != blankpassport.hgt;
		validFieldCounts += p.hcl != blankpassport.hcl;
		validFieldCounts += p.ecl != blankpassport.ecl;
		validFieldCounts += p.pid != blankpassport.pid;
		//Ignore cid
		validPassportCount += validFieldCounts == 7;
		//std::cout << validFieldCounts << std::endl;
	}

	std::cout << validPassportCount << std::endl;
	return 0;
}
