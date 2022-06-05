/******************************************************************************


						 Theodore Luna et Louis Gagneux

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void level();	
void easy();	
void medium();	
void custom();	
void guess();
void loose();
void minefield1();	
void minefield2();
void minefield3();
void win();
void scoreboard();
void restart();	
void goodbye();

char mode[20];	//this char will be used to defind the level in the scoreboard
char pseudo[20];	//this char will be used to defind the name of the player in the scoreboard
int  flag = 'F';	
int x, y;		//variable used for the minefield
int L, C, O, S;	//L is for lines, C for columns. the variable O will be used for restart function and S for scoreboard function
float lvl;		//variable used to choose the difficulty
float diff1;  //variable used when you have to choose between placing a flag and discovering a box
int mines = 0;	//This variable is the total of bombs
int M = 0;	//This variable is the number of bombs
int minefield[30][30];		//This contains all of the mines, numbers and blank spaces
int minefield4[30][30];	//This contains the minefield full of '|~|' characters
int minefield5[30][30];
time_t t1;	//This will be used as a timer for the scoreboard
time_t t2;	//This will be used as a timer for the scoreboard
FILE* fichier = NULL;


int main()	//This is the main menu. The rules of the game are exposed as well as the different levels.
{

	printf("\t\tWelcome to Minsweeper de Theodore et Louis\n\n");
	printf("Minesweeper is a puzzle video game whose goal is to locate mines hidden in a grid representing a virtual minefield, with the only indication being the number of mines in adjacent areas.\n\n");
	printf("There are 3 levels in this game :\n");
	printf("\t-The first level is easy and includes a 9x9 grid as well as 10 bombs.\n");
	printf("\t-The second level is medium and includes a 16x16 grid as well as 40 bombs.\n");
	printf("\t-The third level is a custom mode: you choose the size of the grid and the number of bombs!\n");

	level();	//Function for choosing the level
	return 0;
}

void level()		//Function for choosing the level
{
	time(&t1);	//start of the timer

	lvl = 0;
	while ((lvl != 1) && (lvl != 2) && (lvl != 3))
	{
		printf("\n\tChoose the level : ");
		printf("\n\t-Enter 1 for easy\n\t-Enter 2 for medium\n\t-Enter 3 for custom\n ");		//the player selects the level he wants
		scanf("%f", &lvl);
		if ((lvl != 1) && (lvl != 2) && (lvl != 3))
		{
			printf("\t\tYou took a level that doesn't exist\n\t Please enter either 1, 2, 3\n");	//If the player chooses a level that doesn't exist
		}
	}

	if (lvl == 1)		//If the player chooses the easy difficulty
	{
		easy();
	}
	else if (lvl == 2)		//if the player chooses the medium difficulty
	{
		medium();
	}
	else if (lvl == 3)		//if the player chooses the custom difficulty
	{
		custom();
	}
}

void easy()			//Gives the minefield the 'easy' grid and mines
{
	printf("\t\tyou chose easy mode\n\n");
	L = 10;		//we add one to the number of grid and column because there is one which is used to identify the coordinates of a square on the grid
	C = 10;		
	mines = 10;
	minefield1();		//Function that generates the minefield
	guess();
}

void medium()		//Gives the minefield the 'medium' grid and mines
{
	printf("\t\tyou chose medium mode\n\n");
	L = 17;		//we add one to the number of grid and column because there is one which is used to identify the coordinates of a square on the grid
	C = 17;		
	mines = 40;
	minefield1();		//Function that generates the minefield
	guess();
}

void custom()		//Gives the minefield the 'custom' grid and mines
{
	printf("\t\tyou chose custom mode\n\n");
	L = 0;
	C = 0;
	while (C < 2)
	{
		printf("\t\tEnter the dimension of the grid :\n");		//we ask the player the dimension
		scanf("%d", &C);
		if (C < 2)
		{
			printf("\t\t The grid is too small to be able to play!\n\t Enter a valid number :\n");	//this is here to assure the game to work because we can't play on 1x1 or 0x0 grid
			scanf("%d", &C);
		}
	}

	L = C;
	
	printf("\t\t Enter the number of mines you want to assign to the board :\n");		//we ask the number of bomb
	scanf("%d", &mines);

	while (mines >= C * L)
	{
		if (mines = C * L)
		{
			printf("\t\t There are as many bombs as squares, it's a little too simple!\n\t Enter a valid number of bombs :\n");		//we can't have a grid with the same number of bombs as squares
			scanf("%d", &mines);
		}
		if (mines > C * L)
		{
			printf("\t\t There are more bombs than possible squares, that's a problem!\n\t Enter a valid number of bombs :\n");		//moreover, having more bombb than squares is impossible
			scanf("%d", &mines);
		}
	}
	C = C++;	//we add one to the number of grid and column because there is one which is used to identify the coordinates of a square on the grid
	L = C;		//there are the same number of lines and columns
	minefield1();		//Function that generates the minefield
	guess();
}

void minefield1()		//Function that generates the minefield
{

	srand(time(NULL));		
	int i;
	int j;

	for (int j = 0; j < C; j++)		//creating all the line and column in grill
	{
		for (int i = 0; i < L; i++)
		{
			minefield[i][j] = '~';		//'~' will be used for all square cover
			minefield4[i][j] = minefield[i][j];		//we have the same grid for all minefield
			minefield5[i][j] = minefield[i][j];		//
		}
	}
	M;
	while (M < mines)		//we are generating the bombs randomly
	{
		i = rand() % (L);		//% random chance to creat a bomb
		j = rand() % (C);		//% random chance to creat a bomb
		if (minefield[i][j] != '*')		//because we don't want to have 2 bombs at the same square
		{
			minefield[i][j] = '*';		//so there is only one bomb
			minefield5[i][j] = minefield[i][j];
			M++;
		}
	}
	//i = 0;
	//j = 0;

	for (int j = 0; j < C; j++)			//that will creat the number around the bomb
	{
		for (int i = 0; i < L; i++)
		{
			if (minefield[i][j] != '*')		//if there nothing, the number is 0
			{
				minefield[i][j] = 0;
			}
			for (int k = -1; k < 2; k++)		//we add 1 for each bo
			{
				for (int r = -1; r < 2; r++)
				{
					if ((minefield[i + k][j + r] == '*') && (minefield[i][j] != '*'))
					{
						minefield[i][j]++;
					}
				}
			}
		}
	}
}


void minefield2()		// This function prints the minefield
{
	int i = 0, j = 0, z = 0;
	for (z = 0; z < L; z++)			
	{
		if (z == 0)
		{
			printf("\t");
		}
		printf("|%d|\t", z);
	}
	printf("\n\n");

	for (j = 0; j < C; j++)			                     
	{
		printf("|%d|\t", j);
		for (i = 0; i < L; i++)
		{
			if (minefield4[i][j] == '~')
			{
				printf("|%c|\t", minefield4[i][j]);

			}
			else if (minefield[i][j] == 0)	//This changes any spaces with values of zero to the character 'B'
			{
				minefield4[i][j] = 'B';
				printf("|%d|\t", minefield4[i][j]);
			}

			/* else if (minefield[i][j] == 'F')	// This changes any spaces with values of zero to the character 'F'
			   {
				 minefield4[i][j] = '~';
				 printf ("|%c|\t", minefield4[i][j]);
			   }*/
			else
			{
				printf("|%d|\t", minefield4[i][j]);

			}
		}
		printf("\n");
	}
}


