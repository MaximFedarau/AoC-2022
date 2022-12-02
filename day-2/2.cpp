#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    uint64_t counter = 0;
    std::map <std::string, uint64_t> order = {{"X", 0}, {"Y", 1}, {"Z", 2}};
    std::map <std::string, std::vector<uint64_t>> scores = {{"A", {3,4,8}}, {"B", {1,5,9}}, {"C", {2,6,7}}}; // one item in map is a name of opponent's item & vector of points in 3 cases: lose, draw, win

    while (true) {
        std::string a,b;
        std::cin >> a >> b;

        counter += scores[a][order[b]];

        std::cout << counter << std::endl; // outputs answer after every block
    }
}