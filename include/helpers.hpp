
#include <string>
#include <iostream>
#include <vector>

/*
    strip_string()
*/
std::string strip_string(std::string str) {
    str.erase(str.find_last_not_of(' ') + 1);       //suffixing spaces
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    return str;
}

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

std::vector<std::string> split_string(std::string text, std::string sep, bool strip = true) {
    std::vector<std::string> tokens = {};
    std::size_t pos = 0;
    std::size_t found = 0;

    while (found != std::string::npos) {
        found = text.find(sep, pos);
        if (strip == true)
            tokens.push_back(strip_string(text.substr(pos, found-pos)));
        else
            tokens.push_back(text.substr(pos, found-pos));
        pos = found + sep.size();
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

template <typename T>
void print_vector2d(std::vector<std::vector<T>> data) {
    std::cout << "[" << std::endl;
    for (int i=0; i < data.size(); i++) {
        std::cout << " ";
        print_vector1d<T>(data[i]);
    }
    std::cout << "]" << std::endl;
}