void guess()		//function who will reveal the square
{
	int q = 0, i = 0, j = 0, match = 0;
	minefield2();
	for (j = 0; j < C; j++)			
	{
		for (i = 0; i < L; i++)
		{
			if (minefield[i][j] == minefield4[i][j])
			{
				match++;
			}
		}
	}
	if (match == ((L * C) - mines))	
	{
		win();		
	}

	diff1 = 0;
	while ((diff1 != 1) && (diff1 != 2))		//to assure that the player only choose 1 or 2

	{
		printf("\t\t You have %d mines left to find \n\n", M);	
		printf("\t\tChoose between 1- Discover a box or 2- put a flag:");
		scanf("%f", &diff1);
		if ((diff1 != 1) && (diff1 != 2))
		{
			printf("\t\tPlease enter either 1, 2\n");
		}
	}
	if (diff1 == 1)
	{

		printf("\nEnter the line of the square you want to uncover :");		//if the player want to uncover a square, we ask the position of the square
		scanf("%d", &x);	
		printf("\nEnter the column of the square you want to uncover :");
		scanf("%d", &y);

		if ((x >= L) || (x < 0) || (y < 0) || (y >= C))
		{
			printf("\nPlease enter a value inside the grid\n");
			guess();
		}
		if (minefield[x][y] == '*')	// Runs the loose() function if the user selects a mine
		{
			loose();
		}
		if (minefield4[x][y] != '~')
		{
			printf
			("\nPlease enter a value that has not already been entered\n");
			guess();
		}

		else			//Checks if the adjacent spaces are blank, then changes the values in the minefield4 array. Because they are changed, they will now print out in the print_minefield function
		{
			minefield4[x][y] = minefield[x][y];
			if (minefield[x][y] == 0)
			{
				for (int k = -1; k < 2; k++) {
					for (int r = -1; r < 2; r++) {
						if (minefield[x + k][y + r] == 0)
						{
							if (k != 0 || r != 0)
							{
								minefield4[x + k][y + r] = minefield[x + k][y + r];
							}
						}
					}
				}

			}

			guess();

		}

	}
	else
	{

		printf("\nEnter the line of the flag you want to place :");		//we ask the place of the flag
		scanf("%d", &x);

		printf("\nEnter the column of the flag you want to place :");
		scanf("%d", &y);

		if ((x >= L) || (x < 0) || (y < 0) || (y >= C))		//if the value isn't in the grid
		{
			printf("\nPlease enter a value inside the grid\n");
			guess();
		}
		if (minefield4[x][y] == '/')
		{
			minefield4[x][y] = '~';
			guess();

		}
		else
		{
			minefield4[x][y] = '/';
			guess();
		}
	}
}

