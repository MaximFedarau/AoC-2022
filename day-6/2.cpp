#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main() {
    std::ifstream input ("2.txt");
    std::string line;
    getline(input, line);

    for (int64_t i = 0; i <= line.size() - 14; i++) {
        std::string substring = line.substr(i, 14);
        std::set<char> elements_set(substring.begin(), substring.end());
        
        if (substring.size() == elements_set.size()) {
            std::cout << i + 14 << std::endl;
            return 0;
        }
    }
}