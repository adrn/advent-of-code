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

std::set<std::tuple<int, int>> find_minima(std::vector<std::vector<int>> data) {
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

    for (int iter=0; iter < 100; iter++) {
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

            // std::cout << "shite" << min_idx << std::endl;
            minima.insert(nbidx[min_idx]);
            // break;
        }

        intersect = {};
        intersect = custom_intersect(past_minima, minima);
        // std::cout << "intersect: " << intersect.size() << " past: " << past_minima.size() << std::endl;
        if (intersect.size() == past_minima.size())
            break;

        past_minima = minima;
    }

    return minima;
}

void part1(std::vector<std::vector<int>> data) {
    auto minima = find_minima(data);
    std::cout << "There are " << minima.size() << " low points." << std::endl;
    // for (auto [i1, i2] : minima)
    //     std::cout << i1 << ", " << i2 << std::endl;

    int risk_level_sum = 0;
    for (auto [i, j] : minima)
        risk_level_sum += data[i][j] + 1;

    std::cout << "Sum of risk levels: " << risk_level_sum << std::endl;

    for (int i=0; i < data.size(); i++) {
        for (int j=0; j < data[i].size(); j++) {
            if (minima.count({i, j}) > 0)
                std::cout << underline;
            std::cout << data[i][j] << offline;
        }
        std::cout << std::endl;
    }
}

// void part2(std::vector<EncodedDigits> signal_patterns, std::vector<EncodedDigits> outputs) {
//     std::vector<int> digits;
//     int sum = 0;

//     for (int i=0; i < signal_patterns.size(); i++) {
//         digits = {};
//         auto decoder = get_decoder(signal_patterns[i]);
//         for (auto &elem : outputs[i])
//             digits.push_back(decoder[elem]);
//         std::cout << vector_to_int(digits) << std::endl;
//         sum += vector_to_int(digits);
//     }
//     std::cout << "Part 2 answer: " << sum << std::endl;
// }

int main(int argc, char** argv) {
    std::cout << "---------------- Day 09 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);
    // print_vector2d(data);

    // auto fuck = get_neighbors(9, 8, 10, 10);
    // std::cout << fuck.size() << std::endl;

    // std::cout << std::endl;
    // for (auto [i, j] : fuck)
    //     std::cout << i << " " << j << std::endl;

    part1(data);
    // std::cout << "--------" << std::endl;
    // part2(signal_patterns, outputs);

}
