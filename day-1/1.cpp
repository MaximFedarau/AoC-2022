#include <iostream>
#include <vector>
#include <string>

int main() {

    uint64_t answer = 0, counter = 0;

    while (true) {
        std::string input;
        getline(std::cin, input); // get full line including spaces

        if (input.length() == 0) {
            answer = std::max(answer, counter);
            counter = 0;
            std::cout << answer << std::endl; // outputs answer after every block
        } else counter += std::stoi(input); // converting string to int
    }

    return 0;
}