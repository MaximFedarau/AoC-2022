#include <iostream>
#include <fstream> // file input
#include <string>
#include <utility> // for std::pair
#include <vector>
#include <algorithm>

// check is string is an array (if isArray returns false, it means that input is a number)
bool isArray(std::string input) {
    int64_t open_brackets_counter = 0, close_brackets_counter = 0;
    for (size_t i = 0; i != input.size(); ++i) {
        if (input.at(i) == '[') open_brackets_counter++;
        if (input.at(i) == ']') close_brackets_counter++;

        // if arrays is "closed" and there is at least one bracket 
        if (open_brackets_counter == close_brackets_counter && close_brackets_counter != 0 && open_brackets_counter != 0) return true;
    }
    return false;
}

// create array from number
std::string createArray(std::string input) {
    return "[" + input + "]";
}

// get indices of all array elements
std::vector<std::pair<int64_t, int64_t>> getArrayElements(std::string input) {
    std::vector<std::pair<int64_t, int64_t>> ans;
    int64_t open_brackets_counter = 0, close_brackets_counter = 0, start_index = 1;
    for (int64_t i = 1; i < input.size() - 1; ++i) {
        if (input.at(i) == '[') open_brackets_counter++;
        if (input.at(i) == ']') close_brackets_counter++;

        // if we reached a , or the end of the input
        if (open_brackets_counter == close_brackets_counter && ((i == input.size() - 2) || input.at(i) == ',')) {
            std::pair<int64_t, int64_t> element_coords = std::make_pair(start_index, i == input.size() - 2 ? i + 1 : i ); // if we reached the end, we count its index
            ans.push_back(element_coords);
            start_index = i + 1; // new start index(exclude ,)
            open_brackets_counter = 0;
            close_brackets_counter = 0;
        }
    } 
    return ans;
}

// comparing input elements, i.e. rules implementation
int64_t compare(std::string first, std::string second) {
    // both values are numbers
    if (!isArray(first) && !isArray(second)) {
        int64_t first_number = stoi(first), second_number = stoi(second); // convert to numbers
        if (first_number < second_number) return 1; // true
        if (first_number > second_number) return 0; // false
        return 2; // continue
    } else if (isArray(first) && isArray(second)) { // if both values are arrays
        std::vector<std::pair<int64_t, int64_t>> first_elements_coords = getArrayElements(first), second_elements_coords = getArrayElements(second); // get array elements coords

        // quantity of all array elements
        int64_t first_elements_size = first_elements_coords.size(), second_elements_size = second_elements_coords.size();

        for (int64_t i = 0; i < std::min(first_elements_size, second_elements_size); ++i) {
            std::pair<int64_t, int64_t> first_element_coords = first_elements_coords.at(i), second_element_coords = second_elements_coords.at(i);
            std::string first_element = first.substr(first_element_coords.first, first_element_coords.second - first_element_coords.first), second_element = second.substr(second_element_coords.first, second_element_coords.second - second_element_coords.first);
            int64_t result = compare(first_element, second_element);

            if (result != 2) return result; // according to the example, 1 result (false or true) is enough
        }

        // сheck elements quantity
        if (first_elements_size < second_elements_size) return 1; // true
        if (first_elements_size > second_elements_size) return 0; // false
        if (first_elements_size == second_elements_size) return 2; // continue
    } else { // if both first & second are not of the same type
        std::string modified_first = !isArray(first) ? createArray(first) : first, modified_second = !isArray(second) ? createArray(second) : second; // if first or second is a number, then convert it to an array
        int64_t result = compare(modified_first, modified_second);
        return result;
    }
}

int main() {
    std::ifstream file("2.txt");
    std::string input;

    std::vector<std::string> inputs = {"[[2]]", "[[6]]"}; // all our inputs
    std::string first, second;
    while(std::getline(file, input)) {
        if (first.empty()) first = input;
        else if (second.empty()) second = input;

        if (!first.empty() && !second.empty() && input.size() == second.size()) {
            inputs.push_back(first);
            inputs.push_back(second);
        }

        if (!input.size()) {
            first.clear();
            second.clear();
        }
    }
    struct {
        bool operator()(std::string a, std::string b) const { 
            if (compare(a,b) == 1) return true; // if a > b
            else return false; // if a == b or if a < b
         }
    } sortComparison; // comparison method
    std::sort(inputs.begin(), inputs.end(), sortComparison);

    std::vector<int64_t> divider_coords;
    for (int64_t i = 0; i != inputs.size(); ++i) {
        if (inputs.at(i) == "[[2]]" || inputs.at(i) == "[[6]]") divider_coords.push_back(i + 1); 
    }
    std::cout << divider_coords.at(0) * divider_coords.at(1) << std::endl;
}