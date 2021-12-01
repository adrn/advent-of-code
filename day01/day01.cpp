#include <string>
#include <iostream>
#include <fstream>

int main() {
    std::ifstream datafile ("day01-data.txt");
    std::string line;

    if (datafile.is_open()) {
        while(std::getline(datafile, line)) {
            std::cout << line << std::endl;
        }
        datafile.close();
    }

}
