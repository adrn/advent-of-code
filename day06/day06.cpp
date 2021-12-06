#include <vector>
#include <cmath>
#include <iostream>
#include "day06.hpp"


void part1(std::vector<int> fishies) {
    int ndays = 80;
    int create_every = 6;
    int newborn_penalty = 2;

    auto state = fishies;
    for (int day=1; day < ndays+1; day++) {
        std::vector<int> newborn = {};
        for (int i=0; i < state.size(); i++){
            if (state[i] == 0) {
                state[i] = create_every;
                newborn.push_back(create_every + newborn_penalty);
            } else
                state[i] = state[i] - 1;
        }
        // concatenate:
        std::copy(newborn.begin(), newborn.end(), std::back_inserter(state));

        // std::cout << "After " << day << " days:  ";
        // print_vector1d(state);
        if ((day == 18) || (day == 80))
            std::cout << "After " << day << " days:  " << state.size() << std::endl;
    }
}


int main(int argc, char** argv) {
    std::cout << "---------------- Day 06 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto fishies = parse_file(datafile_path);

    part1(fishies);
    std::cout << "--------" << std::endl;

}
