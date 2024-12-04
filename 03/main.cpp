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

int part2(std::string& input) {
    input = std::regex_replace(input, std::regex(R"((?:\r\n|\n))"), ""); // newlines break doDont
    std::regex doDont(R"((?:do\(\)|^)(.*?)(?:don't\(\)|$))");
    std::string newInput = "";
    for (auto i = std::sregex_token_iterator(input.begin(), input.end(), doDont, {0}); i != std::sregex_token_iterator(); ++i)
        newInput += i->str();
    return part1(newInput);
}

int main() {
    std::string input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
