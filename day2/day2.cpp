#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

int main()
{
    ifstream puzzle;
    string line;
    int redCount = 12, greenCount = 13, blueCount = 14, sum = 0, powersSum = 0;
    puzzle.open("puzzle.txt");
    vector<string> rounds;
    array<int, 3> powers = {0,0,0};
    int lineNr;

    //which games are POSSIBLE, sum their ID's
    while (getline(puzzle, line)) {
        line += ';';
        int redDie = 0, greenDie = 0, blueDie = 0, additionalErase = 0, minRed = 0, minGreen = 0, minBlue = 0;
        if (isdigit(line[6])) {
            if (isdigit(line[7])) {
                lineNr = ((int)line[5] - 48) * 100 + ((int)line[6] - 48) * 10 + (int)line[7] - 48;
                additionalErase = 2;
            }
            else {
                lineNr = ((int)line[5] - 48) * 10 + (int)line[6] - 48;
                additionalErase = 1;
            }
        }
        else {
            lineNr = (int)line[5] - 48;
        }
        
        cout << lineNr << endl;
        line.erase(line.begin(), line.begin() + (7 + additionalErase)); //start with space
        string round = "";
        char color;
        int gameCounter = 0, gamePossibleCounter = 0;
        cout << "Line: " << line << '\n';

        for (int i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                if (isdigit(line[i + 1]) && !isdigit(line[i-1])) {
                    color = line[i + 3];
                    switch (color)
                    {
                        case 'r':
                            redDie += ((((int)line[i]) - 48) * 10);
                            break;
                        case 'g':
                            greenDie += ((((int)line[i]) - 48) * 10);
                            break;
                        case 'b':
                            blueDie += ((((int)line[i]) - 48) * 10);
                            break;
                        default:
                            break;
                    }
                }
                else {
                    color = line[i + 2];
                    switch (color)
                    {
                        case 'r':
                            redDie += (int)line[i] - 48;
                            break;
                        case 'g':
                            greenDie += (int)line[i] - 48;
                            break;
                        case 'b':
                            blueDie += (int)line[i] - 48;
                            break;
                        default:
                            break;
                    }
                }
                cout << "Red: " << redDie << '\n';
                cout << "Green: " << greenDie << '\n';
                cout << "Blue: " << blueDie << '\n';
                cout << '\n';
            }

            minRed = minRed < redDie ? redDie : minRed;
            minGreen = minGreen < greenDie ? greenDie : minGreen;
            minBlue = minBlue < blueDie ? blueDie : minBlue;


            if (line[i] == ';') {
                if (redDie <= redCount && greenDie <= greenCount && blueDie <= blueCount) {
                    gamePossibleCounter++;
                }
                gameCounter++;
                redDie = 0;
                greenDie = 0;
                blueDie = 0;
            }
        }

        powers[0] = powers[0] < minRed ? minRed : powers[0];
        powers[1] = powers[1] < minGreen ? minGreen : powers[1];
        powers[2] = powers[2] < minBlue ? minBlue : powers[2];
        cout << "Powers: " << powers[0] << ", " << powers[1] << ", " << powers[2] << endl;
        powersSum += powers[0] * powers[1] * powers[2];
        powers = {};
        if (gameCounter == gamePossibleCounter) {
            cout << "Before adding " << lineNr << " to sum = " << sum << endl;
            sum += lineNr;
            cout << "After adding = " << sum << endl;
        }
    }

    cout << "Powers sum: " << powersSum << endl;
    cout << "Sum: " << sum << endl;
}