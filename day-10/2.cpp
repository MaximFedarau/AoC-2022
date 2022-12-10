#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("2.txt");
    std::string input;

    int64_t x = 1;
    std::string line = "";

    while (std::getline(file, input)) {
        if (input.size() == 4) { // if noop
            // x can possibly be negative, so we transform size_t to int64_t
            if (static_cast<int64_t>(line.size()) >= x - 1 && static_cast<int64_t>(line.size()) <= x+1) line += "#";
            else line += ".";

            if (line.size() == 40) {
                std::cout << line << std::endl;
                line = "";
            }
        }
        else {
            int64_t change = stoi((input.substr(5, input.size() - 5)));
            
            for (int64_t i = 0; i < 2; ++i) {
                if (static_cast<int64_t>(line.size()) >= x - 1 && static_cast<int64_t>(line.size()) <= x+1) line += "#";
                else line += ".";

                if (line.size() == 40) {
                    std::cout << line << std::endl;
                    line = "";
                }
            }

            x += change;
        }
    }
}