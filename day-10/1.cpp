#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("1.txt");
    std::string input;

    int64_t finished_cycles_counter = 0, ans = 0,  x = 1, signal_point = 20;

    while (std::getline(file, input)) {
        if (input.size() == 4) { // if noop
            if (finished_cycles_counter + 1 == signal_point) { // if processing key (20th, 60th, ...) cycle
                ans += signal_point * x;
                signal_point += 40;
            }
            finished_cycles_counter++; // cycle has ended
        }
        else {
            int64_t change = stoi((input.substr(5, input.size() - 5)));
            
            for (int64_t i = 0; i < 2; ++i) {
                if (finished_cycles_counter + 1 == signal_point) { // if processing key (20th, 60th, ...) cycle
                    ans += signal_point * x;
                    signal_point += 40;
                }
                finished_cycles_counter++;
            }

            x += change;
        }
    }

    std::cout << ans << std::endl;
}