/**
 **
 * @author Miao He mhe23@myseneca.ca
 * @version 1.0
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

void playBattleship(void);//
void loadShips(char board[], char ship[]);//
void initGame(char board[], char mask[]);//
void drawGame(char mask[], int missilesFired, int missilesRemaining, int
	score, char previousMove[]);//
int checkMove(char coord[]);
void updateData(char board[], char mask[], int *missilesFired, int
	*missilesRemaining, int *score, char previousMove[], char currentMove[]);

int main() {
	playBattleship();
	getchar();
	return 0;
}

void playBattleship(void){
	//definiation
	//define board,mask, and any variables you need in this function
	char mask[391];
	char board[391];
	int missilesFired = 0, missilesRemaining = 100, score = 0;
	char currentMove[3];
	char previousMove[11] = "NA";
	int coord;

	initGame(board, mask);
	while (missilesRemaining != 0 && score != 110){
		drawGame(mask, missilesFired, missilesRemaining, score, previousMove);

		do{
			printf("Enter Target Coordinates--> ");
			scanf("%2[^/n]", currentMove);
			getchar();
			coord = checkMove(currentMove);
			if (coord == -1)
				printf("Sorry... '%s' is not a valid coordinate... Try again!\n", currentMove);
		} while (coord == -1);

		updateData(board, mask, &missilesFired, &missilesRemaining, &score, previousMove, currentMove);
	}//while (missilesRemaining != 0)
	int i, j;
	if (missilesFired == 100)
		{
		printf("Sorry... You lost the WAR!\n");
		printf("   C Battleship...\n");
		printf("   ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
		for (i = 0; i<15; i++) {               
			if (i < 9) {
				printf(" %c|", i + 1 + '0');  
			}
			else {
				printf(" %c|", i + 1 + 55);    
			}
			for (j = 0; j<26; j++) {            
				printf("%c", mask[j + (i * 26)]);
			}
			printf("|\n");
	}}
	else if (score == 110){

		printf("Hooray... You SUNK ALL the Battleships! You won the WAR!\n");
	        printf("   C Battleship...\n");
                printf("   ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
                for (i = 0; i<15; i++) {               
                        if (i < 9) {
                                printf(" %c|", i + 1 + '0'); 
                        }
                        else {
                                printf(" %c|", i + 1 + 55);    
                        }
                        for (j = 0; j<26; j++) {            
                                printf("%c", mask[j + (i * 26)]);
                        }
                        printf("|\n");

	}
}
}
void initGame(char board[], char mask[])
{
	int i, j;
	for (i = 0; i<390; i++)
	{
		board[i] = '~';
		mask[i] = '~';
	}
	board[390] = mask[390] = '\0';
	//define the ships
	char aircraft[9] = "[CCCCC=>";
	char destory[7] = "[DDD=>";
	char submarines[6] = "[SS=>";
	char frigate[4] = "[F>";
	//calls the "loadShips" function 4 times (once for each ship)
	loadShips(board, aircraft);
	loadShips(board, destory);
	loadShips(board, submarines);
	loadShips(board, frigate);



}
void loadShips(char board[], char ship[])

{
	//step1: calculate the length of each ship
	//step2:randomly choose a position for the ships
	//and load ships

	int length, row, col, i;
	int isEmpty = 1; //0 -false, 1 -true
	int count;

	if (ship[1] == 'C')
		length = 8;
	else if (ship[1] == 'D')
		length = 6;
	else if (ship[1] == 'S')
		length = 5;
	else if (ship[1] == 'F')
		length = 3;

	srand(time(NULL));

	do{
		isEmpty = 1;
		row = rand() % 15;//0-14
		col = rand() % (26 - length);//0-25
		//check if the position of row and col are OK
		//copy the ships
		i = row * 26 + col;
		for (count = 0; count < length; count++)
		{
			if (board[i] != '~')
				isEmpty = 0;
			i++;
		}
	} while (isEmpty == 0);

	i = i - length;
	for (count = 0; count < length; count++)
	{
		board[i] = ship[count];
		i++;
	}
}

void drawGame(char mask[], int missilesFired, int missilesRemaining, int
	score, char previousMove[])
{

	int i, j;

	printf("   C Battleship...\n");
	printf("   ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
	for (i = 0; i<15; i++) {                /* display 15 rows of information
											(incl. border) */
		if (i < 9) {
			printf(" %c|", i + 1 + '0');   /* for each digit character */
		}
		else {
			printf(" %c|", i + 1 + 55);    /* for each alphabetic character
										   'A' through 'F' */
		}
		for (j = 0; j<26; j++) {             /* display all 26 columns in
their background and musical genres, faith and freedom, and song’s theme. 											 
eachrow */
			printf("%c", mask[j + (i * 26)]);
		}
		printf("|\n");
	}//for (i = 0; i<15; i++)

	printf("Missiles Fired: %02d  Missiles Remaining: %03d\n", missilesFired, missilesRemaining);
	printf("Current  Score: %03d Previous Move: %s\n", score, previousMove);
}

int checkMove(char coord[])
{
	int row, col, i, c = 0;
	int valid = 0;

	char rows[16] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };//15
	char columns[27] = { 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };//27
	for (i = 0; i < 16; i++)
	{
		if (coord[0] == rows[i])
		{
			row = i;
			valid = 1;
		}
	}
	if (valid){
		valid = 0;
		for (i = 0; i < 27; i++)
		{
			if (coord[1] == columns[i])
			{
				col = i;
				valid = 1;
			}
		}
	}

	if (valid)
		i = row * 26 + col;
	else
		i = -1;

	return i;

}


void updateData(char board[], char mask[], int *missilesFired, int
	*missilesRemaining, int *score, char previousMove[], char currentMove[])
{
	int i;

	*missilesFired += 1;
	*missilesRemaining -= 1;

	 i = checkMove(currentMove);
	
	if (board[i] != '~')
	{

		mask[i] = board[i];
		//mask[i] = {'HIT'};
		*score = *score + 5;
		strcpy(previousMove, "HIT on ");//"HIT on "
		strcat(previousMove, currentMove);
	}
	else
	{
		mask[i] = 'X';
		strcpy(previousMove, "MISS on ");//"MISS on "
		strcat(previousMove, currentMove);
	}

}

