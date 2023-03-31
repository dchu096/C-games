#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORD_LEN 20
#define MAX_GUESSES 7
#define NUM_WORDS 5

char* word_list[] = {"apple", "banana", "orange", "grape", "pineapple"};

int main() {
    char* word;
    char guessed[MAX_WORD_LEN+1];
    char guess;
    int num_guesses = 0;
    int word_len, i, j, correct_guesses;
    int letters_left = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Pick a random word from the list
    word = word_list[rand() % NUM_WORDS];
    word_len = strlen(word);

    // Initialize the guessed array
    for (i = 0; i < word_len; i++) {
        guessed[i] = '_';
    }
    guessed[word_len] = '\0';

    // Loop until the player guesses the word or runs out of guesses
    while (num_guesses < MAX_GUESSES && strcmp(word, guessed) != 0) {
        printf("\n%s\n", guessed);
        printf("Guess a letter (%d guesses left): ", MAX_GUESSES - num_guesses);
        scanf(" %c", &guess);
        guess = tolower(guess);

        // Check if the letter has already been guessed
        for (i = 0; i < word_len; i++) {
            if (guessed[i] == guess) {
                printf("You already guessed that letter!\n");
                break;
            }
        }
        if (i < word_len) {
            continue;
        }

        // Check if the letter is in the word
        correct_guesses = 0;
        for (i = 0; i < word_len; i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                correct_guesses++;
            }
        }
        if (correct_guesses == 0) {
            printf("Sorry, '%c' is not in the word.\n", guess);
            num_guesses++;
        } else {
            printf("Good guess!\n");
        }
    }

    // Display the result
    if (num_guesses < MAX_GUESSES) {
        printf("\nCongratulations, you guessed the word: %s\n", word);
    } else {
        printf("\nSorry, you ran out of guesses. The word was: %s\n", word);
    }

    return 0;
}
