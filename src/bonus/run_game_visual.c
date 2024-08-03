#include "../../inc/bonus_sdl2.h"

int initializeWindow(t_gameVisual *game, int rows, int cols, int scale);
void destroyWindow(t_gameVisual *game);

int runGameVisual(t_game *game)
{
    t_gameVisual *gameVis = gc_malloc(sizeof(t_gameVisual*));
    gameVis->isGameRunning = initializeWindow(gameVis, game->rows, game->cols, 1);
    initGame(game);
    printBoard(game);
    printBitBoard(game->bmask, game->bp1, game->rows, game->cols); // rm
    while (gameVis->isGameRunning)
    {
        processInput(gameVis, game);
        if (game->turn % 2 != 0 && game->winner == FALSE)
            executeBotTurnVisual(game);
        render(gameVis, game);
        
        // renderGameBoard(gameVis, game);
    }
    destroyWindow(gameVis); //gc_malloc how to free
    return 0;
}

int initializeWindow(t_gameVisual *game, int rows, int cols, int scale)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        ft_putstr_fd("Error initializing SDL.\n", STDERR_FILENO);
        return 0;
    }
    game->win = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH(cols, scale),
        WINDOW_HEIGHT(rows, scale),
        SDL_WINDOW_SHOWN
    ); // SDL_WINDOW_BORDERLESS //SDL_WINDOW_SHOWN
    if (!game->win)
    {
        ft_putstr_fd("Error creating SDL window.\n", STDERR_FILENO);
        return FALSE;
    }
    game->ren = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //0
    if (game->ren == NULL)
    {
        SDL_DestroyWindow(game->win);
        ft_putstr_fd("SDL_CreateRenderer Error\n", STDERR_FILENO);
        // ft_putstr_fd(SDL_GetError(), STDERR_FILENO);
        return FALSE;
    }
    SDL_SetRenderDrawColor(game->ren, 255, 255, 255, 100);
    SDL_RenderClear(game->ren);
    SDL_RenderPresent(game->ren);
    return TRUE;
}

void destroyWindow(t_gameVisual *game)
{
    SDL_DestroyRenderer(game->ren);
    SDL_DestroyWindow(game->win);
    SDL_Quit();
}
