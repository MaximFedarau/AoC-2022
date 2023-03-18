#include <iostream>
#include <string>
#include <vector>

int main() {
    freopen("1.txt", "r", stdin);

    std::vector<std::vector<int64_t>> data;
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
        data.push_back({x,y,stoi(val)});
    }

    int64_t global_counter = 6 * data.size();
    for (int64_t i = 0; i < data.size(); ++i) {
        int64_t x = data[i][0], y = data[i][1], z = data[i][2];
        for (int64_t j = i + 1; j < data.size(); ++j) {
            int64_t x1 = data[j][0], y1 = data[j][1], z1 = data[j][2];
            // if we have 2 cubes-neighbours
            if (std::abs(x1 - x) == 1 && y1 == y && z1 == z) global_counter-=2;
            else if (x1 == x && std::abs(y1 - y) == 1 && z1 == z) global_counter-=2;
            else if (x1 == x && y1 == y && std::abs(z1 - z) == 1) global_counter-=2;
        }
    }
    std::cout << global_counter << std::endl;
}