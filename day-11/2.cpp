#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Monkey {
    std::vector<unsigned long long> items;
    std::string operation;
    unsigned long long test_number;
    std::vector<unsigned long long> monkeys_list;
};

int main() {
    std::ifstream file("2.txt");
    std::string input;

    std::vector<Monkey> monkeys;
   
    unsigned long long monkey_index = 0;
    while(std::getline(file, input)) {
        if (input.find("Monkey") != -1) {
            Monkey monkey;
            monkeys.push_back(monkey);
            monkey_index = stoi(input.substr(7, input.size() - 2));
        }

        Monkey* monkey = &monkeys.at(monkey_index);

        if (input.find("items") != -1) {
            std::vector<unsigned long long> items;
            std::string items_input = input.substr(18);
            while (items_input.find(",") != -1) {
                items.push_back(stoi(items_input.substr(0, items_input.find(","))));
                items_input = items_input.substr(items_input.find(",") + 2);
            }
            items.push_back(stoi(items_input));
            (*monkey).items = items;
        }

        if (input.find("Operation") != -1) (*monkey).operation = input.substr(19);

        if (input.find("Test") != -1) (*monkey).test_number = stoi(input.substr(21));

        if (input.find("true") != -1) (*monkey).monkeys_list.push_back(stoi(input.substr(29)));
        if (input.find("false") != -1) (*monkey).monkeys_list.push_back(stoi(input.substr(30)));

        if (input.size() == 0) monkey_index = 0;
    }

    std::vector<unsigned long long> counters_array(monkeys.size(), 0);
    unsigned long long general_remainder = 1;
    for (Monkey monkey: monkeys) {
        general_remainder *= monkey.test_number;
    }

    // * About general_remainder - from AoC subreddit
    // * You have to notice, that the division on the items are actually operations on the ITEM/(2x3x5x7x11x13x19) - prime numbers, ring. So basically you can use as an item the value item modulo 2x3x5x7x11x13x19.

    for (unsigned long long i = 0; i < 10000; ++i) { // 20 rounds
        for (unsigned long long j = 0; j != monkeys.size(); ++j) {
            Monkey* original_monkey = &monkeys.at(j);
            Monkey* true_monkey = &monkeys.at((*original_monkey).monkeys_list.at(0)); 
            Monkey* false_monkey = &monkeys.at((*original_monkey).monkeys_list.at(1));
            counters_array.at(j) += (*original_monkey).items.size();

            std::string sign = (*original_monkey).operation.substr(4,1);

            for (unsigned long long x = 0; x != (*original_monkey).items.size(); ++x) {
                unsigned long long item = (*original_monkey).items.at(x), operation_member = (*original_monkey).operation.substr(6) == "old" ? item : stoll((*original_monkey).operation.substr(6));

                if (sign == "+") item += operation_member;
                if (sign == "*") item *= operation_member;

                unsigned long long test_number = (*original_monkey).test_number;
 
                item %= general_remainder; // ! very important
                if (item % test_number == 0) {
                    (*true_monkey).items.push_back(item);
                } else {
                    (*false_monkey).items.push_back(item);
                }
            }
            (*original_monkey).items.clear(); // we throw all our items
        }
    }

    sort(counters_array.rbegin(), counters_array.rend()); // sort in reverse way

    std::cout << counters_array.at(0) * counters_array.at(1) << std::endl;
}