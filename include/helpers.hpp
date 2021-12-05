
#include <string>
#include <iostream>
#include <vector>

/*
    split_string()
*/
std::vector<std::string> split_string(std::string text, char sep) {
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

std::vector<std::string> split_string(std::string text, std::string sep) {
    std::vector<std::string> tokens = {};
    std::size_t pos = 0;
    std::size_t found = 0;

    while ((pos < (text.size()-1)) && (found != std::string::npos)) {
        found = text.find(sep, pos + 1);
        tokens.push_back(text.substr(pos, found));
        pos = found;
        std::cout << "pos=" << pos << " --- found=" << found << std::endl;
    }

    return tokens;
}

/*
    Printing:

    Vectors
*/
template <typename T>
void print_vector1d(std::vector<T> data) {
    std::cout << "[";
    for (int i=0; i < data.size(); i++) {
        std::cout << data[i];
        if (i != (data.size()-1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

template <>
void print_vector1d(std::vector<std::string> data) {
    std::cout << "[";
    for (int i=0; i < data.size(); i++) {
        std::cout << "'" << data[i] << "'";
        if (i != (data.size()-1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}