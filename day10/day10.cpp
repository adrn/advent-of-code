#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "helpers.hpp"

std::vector<std::string> parse_file(std::string filename) {
    std::vector<std::string> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            data.push_back(line);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}

std::map<std::string, std::tuple<int, int>> count_open_close(
        std::string line,
        std::vector<std::string> pairs
) {
    std::map<std::string, std::tuple<int, int>> counts;

    for (auto &pair : pairs) {
        counts[pair] = {
            std::count(line.begin(), line.end(), pair[0]),
            std::count(line.begin(), line.end(), pair[1])
        };

        std::cout << pair << " " << std::get<0>(counts[pair]) << " " << std::get<1>(counts[pair]) << std::endl;
    }

    return counts;
}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 10 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);
    // print_vector1d(data);

    // Part 1
    std::map<char, int> invalid_scores = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

    std::vector<std::string> incomplete_lines = {};
    bool is_corrupted;
    std::vector<char> invalid = {};
    std::vector<char> queue;
    std::map<char, char> pairs = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    for (auto &line : data) {
        is_corrupted = false;
        queue = {};
        for (auto &ch : line) {
            if (pairs.count(ch) == 1)
                queue.push_back(ch);
            else {
                if (ch == pairs[queue[queue.size()-1]])
                    queue.pop_back();
                else {
                    // std::cout << "INVALID: Expected " << pairs[queue[queue.size()-1]] << " but found " << ch << std::endl;
                    invalid.push_back(ch);
                    is_corrupted = true;
                    break;
                }
            }
        }
        if ((queue.size() > 0) && !is_corrupted)
            incomplete_lines.push_back(line);
    }

    std::cout << data.size() << " " << incomplete_lines.size() << std::endl;

    int score = 0;
    for (auto &ch : invalid)
        score += invalid_scores[ch];
    print_vector1d(invalid);
    std::cout << "Part 1: score = " << score << std::endl;

    std::cout << "--------" << std::endl;

    // Part 2
    std::map<char, int> complete_scores = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

    std::vector<std::string> complete_sequences;
    for (auto &line : incomplete_lines) {
        queue = {};
        for (auto &ch : line) {
            if (pairs.count(ch) == 1)
                queue.push_back(ch);
            else {
                if (ch == pairs[queue[queue.size()-1]])
                    queue.pop_back();
                else {
                    queue.pop_back();
                    complete_sequences.back() += pairs[queue[queue.size()-1]];
                }
            }
        }

        std::string seq = "";
        for (auto &elem : queue)
            seq = pairs[elem] + seq;
        complete_sequences.push_back(seq);
    }

    std::vector<long> scores = {};
    for (auto &seq : complete_sequences) {
        long score = 0;
        for (auto &ch : seq)
            score = score * 5 + complete_scores[ch];
        scores.push_back(score);
    }
    // print_vector1d(complete_sequences);
    // print_vector1d(scores);
    std::cout << "N scores: " << scores.size() << std::endl;

    std::sort(scores.begin(), scores.end());
    std::cout << "Part 2 score: " << scores[scores.size() / 2] << std::endl;

}
