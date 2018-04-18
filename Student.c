#if 0
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"

                // assume that this is player_1 1, X
int* getMove(int board[][SIZE], int *move)
{
  do
  { move[0] = rand()%SIZE;
    move[1] = rand()%SIZE;
  }while (checkMove(board, move) == 0);

  return move;
}
#endif
#if 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Student.h"
#include "Instructor.h"
                // assume that this is player_1 1, X
const int player_1 = 1;
const int opponent_1 = 2;
double MAX_1 = 1.0/0.0;
double MIN_1 = -1.0/0.0;

typedef struct move_player
{
	int row, col;
}Move;

double max_1(double a, double b)
{
    if (a>b)
        return a;
    else
        return b;
}
double min_1(double a, double b)
{
    if (a<b)
        return a;
    else
        return b;
}


/*===============================================================================*/


/*===============================EVALUATION======================================*/
// This is the evaluation function
double evaluate_1(int board[][SIZE])
{
	int row, col;
	
	/*================================================================================*/
	// Checking for Rows for X or O victory.
	// Check case of 5 in a row.
	for (row = 0; row<SIZE-4; row++)
	{
		for (col = 0; col<SIZE-4; col++)
		{
			// Horizontal -> left to right
			if (board[row][col]==board[row][col+1]   &&
				board[row][col+1]==board[row][col+2] && 
				board[row][col+2]==board[row][col+3] &&
				board[row][col+3]==board[row][col+4])
			{
				if (board[row][col]==player_1)
					return +10000000;
				else if (board[row][col]==opponent_1)
					return -10000000;
			}
			// Vertical -> Bottom to top
			else if (board[row][col]==board[row+1][col] &&
				board[row+1][col]==board[row+2][col] && 
				board[row+2][col]==board[row+3][col] &&
				board[row+3][col]==board[row+4][col])
			{
				if (board[row][col]==player_1)
					return +10000000;
				else if (board[row][col]==opponent_1)
					return -10000000;
			}
			// Diagonal 1 -> left-down to right-ip
			else if (board[row][col]==board[row+1][col+1] &&
				board[row+1][col+1]==board[row+2][col+2] && 
				board[row+2][col+2]==board[row+3][col+3] &&
				board[row+3][col+3]==board[row+4][col+4])
			{
				if (board[row][col]==player_1)
					return +10000000;
				else if (board[row][col]==opponent_1)
					return -10000000;
			}
			// Diagonal 2 -> Left-Up to right-down
			else if (board[row][col]==board[row-1][col+1] &&
				board[row-1][col+1]==board[row-2][col+2] && 
				board[row-2][col+2]==board[row-3][col+3] &&
				board[row-3][col+3]==board[row-4][col+4])
			{
				if (board[row][col]==player_1)
					return +10000000;
				else if (board[row][col]==opponent_1)
					return -10000000;
			}
		}
	}
/*================================================================================*/
	// Checking for Rows for X or O victory.
	// Check case of open 4.
	for (row = 0; row<SIZE-5; row++)
	{
		for (col = 0; col<SIZE-5; col++)
		{
			if ((board[row][col]==board[row][col+1]  &&
				board[row][col+1]==board[row][col+2] && 
				board[row][col+2]==board[row][col+3] &&
				board[row][col+4]== 0)||
				(board[row][col+1]==board[row][col+2] &&
				board[row][col+2]==board[row][col+3] && 
				board[row][col+3]==board[row][col+4] &&
				board[row][col]== 0))
			{
				if (board[row][col]==player_1)
					return +1000000;
				else if (board[row][col]==opponent_1)
					return -1000000;
			}
			else if ((board[row][col]==board[row+1][col] &&
				board[row+1][col]==board[row+2][col] && 
				board[row+2][col]==board[row+3][col] &&
				board[row+4][col]== 0)|| 
				(board[row+1][col]==board[row+2][col] &&
				board[row+2][col]==board[row+3][col] && 
				board[row+3][col]==board[row+4][col] &&
				board[row][col]== 0))
			{
				if (board[row][col]==player_1)
					return +1000000;
				else if (board[row][col]==opponent_1)
					return -1000000;
			}
			else if ((board[row][col]==board[row+1][col+1] &&
				board[row+1][col+1]==board[row+2][col+2] && 
				board[row+2][col+2]==board[row+3][col+3] &&
				board[row+4][col+4]== 0)||
				(board[row+1][col+1]==board[row+2][col+2] &&
				board[row+2][col+2]==board[row+3][col+3] && 
				board[row+4][col+4]==board[row+4][col+4] &&
				board[row][col]== 0))
			{
				if (board[row][col]==player_1)
					return +1000000;
				else if (board[row][col]==opponent_1)
					return -1000000;
			}
			else if ((board[row][col]==board[row-1][col+1] &&
				board[row-1][col+1]==board[row-2][col+2] && 
				board[row-2][col+2]==board[row-3][col+3] &&
				board[row-4][col+4]==0)||
				(board[row-1][col+1]==board[row-2][col+2] &&
				board[row-2][col+2]==board[row-3][col+3] && 
				board[row-3][col+3]==board[row-4][col+4] &&
				board[row][col]==0))
			{
				if (board[row][col]==player_1)
					return +1000000;
				else if (board[row][col]==opponent_1)
					return -1000000;
			}
		}
	}

// Checking for Rows for X or O victory.
	// Check case of Capped 4, Gapped 4, Gapped 2-2.
	#if 1
	for (row = 0; row<SIZE-5; row++)
	{
		for (col = 0; col<SIZE-5; col++)
		{
/*================================================================================*/
			// For player_1 attacking
			// Capped 4 Horizontal, opponent_1 capping on left or right
			if ((board[row][col] == opponent_1 &&
				board[row][col+1] == player_1 &&
				(board[row][col+1] == board[row][col+2] &&
				 board[row][col+2] == board[row][col+3] && 
				 board[row][col+3] == board[row][col+4]) &&
				 board[row][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row][col+5] == opponent_1 && 
				board[row][col+1] == player_1 &&
				(board[row][col+1] == board[row][col+2] &&
				 board[row][col+2] == board[row][col+3] && 
				 board[row][col+3] == board[row][col+4]) 
				))
			{
				printf("Capped 4 HORIZONTAL\n");
				return +100050;
			}
			// Capped 4 Vertical, opponent_1 capping on top and bottom
			else if ((board[row+1][col] == opponent_1 &&
				board[row+1][col] == player_1 &&
				(board[row+1][col] == board[row+2][col] &&
				 board[row+2][col] == board[row+3][col] && 
				 board[row+3][col] == board[row+4][col]) &&
				 board[row+5][col] == 0) || 
				(board[row][col] == 0 && 
				board[row+5][col] == opponent_1 && 
				board[row+1][col] == player_1 &&
				(board[row+1][col] == board[row+2][col] &&
				 board[row+2][col] == board[row+3][col] && 
				 board[row+3][col] == board[row+4][col]) 
				))
			{
				printf("Capped 4 VERTICAL\n");
				return +100050;
			}
			// Capped 4 Diagonal, and opponent_1 capping top or bottom
			else if ((board[row][col] == opponent_1 &&
				board[row+1][col+1] == player_1 &&
				(board[row+1][col+1] == board[row+2][col+2] &&
				 board[row+2][col+2] == board[row+3][col+3] && 
				 board[row+3][col+3] == board[row+4][col+4]) &&
				 board[row+5][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row+5][col+5] == opponent_1 && 
				board[row+1][col+1] == player_1 &&
				(board[row+1][col+1] == board[row+2][col+2] &&
				 board[row+2][col+2] == board[row+3][col+3] && 
				 board[row+3][col+3] == board[row+4][col+4]) 
				))
			{
				printf("Capped 4 DIAGONAL 1\n");
				return +100050;
			}
			// Capped 4 Other Diagonal, and opponent_1 capping top or bottom
			else if ((board[row][col] == opponent_1 &&
				board[row-1][col+1] == player_1 &&
				(board[row-1][col+1] == board[row-2][col+2] &&
				 board[row-2][col+2] == board[row-3][col+3] && 
				 board[row-3][col+3] == board[row-4][col+4]) &&
				 board[row-5][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row-5][col+5] == opponent_1 && 
				board[row-1][col+1] == player_1 &&
				(board[row-1][col+1] == board[row-2][col+2] &&
				 board[row-2][col+2] == board[row-3][col+3] && 
				 board[row-3][col+3] == board[row-4][col+4]) 
				))
			{
				printf("Capped 4 DIAGONAL 2\n");
				return +100050;
			}

			// For player_1 defending
			// Capped 4 Horizontal, opponent_1 capping on left and right
			else if ((board[row][col] == player_1 &&
				board[row][col+1] == opponent_1 &&
				(board[row][col+1] == board[row][col+2] &&
				 board[row][col+2] == board[row][col+3] && 
				 board[row][col+3] == board[row][col+4]) &&
				 board[row][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row][col+5] == player_1 && 
				board[row][col+1] == opponent_1 &&
				(board[row][col+1] == board[row][col+2] &&
				 board[row][col+2] == board[row][col+3] && 
				 board[row][col+3] == board[row][col+4]) 
				))
			{
				return -100050;
			}
			// Capped 4 Vertical, opponent_1 capping on top and bottom
			else if ((board[row+1][col] == player_1 &&
				board[row+1][col] == opponent_1 &&
				(board[row+1][col] == board[row+2][col] &&
				 board[row+2][col] == board[row+3][col] && 
				 board[row+3][col] == board[row+4][col]) &&
				 board[row+5][col] == 0) || 
				(board[row][col] == 0 && 
				board[row+5][col] == player_1 && 
				board[row+1][col] == opponent_1 &&
				(board[row+1][col] == board[row+2][col] &&
				 board[row+2][col] == board[row+3][col] && 
				 board[row+3][col] == board[row+4][col]) 
				))
			{
				return -100050;
			}
			// Capped 4 Diagonal, and opponent_1 capping top or bottom
			else if ((board[row][col] == player_1 &&
				board[row+1][col+1] == opponent_1 &&
				(board[row+1][col+1] == board[row+2][col+2] &&
				 board[row+2][col+2] == board[row+3][col+3] && 
				 board[row+3][col+3] == board[row+4][col+4]) &&
				 board[row+5][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row+5][col+5] == player_1 && 
				board[row+1][col+1] == opponent_1 &&
				(board[row+1][col+1] == board[row+2][col+2] &&
				 board[row+2][col+2] == board[row+3][col+3] && 
				 board[row+3][col+3] == board[row+4][col+4]) 
				))
			{
				return -100050;
			}
			// Capped 4 Other Diagonal, and opponent_1 capping top or bottom
			else if ((board[row][col] == player_1 &&
				board[row-1][col+1] == opponent_1 &&
				(board[row-1][col+1] == board[row-2][col+2] &&
				 board[row-2][col+2] == board[row-3][col+3] && 
				 board[row-3][col+3] == board[row-4][col+4]) &&
				 board[row-5][col+5] == 0) || 
				(board[row][col] == 0 && 
				board[row-5][col+5] == player_1 && 
				board[row-1][col+1] == opponent_1 &&
				(board[row-1][col+1] == board[row-2][col+2] &&
				 board[row-2][col+2] == board[row-3][col+3] && 
				 board[row-3][col+3] == board[row-4][col+4]) 
				))
			{
				return -100050;
			}
		}
	}
/*==================================================================================*/


/*================================================================================*/
	for (row = 0; row<SIZE-4; row++)
	{
		for (col = 0; col<SIZE-4; col++)
		{		
			// For player_1 attacking
			// GAPPED 4 Horizontal, gap between 1&3, 2&4, 3&5
			if (((board[row][col]==player_1 && board[row][col+2]==player_1 &&
				(board[row][col+1]==0 &&
				 board[row][col+2]==board[row][col+3] && 
				 board[row][col+3]==board[row][col+4])) ||
				(board[row][col]==player_1 &&
				(board[row][col]==board[row][col+1] &&
				 board[row][col+2]== 0 && 
				 board[row][col+3]==board[row][col+4])) || 
				(board[row][col]==player_1 && board[row][col+4]==player_1 &&
				(board[row][col]==board[row][col+1] &&
				 board[row][col+1]== board[row][col+2])&&
				 board[row][col+3]==0)))
			{
				printf("GAPPED 4 HORIZONTAL\n");
				return +100050;
			}
			// GAPPED 4 Vertical, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==player_1 && board[row+2][col]==player_1 &&
				(board[row+1][col]==0 &&
				 board[row+2][col]==board[row+3][col] && 
				 board[row+3][col]==board[row+4][col])) ||
				(board[row][col]==player_1 &&
				(board[row][col]==board[row+1][col] &&
				 board[row+2][col]== 0 && 
				 board[row+3][col]==board[row+4][col])) || 
				(board[row][col]==player_1 && board[row+4][col]==player_1 &&
				(board[row][col]==board[row+1][col] &&
				 board[row+1][col]== board[row+2][col]) &&
				 board[row+3][col]== 0)))
			{
				printf("GAPPED 4 VERTICAL\n");
				return +100050;
			}
			// GAPPED 4 DIAGONAL, gap between 1&3, 2&4, 3&5
			else if (((board[row][col] == player_1 && 
					board[row+1][col+1]==0 && 
					board[row+2][col+2] == player_1 &&
					(board[row+2][col+2]==board[row+3][col+3] && 
				 	board[row+3][col+3]==board[row+4][col+4])) ||
					(board[row][col]==player_1 && 
					 board[row+2][col+2]== 0 &&
					(board[row][col]==board[row+1][col+1] && 
					 board[row+3][col+3]==board[row+4][col+4])) || 
					(board[row][col]==player_1 && board[row+4][col+4]==player_1 &&
						board[row+3][col+3]== 0 &&
					(board[row][col]==board[row+1][col+1] &&
					 board[row+1][col+1]== board[row+2][col+2])
					 )))
			{
				printf("GAPPED 4 DIAGONAL 1\n");
				return +100050;
			}
			// GAPPED 4 OTHER DIAGONAL, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==player_1 && board[row-2][col+2]==player_1 &&
				(board[row-1][col+1]==0 &&
				 board[row-2][col+2]==board[row-3][col+3] && 
				 board[row-3][col+3]==board[row-4][col+4])) ||
				(board[row][col]==player_1 &&
				(board[row][col]==board[row-1][col+1] &&
				 board[row-2][col+2]== 0 && 
				 board[row-3][col+3]==board[row-4][col+4])) || 
				(board[row][col]==player_1 && board[row-4][col+4]==player_1 &&
				(board[row][col]==board[row-1][col+1] &&
				 board[row-1][col+1]== board[row-2][col+2]) &&
				 board[row-3][col+3]== 0)))
			{
				printf("GAPPED 4 DIAGONAL 2\n");
				return +100050;
			}

			// For player_1 defending
			// GAPPED 4 Horizontal, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==opponent_1 && board[row][col+2]==opponent_1 &&
				(board[row][col+1]==0 &&
				 board[row][col+2]==board[row][col+3] && 
				 board[row][col+3]==board[row][col+4])) ||
				(board[row][col]==opponent_1 &&
				(board[row][col]==board[row][col+1] &&
				 board[row][col+2]== 0 && 
				 board[row][col+3]==board[row][col+4])) || 
				(board[row][col]==opponent_1 && board[row][col+4]==opponent_1 &&
				(board[row][col]==board[row][col+1] &&
				 board[row][col+1]== board[row][col+2])&&
				 board[row][col+3]==0)))
			{
				return -100050;
			}
			// GAPPED 4 Vertical, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==opponent_1 && board[row+2][col]==opponent_1 &&
				(board[row+1][col]==0 &&
				 board[row+2][col]==board[row+3][col] && 
				 board[row+3][col]==board[row+4][col])) ||
				(board[row][col]==opponent_1 &&
				(board[row][col]==board[row+1][col] &&
				 board[row+2][col]== 0 && 
				 board[row+3][col]==board[row+4][col])) || 
				(board[row][col]==opponent_1 && board[row+4][col]==opponent_1 &&
				(board[row][col]==board[row+1][col] &&
				 board[row+1][col]== board[row+2][col]) &&
				 board[row+3][col]== 0)))
			{
				return -100050;
			}
			// GAPPED 4 DIAGONAL, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==opponent_1 && board[row+2][col+2]==opponent_1 &&
				(board[row+1][col+1]==0 &&
				 board[row+2][col+2]==board[row+3][col+3] && 
				 board[row+3][col+3]==board[row+4][col+4])) ||
				(board[row][col]==opponent_1 &&
				(board[row][col]==board[row+1][col+1] &&
				 board[row+2][col+2]== 0 && 
				 board[row+3][col+3]==board[row+4][col+4])) || 
				(board[row][col]==opponent_1 && board[row+4][col+4]==opponent_1 &&
				(board[row][col]==board[row+1][col+1] &&
				 board[row+1][col+1]== board[row+2][col+2]) &&
				 board[row+3][col+3]== 0)))
			{
				return -100050;
			}
			// GAPPED 4 OTHER DIAGONAL, gap between 1&3, 2&4, 3&5
			else if (((board[row][col]==opponent_1 && board[row-2][col+2]==opponent_1 &&
				(board[row-1][col+1]==0 &&
				 board[row-2][col+2]==board[row-3][col+3] && 
				 board[row-3][col+3]==board[row-4][col+4])) ||
				(board[row][col]==opponent_1 &&
				(board[row][col]==board[row-1][col+1] &&
				 board[row-2][col+2]== 0 && 
				 board[row-3][col+3]==board[row-4][col+4])) || 
				(board[row][col]==opponent_1 && board[row-4][col+4]==opponent_1 &&
				(board[row][col]==board[row-1][col+1] &&
				 board[row-1][col+1]== board[row-2][col+2]) &&
				 board[row-3][col+3]== 0)))
			{
				return -100050;
			}
		}
	}
	#endif
