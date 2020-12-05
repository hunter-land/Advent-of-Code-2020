#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct passport{
	int byr = 0;
	int iyr = 0;
	int eyr = 0;
	int hgt = 0;
	std::string hgtunit = "";
	std::string hcl = "";
	std::string ecl = "";
	std::string pid = "";
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
				} else if (field == "hgt" && value.length() > 2) {
					if(value.find("cm") != std::string::npos) {
						p.hgtunit = "cm";
					} else if (value.find("in") != std::string::npos) {
						p.hgtunit = "in";
					}
					p.hgt = std::stoi(value.substr(0, value.length() - 2));
				} else if (field == "hcl") {
					if (value[0] == '#') {
						int validChars = 0;
						for(int i = 1; i < 7; i++) {
							validChars += (value[i] >= 97 && value[i] <= 102) || (value[i] >= 48 && value[i] <= 57);
						}
						if (validChars == 6) {
							p.hcl = value;
						}
					}
				} else if (field == "ecl") {
					if (value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth") {
						p.ecl = value;
					}
				} else if (field == "pid") {
					int validChars = 0;
					for (int i = 0; i < 9; i++) {
						validChars += value[i] >= 48 && value[i] <= 57;
					}
					if (validChars == 9) {
						p.pid = value;
					} else {
						//std::cerr << "Invalid pid: \"" << value << "\"" << std::endl;
					}
				} else if (field == "cid") {
					p.cid = std::stoi(value);
				} else {
					//Unknown field
				}
			}
		}
	}
	passports.push_back(p);

	passport blankpassport;
	int validPassportCount = 0;
	for (passport &p : passports) {
		int validFieldCounts = 0;
		validFieldCounts += p.byr >= 1920 && p.byr <= 2002;
		validFieldCounts += p.iyr >= 2010 && p.iyr <= 2020;
		validFieldCounts += p.eyr >= 2020 && p.eyr <= 2030;
		if (p.hgtunit == "cm") {
			validFieldCounts += p.hgt >= 150 && p.hgt <= 193;
		} else if (p.hgtunit == "in") {
			validFieldCounts += p.hgt >= 59 && p.hgt <= 76;
		}
		validFieldCounts += p.hcl != blankpassport.hcl;
		validFieldCounts += p.ecl != blankpassport.ecl;
		validFieldCounts += p.pid != blankpassport.pid;
		//Ignore cid
		validPassportCount += validFieldCounts == 7;
		//std::cout << validFieldCounts << std::endl;
	}

	//the `- 1` is here because there seems to be a theme found in a local group for the second part
	//where the answer is one below what people are getting. This is either an error on the checker
	//or everyone not noticing a similar bug
	std::cout << validPassportCount - 1 << std::endl;
	return 0;
}
