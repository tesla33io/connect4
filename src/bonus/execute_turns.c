#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

int getPosFromPixel(int pos, int maxSize, int tile_size);

void executeBotTurnVisual(t_game *game, t_gameVisual *gameVis)
{
    SDL_Delay(400);
    botTurn(game);
    if (game->visual)
    {
        SDL_Delay(400);
        drawAnimatedChecker(game->bp1, game->bmask, game, gameVis, game->last_checker_row, game->last_checker_col);
        game->last_checker_row = -1;
        game->last_checker_col = -1;
    }
    printBoard(game);
    render(gameVis, game);
    displayUserMsg();
    if (isWinner(game->bp2, game->rows, game->cols))
    {
        game->winner = TRUE;
        ft_putendl_fd("\tBOT THE WINNER!", 1);
        printBoard(game);
        render(gameVis, game);
        botWinner();
    }
    if (game->turn >= (game->cols * game->rows))
    {
        game->winner = TRUE;
        render(gameVis, game);
        printBoard(game);
        drawGame();
    }
}

int executeUserTurnVisual(t_game *game, t_gameVisual *gameVis, int x, int y)
{
    displayUserMsg();
    setUserInputVisual(game, gameVis, x, y);
    render(gameVis, game);
    printBoard(game);
    if (isWinner(game->bp1, game->rows, game->cols))
    {
        game->winner = TRUE;
        return (ft_putendl_fd("\tUSER THE WINNER!", 1), render(gameVis, game) ,printBoard(game), userWinner(), 1);
    }
    if (game->turn >= (game->cols * game->rows))
    {
        game->winner = TRUE;
        return (printBoard(game), render(gameVis, game), drawGame(), 1);
    }
    return (0);
}

void    setUserInputVisual(t_game *game, t_gameVisual *gameVis, int col, int row)
{
    col = getPosFromPixel(col, game->cols, game->tile_size);
    row =  getOpenedRowFromCol(game->bmask, col, game->cols, game->rows);
    game->last_checker_row = row;
    game->last_checker_col = col;
    setChecker(game->bp1, game->rows, row, col);
    setChecker(game->bmask, game->rows, row, col);
    SDL_Delay(400);
    drawAnimatedChecker(game->bp1, game->bmask, game, gameVis, row, col);
    game->last_checker_row = -1;
    game->last_checker_col = -1;
    game->steps[game->turn] = col + 1;
    game->turn += 1;
}

int getPosFromPixel(int pos, int maxSize, int tile_size)
{
    int n = round(pos / tile_size);
    if (n < 0)
        n = 0;
    if (n > maxSize * tile_size)
        n = maxSize - 1;
    return (n); 
}
