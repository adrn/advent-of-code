#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <charconv>
#include <algorithm>
#include <set>
#include "helpers.hpp"

#define underline "\033[4m"
#define offline "\033[0m"
#define MAXITER 128

std::vector<std::vector<int>> parse_file(std::string filename) {
    std::vector<std::vector<int>> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            std::vector<int> row = {};
            for (char &char_ : line)
                // std::cout << char_ << std::endl;
                row.push_back(((int)char_) - 48);
            data.push_back(row);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}

std::vector<std::tuple<int, int>> get_neighborhood(int i1, int i2, int size1, int size2) {
    std::vector<std::tuple<int, int>> neighbors = {};
    for (int i=i1-1; i <= (i1+1); i++)
        for (int j=i2-1; j <= (i2+1); j++) {
            if (
                ((i == i1) || (j == i2)) &&
                (i >= 0) && (j >= 0) && (i <= (size1-1)) && (j <= (size2-1))
            ) {
                neighbors.push_back({i, j});
            }
        }
    return neighbors;
}

std::set<std::tuple<int, int>> find_minima(std::vector<std::vector<int>> &data) {
    auto size1 = data.size();
    auto size2 = data[0].size();

    std::set<std::tuple<int, int>> intersect;

    std::set<std::tuple<int, int>> minima = {};
    for (int i=0; i < size1; i++) {
        for (int j=0; j < size2; j++) {
            if (data[i].size() != size2)
                std::cout << "ERROR" << std::endl; // TODO: throw exception?
            minima.insert({i, j});
        }
    }

    int iter = 0;
    int minima_size = minima.size();
    auto past_minima = minima;

    for (int iter=0; iter < MAXITER; iter++) {
        std::cout << "iter: " << iter << std::endl;
        minima = {};
        for (auto [i, j] : past_minima) {
            auto nbidx = get_neighborhood(i, j, size1, size2);

            std::vector<int> vals = {};
            for (auto [i1, i2] : nbidx)
                vals.push_back(data[i1][i2]);
            auto min_idx = std::min_element(vals.begin(), vals.end()) - vals.begin();

            if (std::count(vals.begin(), vals.end(), vals[min_idx]) > 1)
                continue;

            minima.insert(nbidx[min_idx]);
        }

        intersect = {};
        intersect = custom_intersect(past_minima, minima);
        if (intersect.size() == past_minima.size())
            break;

        past_minima = minima;
    }

    return minima;
}

std::set<std::tuple<int, int>> get_basin(
    std::vector<std::vector<int>> &data,
    std::tuple<int, int> minimum
) {
    auto size1 = data.size();
    auto size2 = data[0].size();

    int prev_size;

    std::set<std::tuple<int, int>> basin_idx = {minimum};
    for (int iter=0; iter < MAXITER; iter++) {
        // std::cout << "iter: " << iter << std::endl;

        prev_size = basin_idx.size();
        auto prev_basin_idx = basin_idx;
        for (auto [i, j] : prev_basin_idx) {
            auto nbidx = get_neighborhood(i, j, size1, size2);

            for (auto [k, l] : nbidx) {
                if (data[k][l] < 9)
                    basin_idx.insert({k, l});
            }
        }

        if (basin_idx.size() == prev_size)
            break;

        prev_size = basin_idx.size();
    }

    return basin_idx;
}

std::set<std::tuple<int, int>> part1(std::vector<std::vector<int>> data) {
    auto minima = find_minima(data);
    std::cout << "There are " << minima.size() << " low points." << std::endl;

    int risk_level_sum = 0;
    for (auto [i, j] : minima)
        risk_level_sum += data[i][j] + 1;

    std::cout << "Part 1: Sum of risk levels: " << risk_level_sum << std::endl;

    return minima;
}

void part2(std::vector<std::vector<int>> data, std::set<std::tuple<int, int>> minima) {
    std::set<std::tuple<int, int>> basin;

    std::vector<int> basin_sizes = {};
    for (auto &min : minima) {
        basin = get_basin(data, min);
        basin_sizes.push_back(basin.size());
        // for (auto [i, j] : basin)
        //     std::cout << i << " " << j << std::endl;
    }

    std::sort(basin_sizes.begin(), basin_sizes.end(), std::greater<int>());
    print_vector1d(basin_sizes);

    std::cout << "Part 2: " << basin_sizes[0] * basin_sizes[1] * basin_sizes[2] << std::endl;

}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 09 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    auto minima = part1(data);
    // for (int i=0; i < data.size(); i++) {
    //     for (int j=0; j < data[i].size(); j++) {
    //         if (minima.count({i, j}) > 0)
    //             std::cout << underline;
    //         std::cout << data[i][j] << offline;
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << "--------" << std::endl;
    part2(data, minima);
}
