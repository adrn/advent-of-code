#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "helpers.hpp"

using namespace std;

vector<vector<int>> parse_file(string filename) {
    vector<vector<int>> data = {};

    cout << "Loading data file at " << filename << endl;

    ifstream datafile (filename);
    string line;

    if (datafile.is_open()) {
        while(getline(datafile, line)) {
            vector<int> row = {};
            for (char &char_ : line)
                row.push_back(((int)char_) - 48);
            data.push_back(row);
        }
        datafile.close();
    } else {
        cout << "ERROR: failed to open data file" << endl;
    }

    return data;
}

vector<tuple<int, int>> get_neighborhood(int i1, int i2, int size1, int size2) {
    vector<tuple<int, int>> neighbors = {};
    for (int i=i1-1; i <= (i1+1); i++)
        for (int j=i2-1; j <= (i2+1); j++) {
            if (
                (i >= 0) && (j >= 0) && (i <= (size1-1)) && (j <= (size2-1))
            ) {
                neighbors.push_back({i, j});
            }
        }
    return neighbors;
}

vector<tuple<int, int>> get_ready_octopi(vector<vector<int>> &data) {
    vector<tuple<int, int>> ready = {};
    for (int i=0; i < data.size(); i++)
        for (int j=0; j < data[0].size(); j++)
            if (data[i][j] > 9)
                ready.push_back({i, j});
    return ready;
}

int flash_step(vector<vector<int>> &data) {
    auto ready = get_ready_octopi(data);
    vector<tuple<int, int>> flashed;
    while (ready.size() > 0) {
        for (auto [i, j] : ready) {
            auto nbidx = get_neighborhood(i, j, data.size(), data[0].size());
            for (auto [i1, i2] : nbidx)
                data[i1][i2] += 1;
            data[i][j] = 0;
            flashed.push_back({i, j});
        }
        ready = get_ready_octopi(data);
    }
    for (auto [i1, i2] : flashed)
        data[i1][i2] = 0;

    return flashed.size();
}

void part1(vector<vector<int>> &data, int nsteps) {
    int nflashes = 0;
    int step;

    cout << "Initial state: ";
    print_vector2d(data);

    vector<vector<vector<int>>> flash_sequence = {data};
    for (step=0; step < nsteps; step++) {
        for (int i=0; i < data.size(); i++)
            for (int j=0; j < data[0].size(); j++)
                data[i][j] += 1;

        nflashes += flash_step(data);

        // cout << "After step " << step+1 << ": ";
        // print_vector2d(data);

        flash_sequence.push_back(data);
    }
    cout << "After " << step << " steps, there have been " << nflashes << " flashes." << endl;
}

int main(int argc, char** argv) {
    cout << "---------------- Day 11 ----------------" << endl;

    if (argc != 2)
        throw runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    string datafile_path(argv[1]);
    auto data = parse_file(datafile_path);
    // print_vector2d(data);

    // Part 1
    cout << "Part 1: " << endl;
    part1(data, 100);

    cout << "--------" << endl;

    // Part 2
    cout << "Part 2: " << endl;

}
