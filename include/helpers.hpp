#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <tuple>

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

template <typename T1, typename T2>
void print_map(std::map<T1, T2> data) {
    std::cout << "{" << std::endl;
    for (auto const& [key, val] : data)
        std::cout << "    " << key << ": " << val << "," << std::endl;
    std::cout << "}" << std::endl;
}

/*
    Math helpers:
*/
template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T>
T max(std::vector<T> data) {
    // Get minimum value for the type:
    T max_comp = std::numeric_limits<T>::min();
    for (int i=0; i < data.size(); i++)
        max_comp = std::max(max_comp, data[i]);
    return max_comp;
}

template <typename T>
T max(std::vector<std::vector<T>> data) {
    // Get minimum value for the type:
    T max_comp = std::numeric_limits<T>::min();
    for (int i=0; i < data.size(); i++)
        for (int j=0; j < data[i].size(); j++)
            max_comp = std::max(max_comp, data[i][j]);
    return max_comp;
}

template <typename T>
T min(std::vector<T> data) {
    // Get maximum value for the type:
    T min_comp = std::numeric_limits<T>::max();
    for (int i=0; i < data.size(); i++)
        min_comp = std::min(min_comp, data[i]);
    return min_comp;
}

template <typename T>
T min(std::vector<std::vector<T>> data) {
    // Get maximum value for the type:
    T min_comp = std::numeric_limits<T>::max();
    for (int i=0; i < data.size(); i++)
        for (int j=0; j < data[i].size(); j++)
            min_comp = std::min(min_comp, data[i][j]);
    return min_comp;
}

template <typename T>
T sum(std::vector<T> data) {
    T data_sum = 0;
    for (const auto &item : data)
        data_sum += item;
    return data_sum;
}

template <typename T>
T median(std::vector<T> &v) {
    // https://stackoverflow.com/questions/1719070/what-is-the-right-approach-when-using-stl-container-for-median-calculation/1719155#1719155
    size_t n = v.size() / 2;
    std::nth_element(v.begin(), v.begin()+n, v.end());
    return v[n];
}


/*
    Optimization
*/

template <typename T>
T simple_minimize(
    std::vector<T> (*func)(T, std::vector<T>),
    T x0,
    std::vector<T> &data,
    int maxiter = 1000,
    double alpha=0.05
) {
    std::vector<T> obj_and_grad;
    auto x = x0;
    auto trial_x = x;
    T result;

    int i;
    for (i=0; i < maxiter; i++) {
        obj_and_grad = func(x, data);
        if (obj_and_grad[1] == 0)
            break;
        trial_x = x - alpha * obj_and_grad[1];

        std::cout << "iter=" << i << " x=" << x << " trial_x=" << trial_x << " val=" << obj_and_grad[0] <<  " grad=" << obj_and_grad[1] << std::endl;

        if ((trial_x < 0) || std::isnan(trial_x))
            break;

        x = trial_x;
        std::cout << "x=" << x << std::endl;
    }

    if (i >= maxiter)
        std::cout << "Warning: optimizer hit maxiter" << std::endl;

    result = x;
    return result;
}

/*
    Misc.
*/
int vector_to_int(std::vector<int> v) {
    std::reverse(v.begin(), v.end());
    int decimal = 1;
    int total = 0;
    for (auto &it : v)
    {
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}

std::set<std::tuple<int, int>> custom_intersect(
    std::set<std::tuple<int, int>> &s1,
    std::set<std::tuple<int, int>> &s2
) {
    std::set<std::tuple<int, int>> intersect;

    for (auto &elem : s1) {
        if (s2.find(elem) != s2.end())
            intersect.insert(elem);
    }

    return intersect;
}