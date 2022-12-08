#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int main() {
    std::vector<std::string> grid;
    std::string input;
    while(std::getline(std::cin,input)) {
        grid.push_back(input);
    }
    uint64_t ans = grid.size() * 2 + (grid.at(0).size() - 2) * 2;

    for (size_t i = 1; i < grid.size() - 1; ++i) {
        std::string line = grid.at(i);
        for (size_t j = 1; j < line.size() - 1; ++j) {
            uint64_t tree = stoi(std::string(1, line.at(j)));
            std::vector<bool> statuses;

            // checking 4 ways: left, right, top & bottom 
            for (size_t x = 0; x < j; ++x) {
                // comparing char => string => int & int
                if (stoi(std::string(1, line.at(x))) >= tree) {
                    statuses.push_back(false); 
                    break;
                }
            }
            for (size_t x = j+1; x < line.size(); ++x) {
                if (stoi(std::string(1, line.at(x))) >= tree) {
                    statuses.push_back(false); 
                    break;
                }
            }
            for (size_t x = 0; x < i; ++x) {
                if (stoi(std::string(1, grid.at(x).at(j))) >= tree) {
                    statuses.push_back(false); 
                    break;
                }
            }
            for (size_t x = i+1; x < grid.size(); ++x) {
                if (stoi(std::string(1, grid.at(x).at(j))) >= tree) {
                    statuses.push_back(false); 
                    break;
                }
            }

            if (statuses.size() < 4) ++ans;
        }
    }

    std::cout << ans << std::endl;
}