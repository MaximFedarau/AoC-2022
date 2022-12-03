#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    uint64_t counter = 0;

    while (true) {
        std::string input;
        std::cin >> input;

        std::string compartment1 = input.substr(0, input.length() / 2); // first half of the string
        std::string compartment2 = input.substr(input.length() / 2, input.length() + 1); // second half of the string
        for (char symbol: compartment1) {
            for (char symbol2: compartment2) {
                    if (symbol == symbol2) {
                        // using this table: https://en.cppreference.com/w/cpp/language/ascii
                        if (symbol >= 'A' && symbol <= 'Z') counter += symbol - 38;
                        else if (symbol >= 'a' && symbol <= 'z') counter += symbol - 96;
                        goto END; // if we found a duplicate, then we should break all loops
                    }
            }
        }
        END:
        std::cout << counter << std::endl; // outputs answer after every block
    }
}