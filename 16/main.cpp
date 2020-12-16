#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct field {
	std::string alias;
	std::vector<std::pair<int, int>> ranges;
};
bool operator<(const field& l, const field& r) {
	return l.alias < r.alias;
}
bool operator==(const field& l, const field& r) {
	return l.alias == r.alias;
}
bool numberFits(int n, field &f) {
	for (std::pair<int, int> p : f.ranges) {
		if (p.first <= n && n <= p.second) {
			//std::cout << n << " fits " << f.alias << std::endl;
			return true; //Fits this range, return true
		}
	}
	//std::cout << n << " does not fit " << f.alias << std::endl;
	return false;
}
struct ticket {
	std::vector<int> v;
};

int main () {
	std::vector<field> fields;
	std::vector<ticket> tickets;

	int section = 0;
	std::ifstream input("input.txt");
	std::string line;
	while (std::getline(input, line)) {
		//std::cout << section << ":\t" << line << std::endl;
		if (line == "") {
		} else if (line == "your ticket:") {
			section = 1;
		} else if (line == "nearby tickets:") {
			section = 2;
		} else if (section == 0) { //Field limits
			field f;
			f.alias = line.substr(0, line.find(':'));
			line = line.substr(line.find(':') + 2); //Extra `+1` because of space

			std::pair<int, int> p;
			p.first = std::stoi(line.substr(0, line.find('-')));
			p.second = std::stoi(line.substr(line.find('-') + 1, line.find(' ')));
			f.ranges.push_back(p);

			//std::cout << f.alias << ": " << p.first << "-" << p.second;

			line = line.substr(line.find(' ') + 1 + 3); //Extra `+3` because of "or "

			p.first = std::stoi(line.substr(0, line.find('-')));
			p.second = std::stoi(line.substr(line.find('-') + 1));
			f.ranges.push_back(p);

			//std::cout << " or " << p.first << "-" << p.second << std::endl;

			fields.push_back(f);
		} else if (section == 2 || section == 1) {
			ticket t;
			//Each line is CSV of a ticket
			while (line.find(',') != std::string::npos) {
				int n = std::stoi( line	.substr(0, line.find(',')) );
				t.v.push_back(n);

				line = line.substr(line.find(',') + 1);
			}
			t.v.push_back(std::stoi(line));
			tickets.push_back(t);
		}
	}

	std::vector<std::vector<bool>> table; //Table [i][j] where i = ticket order and j = field
	table.resize(fields.size());
	for (std::vector<bool> &row : table) {
		//row.resize(fields.size());
		for (int i = 0; i < fields.size(); i++) {
			row.push_back(true);
		}
	}
	/*	departure location: 34-269 or 286-964
		departure station: 27-584 or 609-973
		departure platform: 49-135 or 155-974
		departure track: 36-248 or 255-954
		departure date: 50-373 or 381-974
		departure time: 49-454 or 472-967
		arrival location: 33-900 or 925-968
		arrival station: 46-699 or 706-965
		arrival platform: 42-656 or 666-967
		arrival track: 49-408 or 425-950
		class: 30-626 or 651-957
		duration: 43-109 or 127-964
		price: 33-778 or 795-952
		route: 37-296 or 315-966
		row: 28-318 or 342-965
		seat: 33-189 or 208-959
		train: 49-536 or 552-968
		type: 46-749 or 772-949
		wagon: 29-386 or 401-954
		zone: 34-344 or 368-954			*/

	std::vector<int> invalidNumbers;
	for (ticket &t : tickets) {
		//For every number on a ticket
		for (int i = 0; i < t.v.size(); i++) {
			bool valid = false;
			for (int j = 0; j < fields.size(); j++) {
				bool b = numberFits(t.v[i], fields[j]);
				valid |= b;
			}

			if (!valid) {
				invalidNumbers.push_back(t.v[i]);
				break;
			}

			for (int j = 0; j < fields.size(); j++) {
				if (table[i][j]) {
					bool b = numberFits(t.v[i], fields[j]);
					table[i][j] = b;
				}
			}
		}
	}

	long total = 0;
	for (int n : invalidNumbers) {
		total += n;
	}
	std::cout << total << std::endl;

	std::map<field, int> correctFields;
	for (int i = 0; correctFields.size() != fields.size(); i = (i + 1) % table.size()) {
		std::cout << "Checking field #" << i << std::endl;
		std::vector<field> possible;
		for (int j = 0; j < fields.size(); j++) {
			if (table[i][j] && correctFields.find(fields[j]) == correctFields.end()) {
				//std::cout << "Entry #" << i << " may be " << fields[j].alias << std::endl;
				possible.push_back(fields[j]);
			}
		}
		std::cout << possible.size() << " possible fields match" << std::endl;
		if (possible.size() == 1) {
			correctFields[possible[0]] = i;
		}
	}

	long out = 1;
	for (std::pair<field, int> p : correctFields) {
		std::cout << p.first.alias << " at index " << p.second << std::endl;
		if (p.first.alias.substr(0, 9) == "departure") {
			std::cout << "My ticket's value for " << p.first.alias << " is " << tickets[0].v[p.second] << std::endl;
			out *= tickets[0].v[p.second];
		}
	}

	std::cout << out << std::endl;

	return 0;
}
