#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    uint64_t counter = 0;
    std::string input;
    
    while (getline(std::cin, input)) {
        uint64_t comma_index = input.find_first_of(","); // find index of , in input
        uint64_t first_interval_index = input.find_first_of("-"); // find index of the first - in input
        uint64_t second_interval_index = input.find_last_of("-"); // find index of the last - in input

        uint64_t a = stoi(input.substr(0,first_interval_index)); // get first number and convert it to int
        uint64_t b = stoi(input.substr(first_interval_index + 1, comma_index - (first_interval_index + 1))); // get second number and convert it to int
        uint64_t c = stoi(input.substr(comma_index + 1,second_interval_index - (comma_index + 1))); // get third number and convert it to int
        uint64_t d = stoi(input.substr(second_interval_index+1, input.length() + 1)); // get last number and convert it to int
 
        if ((c >= a && d <= b  && c <= b) || (a >= c && a <= d && b <= d)) counter++;

    }

    std::cout << counter << std::endl;
}