#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include "helpers.hpp"

std::vector<int> parse_file(std::string filename) {
    std::vector<int> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::string> lines;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            auto fishes = split_string(line, ",");
            for (auto &fish : fishes)
                data.push_back(std::stoi(fish));
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}
