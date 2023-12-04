#include <iostream>
#include <set>
#include <sstream>
#include <string>

int get_points(const std::set<int>& scratch, std::set<int>& winning);

int main() {
    std::string line;   // Each line is a card
    int point_sum = 0;

    while (std::getline(std::cin, line)) {
        std::istringstream scratch_card(line);  // Easier processsing
        std::string value;
        std::set<int> winning_numbers{};        // Set of winning numbers
        std::set<int> scratched_numbers{};      // Set of numbers found

        scratch_card.ignore(255,':');

        // Scrached num & winning num seperated by '|'
        do {
            scratch_card >> value;
            if (value != "|") {
                scratched_numbers.insert(std::stoi(value));
            }
        } while (value != "|");

        while (scratch_card >> value) {
            winning_numbers.insert(stoi(value));
        }
        int points = get_points(scratched_numbers, winning_numbers);
        point_sum += points;
    }
    std::cout << "Total points: " << point_sum << '\n';
}

/// @brief Gets the point total earned from a given scratch card
/// @param scratch: Set of numbers found by scratching
/// @param winning: Set of winning numbers
/// @return int: Points earned
int get_points(const std::set<int>& scratch, std::set<int>& winning) {
    int counter = 0;    // Number of matches
    int points = 0;     // Points earned

    // Duplicate numbers do not get inserted => match found
    for (auto& num : scratch) {
        auto result = winning.insert(num);
        if (!result.second) {
            ++counter;
        }
    }

    // first point is worth 1, every point after doubles it
    if (counter > 0) {
        points = 1;
        --counter;
    }
    while (counter > 0) {
        points *= 2;
        --counter;
    }
    return points;
}
