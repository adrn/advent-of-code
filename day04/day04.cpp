#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <charconv>
#include <stdexcept>
#include <cmath>
#include "day04.hpp"

typedef std::vector<std::vector<int>> BingoCard;

std::vector<int> get_called_numbers(std::string line) {
    std::vector<int> data = {};
    auto tmp = split(line, ',');
    for (auto elem : tmp)
        data.push_back(std::stoi(elem));
    return data;
}

std::vector<BingoCard> get_bingo_cards(std::vector<std::string> lines) {
    std::vector<BingoCard> cards = {};

    BingoCard card = {};
    for (auto line = lines.begin() + 1; line != lines.end(); ++line) {
        if ((*line).size() == 0) {
            if (card.size() != 0)
                cards.push_back(card);
            card = {};
        } else {
            std::vector<int> row = {};
            auto tmp = split((*line), ' ');
            for (auto elem : tmp)
                row.push_back(std::stoi(elem));
            card.push_back(row);
        }
    }

    if (card.size() != 0)
        cards.push_back(card);

    std::cout << "Number of cards: " << cards.size() << std::endl;

    return cards;
}

std::vector<std::vector<bool>> get_called_numbers(BingoCard card, std::vector<int> called_numbers) {
    int size = card.size();
    std::vector<std::vector<bool>> card_called_numbers;

    for (int i=0; i < size; i++) {
        std::vector<bool> row = {};
        for (int j=0; j < size; j++)
            row.push_back(std::count(called_numbers.begin(), called_numbers.end(), card[i][j]));
        card_called_numbers.push_back(row);
    }
    return card_called_numbers;
}

bool is_a_winner(BingoCard card, std::vector<int> called_numbers) {
    int size = card.size();
    auto card_called_numbers = get_called_numbers(card, called_numbers);
    // print_vector2d<bool>(card_called_numbers);

    int count;
    for (int i=0; i < size; i++) {
        count = 0;
        for (int j=0; j < size; j++)
            count += card_called_numbers[i][j];
        if (count == size)
            return true;
    }

    for (int j=0; j < size; j++) {
        count = 0;
        for (int i=0; i < size; i++)
            count += card_called_numbers[i][j];
        if (count == size)
            return true;
    }

    return false;

}


void part1(std::vector<int> all_called, std::vector<BingoCard> bingo_cards) {
    for (int i = 1; i < all_called.size(); i++) {
        std::vector<int> called_now(all_called.begin(), all_called.begin() + i + 1);

        for (auto card : bingo_cards) {
            bool winner = is_a_winner(card, called_now);
            if (winner) {
                auto called_card_numbers = get_called_numbers(card, called_now);

                int sum = 0;
                for (int i=0; i < card.size(); i++)
                    for (int j=0; j < card.size(); j++)
                        if (called_card_numbers[i][j] == 0)
                            sum += card[i][j];
                std::cout << "Board won on number: " << i << std::endl;
                std::cout << "Sum of uncalled numbers: " << sum << std::endl;
                std::cout << "Last called number: " << called_now.back() << std::endl;
                std::cout << "Part 1 answer: " << sum * called_now.back() << std::endl;
                return;
            }
        }
    }
}


void part2(std::vector<std::vector<bool>> data) {

}


int main(int argc, char** argv) {
    std::cout << "---------------- Day 04 ----------------" << std::endl;

    if (argc != 2)
        throw std::runtime_error(
            "Invalid number of command-line arguments: Pass only the path to the data file");

    std::string datafile_path(argv[1]);
    auto lines = read_lines(datafile_path);

    auto all_called = get_called_numbers(lines[0]);
    /// print_vector1d<int>(called);

    auto bingo_cards = get_bingo_cards(lines);
    // print_vector2d<int>(bingo_cards[0]);

    part1(all_called, bingo_cards);
    // part2(data);

}
