#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>

/// @brief Represents a bag of cubes...
struct bag {
    /// @brief Default constructor
    /// @param red: Red cube count
    /// @param green: Green cube count
    /// @param blue: Blue cube count
    bag(int red = 0, int green = 0, int blue = 0)
        : red_cubes(red), green_cubes(green), blue_cubes(blue) {}

    /// @brief Updates the possible contents of the bag
    /// @param red: Number of red cubes pulled
    /// @param green: Number of green cubes pulled
    /// @param blue: Number of blue cubes pulled
    void update(int red, int green, int blue) {
        if (red_cubes < red) {
            red_cubes = red;
        }
        if (green_cubes < green) {
            green_cubes = green;
        }
        if (blue_cubes < blue) {
            blue_cubes = blue;
        }
    }

    /// @brief Gets the power of a bag
    /// @return int: bag's power
    int power() {return red_cubes * green_cubes * blue_cubes; }

    int red_cubes;
    int green_cubes;
    int blue_cubes;
};

static const std::string INPUT_FILE = "input.txt";

void get_that_bag(const std::string& round, bag& source);

int main() {
    std::string game;
    std::string round;
    int power_sum = 0;
    std::ifstream infile(INPUT_FILE);

    while (std::getline(infile,game)) {
        bag round_bag;      // This round's bag
        std::istringstream game_stream(game);
        game_stream.ignore(255, ':');

        while (std::getline(game_stream, round, ';')) {
            get_that_bag(round, round_bag);
        }
        power_sum += round_bag.power();
    }
    std::cout << "Sum of bag powers: " << power_sum << '\n';
    return 0;
}

/// @brief Given a round in the game, extracts the number of each color cube
/// pulled and updates the source bag's possible contents accordingly
/// @param round: The current round being played
/// @param source: The source of the cubes
void get_that_bag(const std::string& round, bag& source) {
    // Patterns
    static const std::regex RED_REGEX("\\d+\\s(?=red)");
    static const std::regex GRN_REGEX("\\d+\\s(?=green)");
    static const std::regex BLU_REGEX("\\d+\\s(?=blue)");

    int red_count = 0;
    int green_count = 0;
    int blue_count = 0;

    // Count each color occurance
    std::smatch match;
    if (std::regex_search(round, match, RED_REGEX)) {
        red_count = std::stoi(match.str());
    }
    if (std::regex_search(round, match, GRN_REGEX)) {
        green_count = std::stoi(match.str());
    }
    if (std::regex_search(round, match, BLU_REGEX)) {
        blue_count = std::stoi(match.str());
    }

    // Update bag with new values
    source.update(red_count, green_count, blue_count);
}
