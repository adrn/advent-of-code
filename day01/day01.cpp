#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <stdexcept>

int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    std::cout << "Loading data file at " << datafile_path << std::endl;

    std::ifstream datafile (datafile_path);
    std::string line;
    std::vector<int> depths;
    int depth;
    int num_larger = 0;

    if (datafile.is_open()) {

        // Date file parsing:
        while(std::getline(datafile, line)) {
            std::from_chars(line.data(), line.data() + line.size(), depth);
            depths.push_back(depth);
        }
        datafile.close();

        std::cout << "Loaded " << depths.size() << " depths." << std::endl;

        // Part 1: Now analyze the loaded data:
        for (auto iter = depths.begin() + 1; iter != depths.end(); iter++) {
            auto iter_prev = iter;
            --iter_prev;
            if (*iter > *iter_prev) {
                num_larger++;
            }
        }
        std::cout << "Number of measurements larger than the previous: " << num_larger << std::endl;

        // Part 2: TODO

    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

}