/*==================================================================================*/

	// Checking for Rows for X or O victory.
	// Check case of open 3 and Gapped 3.

	// For player_1 attacking and defending
	// open 3 Horizontal -> 3 cases 
			// 2 empty on left, 2 empty on right, 1-1 empty on left and right
	for (row = 0; row<SIZE-4; row++)
	{
		for (col = 0; col<SIZE-4; col++)
		{
			
			// HORIZONTAL
			// 2 empty on left
			if ((board[row][col]== 0 &&
				(board[row][col]==board[row][col+1]) && 
				(board[row][col+2]==board[row][col+3] &&
				board[row][col+3]== board[row][col+4])))
			{
				if (board[row][col+2]==player_1)
					return +100000;
				else if (board[row][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on right
			else if (((board[row][col]==board[row][col+1] && 
				board[row][col+1]==board[row][col+2]) &&
				board[row][col+3] == 0 &&
				(board[row][col+3] == board[row][col+4])))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 && board[row][col+4]== 0 &&
				(board[row][col+1]==board[row][col+2] &&
				board[row][col+2] == board[row][col+3])))
			{
				if (board[row][col+1]==player_1)
					return +100000;
				else if (board[row][col+1]==opponent_1)
					return -100000;
			}

			// VERTICAL
			// 2 empty on top
			else if ((board[row][col]== 0 &&
				(board[row+1][col]==board[row+1][col]) && 
				(board[row+2][col]==board[row+3][col] &&
				board[row+3][col]== board[row+4][col])))
			{
				if (board[row+2][col]==player_1)
					return +100000;
				else if (board[row+2][col]==opponent_1)
					return -100000;
			}
			// 2 empty on bottom
			else if (((board[row][col]==board[row+1][col] && 
				board[row+1][col]==board[row+2][col]) &&
				board[row+3][col] == 0 &&
				(board[row+3][col] == board[row+4][col])))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 && board[row+4][col]== 0 &&
				(board[row+1][col]==board[row+2][col] &&
				board[row+2][col] == board[row+3][col])))
			{
				if (board[row+1][col]==player_1)
					return +100000;
				else if (board[row+1][col]==opponent_1)
					return -100000;
			}

			// DIAGONAL
			// 2 empty on down-left
			else if ((board[row][col]== 0 && board[row+1][col+1] == 0 &&
				(board[row+2][col+2]==board[row+3][col+3] &&
				board[row+3][col+3]== board[row+4][col+4])))
			{
				if (board[row+2][col+2]==player_1)
					return +100000;
				else if (board[row+2][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on up-right
			else if (((board[row][col]==board[row+1][col+1] && 
				board[row+1][col+1]==board[row+2][col+2]) &&
				board[row+3][col+3] == 0 &&
				(board[row+3][col+3] == board[row+4][col+4])))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on up-right and down-left
			else if ((board[row][col]== 0 && board[row+4][col+4]== 0 &&
				(board[row+1][col+1]==board[row+2][col+2] &&
				board[row+2][col+2] == board[row+3][col+3])))
			{
				if (board[row+1][col+1]==player_1)
					return +100000;
				else if (board[row+1][col+1]==opponent_1)
					return -100000;
			}

			// OTHER DIAGONAL
			// 2 empty on up-left
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row-1][col+1]) && 
				(board[row-2][col+2]==board[row-3][col+3] &&
				board[row-3][col+3]== board[row-4][col+4])))
			{
				if (board[row-2][col+2]==player_1)
					return +100000;
				else if (board[row-2][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on down-right
			else if (((board[row][col]==board[row-1][col+1] && 
				board[row-1][col+1]==board[row-2][col+2]) &&
				board[row-3][col+3] == 0 &&
				(board[row-3][col+3] == board[row-4][col+4])))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on down-right and up-left
			else if ((board[row][col]== 0 && board[row-4][col+4]== 0 &&
				(board[row-1][col+1]==board[row-2][col+2] &&
				board[row-2][col+2] == board[row-3][col+3])))
			{
				if (board[row-1][col+1]==player_1)
					return +100000;
				else if (board[row-1][col+1]==opponent_1)
					return -100000;
			}
		}
	}
			
			
/*=====================================================================*/
	// For the case of Gapped 3
	for (row = 0; row<SIZE-5; row++)
	{
		for (col = 0; col<SIZE-5; col++)
		{
			// HORIZONTAL
			// 2 empty on left -> Has 2 cases, when gap is between 1 and 3 or when gap is between 2 and 4
			if ((board[row][col]== 0 &&
				(board[row][col]==board[row][col+1]) && 
				(board[row][col+2]==board[row][col+4] &&
				board[row][col+4]== board[row][col+5])&& 
				board[row][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row][col+1]) && 
				(board[row][col+2]==board[row][col+3] &&
				board[row][col+3]== board[row][col+5])&& 
				board[row][col+4] == 0))
			{
				if (board[row][col+2]==player_1)
					return +100000;
				else if (board[row][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on right
			else if ((board[row][col+4]== 0 &&
				(board[row][col+4]==board[row][col+5]) && 
				(board[row][col]==board[row][col+1] &&
				board[row][col+1]== board[row][col+3])&& 
				board[row][col+2] == 0) ||
				(board[row][col+4]== 0 &&
				(board[row][col+4]==board[row][col+5]) && 
				(board[row][col]==board[row][col+2] &&
				board[row][col+2]== board[row][col+3])&& 
				board[row][col+1] == 0))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row][col+5]) && 
				(board[row][col+1]==board[row][col+2] &&
				board[row][col+2]== board[row][col+4])&& 
				board[row][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row][col+5]) && 
				(board[row][col+1]==board[row][col+3] &&
				board[row][col+3]== board[row][col+4])&& 
				board[row][col+2] == 0))
			{
				if (board[row][col+1]==player_1)
					return +100000;
				else if (board[row][col+1]==opponent_1)
					return -100000;
			}

			// VERTICAL
			// 2 empty on top -> Has 2 cases, when gap is between 1 and 3 or when gap is between 2 and 4
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row+1][col]) && 
				(board[row+2][col]==board[row+4][col] &&
				board[row+4][col]== board[row+5][col])&& 
				board[row+3][col] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row+1][col]) && 
				(board[row+2][col]==board[row+3][col] &&
				board[row+3][col]== board[row+5][col])&& 
				board[row+4][col] == 0))
			{
				if (board[row+2][col]==player_1)
					return +100000;
				else if (board[row+2][col]==opponent_1)
					return -100000;
			}
			// 2 empty on bottom
			else if ((board[row+4][col]== 0 &&
				(board[row+4][col]==board[row+5][col]) && 
				(board[row][col]==board[row+1][col] &&
				board[row+1][col]== board[row+3][col])&& 
				board[row+2][col] == 0) ||
				(board[row+4][col]== 0 &&
				(board[row+4][col]==board[row+5][col]) && 
				(board[row][col]==board[row+2][col] &&
				board[row+2][col]== board[row+3][col])&& 
				board[row+1][col] == 0))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row+5][col]) && 
				(board[row+1][col]==board[row+2][col] &&
				board[row+2][col]== board[row+4][col])&& 
				board[row+3][col] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row+5][col]) && 
				(board[row+1][col]==board[row+3][col] &&
				board[row+3][col]== board[row+4][col])&& 
				board[row+2][col] == 0))
			{
				if (board[row+1][col]==player_1)
					return +100000;
				else if (board[row+1][col]==opponent_1)
					return -100000;
			}

			// DIAGONAL
			// 2 empty on up-left
			// 2 empty on top -> Has 2 cases, when gap is between 1 and 3 or when gap is between 2 and 4
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row+1][col+1]) && 
				(board[row+2][col+2]==board[row+4][col+4] &&
				board[row+4][col+4]== board[row+5][col+5])&& 
				board[row+3][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row+1][col+1]) && 
				(board[row+2][col+2]==board[row+3][col+3] &&
				board[row+3][col+3]== board[row+5][col+5])&& 
				board[row+4][col+4] == 0))
			{
				if (board[row+2][col+2]==player_1)
					return +100000;
				else if (board[row+2][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on bottom
			else if ((board[row+4][col+4]== 0 &&
				(board[row+4][col+4]==board[row+5][col+5]) && 
				(board[row][col]==board[row+1][col+1] &&
				board[row+1][col+1]== board[row+3][col+3])&& 
				board[row+2][col+2] == 0) ||
				(board[row+4][col+4]== 0 &&
				(board[row+4][col+4]==board[row+5][col+5]) && 
				(board[row][col]==board[row+2][col+2] &&
				board[row+2][col+2]== board[row+3][col+3])&& 
				board[row+1][col+1] == 0))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row+5][col+5]) && 
				(board[row+1][col+1]==board[row+2][col+2] &&
				board[row+2][col+2]== board[row+4][col+4])&& 
				board[row+3][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row+5][col+5]) && 
				(board[row+1][col+1]==board[row+3][col+3] &&
				board[row+3][col+3]== board[row+4][col+4])&& 
				board[row+2][col+2] == 0))
			{
				if (board[row+1][col+1]==player_1)
					return +100000;
				else if (board[row+1][col+1]==opponent_1)
					return -100000;
			}

			// OTHER DIAGONAL
			// 2 empty on down-left
			// 2 empty on up-left
			// 2 empty on top -> Has 2 cases, when gap is between 1 and 3 or when gap is between 2 and 4
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row-1][col+1]) && 
				(board[row-2][col+2]==board[row-4][col+4] &&
				board[row-4][col+4]== board[row-5][col+5])&& 
				board[row-3][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row-1][col+1]) && 
				(board[row-2][col+2]==board[row-3][col+3] &&
				board[row-3][col+3]== board[row-5][col+5])&& 
				board[row-4][col+4] == 0))
			{
				if (board[row-2][col+2]==player_1)
					return +100000;
				else if (board[row-2][col+2]==opponent_1)
					return -100000;
			}
			// 2 empty on bottom
			else if ((board[row-4][col+4]== 0 &&
				(board[row-4][col+4]==board[row-5][col+5]) && 
				(board[row][col]==board[row-1][col+1] &&
				board[row-1][col+1]== board[row-3][col+3])&& 
				board[row-2][col+2] == 0) ||
				(board[row-4][col+4]== 0 &&
				(board[row-4][col+4]==board[row-5][col+5]) && 
				(board[row][col]==board[row-2][col+2] &&
				board[row-2][col+2]== board[row-3][col+3])&& 
				board[row-1][col+1] == 0))
			{
				if (board[row][col]==player_1)
					return +100000;
				else if (board[row][col]==opponent_1)
					return -100000;
			}
			// 1-1 empty on right and left
			else if ((board[row][col]== 0 &&
				(board[row][col]==board[row-5][col+5]) && 
				(board[row-1][col+1]==board[row-2][col+2] &&
				board[row-2][col+2]== board[row-4][col+4])&& 
				board[row-3][col+3] == 0) ||
				(board[row][col]== 0 &&
				(board[row][col]==board[row-5][col+5]) && 
				(board[row-1][col+1]==board[row-3][col+3] &&
				board[row-3][col+3]== board[row-4][col+4])&& 
				board[row-2][col+2] == 0))
			{
				if (board[row-1][col+1]==player_1)
					return +100000;
				else if (board[row-1][col+1]==opponent_1)
					return -100000;
			}

