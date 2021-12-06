#include <vector>
#include <cmath>
#include <iostream>
#include "day06.hpp"


void part1(std::vector<fish_t> fishies, int ndays) {
    // Spawn fish the dumb way!
    int create_every = 6;
    int newborn_penalty = 2;

    auto state = fishies;
    for (int day=1; day < ndays+1; day++) {
        std::vector<fish_t> newborn = {};
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
        if ((day == 18) || (day == ndays))
            std::cout << "After " << day << " days:  " << state.size() << std::endl;
    }
}

void part2(std::vector<fish_t> fishies, int ndays) {
    // part1 solution obviously doesn't scale, so just keep track of the number of fish in each bin:
    int create_every = 6;
    int newborn_penalty = 2;

    // Get initial state:
    std::vector<unsigned long long> state(create_every + newborn_penalty + 1, 0);
    for (auto fish : fishies)
        state[fish] += 1;

    unsigned long long nbabies;
    for (int day=1; day < ndays+1; day++) {
        nbabies = state[0];
        for (int i=1; i < state.size(); i++)
            state[i - 1] = state[i];
        state[create_every] += nbabies;
        state[create_every + newborn_penalty] = nbabies;

        if ((day == 18) || (day == 80) || (day == ndays)) {
            std::cout << "After " << day << " days:  " << sum(state) << " fish -- ";
            print_vector1d(state);
        }
    }
}

int main(int argc, char** argv) {
    std::cout << "---------------- Day 06 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto fishies = parse_file(datafile_path);

    part1(fishies, 80);
    std::cout << "--------" << std::endl;
    part2(fishies, 256);

}
