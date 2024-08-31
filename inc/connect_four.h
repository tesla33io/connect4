#ifndef CONNECT_FOUR_H
# define CONNECT_FOUR_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <time.h>
# include "../lib/libft/libft.h"

# define MAX_SIZE 60
# define MIN_ROWS 6
# define MIN_COLS 7
# define MAX_COLS_TERMINAL 26
# define TRUE 1
# define FALSE 0

# define COLOR_GRAY  "\033[90m"
# define COLOR_RED    "\033[91m"
# define COLOR_GREEN  "\033[92m"
# define COLOR_BLUE   "\033[94m"
# define COLOR_MAGENTA "\033[95m"
# define COLOR_CYAN   "\033[96m"
# define COLOR_WHITE  "\033[97m"
# define COLOR_RESET  "\033[0m"

enum e_turn
{
    USER,
    BOT,
};

typedef struct s_game
{
    int     visual;
    int     rows;
    int     cols;
    int     turn;
    int     winner;
    int     tile_size;
    int     steps[MAX_SIZE * MAX_SIZE];
    int     last_checker_row;
    int     last_checker_col;
    uint64_t bp1[MAX_SIZE];
    uint64_t bp2[MAX_SIZE];
    uint64_t bmask[MAX_SIZE];

}   t_game;


void    initGame(t_game *game);
int     validateInput(int size, char **args, t_game *game);
int     launchGame(t_game *game);
int     usersTurn(t_game *game);
void    botTurn(t_game *game);
int     isWinner(uint64_t board[MAX_SIZE], int rowMax, int colMax);
void    userWinner();
void    botWinner();
/**
 * @brief display the current board
 */
void    printBoard(t_game *game);

/**
 * @brief sets a bit at the given position
 */
void    setChecker(uint64_t board[MAX_SIZE], int rowMax, int row, int col);

/**
 * @brief gets a first available row index based on column position in the board game
   @param col 0-based index of a playable column.
   @return      int 0-based index of a playable row
                -1 in a case no available positions
*/
int     getOpenedRowFromCol(uint64_t board[MAX_SIZE], int col, int maxCol, int maxRow);

/**
 * @brief validates if a position is empty
 */
int     isValidPosition (uint64_t board[MAX_SIZE], int row, int col);

/**
 * @brief        displays the game bit board
 * @param bmask  The board mask includes player1 and player2 checkers
 * @param bp     The board mask includes player1 checkers
 * @param rowMax Maximum rows in the game board   
 * @param colMax Maximum columns in the game board   
 */
void    printBitBoard(uint64_t bmask[MAX_SIZE], uint64_t bp[MAX_SIZE], int rowMax, int colMax);

/**
 * @brief displays a message 'Game over'
 */
void    drawGame();


int runGameVisual(t_game *game);
void    displayUserMsg(void);

#endif // CONNECT_FOUR_H

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