/*================================================================================*/
			// For player_1 attacking
			// Capped 3 Horizontal, opponent_1 capping on left and right
			else if ((board[row][col+1]==player_1 &&
				(board[row][col+1]==board[row][col+2] &&
				 board[row][col+2]==board[row][col+3]) &&
				board[row][col]==opponent_1 &&
				board[row][col+4]==0 &&
				board[row][col+5]==0) || 
				(board[row][col+2]==player_1 &&
				(board[row][col+2]==board[row][col+3] &&
				 board[row][col+3]==board[row][col+4]) &&
				board[row][col+5]==opponent_1 &&
				board[row][col]==0 &&
				board[row][col+1]==0))
			{
				return +10000;
			}
			// Capped 3 Vertical, opponent_1 capping on top and bottom
			else if ((board[row+1][col]==player_1 &&
				(board[row+1][col]==board[row+2][col] &&
				 board[row+2][col]==board[row+3][col]) &&
				board[row][col]==opponent_1 &&
				board[row+4][col]==0 &&
				board[row+5][col]==0) || 
				(board[row+2][col]==player_1 &&
				(board[row+2][col]==board[row+3][col] &&
				 board[row+3][col]==board[row+4][col]) &&
				board[row+5][col]==opponent_1 &&
				board[row][col]==0 &&
				board[row+1][col]==0))
			{
				return +10000;
			}
			// Capped 3 Diagonal, and opponent_1 capping top or bottom
			else if ((board[row+1][col+1]==player_1 &&
				(board[row+1][col+1]==board[row+2][col+2] &&
				 board[row+2][col+2]==board[row+3][col+3]) &&
				board[row][col]==opponent_1 &&
				board[row+4][col+4]==0 &&
				board[row+5][col+5]==0) || 
				(board[row+2][col+2]==player_1 &&
				(board[row+2][col+2]==board[row+3][col+3] &&
				 board[row+3][col+3]==board[row+4][col+4]) &&
				board[row+5][col+5]==opponent_1 &&
				board[row][col]==0 &&
				board[row+1][col+1]==0))
			{
				return +10000;
			}
			// Capped 3 Other Diagonal, and opponent_1 capping top or bottom
			else if ((board[row-1][col+1]==player_1 &&
				(board[row-1][col+1]==board[row-2][col+2] &&
				 board[row-2][col+2]==board[row-3][col+3]) &&
				board[row][col]==opponent_1 &&
				board[row-4][col+4]==0 &&
				board[row-5][col+5]==0) || 
				(board[row-2][col+2]==player_1 &&
				(board[row-2][col+2]==board[row-3][col+3] &&
				 board[row-3][col+3]==board[row-4][col+4]) &&
				board[row-5][col+5]==opponent_1 &&
				board[row][col]==0 &&
				board[row-1][col+1]==0))
			{
				return +10000;
			}

			// For player_1 defending
			// Capped 3 Horizontal, opponent_1 capping on left and right
			else if ((board[row][col+1]==opponent_1 &&
				(board[row][col+1]==board[row][col+2] &&
				 board[row][col+2]==board[row][col+3]) &&
				board[row][col]==player_1 &&
				board[row][col+4]==0 &&
				board[row][col+5]==0) || 
				(board[row][col+2]==opponent_1 &&
				(board[row][col+2]==board[row][col+3] &&
				 board[row][col+3]==board[row][col+4]) &&
				board[row][col+5]==player_1 &&
				board[row][col]==0 &&
				board[row][col+1]==0))
			{
				return -10000;
			}
			// Capped 3 Vertical, opponent_1 capping on top and bottom
			else if ((board[row+1][col]==opponent_1 &&
				(board[row+1][col]==board[row+2][col] &&
				 board[row+2][col]==board[row+3][col]) &&
				board[row][col]==player_1 &&
				board[row+4][col]==0 &&
				board[row+5][col]==0) || 
				(board[row+2][col]==opponent_1 &&
				(board[row+2][col]==board[row+3][col] &&
				 board[row+3][col]==board[row+4][col]) &&
				board[row+5][col]==player_1 &&
				board[row][col]==0 &&
				board[row+1][col]==0))
			{
				return -10000;
			}
			// Capped 3 Diagonal, and opponent_1 capping top or bottom
			else if ((board[row+1][col+1]==opponent_1 &&
				(board[row+1][col+1]==board[row+2][col+2] &&
				 board[row+2][col+2]==board[row+3][col+3]) &&
				board[row][col]==player_1 &&
				board[row+4][col+4]==0 &&
				board[row+5][col+5]==0) || 
				(board[row+2][col+2]==opponent_1 &&
				(board[row+2][col+2]==board[row+3][col+3] &&
				 board[row+3][col+3]==board[row+4][col+4]) &&
				board[row+5][col+5]==player_1 &&
				board[row][col]==0 &&
				board[row+1][col+1]==0))
			{
				return -10000;
			}
			// Capped 3 Other Diagonal, and opponent_1 capping top or bottom
			else if ((board[row-1][col+1]==opponent_1 &&
				(board[row-1][col+1]==board[row-2][col+2] &&
				 board[row-2][col+2]==board[row-3][col+3]) &&
				board[row][col]==player_1 &&
				board[row-4][col+4]==0 &&
				board[row-5][col+5]==0) || 
				(board[row-2][col+2]==opponent_1 &&
				(board[row-2][col+2]==board[row-3][col+3] &&
				 board[row-3][col+3]==board[row-4][col+4]) &&
				board[row-5][col+5]==player_1 &&
				board[row][col]==0 &&
				board[row-1][col+1]==0))
			{
				return -10000;
			}
