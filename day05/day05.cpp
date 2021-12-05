#include <Eigen/Sparse>
#include <vector>
#include <cmath>
#include <iostream>
#include "day05.hpp"


typedef Eigen::SparseMatrix<int> SpMat;

void add_line_to_grid(std::vector<int> &data_row, SpMat &grid, bool diagonal=true) {
    int i, j, start, end;

    int step_horiz = data_row[2] - data_row[0];
    int step_verti = data_row[3] - data_row[1];
    int sign_horiz = sign(step_horiz);
    int sign_verti = sign(step_verti);

    if ((!diagonal) && !((step_horiz == 0) || (step_verti == 0)))
        return;

    if (((step_horiz != 0) && (step_verti != 0)) &&
            (std::abs(step_horiz) != std::abs(step_verti))) {
        std::cout << "Horiz step: " << step_horiz;
        std::cout << "  Vertical step: " << step_verti << std::endl;
        throw std::runtime_error("APW: Your assumption isn't right!");
    }

    int step = std::max(std::abs(step_horiz), std::abs(step_verti));
    for (int k=0; k < (step+1); k++) {
        i = sign_horiz * k * (step_horiz != 0) + data_row[0];
        j = sign_verti * k * (step_verti != 0) + data_row[1];
        grid.coeffRef(i, j) += 1;
    }

}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 05 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);

    int grid_size = max(data) + 1;
    // print_vector2d<int>(data);
    std::cout << "grid size: " << grid_size << std::endl;

    int num_2s;
    SpMat grid_part1(grid_size, grid_size);
    SpMat grid_part2(grid_size, grid_size);

    // Part 1
    for (auto row : data)
        add_line_to_grid(row, grid_part1, false);

    // std::cout << grid_part1 << std::endl;

    num_2s = 0;
    for (int i=0; i < grid_size; i++)
        for (int j=0; j < grid_size; j++)
            num_2s += (grid_part1.coeff(i, j) >= 2);
    std::cout << "Part 1 answer: " << num_2s << std::endl;

    std::cout << "--------" << std::endl;

    // Part 2
    for (auto row : data)
        add_line_to_grid(row, grid_part2, true);

    // std::cout << grid_part2 << std::endl;

    num_2s = 0;
    for (int i=0; i < grid_size; i++)
        for (int j=0; j < grid_size; j++)
            num_2s += (grid_part2.coeff(i, j) >= 2);
    std::cout << "Part 2 answer: " << num_2s << std::endl;

}
