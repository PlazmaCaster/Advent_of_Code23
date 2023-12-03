#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>

/// @brief A horizontal line of the grid
using line = std::vector<char>;

/// @brief A character grid
using grid = std::vector<std::vector<char>>;

/// @brief Orderd pair indicating the start and stop of a "string" on the line
using selection = std::pair<std::size_t, std::size_t>;

/// @brief Ordered pair indicationg the location of a string
using coordinate = std::pair<std::size_t, selection>;

bool is_symbol(char ch);
bool is_adjacent(const coordinate& part_num, const grid& source);
void get_schematic(grid& schematic);
std::string get_string(const selection& part_num, const line& source);
selection number_location(std::size_t start, const line& source);

int main() {
    grid schematic {};
    get_schematic(schematic);

    int sum = 0;

    for (size_t row = 0; row < schematic.size(); ++row) {
        for (size_t col = 0; col < schematic[row].size(); ++col) {
            if (std::isdigit(schematic[row][col])) {
                selection number = number_location(col, schematic[row]);
                col += number.second - number.first;
                if (is_adjacent(coordinate(row, number), schematic)) {
                    int testing = stoi(get_string(number,schematic[row]));
                    sum += stoi(get_string(number, schematic[row]));
                }
            }
        }
    }
    std::cout << "Sum of part numbers: " << sum << '\n';
    return 0;
}

bool is_symbol(char ch) {
    return (!std::isdigit(ch) && ch != '.');
}

bool is_adjacent(const coordinate& part_num, const grid& source) {
    auto [line_start, column] = part_num;
    auto [start, stop] = column;
    bool adjacent = false;
    int compare = stoi(get_string(column,source[line_start]));

    for (auto row = line_start - 1; row != line_start + 2 && !adjacent; ++row) {
        if (row < source.size()) {
            for (auto col = start - 1; col != stop + 1 && !adjacent; ++col) {
                if (col < source[row].size()) {
                    if (is_symbol(source[row][col])) {
                        adjacent = true;
                    }
                }
            }
        }
    }
    return adjacent;
}

void get_schematic(grid& schematic) {
    std::string input;
    std::ifstream infile("input.txt");

    while (infile >> input) {
        std::vector<char> current {};
        for (char& ch : input) {
            current.push_back(ch);
        }
        schematic.push_back(current);
    }
}

std::string get_string(const selection& part_num, const line& source) {
    auto [start, stop] = part_num;
    std::string str;
    for (size_t curr = start; curr != stop; ++curr) {
        str.push_back(source[curr]);
    }
    return std::move(str);
}

selection number_location(std::size_t start, const line& source) {
    size_t stop = start;
    while (stop != source.size() && isdigit(source[stop])) {
        ++stop;
    }
    return selection(start, stop);
}