/*==================================================================================*/
		}
	}
	for (row = 0; row<SIZE-4; row++)
	{
		for (col = 0; col<SIZE-4; col++)
		{
			if ((board[row][col] == board[row][col+1] &&
				board[row][col+2] == 0)||
				(board[row][col] == board[row+1][col] &&
				board[row+2][col] == 0)||
				(board[row][col] == board[row+1][col+1] &&
				board[row+2][col+2] == 0)||
				(board[row][col] == board[row-1][col+1] &&
				board[row-2][col+2] == 0))
				if (board[row][col] == player_1)
					return 1000;
				else if (board[row][col] == opponent_1)
					return -1000;
			else if (board[row][col+1] == 0|| board[row+1][col] == 0|| board[row+1][col+1] == 0|| board[row-1][col+1] == 0)
				if (board[row][col] == player_1)
					return 100;
				else if (board[row][col] == opponent_1)
					return -100;
		}
	}
	return 0;
}
/*===============================================================================*/

/*==============================MINIMAX==========================================*/

// This is the minimax_1 function. It considers all
// the possible ways the game can go and returns
// the value of the board
double minimax_1(int board[][SIZE], int depth, bool isMax, double alpha, double beta)
{
	double score = MIN_1;
	score = evaluate_1(board);
	//printf("RETURN VALUE IS: %f\n", score);
	double max_diff = MIN_1, diff;
	//printf("SCORE VALUE IS = %f\n\n", score);
	double best = MIN_1;
	int i, j;
	double val;
	double max_score;
	// If Maximizer has won the game return his/her
	// evaluated score
	if (score == 10000000)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score
	if (score == -10000000)
		return score;
	
	// If this maximizer's move
	if (isMax)
	{
		// Traverse all cells
		for (i = 0; i<SIZE; i++)
		{
			for (j = 0; j<SIZE; j++)
			{
				// Check if cell is empty
				if (board[i][j]==0)
				{
					
					// Make the move
					board[i][j] = opponent_1;
					
					val = minimax_1(board, depth+1, !isMax, alpha, beta);
            		//best = max_1(best, val);
            		//alpha = max_1(alpha, best);
					diff = score + val;
					if (diff > max_diff)
					{
						max_diff = diff;
						max_score = score;
					}

					// Undo the move
					board[i][j] = 0;

		            // Alpha Beta Pruning
		            //if (beta <= alpha)
		              //  break;
				}
			}
		}
		printf("MAX_1 SCORE THAT WAS OBATINED WAS %f\n", max_score);
		return max_diff;
	}
}


