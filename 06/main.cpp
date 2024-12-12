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

bool checkObstruction(std::set<std::tuple<int, int, int, int>> const& visited, int x, int y, std::pair<int, int> const& direction) {
    auto [dx, dy] = direction;

    if (dx == -1)
	return visited.end() != std::find_if(visited.begin(), visited.end(), [&](auto v){ return (std::get<1>(v) == y and std::get<0>(v) < x) and std::get<2>(v) == dx and std::get<3>(v) == dy; });
    if (dx == 1)
	return visited.end() != std::find_if(visited.begin(), visited.end(), [&](auto v){ return (std::get<1>(v) == y and std::get<0>(v) > x) and std::get<2>(v) == dx and std::get<3>(v) == dy; });
    if (dy == -1)
	return visited.end() != std::find_if(visited.begin(), visited.end(), [&](auto v){ return (std::get<1>(v) < y and std::get<0>(v) == x) and std::get<2>(v) == dx and std::get<3>(v) == dy; });
    //if (dy == 1)
    return visited.end() != std::find_if(visited.begin(), visited.end(), [&](auto v){ return (std::get<1>(v) > y and std::get<0>(v) == x) and std::get<2>(v) == dx and std::get<3>(v) == dy; });
}

int part2(std::vector<std::string> const& input) {
    int obstructionPositions = 0;
    auto [x, y] = findStartingPosition(input);
    std::set<std::tuple<int, int, int, int>> visited; // coord, direction
    auto direction = DirectionCycle();
    while (x >= 0 and x < input[0].size() and y >= 0 and y < input.size()) {
	if (input[y][x] == '#') {
	    std::tie(x, y) = std::make_pair(x - direction->first, y - direction->second);
	    ++direction;
	    continue;
	}
	visited.insert({x, y, direction->first, direction->second});
	auto peekDirection = direction.peek();
	std::cout << "checking for {" << x + peekDirection.first << ", " << y + peekDirection.second << ", " << peekDirection.first << ", " << peekDirection.second << "}" << std::endl;
	std::cout << "visited: {" << std::endl;
	for (auto m: visited) {
	    std::cout << "    {" << std::get<0>(m) << ", " << std::get<1>(m) << ", " << std::get<2>(m) << ", " << std::get<3>(m) << "}" << std::endl;
	}
	if (checkObstruction(visited, x, y, peekDirection)) {
	    std::cout << "good spot at (" << x + direction->first << ", " << y + direction->second << ")" << std::endl;
	    obstructionPositions++;
	}
	std::tie(x, y) = std::make_pair(x + direction->first, y + direction->second);
    }
    return obstructionPositions;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
