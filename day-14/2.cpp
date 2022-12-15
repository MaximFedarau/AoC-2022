#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

const int64_t FIELD_SIZE = 1000; // field (cave) size
const int64_t SAND_SOURCE = FIELD_SIZE / 2;

// create std::pair out of coords string, e.g. 498,6 => {498,6}
std::pair<int64_t, int64_t> create_coords_pair(std::string input) {
    int64_t first_coord = stoi(input.substr(0,input.find(","))), second_coord = stoi(input.substr(input.find(",") + 1));
    return std::make_pair(first_coord, second_coord);
}

// create std::vector of std::pair-s of coords, e.g. 498,6 -> 499,6 => {{498, 6}, {499,6}}
std::vector<std::pair<int64_t, int64_t>> get_rocks_coords(std::string input) {
    std::string search_input = input;
    std::vector<std::pair<int64_t, int64_t>> result;
    while (search_input.find(" -> ") != -1) {
        std::string unformatted_coords = search_input.substr(0, input.find(" -> "));
        result.push_back(create_coords_pair(unformatted_coords));
        search_input = search_input.substr(input.find(" -> ") + 4);
    }
    result.push_back(create_coords_pair(search_input)); // last coords
    return result;
}

int main() {
    std::ifstream file("2.txt");
    std::string input;

    std::vector<char> row(FIELD_SIZE, '.');
    std::vector<std::vector<char>> field(FIELD_SIZE, row);

    int64_t floor_position = 0;
    while(std::getline(file, input)) {
        std::vector<std::pair<int64_t, int64_t>> rocks_coords = get_rocks_coords(input);
        for (size_t i = 1; i != rocks_coords.size(); ++i) {
            std::pair<int64_t, int64_t> current_coords_pair = rocks_coords.at(i), previous_coords_pair = rocks_coords.at(i - 1);
            floor_position = std::max(std::max(floor_position, current_coords_pair.second), previous_coords_pair.second); // getting a floor coord
            if (current_coords_pair.first == previous_coords_pair.first) { // placing rocks vertically
                int64_t min_horizontal_coord = std::min(current_coords_pair.second, previous_coords_pair.second), max_horizontal_coord = std::max(current_coords_pair.second, previous_coords_pair.second); // getting min/max values, because values can go both ascending and descending
                for (size_t j = min_horizontal_coord; j <= max_horizontal_coord; ++j) field.at(j).at(current_coords_pair.first) = '#';
            } else if (current_coords_pair.second == previous_coords_pair.second) { // placing rocks horizontally
                int64_t min_vertical_coord = std::min(current_coords_pair.first, previous_coords_pair.first), max_vertical_coord = std::max(current_coords_pair.first, previous_coords_pair.first); // getting min/max values, because values can go both ascending and descending
                for (size_t j = min_vertical_coord; j <= max_vertical_coord; ++j) field.at(current_coords_pair.second).at(j) = '#';
            }
        }
    }

    for (size_t i = 0; i != FIELD_SIZE; ++i) field.at(floor_position + 2).at(i) = '#'; // creating floor

    int64_t counter = 0;
    while (true) {
        std::pair<int64_t, int64_t> sand_position = std::make_pair(0, SAND_SOURCE); // one sand unit coords - starting location
        while (true) {
            // if we can go down, then we do it
            if (field.at(sand_position.first + 1).at(sand_position.second) == '.') sand_position.first++;
            else {
                if (field.at(sand_position.first + 1).at(sand_position.second - 1) == '.') sand_position = std::make_pair(sand_position.first + 1, sand_position.second - 1); // go one step down and to the left
                else if (field.at(sand_position.first + 1).at(sand_position.second + 1) == '.') sand_position = std::make_pair(sand_position.first + 1, sand_position.second + 1); // go one step down and to the right
                else { // if a sand unit can't go anywhere

                    // if a sand unit can't go anywhere and stuck at the start
                    if (sand_position.first == 0 && sand_position.second == SAND_SOURCE) {
                        std::cout << counter + 1 << std::endl; // we increase counter by 1, because we also count current sand unit
                        return 0;
                    }

                    field.at(sand_position.first).at(sand_position.second) = 'o';
                    counter++;
                    break;
                }
            }
        }
    }
}