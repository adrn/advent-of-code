#include <Eigen/Sparse>
#include <vector>
#include <iostream>
#include "day05.hpp"


typedef Eigen::SparseMatrix<int> SpMat;

void add_line_to_grid(std::vector<int> &data_row, SpMat &grid) {
    int i, j, start, end;
    if (data_row[0] == data_row[2]) {
        // Vertical line
        i = data_row[0];
        start = std::min(data_row[1], data_row[3]);
        end = std::max(data_row[1], data_row[3]) + 1;
        for (j = start; j < end; j++)
            grid.coeffRef(j, i) += 1;

    } else if (data_row[1] == data_row[3]) {
        // Horizontal line
        j = data_row[1];
        start = std::min(data_row[0], data_row[2]);
        end = std::max(data_row[0], data_row[2]) + 1;
        for (i = start; i < end; i++)
            grid.coeffRef(j, i) += 1;
    }
}

void part1(std::vector<std::vector<int>> data) {
    int grid_size = max(data) + 1;
    print_vector2d<int>(data);
    std::cout << "grid size: " << grid_size << std::endl;

    SpMat grid(grid_size, grid_size);

    for (auto row : data)
        add_line_to_grid(row, grid);

    std::cout << grid << std::endl;

    int num_2s = 0;
    for (int i=0; i < grid_size; i++)
        for (int j=0; j < grid_size; j++)
            num_2s += (grid.coeff(i, j) == 2);
    std::cout << "Part 1 answer: " << num_2s << std::endl;

}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 05 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    part1(data);
    // std::cout << "--------" << std::endl;
    // part2(all_called, bingo_cards);

}
