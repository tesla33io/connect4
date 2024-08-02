#ifndef CONNECT_FOUR_H
# define CONNECT_FOUR_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <time.h>
# include "../lib/libft/libft.h"
# include "colors.h"

# define MAX_SIZE 60


enum e_turn
{
    USER,
    ROBOT,
};

typedef struct s_game
{
    int rows;
    int cols;
    int turn;
    int *steps;
    int **board;
    uint64_t bp1[MAX_SIZE];
    uint64_t bp2m[MAX_SIZE];

}   t_game;

int     validateInput(int size, char **args, t_game *game);
void    printBoard(t_game *game);

void    freeMemory(t_game *game);
int     allocateMemory(t_game *game);
void    drawGame();

int     isValidPosition (int **board, int row, int col);
void    initBoard(t_game *game);
int     getOpenRowFromCol(int **board, int col, int maxCol, int maxRow);
void    setChecker(int **board, int row, int col, int checker);


#endif

/**
 * max board: 60 x 60
 
 * map1:
    @brief 1player's checkers
 * - uint_64 bp1[60] = {
    .......
    101011.. 
    010010..
 }

 * map2:
    @brief store 2player's checkers and maskof the board
    - uint_64 bp2m[60] = {
    .......
    101011..
    111011..
    }

* board
    _ _ _ _ _ _ ..
    _ _ _ _ _ _ ..
    _ _ _ _ _ _ ..
    1 _ 1 _ 1 1 ..
    2 1 2 _ 1 2 ..
 
 */





/**
 * Board:
 * -1 - empty
 * 0 - user
 * 1 - robot
*/

/**
 * Libft.
 * malloc(3), free(3), rand(3), srand(3), time(3)
 * 
*/

/**
 * Standard Colors:
Black: "\033[30m"
Red: "\033[31m"
Green: "\033[32m"
Yellow: "\033[33m"
Blue: "\033[34m"
Magenta: "\033[35m"
Cyan: "\033[36m"
White: "\033[37m"

* Bright Colors (often called "bold" or "intense"):
Bright Black (Gray): "\033[90m"
Bright Red: "\033[91m"
Bright Green: "\033[92m"
Bright Yellow: "\033[93m"
Bright Blue: "\033[94m"
Bright Magenta: "\033[95m"
Bright Cyan: "\033[96m"
Bright White: "\033[97m"

* Background Colors:
Black Background: "\033[40m"
Red Background: "\033[41m"
Green Background: "\033[42m"
Yellow Background: "\033[43m"
Blue Background: "\033[44m"
Magenta Background: "\033[45m"
Cyan Background: "\033[46m"
White Background: "\033[47m"

* Bright Background Colors:
Bright Black Background: "\033[100m"
Bright Red Background: "\033[101m"
Bright Green Background: "\033[102m"
Bright Yellow Background: "\033[103m"
Bright Blue Background: "\033[104m"
Bright Magenta Background: "\033[105m"
Bright Cyan Background: "\033[106m"
Bright White Background: "\033[107m"
Other Attributes:
Reset: "\033[0m"
Bold: "\033[1m"
Underline: "\033[4m"
Reversed: "\033[7m"
*/