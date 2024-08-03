#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

int getPosFromPixel(int pos, int maxSize);
void    setUserInputVisual(t_game *game, int row, int col);

void processInput(t_gameVisual *gameVis, t_game *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameVis->isGameRunning = FALSE;
            return;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                gameVis->isGameRunning = FALSE;
                return;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            printBitBoard(game->bmask, game->bp1, game->rows, game->cols);
            if (game->turn % 2 == 0)
            {
                robotsTurn(game);
                int x, y;
                displayUserMsg();
                SDL_GetMouseState(&x, &y);
                setUserInputVisual(game, x, y);
                printf("Mouse click at (%d, %d)\n", x, y); // rm
            }
            else
                robotsTurn(game);
            if (game->turn >= (game->cols * game->rows))
                return (drawGame()); //printBoard(game),
        }
    }
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
    int n = round(pos / TILE_SIZE);
    if (n < 0)
        n = 0;
    if (n > maxSize * TILE_SIZE)
        n = maxSize * TILE_SIZE;
    // int boardPos = maxSize - 1 - n;
    printf("Board pos: %i, res -> %i\n", pos, n);
    return (n); 
}
