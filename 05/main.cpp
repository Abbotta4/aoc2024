#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

std::vector<std::string> readInput(std::string fileName) {
    std::vector<std::string> input;
    std::string tmp;
    std::ifstream file;
    file.open(fileName);
    while (file) {
        std::getline(file, tmp);
        input.push_back(tmp);
    }
    file.close();
    input.pop_back(); // remove empty line at end
    return input;
}

int part1(std::vector<std::string> const& input) {
    std::map<int, std::vector<int>> rules;
    auto splitIt = std::find(input.begin(), input.end(), "");
    for (auto it = input.begin(); it < splitIt; ++it) {
	std::smatch sm;
	auto re = std::regex_search(it->begin(), it->end(), sm, std::regex(R"((\d+)\|(\d+))"));
	rules[std::stoi(sm[1].str())].push_back(std::stoi(sm[2].str()));
    }

    int middleSum = 0;
    for (auto it = ++splitIt; it < input.end(); ++it) { // orderings
	std::vector<int> pages = {};
	auto numberRegex = std::regex(R"(\d+)");
	for (auto r = std::sregex_iterator(it->begin(), it->end(), numberRegex); r != std::sregex_iterator(); ++r) {
	    pages.push_back(std::stoi(r->str()));
	}
	bool correctlyOrdered = true;
	for (auto firstPageIt = pages.begin(); firstPageIt < pages.end(); ++firstPageIt) {
	    for (int secondPage: rules[*firstPageIt]) {
		if (std::find(pages.begin(), pages.end(), secondPage) < firstPageIt) {
		    correctlyOrdered = false;
		    break;
		}
	    }
	    if (!correctlyOrdered)
		break;	    
	}
	if (correctlyOrdered)
	    middleSum += pages[pages.size()/2];
    }
    return middleSum;
}

int part2(std::vector<std::string> const& input) {
    std::map<int, std::vector<int>> rules;
    auto splitIt = std::find(input.begin(), input.end(), "");
    for (auto it = input.begin(); it < splitIt; ++it) {
	std::smatch sm;
	auto re = std::regex_search(it->begin(), it->end(), sm, std::regex(R"((\d+)\|(\d+))"));
	rules[std::stoi(sm[1].str())].push_back(std::stoi(sm[2].str()));
    }

    int middleSum = 0;
    for (auto it = ++splitIt; it < input.end(); ++it) { // orderings
	std::vector<int> pages = {};
	auto numberRegex = std::regex(R"(\d+)");
	for (auto r = std::sregex_iterator(it->begin(), it->end(), numberRegex); r != std::sregex_iterator(); ++r) {
	    pages.push_back(std::stoi(r->str()));
	}
	bool correctlyOrdered = true;
	for (auto firstPageIt = pages.begin(); firstPageIt < pages.end(); ++firstPageIt) {
	    for (int secondPage: rules[*firstPageIt]) {
	        auto secondPageIt = std::find(pages.begin(), pages.end(), secondPage);
		if ( secondPageIt < firstPageIt) {
		    correctlyOrdered = false;
		    int tmp = *secondPageIt;
		    *secondPageIt = *firstPageIt;
		    *firstPageIt = tmp;
		    firstPageIt = (secondPageIt == pages.begin() ? pages.begin() : std::prev(secondPageIt));
		    break;
		}
	    }
	}
	if (!correctlyOrdered) {
	    middleSum += pages[pages.size()/2];
	}
    }
    return middleSum;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
