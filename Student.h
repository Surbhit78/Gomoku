#include<stdbool.h>
#define SIZE 15
// #define ROW_CHAR(x) ((x) + 'a')
int max(int val1, int val2);
int min(int val1, int val2);
int* getMove(int board[][SIZE], int *move);
bool isMovesLeft(int board[][SIZE]);
int evaluate(int board[][SIZE]);
int minimax(int board[][SIZE], int depth, bool isMax, double alpha, double beta);