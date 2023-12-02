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
    //57345

    if (!puzzle.is_open()) return -1;

    while (getline(puzzle, line)) {
        char values[2] = {'0', '0'};
        int intPos = -1, stringPos = -1, firstDigitPos = -1, firstWordPos = -1;
        bool stop = false, secondDigit = false, secondWord = false;
        int indexL = -1, indexR = -1;
        string foundViableString;
        for (int i = 0; i < line.length(); i++) {
            stop = false;
            if (isdigit(line[i])) {
                intPos = i;
                firstDigitPos = i;
            }

            for (auto it = viableStrings.begin(); it != viableStrings.end(); it++) {
                size_t posIndex = line.find(*it);
                if (posIndex != string::npos && posIndex < stringPos) {
                    foundViableString = *it;
                    stringPos = posIndex;
                    firstWordPos = posIndex;
                }
            }

            if (intPos != -1 && (intPos < stringPos || stringPos == -1) && stop == false) {
                values[0] = line[i];
                intPos = -1;
                stop = true;
            }
            else if(stringPos != -1 && (stringPos < intPos || intPos == -1)){
                auto p = find(viableStrings.begin(), viableStrings.end(), foundViableString);
                indexL = distance(viableStrings.begin(), p);
                stop = true;
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

            for (auto it = viableStrings.begin(); it != viableStrings.end(); it++) {
                size_t posIndex = line.rfind(*it);
                if (posIndex != string::npos && posIndex > stringPos && firstWordPos != posIndex) {
                    foundViableString = *it;
                    stringPos = posIndex;
                }
            }

            if (intPos != -1 && (intPos > stringPos || stringPos == -1) && stop == false && firstDigitPos != intPos) {
                values[1] = line[i];
                stop = true;
                intPos = -1;
                secondDigit = true;
            }
            else if (stringPos != -1 && (stringPos > intPos || intPos == -1)) {
                values[1] = '0';
                auto p = find(viableStrings.begin(), viableStrings.end(), foundViableString);
                indexR = distance(viableStrings.begin(), p);
                stop = true;
                if (indexL == indexR) {
                    if (firstWordPos == stringPos) {
                        indexR = -1;
                        stop = false;
                    }
                }
                secondDigit = true;
            }
            
            std::cout << "R > L" << endl;
            std::cout << "Values[0] = " << values[0] << endl;
            std::cout << "Values[1] = " << values[1] << endl;
            std::cout << "String pos = " << stringPos << endl;
            std::cout << "String indexR + 1 = " << indexR + 1 << endl;
            
            if (stop) break;
        }
        
        std::cout << "End of getline iteration: " << endl;
        std::cout << "Line: " << line << endl;
        std::cout << "Values[0] = " << (int)values[0] - 48 << endl;
        std::cout << "Values[1] = " << (int)values[1] - 48 << endl;
        std::cout << "indexL + 1 = " << indexL + 1 << endl;
        std::cout << "indexR + 1 = " << indexR + 1 << endl;
        std::cout << "Found string values: " << (indexL + 1) * 10 + indexR + 1 << endl;
        
        if (secondDigit == true) {
            sum = sum + ((int)values[0] - 48) * 10 + (int)values[1] - 48;
        }
        else {
            sum = sum + (int)values[0] - 48;
        }
        
        sum += (indexL + 1) * 10;
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
