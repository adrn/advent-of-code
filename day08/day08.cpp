#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "day08.hpp"

void part1(std::vector<EncodedDigits> outputs) {
    auto unq_length_map = get_unique_length_digit_map();
    std::vector<int> unq_lengths;
    std::vector<int> unq_length_digits;
    for (auto const& [key, val] : unq_length_map) {
        unq_lengths.push_back(key);
        unq_length_digits.push_back(val);
    }

    int counter = 0;
    for (int i=0; i < outputs.size(); i++) {
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

void part2(std::vector<EncodedDigits> signal_patterns, std::vector<EncodedDigits> outputs) {
    std::vector<int> digits;
    int sum = 0;

    for (int i=0; i < signal_patterns.size(); i++) {
        digits = {};
        auto decoder = get_decoder(signal_patterns[i]);
        for (auto &elem : outputs[i])
            digits.push_back(decoder[elem]);
        std::cout << vector_to_int(digits) << std::endl;
        sum += vector_to_int(digits);
    }
    std::cout << "Part 2 answer: " << sum << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 08 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto [signal_patterns, outputs] = parse_file(datafile_path);

    // print_vector2d(signal_patterns);
    // print_vector2d(outputs);

    part1(outputs);
    std::cout << "--------" << std::endl;
    part2(signal_patterns, outputs);

}
