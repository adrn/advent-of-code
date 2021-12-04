#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <stdexcept>
#include <cmath>


std::vector<std::vector<bool>> parse_file(std::string filename) {
    std::vector<std::vector<bool>> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::string> lines;
    std::string line;

    bool a;
    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            std::vector<bool> row = {};
            for(char& c : line)
                row.push_back(std::stoi(std::string(1, c)));
            data.push_back(row);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}

std::vector<bool> get_most_common(std::vector<std::vector<bool>> data) {
    unsigned int num_rows = data.size();
    if (num_rows == 0)
        throw std::runtime_error("Invalid data! No rows found.");

    unsigned int row_size = data[0].size();

    std::vector<int> counts(num_rows, 0);
    for (int i=0; i < num_rows; i++)
        for (int j=0; j < row_size; j++)
            counts[j] += data[i][j];

    std::vector<bool> most_common = {};
    for (int j=0; j < row_size; j++) {
        if (counts[j] > num_rows/2)
            most_common.push_back(true);
        else if (counts[j] < num_rows/2)
            most_common.push_back(false);
        else
            throw std::runtime_error("Both bits equally likely and I didn't account for that!");
    }

    return most_common;
}


int binary_to_decimal(std::vector<bool> binary) {
    int num = 0;
    int j;
    for (int i=0; i < binary.size(); i++) {
        j = binary.size() - 1 - i;
        if (binary[j])
            num += std::pow(2, i);
    }
    return num;
}


void part1(std::vector<std::vector<bool>> data) {
    auto most_common = get_most_common(data);

    std::vector<bool> least_common = {};
    for (auto elem : most_common)
        least_common.push_back(!elem);

    int gamma = binary_to_decimal(most_common);
    int epsilon = binary_to_decimal(least_common);

    std::cout << "Part 1 answer: " << gamma * epsilon << std::endl;
}


int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    part1(data);

}
