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
    int numSafe = 0;
    std::regex numbers(R"([0-9]+)");
    for (auto const& report: input) {
	std::vector<int> nums;
	for (auto i = std::sregex_iterator(report.begin(), report.end(), numbers); i != std::sregex_iterator(); ++i)
	    nums.push_back(std::stoi(i->str()));
	bool dec = nums[0] - nums[1] > 0;
	bool safe = true;
	for (int i = 0; i < nums.size()-1; ++i) {
	    int delta = nums[i] - nums[i+1];
	    if (delta == 0 or delta > 0 != dec or delta > 3 or delta < -3)
		safe = false;
	    if (!safe)
		break;
	}
	if (safe)
	    numSafe++;
    }
    return numSafe;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    return 0;
}
