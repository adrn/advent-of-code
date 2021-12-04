#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>

template <class T>
void print_vector1d(std::vector<T> data) {
    std::cout << "[";
    for (auto elem : data) {
        std::cout << elem << ", ";
    }
    std::cout << "]" << std::endl;
}

template <class T>
void print_vector2d(std::vector<std::vector<T>> data) {
    std::cout << "[";
    for (auto vec : data)
        print_vector1d<T>(vec);
    std::cout << "]" << std::endl;
}

std::vector<std::string> read_lines(std::string filename) {
    std::vector<std::string> data = {};

    std::cout << "Loading data file at " << filename << std::endl;

    std::ifstream datafile (filename);
    std::vector<std::string> lines;
    std::string line;

    bool a;
    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            data.push_back(line);
        }
        datafile.close();
    } else {
        std::cout << "ERROR: failed to open data file" << std::endl;
    }

    return data;
}

std::vector<std::string> split(std::string text, char sep) {
    std::vector<std::string> tokens = {};
    std::string token = "";
    for (unsigned int i = 0; i < text.size(); i++) {
        if ((char)text.at(i) != sep)
            token += text.at(i);
        else {
            if (token.size() != 0)
                tokens.push_back(token);
            token = "";
        }
    }

    if (token.size() != 0)
        tokens.push_back(token);

    return tokens;
}