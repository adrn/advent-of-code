#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include "helpers.hpp"

std::vector<std::vector<int>> parse_file(std::string filename) {
    std::vector<std::vector<int>> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::string> lines;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            std::vector<int> row = {};

            auto str_coords = split_string(line, "->");
            for (auto str_coord : str_coords)
                for (auto token : split_string(str_coord, ","))
                    row.push_back(std::stoi(token));
            data.push_back(row);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}
