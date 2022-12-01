#include <iostream>
#include <vector>
#include <string>

int main() {

   uint64_t answer = 0, counter = 0, ans[3] = {0,0,0};

    while (true) {
        std::string input;
        getline(std::cin, input); // get full line including spaces

        if (input.length() == 0) {
            if (counter > ans[0]) {
                if (ans[0] > ans[1]) {
                    if (ans[1] > ans[2]) ans[2] = ans[1];
                    ans[1] = ans[0];
                }
                ans[0] = counter;
            }
            else if (counter > ans[1]) {
                if (ans[1] > ans[2]) ans[2] = ans[1];
                ans[1] = counter;
            }
            else if (counter > ans[2]) ans[2] = counter;
            counter = 0; 
            std::cout << ans[0] + ans[1] + ans[2] << std::endl; // outputs answer after every block
        } else counter += std::stoi(input); // converting string to int
    }

    return 0;
}