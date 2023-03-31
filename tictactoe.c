#include <stdio.h>
#include <stdlib.h>

// Declare the board as a 3x3 array of characters
char board[3][3];

// Function to initialize the board
void init_board() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board
void print_board() {
    int i, j;
    printf("\n");
    for (i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i != 2) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n");
}

// Function to check if a player has won
int check_win(char player) {
    int i, j;
    // Check rows
    for (i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
    }
    // Check columns
    for (j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) {
            return 1;
        }
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1;
    }
    // If no win conditions are met, return 0
    return 0;
}

// Function to get the player's move
void get_move(char player, int *row, int *col) {
    printf("Player %c, enter row (1-3): ", player);
    scanf("%d", row);
    printf("Player %c, enter column (1-3): ", player);
    scanf("%d", col);
    // Adjust row and column to 0-based indexing
    *row -= 1;
    *col -= 1;
}

int main() {
    int row, col, i, j;
    char player = 'X';
    init_board();
    printf("Welcome to Tic Tac Toe!\n");
    printf("Player 1 is X, Player 2 is O.\n");
    printf("The board is numbered from 1 to 3, left to right.\n");
    print_board();
    for (i = 0; i < 9; i++) {
        get_move(player, &row, &col);
        while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Please try again.\n");
            get_move(player, &row, &col);
        }
        board[row][col] = player;
        print_board();
        if (check_win(player)) {
            printf("Player %c wins!\n", player);
            return 0;
        }
        // Switch players
        if (player == 'X') {
            player = 'O';
        } else {
            player = 'X';
        }
    }
    // If there is no winner after 9 moves, the game is a tie
    printf("It's a tie!\n");
    return 0;
}
