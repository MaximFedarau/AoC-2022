#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

// get this coords from reddit
const int64_t MIN_COORD = -1;
const int64_t MAX_COORD = 21;

std::vector<std::vector<int64_t>> get_all_neighbours(std::vector<int64_t> point) {
    int64_t x = point[0];
    int64_t y = point[1];
    int64_t z = point[2];
    return {{x + 1, y, z}, {x - 1, y, z}, {x, y + 1, z}, {x, y - 1, z}, {x, y, z + 1}, {x, y, z - 1}};
}

int main() {
    freopen("2.txt", "r", stdin);

    std::set<std::vector<int64_t>> lava;
    while (true) {
        // read data
        std::string val;
        std::cin >> val;
        if (!std::cin) break;
        // convert data
        int64_t x = stoi(val.substr(0, val.find(",")));
        val.erase(0, val.find(",") + 1);
        int64_t y = stoi(val.substr(0, val.find(",")));
        val.erase(0, val.find(",") + 1);
        int64_t z = stoi(val);
        lava.insert({x,y,z});
    }

    // using BFS => checking if current point is lava, because lava blocks the way

    int64_t ans_counter = 0;
    std::queue<std::vector<int64_t>> points;
    points.push({0,0,0});
    std::set<std::vector<int64_t>> visited_points;

    while (!points.empty()) {
        std::vector<int64_t> current_point = points.front();
        points.pop();
        // if we've already visited the point
        if (visited_points.find(current_point) != visited_points.end()) continue;
        visited_points.insert(current_point);
        for (auto& neighbour: get_all_neighbours(current_point)) {
            if (neighbour[0] >= MIN_COORD && neighbour[0] <= MAX_COORD && neighbour[1] >= MIN_COORD && neighbour[1] <= MAX_COORD && neighbour[2] >= MIN_COORD && neighbour[2] <= MAX_COORD) {
                // if current_point is lava
                if (lava.find(neighbour) != lava.end()) ans_counter++;
                else points.push(neighbour);
            }
        }
    } 

    std::cout << ans_counter << std::endl;
}