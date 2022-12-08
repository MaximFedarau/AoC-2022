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
    uint64_t ans = 1;

    for (size_t i = 1; i < grid.size() - 1; ++i) {
        std::string line = grid.at(i);
        for (size_t j = 1; j < line.size() - 1; ++j) {
            uint64_t tree = stoi(std::string(1, line.at(j)));
            std::vector<bool> statuses;
            uint64_t counter = 1;

            // checking 4 ways: left, right, top & bottom 
            for (size_t x = j-1; x >= 0; --x) {
                // comparing char => string => int & int
                if (stoi(std::string(1, line.at(x))) >= tree) {
                    statuses.push_back(false); 
                    counter *= (j - x);
                    break;
                }
                if (x == 0) {
                    counter *= (j - x); 
                    break;
                }
            }
            for (size_t x = j+1; x < line.size(); ++x) {
                if (stoi(std::string(1, line.at(x))) >= tree) {
                    statuses.push_back(false); 
                    counter *= (x - j);
                    break;
                }
                if (x == line.size() - 1) counter *= (x - j);
                
            }
            for (size_t x = i - 1; x >= 0; --x) {
                if (stoi(std::string(1, grid.at(x).at(j))) >= tree) {
                    statuses.push_back(false); 
                    counter *= (i - x);
                    break;
                }
                if (x == 0) {
                    counter *= (i - x);
                    break;
                }
            }
            for (size_t x = i+1; x < grid.size(); ++x) {
                if (stoi(std::string(1, grid.at(x).at(j))) >= tree) {
                    statuses.push_back(false); 
                    counter *= (x - i);
                    break;
                }
                if (x == grid.size() - 1) counter *= (x - i);
            }

            if (statuses.size() < 4) ans = std::max(ans, counter);
        }
    }

    std::cout << ans << std::endl;
}