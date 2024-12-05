#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

/*
  dir:
  1 2 3
  4 X 6
  7 8 9
 */
bool tryMAS(std::vector<std::string> const& crossword, int row, int col, int dir, int len) {
    if (len == 4)
	return true;
    if (col < 0 or col > crossword[0].size() or row < 0 or row > crossword.size())
	return false;
    if (crossword[row][col] == "XMAS"[len])
	return tryMAS(crossword, row + (dir > 6 ? 1 : 0) - (dir < 4 ? 1 : 0), col + (dir%3 == 0 ? 1 : 0) - ((dir-1)%3 == 0 ? 1 : 0), dir, len+1);
    return false;
}

int part1(std::vector<std::string> const& crossword) {
    int numXMAS = 0;
    for (int row = 0; row < crossword.size(); ++row) {
	for (int col = 0; col < crossword[0].size(); ++col) {
	    if (crossword[row][col] == 'X') {
		for (int dir = 1; dir < 10; ++dir) {
		    if (dir == 5)
			continue;
		    if (tryMAS(crossword, row + (dir > 6 ? 1 : 0) - (dir < 4 ? 1 : 0), col + (dir%3 == 0 ? 1 : 0) - ((dir-1)%3 == 0 ? 1 : 0), dir, 1))
			numXMAS++;
		}
	    }
	}
    }
    return numXMAS;
}

int part2(std::vector<std::string> const& crossword) {
    int numXMAS = 0;
    for (int row = 0; row < crossword.size(); ++row) {
	for (int col = 0; col < crossword[0].size(); ++col) {
	    if (crossword[row][col] == 'A') {
		if (row == 0 or row == crossword.size()-1 or col == 0 or col == crossword[0].size()-1)
		    continue;
		std::vector<char> letters = {crossword[row-1][col-1], crossword[row-1][col+1], crossword[row+1][col+1], crossword[row+1][col-1]};
		if (std::count(letters.begin(), letters.end(), 'S') == 2 and std::count(letters.begin(), letters.end(), 'M') == 2 and crossword[row-1][col-1] != crossword[row+1][col+1])
		    numXMAS++;
	    }
	}
    }
    return numXMAS;
}

int main() {
    std::vector<std::string> input = readInput("input.txt");
    std::cout << part1(input) << std::endl;
    std::cout << part2(input) << std::endl;
    return 0;
}
