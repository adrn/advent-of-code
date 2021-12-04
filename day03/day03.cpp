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

    std::vector<int> counts(row_size, 0);
    for (int i=0; i < num_rows; i++)
        for (int j=0; j < row_size; j++)
            counts[j] += data[i][j];

    std::vector<bool> most_common = {};
    for (int j=0; j < row_size; j++) {
        if (counts[j] >= (num_rows / 2.0)) {
            most_common.push_back(true);
        }
        else if (counts[j] < (num_rows / 2.0))
            most_common.push_back(false);
    }

    return most_common;
}

std::vector<bool> get_least_common(std::vector<std::vector<bool>> data) {
    auto most_common = get_most_common(data);
    for (int i = 0; i < most_common.size(); i++)
        most_common[i] = !(most_common[i]);
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


int get_life_support_component(
    std::vector<std::vector<bool>> data,
    std::function<std::vector<bool>(std::vector<std::vector<bool>>)> func
) {
    // Make a copy of the data to modify (remove rows)
    std::vector<std::vector<bool> > data_copy = data;

    int row_size = data[0].size();
    std::vector<int> to_delete;

    for (int j = 0; j < row_size; j++) {
        auto common = func(data_copy);
        to_delete = {};

        for (int i = 0; i < data_copy.size(); i++)
            if (data_copy[i][j] != common[j])
                to_delete.push_back(i);

        for (int i = to_delete.size() - 1; i >= 0; i--) {
            if (data_copy.size() <= 1)
                break;
            data_copy.erase(data_copy.begin() + to_delete[i]);
        }

        if (data_copy.size() <= 1)
            break;
    }
    return binary_to_decimal(data_copy[0]);
}


void part2(std::vector<std::vector<bool>> data) {
    int oxygen_gen = get_life_support_component(data, &get_most_common);
    int co2_scrub = get_life_support_component(data, &get_least_common);
    std::cout << "Oxygen generator: " << oxygen_gen << std::endl;
    std::cout << "CO2 scrubber: " << co2_scrub << std::endl;
    std::cout << "Part 2 answer: " << oxygen_gen * co2_scrub << std::endl;
}


int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    part1(data);
    part2(data);

}
