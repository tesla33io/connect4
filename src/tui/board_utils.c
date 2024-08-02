
#include "../../inc/connect_four.h"

int isValidPosition (int **board, int row, int col)
{
    if (board[row][col] == -1)
        return (1);
    return 0;
}

void    initBoard(t_game *game)
{
    for (int i = 0; i < game->rows; i++)
    {
        for (int j = 0; j < game->cols; j++)
            game->board[i][j] = -1;
    }
}

/* to get a first available row index based on column position in the board game
    row index starts from 0
    return -1 in case no available positions
*/
int getOpenRowFromCol(int **board, int col, int maxCol, int maxRow)
{
    if (!board || col > maxCol)
        return -1;
    for (int i = maxRow - 1; i >= 0; i--)
    {
        if (board[i][col] == -1)
            return (i);
    }
    return (-1);
}

void    setChecker(int **board, int row, int col, int checker)
{
    if (!board || row < 0 || col < 0)
        return ;
    board[row][col] = checker;
}
