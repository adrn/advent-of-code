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
        if (counts[j] >= (num_rows / 2.0))
            most_common.push_back(true);
        else if (counts[j] < (num_rows / 2.0))
            most_common.push_back(false);
    }

    return most_common;
}

std::vector<bool> get_least_common(std::vector<std::vector<bool>> data) {
    auto most_common = get_most_common(data);
    for (int i = 0; i < most_common.size(); i++)
        most_common[i] = !most_common[i];
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


void part2(std::vector<std::vector<bool>> data) {
    std::vector<std::vector<bool> > data_copy = data;

    int row_size = data[0].size();
    std::vector<int> to_delete;

    for (int j = 0; j < row_size; j++) {
    // for (int j = 0; j < 3; j++) {
        // auto most_common = get_most_common(data_copy);
        auto most_common = get_least_common(data_copy);
        to_delete = {};

        std::cout << "most common: " << std::endl;
        for (auto elem : most_common) {
            std::cout << elem << " ";
        }
        std::cout << std::endl << std::endl;

        for (int i = 0; i < data_copy.size(); i++) {
            if (data_copy[i][j] != most_common[j]) {
                std::cout << "i=" << i << "  j=" << j;
                std::cout << "  data_copy=" << data_copy[i][j] << "  most_common=" << most_common[j] << std::endl;
                to_delete.push_back(i);
            }
        }

        for (int i = to_delete.size() - 1; i >= 0; i--) {
            std::cout << "delete: " << to_delete[i] << std::endl;
            if (data_copy.size() <= 1)
                break;
            data_copy.erase(data_copy.begin() + to_delete[i]);
        }

        for (auto vec : data_copy) {
            for (auto elem : vec) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "------" << std::endl << std::endl;

        if (data_copy.size() <= 1)
            break;
    }

    // for (auto elem : to_delete) {
    //     std::cout << "to delete: " << elem << std::endl;
    // }

    // std::vector<bool> least_common = {};
    // for (auto elem : most_common)
    //     least_common.push_back(!elem);

    // int gamma = binary_to_decimal(most_common);
    // int epsilon = binary_to_decimal(least_common);

    // std::cout << "Part 1 answer: " << gamma * epsilon << std::endl;
}


int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    // part1(data);
    part2(data);

}
