
#include "../../inc/connect_four.h"



int isValidPosition (uint64_t board[MAX_SIZE], int row, int col)
{
    return !(board[row] & (1UL << col));
}

int getOpenedRowFromCol(uint64_t board[MAX_SIZE], int col, int maxCol, int maxRow)
{
    if (col >= maxCol)
        return (-1);
    for (int row = 0; row < maxRow; row++)
    {
        if (!(board[row] & (1UL << col)))
        {
            write(2, "getOpenedRowFromCol: ", 22);
            ft_putnbr_lft_fd(row, 2);
            write(2, "\n", 1);
            return (row);
        }
    }
    return (-1);
}

void    setChecker(uint64_t board[MAX_SIZE], int rowMax, int row, int col)
{
    if (row >= rowMax)
        return;
    write(2, "setChecker: ", 13);
        ft_putnbr_lft_fd(row, 2);
        write(2, "\n", 1);
    board[row] |= (1ULL << col);
}

