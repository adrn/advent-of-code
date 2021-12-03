#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <stdexcept>


std::vector<std::string> split(std::string text, char sep) {
    std::vector<std::string> tokens = {};
    std::string token = "";
    for (unsigned int i = 0; i < text.size(); i++) {
        if ((char)text.at(i) != sep)
            token += text.at(i);
        else {
            tokens.push_back(token);
            token = "";
        }
    }

    if (token.size() != 0)
        tokens.push_back(token);

    return tokens;
}


std::vector<int> get_move_part1(std::string line) {
    std::vector<int> move = {0, 0};  // (horizontal, depth)
    auto tokens = split(line, ' ');
    int step;

    if (tokens.size() != 2)
        throw std::runtime_error(
            "Invalid command on line: '" + line + "'");

    std::from_chars(tokens[1].data(), tokens[1].data() + tokens[1].size(), step);

    if (tokens[0] == "forward")
        move[0] = step;
    else if (tokens[0] == "up")
        move[1] = -step;
    else if (tokens[0] == "down")
        move[1] = step;

    return move;
}

void part1(std::vector<std::string> lines) {
    std::string line;
    std::vector<int> pos = {0, 0};  // (horiztonal, depth)

    for (auto line : lines) {
        auto move = get_move_part1(line);
        pos[0] += move[0];
        pos[1] += move[1];
    }

    std::cout << "Final position: " << pos[0] << ", " << pos[1] << std::endl;
    std::cout << "Part 1 answer: " << pos[0] * pos[1] << std::endl;
}


int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    std::cout << "Loading data file at " << datafile_path << std::endl;

    std::ifstream datafile (datafile_path);
    std::vector<std::string> lines;
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line))
            lines.push_back(line);
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    part1(lines);

}
