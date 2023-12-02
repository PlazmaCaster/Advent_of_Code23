#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::ifstream infile("input.txt");  // Input file
    char input = '\0';                  // Test each character
    int first = 0;                      // First digit
    int second = 0;                     // Second digit
    int sum = 0;                        // Running sum
    bool newLine = true;                // Determines start of line

    // Is my own file open? (good habit)
    if (infile.is_open()) {

        // Check EACH character
        while (infile.get(input)) {
            // If its a digit do conversion
            if (std::isdigit(input)) {
                if (newLine) {
                    first = input - '0';
                    newLine = false;
                }
                second = input - '0';
            }

            // If its a new line, add to running sum
            if (input == '\n') {
                sum += (10 * first) + second;
                newLine = true;
            }
        }
    }
    // Done :)
    std::cout << sum << '\n';

    return 0;
}