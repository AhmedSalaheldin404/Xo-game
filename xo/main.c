#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_ATTEMPTS 10
#define WORD_COUNT 100
#define WORD_LENGTH 20

const char* chooseRandomWord(const char** wordList, int count) {
    srand(time(NULL));
    return englishWords[rand() % count];
}

void showWord(const char* word, const char* guessedChars) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (strchr(guessedChars, word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int validateGuess(const char* word, char guess) {
    return strchr(word, guess) != NULL;
}

int main() {
    const char* wordList[WORD_COUNT] = {english_words}; // Assuming english_words is an array of words
    const char* selectedWord = chooseRandomWord(wordList, WORD_COUNT);
    char guessedChars[27] = ""; // To store guessed letters
    int attempts = MAX_ATTEMPTS;

    printf("Welcome to Hangman!\n");
    printf("Guess the word (you have %d attempts):\n", attempts);
    showWord(selectedWord, guessedChars);

    while (attempts > 0) {
        char guess;
        printf("Enter your guess: ");
        scanf(" %c", &guess);

        if (strchr(guessedChars, guess)) {
            printf("You already guessed '%c'. Try another letter.\n", guess);
            continue;
        }

        guessedChars[strlen(guessedChars)] = guess;

        if (validateGuess(selectedWord, guess)) {
            printf("Correct guess!\n");
        } else {
            printf("Incorrect guess!\n");
            attempts--;
        }

        printf("Attempts left: %d\n", attempts);
        showWord(selectedWord, guessedChars);

        int correct = 1;
        for (int i = 0; i < strlen(selectedWord); i++) {
            if (!strchr(guessedChars, selectedWord[i])) {
                correct = 0;
                break;
            }
        }

        if (correct) {
            printf("Congratulations! You've won!\n");
            break;
        }
    }

    if (attempts == 0) {
        printf("Sorry, you've run out of attempts.\n");
        printf("The word was: %s\n", selectedWord);
    }

    return 0;
}
