#ifndef GAME_H
#define GAME_H

//read file
int read_file( char* filename, char **buffer );

//write to file
int write_file( char* filename, char **buffer, int size);

//starts and prints new game board
void newGame(int rows, int columns, int **board);

//checks board for underpopulation, overpopulation, or reviving cells
void checkBoard(int row, int column, int **board);

//driver
int main(int argc, char *argv[]);

#endif