/*==============================findBestMove_1===========================================*/


// This will return the best possible move for the player_1
Move findBestMove_1(int board[][SIZE])
{
	Move bestMove;
	int bestVal = MIN_1;
	bestMove.row = -1;
	bestMove.col = -1;
	int i, j;
	double moveVal;
	bool board_empty = true;
	for (i = 0; i<SIZE; i++)
		{
			for (j = 0; j<SIZE; j++)
			{
				if(board[i][j] != 0)
					board_empty = false;
			}
		}
		if (board_empty == true)
		{
			bestMove.row = (SIZE-1)/2;
			bestMove.col = (SIZE-1)/2;
			return bestMove;
		}

	// Traverse all cells, evaluate_1 minimax_1 function for
	// all empty cells. And return the cell with optimal
	// value.
	for (i = 0; i<SIZE; i++)
	{
		for (j = 0; j<SIZE; j++)
		{
			// Check if cell is empty
			if (board[i][j]==0)
			{
				// Make the move
				board[i][j] = player_1;
				printf("i = %d, j = %d\n", i, j);

				// compute evaluation function for this
				// move.
				moveVal = minimax_1(board, 0, true, MIN_1, MAX_1);
				//printf("COST WE GOT = %f\n\n", moveVal);
				// Undo the move
				board[i][j] = 0;

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	//printf("The value of the best Move is : %d\n",
		//	bestVal);

	return bestMove;
}

/*===============================getMove===========================================*/


int* getMove(int board[][SIZE], int *move)
{
  printf("New Move\n\n");
  do
  { 
  	Move bestMove = findBestMove_1(board);
  	move[0] = bestMove.row;
    move[1] = bestMove.col;
  }while (checkMove(board, move) == 0);
  printf("PLACED AT: %d, %d\n\n", move[0], move[1]);
  return move;
}
#endif
