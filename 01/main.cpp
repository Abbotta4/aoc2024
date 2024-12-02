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
    std::vector<int> left, right;
    for (auto const& line: input) {
	std::smatch sm;
	auto r = std::regex_search(line, sm, std::regex(R"((\d+)\s+(\d+))"));
	left.push_back(std::stoi(sm[1]));
	right.push_back(std::stoi(sm[2]));
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int sum = 0;
    for(int i = 0; i < left.size(); ++i) {
	sum += std::max(left[i], right[i]) - std::min(left[i], right[i]);
    }
    return sum;
}

int part2(std::vector<std::string> const& input) {
    std::vector<int> left, right;
    for (auto const& line: input) {
	std::smatch sm;
	auto r = std::regex_search(line, sm, std::regex(R"((\d+)\s+(\d+))"));
	left.push_back(std::stoi(sm[1]));
	right.push_back(std::stoi(sm[2]));
    }

    std::map<int, int> freqMap;
    int similarityScore = 0;
    for (int l: left) {
	int freq;
	try {
	    freq = freqMap.at(l);
	} catch(const std::out_of_range& ex) {
	    freq = std::count(right.begin(), right.end(), l);
	    freqMap.emplace(l, freq);
	}
	similarityScore += l * freq;
    }
    return similarityScore;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
