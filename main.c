#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char board[4][4], currentplayer;
ssize_t inputLength;
size_t bufferSize = 0;
char *input = NULL;
int row, column, playerNo, isNumber;

void initBoard() {
  board[0][0] = ' ';
  board[0][1] = '1';
  board[0][2] = '2';
  board[0][3] = '3';
  board[1][0] = '1';
  board[1][1] = '_';
  board[1][2] = '_';
  board[1][3] = '_';
  board[2][0] = '2';
  board[2][1] = '_';
  board[2][2] = '_';
  board[2][3] = '_';
  board[3][0] = '3';
  board[3][1] = '_';
  board[3][2] = '_';
  board[3][3] = '_';
}

void printBoard() {
  printf("\n");
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

void removeInputNewLine() {
  inputLength = strlen(input);
  if (input[inputLength - 1] == '\n') {
    input[inputLength - 1] = '\0';
    inputLength--;
  }
}

void validateIfNumber() {
  isNumber = 1;
  for (int i = 0; i < inputLength; i++) {
    if (!isdigit(input[i])) {
      isNumber = 0;
      break;
    }
  }
}

int checkIfWon() {
  // player 1 - horizontal
  if ((board[1][1] == 'X' && board[1][2] == 'X' && board[1][3] == 'X') ||
      (board[2][1] == 'X' && board[2][2] == 'X' && board[2][3] == 'X') ||
      (board[3][1] == 'X' && board[3][2] == 'X' && board[3][3] == 'X')) {
    return 1;
  }

  // player 1 - vertical
  if ((board[1][1] == 'X' && board[2][1] == 'X' && board[3][1] == 'X') ||
      (board[1][2] == 'X' && board[2][2] == 'X' && board[3][2] == 'X') ||
      (board[1][3] == 'X' && board[2][3] == 'X' && board[3][3] == 'X')) {
    return 1;
  }

  // player 1 - diagonal
  if ((board[1][1] == 'X' && board[2][2] == 'X' && board[3][3] == 'X') ||
      (board[3][1] == 'X' && board[2][2] == 'X' && board[1][3] == 'X')) {
    return 1;
  }

  // player 2 - horizontal
  if ((board[1][1] == 'O' && board[1][2] == 'O' && board[1][3] == 'O') ||
      (board[2][1] == 'O' && board[2][2] == 'O' && board[2][3] == 'O') ||
      (board[3][1] == 'O' && board[3][2] == 'O' && board[3][3] == 'O')) {
    return 1;
  }

  // player 2 - vertical
  if ((board[1][1] == 'O' && board[2][1] == 'O' && board[3][1] == 'O') ||
      (board[1][2] == 'O' && board[2][2] == 'O' && board[3][2] == 'O') ||
      (board[1][3] == 'O' && board[2][3] == 'O' && board[3][3] == 'O')) {
    return 1;
  }

  // player 2 - diagonal
  if ((board[1][1] == 'O' && board[2][2] == 'O' && board[3][3] == 'O') ||
      (board[3][1] == 'O' && board[2][2] == 'O' && board[1][3] == 'O')) {
    return 1;
  }

  return 0;
}

void play() {
  row = input[0] - '0';
  column = input[1] - '0';

  if (board[row][column] == '_') {
    board[row][column] = currentplayer;
    if (!checkIfWon()) {
      if (currentplayer == 'X') {
        playerNo = 2;
        currentplayer = 'O';
      } else if (currentplayer == 'O') {
        playerNo = 1;
        currentplayer = 'X';
      }
    }
  } else {
    printf("That spot is already taken!\n");
  }
}

int main() {
  currentplayer = 'X';
  playerNo = 1;
  initBoard();
  printf("\nWelcome to Tic Tac Toe!\n");
  while (1) {
    printBoard();
    if (checkIfWon()) {
      printf("Player %d has won!\n\n", playerNo);
      break;
    }
    printf("Player %d, enter your move (row column): ", playerNo);
    inputLength = getline(&input, &bufferSize, stdin);
    removeInputNewLine();
    validateIfNumber();

    if (strcmp(input, "exit") == 0) {
      printf("Exiting the game.\n\n");
      break;
    }

    play();

    if (!isNumber || inputLength > 2 || row > 3 || column > 3 ||
        inputLength < 2) {
      printf("Invalid input!\n");
      continue;
    }
  }

  free(input);

  return 0;
}
