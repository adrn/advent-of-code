#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include "helpers.hpp"

std::map<int, std::string> digit_to_signal = {
    {0, "abcefg"},
    {1, "cf"},
    {2, "acdeg"},
    {3, "acdfg"},
    {4, "bcdf"},
    {5, "abdfg"},
    {6, "abcefg"},
    {7, "acf"},
    {8, "abcdefg"},
    {9, "abcdfg"},
};

std::tuple<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
parse_file(std::string filename) {
    std::vector<int> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::vector<std::string>> signal_patterns;
    std::vector<std::vector<std::string>> outputs;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            auto splitsies = split_string(line, "|");
            signal_patterns.push_back(split_string(splitsies[0], " "));
            outputs.push_back(split_string(splitsies[1], " "));
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return {signal_patterns, outputs};
}