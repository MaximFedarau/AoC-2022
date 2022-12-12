#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node {
    int64_t x;
    int64_t y;
    int64_t distance; // distance from beginning to reach a node
};

int main() {
    std::ifstream file("1.txt");
    std::string input;

    std::vector<std::vector<int64_t>> field; // vector of our heights
    std::vector<int64_t> start(2); // start coords
    std::vector<int64_t> end(2); // end coords

    // creating a field
    int64_t counter = 0;
    while(std::getline(file, input)) {
        std::vector<int64_t> row;
        for (size_t i = 0; i != input.size(); ++i) {
            if (input.at(i) == 'S') {
                start = {counter, static_cast<int64_t>(i)};
                row.push_back(1); // we immediately add heights
            } else if (input.at(i) == 'E') {
                end = {counter, static_cast<int64_t>(i)};
                row.push_back(26); // we immediately add heights
            } else row.push_back(input.at(i) - 96); // lowercase_letter - 96 - its position in alphabet
            
        }
        field.push_back(row);
        ++counter;
    }

    std::vector<bool> visited_row(field.at(0).size(), false);
    std::vector<std::vector<bool>> visited_nodes(counter, visited_row); // vector of visited nodes

    Node start_node = {start.at(0), start.at(1), 0};
    std::vector<Node> nodes = {start_node}; // first node is our start_node (starting point)

    // Dijkstra's algorithm - https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm (Algorithm section)
    // 1) We need to choose the node, which is the closest to the previous one & has minimum distance
    // 2) We check, if current_node is a desired node
    // 3) We check, if we have already visited current_node
    // 4) We get all current_node neighbours and place them in THE BEGINNING (they become the closest in step 1) of the vector
    while (true) {
        // finding an element with the smallest distance - important!
        int64_t min_node_index = 0, min_node_distance = 100000000;
        for (int64_t i = 0; i != nodes.size(); ++i) {
            Node search_node = nodes.at(i);
            if (search_node.distance < min_node_distance) min_node_index = i;
        }
        Node current_node = nodes.at(min_node_index);
        nodes.erase(nodes.begin() + min_node_index); // removing it from nodes, because we are working with it right now


        int64_t current_node_x = current_node.x, current_node_y = current_node.y, current_node_distance = current_node.distance;

        // if our current node is a destination, then we just std::cout our distance
        if (current_node_x == end.at(0) && current_node_y == end.at(1)) {
            std::cout << current_node_distance << std::endl;
            return 0;
        }

        if (visited_nodes.at(current_node_x).at(current_node_y)) continue; // do not check visited node
        visited_nodes.at(current_node_x).at(current_node_y) = true; // we are visiting current node right now

        // checking current_node neighbours
        std::vector<std::vector<int64_t>> possible_coords = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // possible neighbours - top, bottom, left & right neighbours
        for (std::vector<int64_t> coord: possible_coords) {
            int64_t new_x = coord.at(0), new_y = coord.at(1);

            if (current_node_x == 0 && coord == possible_coords.at(0)) continue; // topmost row can't go up
            if (current_node_x == (counter - 1) && coord == possible_coords.at(1)) continue; // the bottom row can't go down
            if (current_node_y == 0 && coord == possible_coords.at(2)) continue; // the left row can't go left
            if (current_node_y == (field.at(0).size() - 1) && coord == possible_coords.at(3)) continue; // the right row can't go right

            Node new_node = {current_node_x + new_x, current_node_y + new_y, current_node_distance + 1};

            // checking heights
            if (field.at(new_node.x).at(new_node.y) - field.at(current_node_x).at(current_node_y) <= 1) nodes.insert(nodes.begin(), new_node); // place neighbour in the beginning of the vector, because this action allows us to choose the closest to current_node node with the minimum distance - important!
        } 
    }
}