#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string readInput(std::string fileName) {
    std::string tmp;
    std::ifstream file;
    file.open(fileName);
    std::getline(file, tmp, {});
    file.close();
    return tmp;
}

int part1(std::string const& input) {
    int sum = 0;
    std::regex muls(R"(mul\(([0-9]+),([0-9]+)\))");
    for (auto i = std::sregex_token_iterator(input.begin(), input.end(), muls, {1, 2}); i != std::sregex_token_iterator(); ++i) {
	int tmp = std::stoi((i++)->str());
	tmp *= std::stoi(i->str());
	sum += tmp;
    }
    return sum;
}

int main() {
    std::string input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    return 0;
}
