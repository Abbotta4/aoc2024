#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

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
    std::pair<int, int> peek() const {
	return cycle[(index+1)%4];
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

std::set<std::pair<int, int>> getVisited(std::vector<std::string> const& input) {
    auto [x, y] = findStartingPosition(input);
    std::set<std::pair<int, int>> visited;
    std::set<std::tuple<int, int, int, int>> visitedWithDir;
    auto direction = DirectionCycle();
    while (x >= 0 and x < input[0].size() and y >= 0 and y < input.size()) {
	if (input[y][x] == '#') {
	    std::tie(x, y) = std::make_pair(x - direction->first, y - direction->second);
	    ++direction;
	    continue;
	}
	visited.insert(std::make_pair(x, y));
	if (visitedWithDir.contains({x, y, direction->first, direction->second}))
	    return {};
	visitedWithDir.insert({x, y, direction->first, direction->second});
	std::tie(x, y) = std::make_pair(x + direction->first, y + direction->second);
    }
    return visited;
}

int part1(std::vector<std::string> const& input) {
    std::set<std::pair<int, int>> visited = getVisited(input);
    return visited.size();
}

int part2(std::vector<std::string>& input) {
    std::set<std::pair<int, int>> visited = getVisited(input);
    visited.erase(findStartingPosition(input));
    int obstructionOptions = 0;
    for (auto position: visited) {
	input[position.second][position.first] = '#';
	if (part1(input) == 0)
	    obstructionOptions++;
	input[position.second][position.first] = '.';
    }
    return obstructionOptions;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