void loose()			// Runs the minefield3 function, then the scoreboard function                    
{
	minefield3();
	printf("\n\t\tYou hit a mine at %d,%d\n\t\tYOU LOSE!!!!", x, y);
	scoreboard();
}

void minefield3()	// Prints the minefield, showing where all of the mines are placed
{
	int i = 0, j = 0, z = 0;
	while (z < L)
	{
		if (z == 0)
		{
			printf("\t");
		}
		printf("|%d|\t", z);
		z++;
	}
	printf("\n\n");

	while (j < C)
	{
		printf("|%d|\t", j);
		while (i < L)
		{
			printf("|%c|\t", minefield5[i][j]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
}

void win()			//function when you win the game
{
	time(&t2);
	printf("\tYOU WIN!!!!!\n");


	printf("Enter your name:\n ");		//ask your name and game mode for the scoreboard fonction
	scanf("%s", pseudo);
	printf("Enter your game mode (easy , medium or custom) \n ");
	scanf("%s", mode);

	fichier = fopen("score.txt", "w");		//.txt file where will be write the score

	if (fichier != NULL)
	{
		char str[100] = "";
		strncat(str, pseudo, 20);
		strncat(str, " completed the mode ", 20);
		strncat(str, mode, 20);
		strncat(str, " in ", 5);
		char arr[20];		//memcpy(arr,&a,sizeof(a)+1);
		sprintf(arr, "%lf", difftime(t2, t1));
		strncat(str, arr, 20);
		strncat(str, " seconds ", 20);		//pseudo + " completed the mode " + mode + "in" + difftime(t2,t1);
		fputs(str, fichier);
		fclose(fichier);		//we close the file
	}
	scoreboard();		//function where we ask if the player want to show the scoreboard
}

void scoreboard()		//the function who will show the scoreboard
{
	S = 0;
	while ((O != 1) && (O != 2))		//we make sure that the player chooses the two available options which are to see the scoreboard or not
	{
		printf("\n\t\tWould you like to see the scoreboard ?");
		printf("\n\t\t-1 for yes\n\t\t-2 for no\n\t\t");
		scanf("%d", &S);

		if (S == 1)		//if he writes 1 then the program show the scoreboard
		{
			FILE* f;
			char c;
			f = fopen("score.txt", "rt");//We open the .txt file where there is scoreboard data
			while ((c = fgetc(f)) != EOF)
			{
				printf("%c", c);
			}
			fclose(f);
			restart();		//the function where if the player wants, he can play again
		}
		if (S == 2)		//if he writes 1 then the program doesn't show the scoreboard
		{
			restart();		//the function where if the player wants, he can play again
		}
		else
		{
			printf("Please enter either 1 or 2\n\t\t");		//if the player doesn't write 1 or 2
			scoreboard();		//we restart the scoreboard function
		}
	}
}

void restart()		//If the player wants, he can play again
{
	O = 0;
	while ((O != 1) && (O != 2))		//we make sure that the player chooses the two available options which are to play again or not
	{
		printf("\n\t\tWould you like to play again ?:");
		printf("\n\t\t-1 for yes\n\t\t-2 for no\n\t\t");
		scanf("%d", &O);
	}

	if (O == 1)		//if he writes 1 then he plays again
	{
		main();		//so return to the level selection function
	}
	else if (O==2)		//if he writes 1 then he doesn't play again
	{
		goodbye();		//the function who end the game
	}
	else
	{
		printf("Please enter either 1 or 2\n\t\t");		//if the player doesn't write 1 or 2
		restart();		//we restart the restart function
	}
}

void goodbye()		//the function who end the program
{
	printf("\n\n\t\tGoodbye and see you next time to play again !");
	exit(1);
}
