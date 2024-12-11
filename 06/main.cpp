#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

class DirectionCycle {
private:
    std::vector<std::pair<int, int>> cycle = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int index;
public:
    DirectionCycle() : index(0) {}
    std::pair<int, int> operator*() const {
	return cycle[index];
    }
    DirectionCycle& operator++() {
	index = (index + 1) % 4;  // Loop back to 0 after 3
	return *this;
    }
    std::pair<int, int>* operator->() {
	return &cycle[index];
    }
};

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

std::pair<int, int> findStartingPosition(std::vector<std::string> const& input) {
    for (int y = 0; y < input.size(); y++) {
	for (int x = 0; x < input[0].size(); x++) {
	    if (input[y][x] == '^')
		return std::make_pair(x, y);
	}
    }
    return std::make_pair(-1, -1); // should never get here
}

int part1(std::vector<std::string> const& input) {
    auto [x, y] = findStartingPosition(input);
    std::set<std::pair<int, int>> visited;
    auto direction = DirectionCycle();
    while (x >= 0 and x < input[0].size() and y >= 0 and y < input.size()) {
	if (input[y][x] == '#') {
	    std::tie(x, y) = std::make_pair(x - direction->first, y - direction->second);
	    ++direction;
	    continue;
	}
	visited.insert(std::make_pair(x, y));
	std::tie(x, y) = std::make_pair(x + direction->first, y + direction->second);
    }
    return visited.size();
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    return 0;
}
