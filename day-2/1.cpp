#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    uint64_t counter = 0;
    std::map <std::string, uint64_t> scores = {{"X", 1}, {"Y", 2}, {"Z", 3}};
    std::map <std::string, std::string> symbols = {{"X", "A"}, {"Y", "B"}, {"Z", "C"}};
    while (true) {
        std::string a,b;
        std::cin >> a >> b;

        if (a == symbols[b]) counter += 3;

        if (a == "A") {
            if (b == "Y") counter += 6;
        }
        else if (a == "B") {
            if (b == "Z") counter += 6;
        } else if (a == "C") {
            if (b == "X") counter += 6;
        }
        counter += scores[b];

        std::cout << counter << std::endl; // outputs answer after every block
    }
}