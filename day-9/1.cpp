#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int main() {
    std::ifstream file("1.txt");
    std::string input;

    std::vector<char> line(1000,'.');
    std::vector<std::vector<char>> field(1000, line);

    std::vector<int64_t> head_coords = {500,500}; // in the middle of the field
    std::vector<int64_t> tail_coords = {500,500}; // in the middle of the field
    field.at(500).at(500) = '#';

    while (std::getline(file, input)) {
        std::string direction = input.substr(0,1);
        int64_t steps = stoi(input.substr(2, input.size() - 2));

        while (steps) {
            std::vector<int64_t> prev_coords = head_coords;
            if (direction == "R") ++head_coords.at(1);
            if (direction == "L") --head_coords.at(1);
            if (direction == "U") --head_coords.at(0);
            if (direction == "D") ++head_coords.at(0);
            
            // if after step tail and head are not close enough
            if (!(std::abs(head_coords.at(0) - tail_coords.at(0)) <= 1 && std::abs(head_coords.at(1) - tail_coords.at(1)) <= 1)) {
                tail_coords = prev_coords;
                field.at(prev_coords.at(0)).at(prev_coords.at(1)) = '#';
            }

            --steps;
        }

    }

    int64_t ans = 0;

    for (auto line: field) {
        for (auto cell: line) {
            if (cell == '#') ++ans;
        }
    }

    std::cout << ans << std::endl;
}