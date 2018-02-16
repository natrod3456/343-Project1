#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameoflife.h"

/**
** A simulator of the Game of Life using 0's and 1's
** @author Natalie Rodriguez
** @version Winter 2018
**/

int main(int argc, char *argv[]){
	int decision;
	int rows;
	int columns;
	int* file;
	
	printf("Welcome to the Game of Life!\n");
	printf("Live cells are shown as 1's\n");
	printf("Dead cells are shown as 0's\n");
	printf("Would you like to load a file (1) or start a new game? (2)\n");
	scanf("%d", &decision);
	
	if(decision == 1){
		printf("Selected to load a file...\n");
		//read_file( char* filename, char **buffer );
		//not working
		exit(1);
	}
	else if(decision == 2){
		printf("Selected to start new game...\n");
		printf("Please input the size of the board to start with!\n");
		printf("Please enter the number of rows:\n");
		scanf("%d", &rows);
		printf("Please enter the number of columns:\n");
		scanf("%d", &columns);
		/**
		** allocating memory
		** http://c-faq.com/aryptr/dynmuldimary.html
		** found out how to do so by using above webpage
		**/
		int **boardgame = malloc(rows * sizeof(int *));
		for(int i = 0; i < rows; i++){
			boardgame[i] = malloc(columns * sizeof(int));
		}
		newGame(rows,columns,boardgame);
		printf("Starting game...\n");
		checkBoard(rows,columns,boardgame);
		printf("Printing new generation..\n");
		for(int s = 0; s < rows; s++){
			for(int k = 0; k < columns; k++){
				printf("%d", boardgame[s][k]);
		}
		printf("\n");
		}
		while(1){
			int choice;
			printf("Would you like to save(1), load(2), play(3), or quit(4)?\n");
			scanf("%d", &choice);
			if(choice == 3){
				printf("Chose to start another generation\n");
				printf("Printing new generation\n");
				checkBoard(rows, columns, boardgame);
				for(int s = 0; s < rows; s++){
					for(int k = 0; k < columns; k++){
						printf("%d", boardgame[s][k]);
					}
					printf("\n");
				}
			}
			if(choice == 4)
				break;
			if(choice == 1){
				write_file(boardgame,rows,columns);
				printf("File saved!\n");
				//save file not working
				//int bytes = sizeof(boardgame);
				//int *file
				//write_file(file,boardgame,bytes);
			}
			if(choice ==2){
				//load not working
				break;
			}
			
		}
		
		printf("All done! Thank you for playing! Freeing arrays!\n");
		/**
		** http://c-faq.com/aryptr/dynmuldimary.html
		** found out how to free all arrays by using above webpage
		**/
		for(int x = 0; x < rows; x++)
			free((void *)boardgame[x]);
		free((void *)boardgame);
		
	}
	else{
		printf("Please enter a 1 or 2\n");
		exit(1);
	}
	return 0;
}

void newGame(int row, int column, int **game){
	int random = 0;
	/**
	** set random 0's and 1's to board
	** http://c-faq.com/lib/randrange.html
	** found out how to do so using above webpage
	**/
	for(int x = 0; x < row; x++){
		for(int y = 0; y < column; y++){
			random = (rand() / (RAND_MAX / 2 +1));
			game[x][y] = random;
		}
	}
	//print out board
	for(int s = 0; s < row; s++){
		for(int k = 0; k < column; k++){
			printf("%d", game[s][k]);
		}
		printf("\n");
	}
}
	
void checkBoard(int row, int column, int **board){
	int deaths = 0;
	int neighbors = 0;
	int alive = 0;
	int revivals = 0;
	for(int i = 0; i <row; i++){
		for(int j = 0; j < column; j++){
				int x = i-1;
				int y = i+1;
				int a = j-1;
				int b = j+1;
				if(j != 0 && board[i][a] == 1)
					neighbors++;
				if(j != column-1 && board[i][b] == 1)
					neighbors++;
				if(i != 0 && board[x][j] == 1)
					neighbors++;
				if(i != row-1 && board[y][j] == 1)
					neighbors++;
				if(i != 0 && j != 0 && board[x][a] == 1)
					neighbors++;
				if(i != 0 && j != column-1 && board[x][b] == 1)
					neighbors++;
				if(i != row-1 && j != column-1 && board[y][b] == 1)
					neighbors++;
				if(i != row-1 && j != 0 && board[y][a] == 1)
					neighbors++;

				if(board[i][j] == 1){
					if(neighbors < 2 || neighbors > 3){
						board[i][j] = 0;
						deaths++;
					}
					else
						alive++;	
				}
				
				if(board[i][j] == 0){
					if(neighbors == 3){
						board[i][j] = 1;
						revivals++;
					}
				}
				
				neighbors = 0;

			}
	}
	printf("There have been %d death(s) due to underpopulation or overcrowding\n", deaths);
	printf("%d cell(s) have lived for another generation\n", alive);
	printf("There have been %d revival(s)\n", revivals);
}	

int read_file(int **board, int row, int column){
	FILE *fp;
	int i;
	int rows = 0;
	int columns = 0;
	//if(fp = fopen("save","rb") == NULL){
	//	printf("file could not be opened\n");
	//}
	//while((i = fgetc(fp))!= EOF){
	//	if(i == '\n')
	//		rows++;
	//}
	//while((i = fgetc(fp))!= EOF){
	//	if(i != '\n')
	//		column++;
	//}
	//fread(board,sizeof(int), row*column,fp);
	//fclose(fp);
	return 0;
}

int write_file(int **board, int row, int column){
	FILE *fp;
	fp = fopen("save","wb");
	//fwrite(board,sizeof(int), row*column, fp);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			fprintf(fp,"%d",board[i][j]);
		}
		if(i != row-1)
			fprintf(fp,"\n");
	}
	fclose(fp);
	return 0;
}
