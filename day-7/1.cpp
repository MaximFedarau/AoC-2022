#include <iostream>
#include <fstream>
#include <string>
#include <map>

int64_t counter = 0;

struct Dir {
    Dir* parent_dir;
    int64_t size = 0;
    std::map<std::string, Dir> dirs = {};
};

int64_t get_size(Dir dir) {
    if (!dir.dirs.empty()) {
        for (auto [name, subdir]: dir.dirs) {
            int64_t subdir_size = get_size(subdir);
            if (subdir_size <= 100000) counter += subdir_size;
            dir.size += subdir_size;
        }
    }

    return dir.size;
}

int main() {
    std::ifstream file("1.txt");
    std::string line;

    Dir root;
    Dir* current_dir = &root;

    // creating a tree
    while(std::getline(file,line)) {
        bool is_command = line.find("$") != -1;
        
        if (is_command) {
            bool is_change_dir = line.find("cd") != -1;
            if (is_change_dir) {
                std::string dir = line.substr(line.find("cd") + 3, line.length() - 3 - line.find("cd"));
                if (dir == "/") current_dir = &root;
                else if (dir == "..") current_dir = (*current_dir).parent_dir;
                else current_dir = &(*current_dir).dirs[dir];
            }
        } else {
            bool is_dir = line.find("dir") != -1;
            if (is_dir) {
                std::string dir_name = line.substr(line.find("dir") + 4, line.length() - line.find("dir") - 4);
                Dir new_dir;
                new_dir.parent_dir = current_dir;
                (*current_dir).dirs.insert({dir_name, new_dir});
            } else {
                std::string file_size = line.substr(0, line.find(" "));
                (*current_dir).size += stoi(file_size);
            }
        }
    }

    get_size(root);
    std::cout << counter << std::endl;
}