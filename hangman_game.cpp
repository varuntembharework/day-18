#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

// Struct to hold player guess info
struct Guess {
    char letter;
    bool correct;
};

// Class to handle the hidden word
class Word {
private:
    string secretWord;
    string guessedWord;

public:
    Word(string word) {
        secretWord = word;
        guessedWord = string(word.length(), '_');
    }

    bool guessLetter(char letter) {
        bool found = false;
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (tolower(secretWord[i]) == tolower(letter)) {
                guessedWord[i] = secretWord[i];
                found = true;
            }
        }
        return found;
    }

    bool isComplete() {
        return guessedWord == secretWord;
    }

    string getGuessedWord() {
        return guessedWord;
    }

    string getSecretWord() {
        return secretWord;
    }
};

// Class to display hangman figure
class HangmanFigure {
public:
    void display(int wrongGuesses) {
        switch (wrongGuesses) {
            case 0:
                cout << "\n  +---+\n      |\n      |\n      |\n     ===\n";
                break;
            case 1:
                cout << "\n  +---+\n  O   |\n      |\n      |\n     ===\n";
                break;
            case 2:
                cout << "\n  +---+\n  O   |\n  |   |\n      |\n     ===\n";
                break;
            case 3:
                cout << "\n  +---+\n  O   |\n /|   |\n      |\n     ===\n";
                break;
            case 4:
                cout << "\n  +---+\n  O   |\n /|\\  |\n      |\n     ===\n";
                break;
            case 5:
                cout << "\n  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n";
                break;
            case 6:
                cout << "\n  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n";
                break;
        }
    }
};

// Class to manage the game
class HangmanGame {
private:
    Word word;
    HangmanFigure figure;
    vector<Guess> guesses;
    int maxAttempts;
    int wrongAttempts;

public:
    HangmanGame(string secret, int attempts = 6) 
        : word(secret), maxAttempts(attempts), wrongAttempts(0) {}

    void play() {
        cout << "==============================\n";
        cout << "        HANGMAN GAME\n";
        cout << "==============================\n";
        cout << "Word to guess: " << word.getGuessedWord() << "\n";

        while (wrongAttempts < maxAttempts && !word.isComplete()) {
            char letter;
            cout << "\nEnter a letter: ";
            cin >> letter;
            letter = tolower(letter);

            bool alreadyGuessed = false;
            for (auto &g : guesses) {
                if (g.letter == letter) {
                    cout << "◯ You already guessed '" << letter << "'. Try again.\n";
                    alreadyGuessed = true;
                    break;
                }
            }
            if (alreadyGuessed) continue;

            bool correct = word.guessLetter(letter);
            guesses.push_back({letter, correct});

            if (correct) {
                cout << "✓ Correct guess!\n";
            } else {
                cout << "✗ Wrong guess!\n";
                wrongAttempts++;
            }

            figure.display(wrongAttempts);
            cout << "Word: " << word.getGuessedWord() << "\n";

            cout << "Guessed letters: ";
            for (auto &g : guesses) cout << g.letter << " ";
            cout << "\n";

            cout << "Attempts left: " << maxAttempts - wrongAttempts << "\n";
        }

        if (word.isComplete()) {
            cout << "\n✓ Congratulations! You guessed the word: " 
                 << word.getSecretWord() << "\n";
        } else {
            cout << "\n✗ Game Over! The word was: " 
                 << word.getSecretWord() << "\n";
        }
    }
};

// Main function
int main() {
    srand(time(0));

    // Word bank
    vector<string> words = {"computer", "hangman", "programming", "cplusplus", "developer"};
    string secret = words[rand() % words.size()];

    HangmanGame game(secret);
    game.play();
    return 0;
}