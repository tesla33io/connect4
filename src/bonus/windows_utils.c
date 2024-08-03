#include "../../inc/bonus_sdl2.h"

int initializeWindow(t_gameVisual *game);
void destroyWindow(t_gameVisual *game);

int runGameVisual(t_game *game)
{
    (void)game;
    t_gameVisual *gameVis = gc_malloc(sizeof(t_gameVisual*));
    gameVis->isGameRunning = initializeWindow(gameVis);
    initGame(game);
    while (gameVis->isGameRunning)
    {
        processInput(gameVis, game);
        SDL_SetRenderDrawColor(gameVis->ren, 255, 0, 0, 255);
        // printBoard(game);
    }
    destroyWindow(gameVis);
    return 0;
}

int initializeWindow(t_gameVisual *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return 0;
    }
    game->win = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH(7),
        WINDOW_HEIGHT(6),
        SDL_WINDOW_SHOWN
    ); // SDL_WINDOW_BORDERLESS //SDL_WINDOW_SHOWN
    if (!game->win)
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return FALSE;
    }
    game->ren = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //0
    if (game->ren == NULL)
    {
        SDL_DestroyWindow(game->win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return FALSE;
    }

    SDL_SetRenderDrawColor(game->ren, 255, 255, 255, 255);
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
