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

void part1(std::vector<int> &crabs) {
    auto x0 = median(crabs);
    std::cout << "Median position: " << x0 << std::endl;

    int fuel_cost = 0;
    for (auto &crab : crabs)
        fuel_cost += std::abs(crab - x0);

    std::cout << "Part 1 answer (fuel cost): " << fuel_cost << std::endl;
}

std::vector<int> func(int x0, std::vector<int> data) {
    int dx, absdx;
    std::vector<int> res = {0, 0};

    for (auto &x : data) {
        dx = x - x0;
        absdx = std::abs(dx);
        res[0] += absdx * (absdx - 1) / 2;
        res[1] += -dx + 0.5 * sign(dx);
    }

    return res;
}

void part2(std::vector<int> &crabs) {
    // std::cout << "Median position: " << x0 << std::endl;
    auto x0 = median(crabs);
    auto opt_x = simple_minimize(&func, x0, crabs, 1000, 1e-4);
    auto fuel_cost = func(opt_x, crabs);
    std::cout << "result=" << opt_x << std::endl;
    std::cout << "fuel cost=" << (int)fuel_cost[0] << std::endl;
    return;

    // int fuel_cost = 0;
    // for (auto &crab : crabs)
    //     fuel_cost += std::abs(crab - x0);

    // std::cout << "Part 1 answer (fuel cost): " << fuel_cost << std::endl;
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
