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
using line_pair = std::pair<std::size_t, std::size_t>;

/// @brief Ordered pair indicationg the location of a string
using coordinate = std::pair<std::size_t, line_pair>;

bool is_symbol(char ch);
bool is_adjacent(const coordinate& part_num, const grid& source);
void get_schematic(grid& schematic);
std::string get_string(const line_pair& part_num, const line& source);
line_pair number_location(std::size_t start, const line& source);

int main() {
    grid schematic {};
    get_schematic(schematic);

    int sum = 0;

    for (size_t row = 0; row < schematic.size(); ++row) {
        for (size_t col = 0; col < schematic[row].size(); ++col) {
            /// Only start more checks after a start digit is found
            if (std::isdigit(schematic[row][col])) {
                // Start and end of the number
                line_pair number = number_location(col, schematic[row]);
                col += number.second - number.first;  // Skip ahead
                if (is_adjacent(coordinate(row, number), schematic)) {
                    sum += stoi(get_string(number, schematic[row]));
                }
            }
        }
    }
    std::cout << "Sum of part numbers: " << sum << '\n';
    return 0;
}

/// @brief Determines if a character is a "symbol": Any non-number that isn't a
/// period '.'
/// @param ch: Test character
/// @return bool: True => is a "symbol" | False => not a "symbol"
bool is_symbol(char ch) {
    return (!std::isdigit(ch) && ch != '.');
}

/// @brief Given the location and size of a number, will determine if the number
/// is adjacent to part meaning it is a valid part number;
/// @param part_num: Consists of a row, and the start and end indices for the
/// number
/// @param source: Where to search for symbols
/// @return bool: True => adjacent to a symbol | False: Not adjacent to a symbol
bool is_adjacent(const coordinate& part_num, const grid& source) {
    auto [line_start, column] = part_num;
    auto [start, stop] = column;
    bool adjacent = false;
    int compare = stoi(get_string(column,source[line_start]));

    for (auto row = line_start - 1; row != line_start + 2 && !adjacent; ++row) {
        // Don't go out of bounds
        if (row < source.size()) {

            for (auto col = start - 1; col != stop + 1 && !adjacent; ++col) {
                // Don't go out of bounds again
                if (col < source[row].size()) {
                    if (is_symbol(source[row][col])) {
                        adjacent = true;
                    }
                }
            }
        }
    }
    // Foreshadowing: bounds checking is annoying, if only I could prevent it...

    return adjacent;
}

/// @brief Fills a grid full of chararcters representing the schematic of the
/// machine
/// @param [out] schematic: Where to store the schematic
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

/// @brief Converts a group of char indices into one string
/// @param part_num: A pair of coordinates indicating where to start and stop
/// @param source: The source for the string
/// @return std::string: [1][2][3][4][5] => "12345"
std::string get_string(const line_pair& part_num, const line& source) {
    auto [start, stop] = part_num;
    std::string str;

    // Build string left to right
    for (size_t curr = start; curr != stop; ++curr) {
        str.push_back(source[curr]);
    }
    return std::move(str);
}

/// @brief Finds the position of the last digit in a number + 1 to mark the end
/// @param start: Starting index in a line
/// @param source: The line to search in
/// @return line_pair: Start and end position for the part number
line_pair number_location(std::size_t start, const line& source) {
    size_t stop = start;
    while (stop != source.size() && isdigit(source[stop])) {
        ++stop;
    }
    return line_pair(start, stop);
}