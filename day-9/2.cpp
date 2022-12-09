#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    std::ifstream file("2.txt");
    std::string input;

    std::vector<char> line(1000,'.');
    std::vector<std::vector<char>> field(1000, line);

    std::vector<std::vector<int64_t>> coords(10,{500,500});
    field.at(500).at(500) = '#';

    while (std::getline(file, input)) {
        std::string direction = input.substr(0,1);
        int64_t steps = stoi(input.substr(2, input.size() - 2));

        while (steps) {
            if (direction == "R") ++coords.at(0).at(1);
            if (direction == "L") --coords.at(0).at(1);
            if (direction == "U") --coords.at(0).at(0);
            if (direction == "D") ++coords.at(0).at(0);

            for (int64_t i = 1; i < 10; ++i) {
                std::vector<int64_t>* head_coords = &coords.at(i - 1); // current head
                std::vector<int64_t>* tail_coords = &coords.at(i); // current tail
                if (!(std::abs((*head_coords).at(0) - (*tail_coords).at(0)) <= 1 && std::abs((*head_coords).at(1) - (*tail_coords).at(1)) <= 1)) { // if head and tail are not close enough

                    // then, I just implement the rules
                    if ((*head_coords).at(0) == (*tail_coords).at(0) && (*head_coords).at(1) != (*tail_coords).at(1)) { // if head and tail are in the same row
                        if ((*head_coords).at(1) > (*tail_coords).at(1)) (*tail_coords).at(1)++;
                        else (*tail_coords).at(1)--;
                    } else if ((*head_coords).at(0) != (*tail_coords).at(0) && (*head_coords).at(1) == (*tail_coords).at(1)) { // if head and tail are in the same column
                        if ((*head_coords).at(0) > (*tail_coords).at(0)) (*tail_coords).at(0)++;
                        else (*tail_coords).at(0)--;
                    } else if ((*head_coords).at(0) != (*tail_coords).at(0) && (*head_coords).at(1) != (*tail_coords).at(1)) { // if head and tail are not in the same column & not in the same row (diagonal move)
                        if ((*head_coords).at(0) > (*tail_coords).at(0)) (*tail_coords).at(0)++;
                        else (*tail_coords).at(0)--;

                        if ((*head_coords).at(1) > (*tail_coords).at(1)) (*tail_coords).at(1)++;
                        else (*tail_coords).at(1)--;
                    }
                    

                    if (i == 9) field.at((*tail_coords).at(0)).at((*tail_coords).at(1)) = '#'; // looking for the 9th tail 
                }
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