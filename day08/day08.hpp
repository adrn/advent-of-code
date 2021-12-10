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

typedef std::vector<std::string> EncodedDigits;

std::tuple<std::vector<EncodedDigits>, std::vector<EncodedDigits>>
parse_file(std::string filename) {
    std::vector<int> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<EncodedDigits> signal_patterns;
    std::vector<EncodedDigits> outputs;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            auto splitsies = split_string(line, "|");

            auto pattern = split_string(splitsies[0], " ");
            for (auto &elem : pattern)
                std::sort(elem.begin(), elem.end());

            signal_patterns.push_back(pattern);

            auto output = split_string(splitsies[1], " ");
            for (auto &elem : output)
                std::sort(elem.begin(), elem.end());
            outputs.push_back(output);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return {signal_patterns, outputs};
}

std::map<int, int> get_unique_length_digit_map() {
    // First, find the unique numbers by length:
    std::vector<int> digit_signal_lengths;
    for (auto const& [key, val] : digit_to_signal)
        digit_signal_lengths.push_back(val.length());
    // print_vector1d(digit_signal_lengths);

    std::map<int, int> length_counts;
    int i, shit;
    for (i=0; i < digit_signal_lengths.size(); i++)
        length_counts[digit_signal_lengths[i]] = 0;
    for (i=0; i < digit_signal_lengths.size(); i++)
        length_counts[digit_signal_lengths[i]] += 1;

    std::map<int, int> unq_map;
    for (i=0; i < digit_signal_lengths.size(); i++) {
        auto len = digit_signal_lengths[i];
        if (length_counts[len] == 1)
            unq_map[len] = i;
    }
    return unq_map;
}

std::map<std::string, int> get_decoder(EncodedDigits signal_patterns) {
    std::map<std::string, int> decoder;
    std::map<int, std::string> encoder;

    auto unq_digit_map = get_unique_length_digit_map();
    for (auto &elem : signal_patterns) {
        if (unq_digit_map.find(elem.size()) != unq_digit_map.end()) {
            decoder[elem] = unq_digit_map[elem.size()];
            encoder[unq_digit_map[elem.size()]] = elem;
        }
    }
    // 1, 4, 7, 8 identified

    std::string intersect1, intersect2, intersect4, intersect7, intersect8;

    // Identify 9 from intersection with 4 and 7:
    for (auto &pattern : signal_patterns) {
        intersect4 = "";
        intersect7 = "";
        std::set_intersection(encoder[4].begin(), encoder[4].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect4));
        std::set_intersection(encoder[7].begin(), encoder[7].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect7));
        if ((intersect4.size() == 4) && (intersect7.size() == 3)
                && (decoder.find(pattern) == decoder.end())) {
            decoder[pattern] = 9;
            encoder[9] = pattern;
        }
    }
    // 1, 4, 7, 8, 9 identified

    // Identify 0 from intersection with 1 and 8:
    for (auto &pattern : signal_patterns) {
        intersect1 = "";
        intersect8 = "";
        std::set_intersection(encoder[1].begin(), encoder[1].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect1));
        std::set_intersection(encoder[8].begin(), encoder[8].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect8));
        if ((intersect1.size() == 2) && (intersect8.size() == 6)
                && (decoder.find(pattern) == decoder.end())) {
            decoder[pattern] = 0;
            encoder[0] = pattern;
        }
    }
    // 0, 1, 4, 7, 8, 9 identified

    // Identify 2 from intersection with 4
    for (auto &pattern : signal_patterns) {
        intersect4 = "";
        std::set_intersection(encoder[4].begin(), encoder[4].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect4));
        if ((intersect4.size() == 2) && (decoder.find(pattern) == decoder.end())) {
            decoder[pattern] = 2;
            encoder[2] = pattern;
        }
    }
    // 0, 1, 2, 4, 7, 8, 9 identified

    // Identify 3 from intersection with 2 and 1
    for (auto &pattern : signal_patterns) {
        intersect1 = "";
        intersect2 = "";
        std::set_intersection(encoder[1].begin(), encoder[1].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect1));
        std::set_intersection(encoder[2].begin(), encoder[2].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect2));
        if ((intersect1.size() == 2) && (intersect2.size() == 4)
                && (decoder.find(pattern) == decoder.end())) {
            decoder[pattern] = 3;
            encoder[3] = pattern;
        }
    }
    // 0, 1, 2, 3, 4, 7, 8, 9 identified

    // Identify 5 from intersection with 8
    for (auto &pattern : signal_patterns) {
        intersect8 = "";
        std::set_intersection(encoder[8].begin(), encoder[8].end(),
                              pattern.begin(), pattern.end(),
                              std::back_inserter(intersect8));
        if ((intersect8.size() == 5) && (decoder.find(pattern) == decoder.end())) {
            decoder[pattern] = 5;
            encoder[5] = pattern;
        }
    }
    // 0, 1, 2, 3, 4, 5, 7, 8, 9 identified

    // Identify 6 as the last one
    for (auto &pattern : signal_patterns) {
        if (decoder.find(pattern) == decoder.end()) {
            decoder[pattern] = 6;
            encoder[6] = pattern;
        }
    }

    return decoder;
}
