#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <cmath>
#include "helpers.hpp"

std::vector<int> parse_file(std::string filename) {
    std::vector<int> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::string> lines;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            auto data_str = split_string(line, ",");
            for (auto &crab : data_str)
                data.push_back(std::stoi(crab));
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}

int median(std::vector<int> &v) {
    // https://stackoverflow.com/questions/1719070/what-is-the-right-approach-when-using-stl-container-for-median-calculation/1719155#1719155
    size_t n = v.size() / 2;
    std::nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}

void part1(std::vector<int> &crabs) {
    auto x0 = median(crabs);
    std::cout << "Median position: " << x0 << std::endl;

    int fuel_cost = 0;
    for (auto &crab : crabs)
        fuel_cost += std::abs(crab - x0);

    std::cout << "Part 1 answer (fuel cost): " << fuel_cost << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 06 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto crabs = parse_file(datafile_path);

    part1(crabs);
    std::cout << "--------" << std::endl;
    // part2(fishies, 256);

}
