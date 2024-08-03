#include "../../inc/connect_four.h"

static int count_consecutive(uint64_t board[MAX_SIZE], int row, int col, int rowDir, int colDir, int rowMax, int colMax);
static int check_four(uint64_t board[MAX_SIZE], int row, int col, int rowMax, int colMax);

int isWinner(uint64_t board[MAX_SIZE], int rowMax, int colMax)
{
    int res = 0;
    for (int r = rowMax - 1; r >= 0; r--)
    {
        for (int c = 0; c < colMax; c++)
        {
            if (board[r] & (1UL << c))
                res = check_four(board, r, c, rowMax, colMax);
            if (res == 4)
                return (TRUE);
        }
    }
    return (FALSE);
}

/**
 * @brief Checks in all four directions from the current position
 * @param board     A board to check for a winning condition
 * @param row       0-based index of a current row
 * @param col       0-based index of a current column
 * @param rowMax    Maximum rows in the game board
 * @param colMax    Maximum columns in the game board
 */
static int check_four(uint64_t board[MAX_SIZE], int row, int col, int rowMax, int colMax)
{
    if (row < 0 || row >= rowMax || col < 0 || col >= colMax)
        return (0);
    if (count_consecutive(board, row, col, 0, 1, rowMax, colMax) >= 4)
        return (4);
    if (count_consecutive(board, row, col, 1, 0, rowMax, colMax) >= 4)
        return (4);
    if (count_consecutive(board, row, col, 1, 1, rowMax, colMax) >= 4)
        return (4);
    if (count_consecutive(board, row, col, 1, -1, rowMax, colMax) >= 4)
        return (4);
    return (0);
}

/**
 * @brief Counts the number of consecutive pieces starting from a given position in a specified direction.
 *          Stops counting if it goes out of bounds or encounters an empty position.
 */
static int count_consecutive(uint64_t board[MAX_SIZE], int row, int col, int rowDir, int colDir, int rowMax, int colMax)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        int r = row + i * rowDir;
        int c = col + i * colDir;
        if (r < 0 || r >= rowMax || c < 0 || c >= colMax || !(board[r] & (1UL << c)))
            break;
        count++;
    }
    return (count);
}
