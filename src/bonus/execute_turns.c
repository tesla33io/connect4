#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

int getPosFromPixel(int pos, int maxSize);;

void executeBotTurnVisual(t_game *game)
{
    SDL_Delay(300);
    botTurn(game);
    printBoard(game);
    printBitBoard(game->bmask, game->bp1, game->rows, game->cols);
    // displayUserMsg();
    if (isWinner(game->bp2, game->rows, game->cols))
    {
        game->winner = TRUE;
        printBoard(game);
        ft_putendl_fd("\tBOT THE WINNER!", 1);
    }
    if (game->turn >= (game->cols * game->rows))
    {
        game->winner = TRUE;
        printBoard(game), drawGame();
    }
}

int executeUserTurnVisual(t_game *game, int x, int y)
{
    displayUserMsg();
    setUserInputVisual(game, x, y);
    printBoard(game); //rm
    printBitBoard(game->bmask, game->bp1, game->rows, game->cols);
    if (isWinner(game->bp1, game->rows, game->cols))
    {
        game->winner = TRUE;
        return (printBoard(game), ft_putendl_fd("\tUSER THE WINNER!", 1), 1);
    }
    if (game->turn >= (game->cols * game->rows))
    {
        game->winner = TRUE;
        return (printBoard(game), drawGame(), 1);
    }
    return (0);
}

void    setUserInputVisual(t_game *game, int col, int row)
{
    col = getPosFromPixel(col, game->cols);
    row =  getOpenedRowFromCol(game->bmask, col, game->cols, game->rows);
    setChecker(game->bp1, game->rows, row, col);
    setChecker(game->bmask, game->rows, row, col);
    game->steps[game->turn] = col + 1;
    game->turn += 1;
}

int getPosFromPixel(int pos, int maxSize)
{
    int n = round(pos / TILE_SIZE(1));
    if (n < 0)
        n = 0;
    if (n > maxSize * TILE_SIZE(1))
        n = maxSize - 1;
    return (n); 
}