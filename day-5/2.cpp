#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::ifstream input ("2.txt");
    std::vector<std::vector<char>> crates = {};

    std::string line, rezult= "";
    getline(input,line);
    for (int64_t i = 0; i < ((line.length() - 3) / 4) + 1; ++i) {
        std::vector<char> crate = {};
        if (line[0 + 4*i] == '[') crate.push_back(line[1 + 4*i]);
        crates.push_back(crate);
    }

    // reading data
    while (true) {
        getline(input,line);
        if (line.length() == 0) break;
        for (int64_t i = 0; i < ((line.length() - 3) / 4) + 1; ++i) {
            if (line[0 + 4*i] == '[') crates.at(i).push_back(line[1 + 4*i]);
        }
    }

    // while there is lines (without duplicates!) - reading moves
    while (getline(input,line)) {
        int64_t from_index = line.find("from"), to_index = line.find("to");
        uint64_t item_quantity = stoi(line.substr(5, from_index - 6)), first_crate_index = stoi(line.substr(from_index + 5, to_index - from_index - 6)), second_crate_index = stoi(line.substr(to_index + 3, line.length()));
        
        std::vector<char> first_crate = crates.at(first_crate_index - 1), second_crate = crates.at(second_crate_index - 1);

        for (int64_t i = item_quantity - 1; i >= 0;i--) {
            second_crate.insert(second_crate.begin(), first_crate.at(i)); // adding new items
        }
        first_crate.erase(first_crate.begin(), first_crate.begin() + item_quantity); // removing old items

        // assigning new data
        crates.at(first_crate_index - 1) = first_crate; 
        crates.at(second_crate_index - 1) = second_crate;
    }

    for (auto crate: crates) rezult += crate.at(0);
    std::cout << rezult << std::endl;
}