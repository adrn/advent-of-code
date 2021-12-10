#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "day08.hpp"

void part1(std::vector<std::vector<std::string>> outputs) {
    // First, we figure out which digits have unique lengths:
    std::vector<int> digit_signal_lengths;
    for (auto const& [key, val] : digit_to_signal)
        digit_signal_lengths.push_back(val.length());
    print_vector1d(digit_signal_lengths);

    std::map<int, int> length_counts;
    int i, shit;
    for (i=0; i < digit_signal_lengths.size(); i++)
        length_counts[digit_signal_lengths[i]] = 0;
    for (i=0; i < digit_signal_lengths.size(); i++)
        length_counts[digit_signal_lengths[i]] += 1;

    std::vector<int> unq_length_digits;
    std::vector<int> unq_lengths;
    for (i=0; i < digit_signal_lengths.size(); i++) {
        auto len = digit_signal_lengths[i];
        if (length_counts[len] == 1) {
            unq_length_digits.push_back(i);
            unq_lengths.push_back(len);
        }
    }

    int counter = 0;
    for (i=0; i < outputs.size(); i++) {
        for (int j=0; j < outputs[i].size(); j++) {
            if (std::count(unq_lengths.begin(),
                           unq_lengths.end(),
                           outputs[i][j].size())) {
                // std::cout << outputs[i][j] << std::endl;
                counter++;
            }
        }
    }
    print_vector1d(unq_length_digits);
    std::cout << counter << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 07 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto [signal_patterns, outputs] = parse_file(datafile_path);

    // print_vector2d(signal_patterns);
    // print_vector2d(outputs);

    part1(outputs);
    // std::cout << "--------" << std::endl;
    // part2(crabs);

}
