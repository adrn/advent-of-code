#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <stdexcept>

int num_larger_than_previous(std::vector<int> data) {
    int num_larger = 0;
    for (auto iter = data.begin() + 1; iter != data.end(); iter++) {
        auto iter_prev = iter;
        --iter_prev;

        if (*iter > *iter_prev)
            num_larger++;
    }
    return num_larger;
}

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
    int num_larger;

    if (datafile.is_open()) {

        // Date file parsing:
        while(std::getline(datafile, line)) {
            std::from_chars(line.data(), line.data() + line.size(), depth);
            depths.push_back(depth);
        }
        datafile.close();

        std::cout << "Loaded " << depths.size() << " depths." << std::endl;

        // Part 1: Now analyze the loaded data:
        num_larger = num_larger_than_previous(depths);
        std::cout << "Part 1: Number of measurements larger than the previous: " << num_larger << std::endl;

        // Part 2: Analyze the 3-element-summed version:
        std::vector<int> depth_3sum;
        for (auto iter = depths.begin(); iter != depths.end()-2; iter++) {
            auto next1 = std::next(iter, 1);
            auto next2 = std::next(iter, 2);
            depth_3sum.push_back(*iter + *next1 + *next2);
        }

        num_larger = num_larger_than_previous(depth_3sum);
        std::cout << "Part 2: Number of measurements larger than the previous: ";
        std::cout << num_larger << std::endl;

    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

}
