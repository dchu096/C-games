#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int guess, number, max_tries, tries;
    char play_again;
    srand(time(0));
    do {
        tries = 0;
        number = rand() % 100 + 1;
        printf("Guess the number between 1 and 100 in less than 5 tries.\n");
        max_tries = 5;
        do {
            printf("Enter your guess: ");
            scanf("%d", &guess);
            tries++;
            if (guess > number) {
                printf("Too high!\n");
            } else if (guess < number) {
                printf("Too low!\n");
            } else {
                printf("Congratulations, you guessed it in %d tries!\n", tries);
                break;
            }
            if (tries == max_tries) {
                printf("Sorry, you didn't guess the number in %d tries. The number was %d.\n", max_tries, number);
                break;
            }
        } while (1);
        printf("Do you want to play again? (y/n) ");
        scanf(" %c", &play_again);
    } while (play_again == 'y' || play_again == 'Y');
    return 0;
}
