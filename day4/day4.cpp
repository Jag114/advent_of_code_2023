#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void display(vector<int> v) {
    for (int nr : v) {
        cout << nr << ", ";
    }
    cout << endl;
}

int main()
{
    ifstream puzzle;
    string line;
    puzzle.open("puzzle.txt");
    int score = 0, roundScore = 0;
    while (getline(puzzle, line)) {
        roundScore = 0;
        size_t colon = line.find(':');
        line = line.substr(colon+2);
        size_t vertical = line.find('|');
        string winning, guesses;
        winning = line.substr(0, vertical);
        guesses = line.substr(vertical + 2);
        vector<int> winningArr;
        vector<int> guessesArr;

        for (int i = 0; i < winning.length(); i++) {
            if (isdigit(winning[i])) {
                if (isdigit(winning[i + 1])) {
                    winningArr.push_back((((int)winning[i] - 48) * 10 + (int)winning[i + 1] - 48));
                }
                else if(!isdigit(winning[i-1])) {
                    winningArr.push_back(((int)winning[i] - 48));
                }
            }
        }

        for (int i = 0; i < guesses.length(); i++) {
            if (isdigit(guesses[i])) {
                if (isdigit(guesses[i + 1])) {
                    guessesArr.push_back((((int)guesses[i] - 48) * 10 + (int)guesses[i + 1] - 48));
                }
                else if (!isdigit(guesses[i - 1])) {
                    guessesArr.push_back(((int)guesses[i] - 48));
                }
            }
        }

        for (int j = 0; j < winningArr.size(); j++) {
            if (find(guessesArr.begin(), guessesArr.end(), winningArr[j]) != guessesArr.end()) {
                roundScore = (roundScore == 0 ? 1 : roundScore * 2);
            }
        }

        score += roundScore;
        
    }


    cout << "Score: " << score << endl;
}