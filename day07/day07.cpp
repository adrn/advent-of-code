#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <cmath>
#include <algorithm>
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

void part1(std::vector<int> &crabs) {
    auto x0 = median(crabs);
    std::cout << "Median position: " << x0 << std::endl;

    int fuel_cost = 0;
    for (auto &crab : crabs)
        fuel_cost += std::abs(crab - x0);

    std::cout << "Part 1 answer (fuel cost): " << fuel_cost << std::endl;
}

int func(int x0, std::vector<int> data) {
    int absdx;
    int val = 0;
    for (auto &elem : data) {
        absdx = std::abs(elem - x0);
        val += (absdx * (absdx + 1)) / 2;
    }
    return val;
}

std::vector<int> func(std::vector<int> x0, std::vector<int> data) {
    std::vector<int> funcvals = {};
    for (auto &x0_val : x0)
        funcvals.push_back(func(x0_val, data));
    return funcvals;
}

void part2(std::vector<int> &crabs) {
    // BRUTE FORCE BABY
    auto med = median(crabs);
    auto maxval = std::min((int)crabs.size(), 8 * med);

    std::vector<int> x0s = {};
    for (int x0=med; x0 < maxval; x0++)
        x0s.push_back(x0);

    auto funcvals = func(x0s, crabs);
    auto best_x0_idx = std::min_element(funcvals.begin(), funcvals.end()) - funcvals.begin();
    std::cout << "Best x0: " << x0s[best_x0_idx] << std::endl;
    std::cout << "Part 2 answer (fuel cost): " << func(x0s[best_x0_idx], crabs) << std::endl;
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
    part2(crabs);

}
