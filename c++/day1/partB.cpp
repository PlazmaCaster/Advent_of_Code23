#include <iostream>
#include <string>
#include <fstream>
#include <regex>    // Using to try and learn regex, might not be best solution
#include <algorithm>

int convert(const std::string& number);

int main() {
    // Regex for plain words
    std::string wordPattern = "one|two|three|four|five|six|seven|eight|nine";
    std::regex pattern(wordPattern+"|\\d");  // Include digits

    // same pattern for backwards to get last match
    std::reverse(wordPattern.begin(), wordPattern.end());
    std::regex nrettap(wordPattern+"|\\d");

    std::ifstream infile("input.txt");  // Input file
    int sum = 0;                        // Running Sum
    std::string line {};                // Parse each line

    while (infile >> line) {
        // Iterator to first match in string
        std::sregex_iterator first_iter(line.begin(), line.end(), pattern);

        // Uno_reverse_card.png
        std::string enil = line;
        std::reverse(enil.begin(), enil.end());
        std::sregex_iterator second_iter(enil.begin(), enil.end(), nrettap);

        std::smatch first = *first_iter;    // First Digit
        std::smatch second = *second_iter;  // Second Digit
        sum += 10 * convert(first.str()) + convert(second.str());
    }
    std::cout << sum << '\n';

    return 0;
}


/// @brief Brute force conversion of string to number
/// @param number "Number"
/// @return int
int convert(const std::string& number) {
    if (number == "one" || number == "1" || number == "eno") {
        return 1;
    }
    else if (number == "two" || number == "2" || number == "owt") {
        return 2;
    }
    else if (number == "three" || number == "3" || number == "eerht") {
        return 3;
    }
    else if (number == "four" || number == "4" || number == "ruof") {
        return 4;
    }
    else if (number == "five" || number == "5" || number == "evif") {
        return 5;
    }
    else if (number == "six" || number == "6" || number == "xis") {
        return 6;
    }
    else if (number == "seven" || number == "7" || number == "neves") {
        return 7;
    }
    else if (number == "eight" || number == "8" || number == "thgie") {
        return 8;
    }
    else {
        return 9;
    }
}
