#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>

// A horizontal line of the grid
using line = std::vector<char>;

// A character grid
using grid = std::vector<std::vector<char>>;

// Ordered pair cooresponding to a location on the grid (x,y)
using coordinate = std::pair<std::size_t, std::size_t>;

// Syntatic sugar: start and end point for a "substring" on a given row
using line_pair = coordinate;

std::vector<coordinate> find_parts(const coordinate& center,
                                     const grid& source);
int gear_ratio(std::vector<coordinate>& parts_list, const grid& source);
void get_schematic(grid& schematic);
std::string get_string(const line_pair& part_num, const line& source);

int main() {
    grid schematic {}; // Empty schematics
    get_schematic(schematic);   // Not so empty

    int sum = 0;

    // Go through each grid square
    for (size_t row = 1; row < schematic.size() - 1; ++row) {
        for (size_t col = 1; col < schematic[row].size() - 1; ++col) {

            if (schematic[row][col] == '*') {
                // Grab all adjacent number locations, less headache
                auto parts_lists = find_parts(coordinate(row,col),schematic);

                // Only valid if exactly two are adjacent
                if (parts_lists.size() == 2) {
                    sum += gear_ratio(parts_lists, schematic);
                }
            }
        }
    }
    std::cout << "Sum of gear ratios: " << sum << '\n';
    return 0;
}

/// @brief Takes all part number locations and creates a running product to find
/// the gear ratio
/// @param parts_list: List of locations for all the parts
/// @param source: The source to get all the parts
/// @return int: The gear ratio of given parts
int gear_ratio(std::vector<coordinate>& parts_list, const grid& source) {
    int gear_ratio = 1; // Running product

    // Go through all the parts given
    for (auto& part : parts_list) {
        auto [row, col] = part;

        // Find the start character position
        auto start = col;
        while (std::isdigit(source[row][start - 1])) {
            start--;
        }

        // Find the last character position + 1
        auto end = col;
        while (std::isdigit(source[row][end])) {
            end++;
        }

        gear_ratio *= stoi(get_string(line_pair(start,end),source[row]));
    }
    return gear_ratio;
}

/// @brief Finds all possible part numbers adjacent to the a given coordinate
/// @param center: x-y coordinate to search around
/// @param source: Source of characters
/// @return std::vector<coordinate>: A list of coordiantes of all part numbers
std::vector<coordinate> find_parts(const coordinate& center,
                                   const grid& source) {
    auto [row, col] = center;
    std::vector<coordinate> parts_list{};

    // Very ugly but gets the job done
    bool top_left  = std::isdigit(source[row-1][col-1]);
    bool top       = std::isdigit(source[row-1][col]);
    bool top_right = std::isdigit(source[row-1][col+1]);
    bool left      = std::isdigit(source[row][col-1]);
    bool right     = std::isdigit(source[row][col+1]);
    bool bot_left  = std::isdigit(source[row+1][col-1]);
    bool bottom    = std::isdigit(source[row+1][col]);
    bool bot_right = std::isdigit(source[row+1][col+1]);

    // If its in the top-middle then there can only be one adjacent number
    if (top) {
        parts_list.push_back(coordinate(row - 1, col));
    }
    // Otherwise at max two adjacent numbers
    else {
        if (top_left) {
            parts_list.push_back(coordinate(row - 1, col - 1));
        }
        if (top_right) {
            parts_list.push_back(coordinate(row - 1, col + 1));
        }
    }

    // Only one left and right possible
    if (left) {
        parts_list.push_back(coordinate(row,col-1));
    }
    if (right) {
        parts_list.push_back(coordinate(row,col+1));
    }

    // Same logic as top
    if (bottom) {
        parts_list.push_back(coordinate(row+1,col));
    }
    else {
        if (bot_left) {
            parts_list.push_back(coordinate(row + 1, col - 1));
        }
        if (bot_right) {
            parts_list.push_back(coordinate(row + 1, col + 1));
        }
    }

    return std::move(parts_list);
}

/// @brief Fills a grid full of chararcters representing the schematic of the
/// machine. Includes a border for an easier life
/// @param [out] schematic: Where to store the schematic
void get_schematic(grid& schematic) {
    std::string input;
    std::ifstream infile("input.txt");

    while (infile >> input) {
        line current {'.'};
        for (char& ch : input) {
            current.push_back(ch);
        }
        current.push_back('.');
        schematic.push_back(current);
    }

    // Hand was forced, added a border to make things simpler
    line empty = line(schematic.front().size() + 2, '.');
    schematic.insert(schematic.begin(),empty);
    schematic.push_back(empty);
}

/// @brief Converts a group of char indices into one string
/// @param part_num: A pair of coordinates indicating where to start and stop
/// @param source: The source for the string
/// @return std::string: [1][2][3][4][5] => "12345"
std::string get_string(const line_pair& part_num, const line& source) {
    auto [start, stop] = part_num;
    std::string str;

    // built up the string left to right
    for (size_t curr = start; curr != stop; ++curr) {
        str.push_back(source[curr]);
    }
    return std::move(str);
}