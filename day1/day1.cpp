#include <iostream>
#include <string>
#include <fstream>
#include <array>

using namespace std;

int main()
{
    ifstream puzzle;
    string line;
    int sum = 0;
    array<string, 9> viableStrings = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" }; //index + 1 = value
    puzzle.open("test.txt");

    if (!puzzle.is_open()) return -1;

    while (getline(puzzle, line)) {
        char values[2] = {};
        int intPos = -1, stringPos = -1;
        bool stop = false;
        int indexL = 0, indexR = 0;
        string foundViableString;
        for (int i = 0; i < line.length(); i++) {
            stop = false;
            if (isdigit(line[i])) {
                intPos = i;
            }

            for (auto it = viableStrings.begin(); it != viableStrings.end(); it++) {
                size_t posIndex = line.find(*it);
                foundViableString = *it;
                if (posIndex != string::npos) {
                    stringPos = posIndex;
                    break;
                }
            }

            if (intPos != -1 && stringPos != -1 && intPos > stringPos) {
                values[0] = line[i];
            }
            else {
                values[0] = '0';
                auto p = find(viableStrings.begin(), viableStrings.end(), foundViableString);
                indexL = distance(viableStrings.begin(), p);
            }

            std::cout << "L > R" << endl;
            std::cout << "Values[0] = " << values[0] << endl;
            std::cout << "Values[1] = " << values[1] << endl;
            std::cout << "String pos = " << stringPos << endl;
            std::cout << "String indexL + 1 = " << indexL + 1 << endl;
            if (stop) break;
        }

        for (int i = line.length() - 1; i >= 0; i--) {
            stop = false;
            if (isdigit(line[i])) {
                intPos = i;
            }

            for (auto it = viableStrings.end() - 1; it != viableStrings.begin(); it--) {
                size_t posIndex = line.rfind(*it);
                foundViableString = *it;
                if (posIndex != string::npos) {
                    stringPos = posIndex;
                    break;
                }
            }

            if (intPos != -1 && stringPos != -1 && intPos > stringPos) {
                values[0] = line[i];
            }
            else {
                values[0] = '0';
                auto p = find(viableStrings.begin(), viableStrings.end(), foundViableString);
                indexR = distance(viableStrings.begin(), p);
            }

            std::cout << "R > L" << endl;
            std::cout << "Values[0] = " << values[0] << endl;
            std::cout << "Values[1] = " << values[1] << endl;
            std::cout << "String pos = " << stringPos << endl;
            std::cout << "String index + 1 = " << indexR + 1 << endl;
            if (stop) break;
        }

        std::cout << "End of getline iteration: " << endl;
        std::cout << "Values[0] = " << (int)values[0] - 48 << endl;
        std::cout << "Values[1] = " << (int)values[1] - 48 << endl;
        std::cout << "indexL + 1 = " << indexL + 1 << endl;
        std::cout << "indexR + 1 = " << indexR + 1 << endl;
        sum = sum + ((int)values[0] - 48) * 10 + (int)values[1] - 48;
        sum += indexL + 1;
        sum += indexR + 1;
        std::cout << "Sum: " << sum << endl;
        std::cout << endl;
        std::cout << endl;
        std::cout << endl;
        std::cout << endl;

    }
    std::cout << sum << endl;
    puzzle.close();
    return 0;
}
