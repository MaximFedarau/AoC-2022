#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    uint64_t counter = 0;

    while (true) {
        std::string a,b,c;
        std::cin >> a >> b >> c;

        for (char symbol: a) {
            bool isExists = false;
            for (char check_symbol: b) {
                if (symbol == check_symbol) isExists = true;
            }

            if (!isExists) continue;

            for (char check_symbol: c) {
                if (symbol == check_symbol) {
                    // using this table: https://en.cppreference.com/w/cpp/language/ascii
                    if (symbol >= 'A' && symbol <= 'Z') counter += symbol - 38;
                    else if (symbol >= 'a' && symbol <= 'z') counter += symbol - 96;
                    goto END; // if we found a common symbol, then we should break all loops
                }
            }
        }

        END:
        std::cout << counter << std::endl; // outputs answer after every block
    }
}