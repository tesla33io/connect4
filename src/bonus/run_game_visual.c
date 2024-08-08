#include "../../inc/bonus_sdl2.h"

int initializeWindow(t_gameVisual *game, int rows, int cols, int tile_size);
void destroyWindow(t_gameVisual *game);
int calcTileSize(int rows, int cols);

int runGameVisual(t_game *game)
{
    t_gameVisual *gameVis = (t_gameVisual *)ft_calloc(1, sizeof(t_gameVisual));
    game->tile_size = calcTileSize(game->rows, game->cols);
    if (game->tile_size == -1)
        return (ft_putstr_fd("Size of the board too big", STDOUT_FILENO), -1);
    gameVis->isGameRunning = initializeWindow(gameVis, game->rows, game->cols, game->tile_size);
    printBoard(game);
    while (gameVis->isGameRunning)
    {
        processInput(gameVis, game);
        if (game->turn % 2 != 0 && game->winner == FALSE)
            executeBotTurnVisual(game, gameVis);
    }
    destroyWindow(gameVis);
    return 0;
}

int initializeWindow(t_gameVisual *game, int rows, int cols, int tile_size)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        ft_putstr_fd("Error initializing SDL.\n", STDERR_FILENO);
        return 0;
    }
    game->win = SDL_CreateWindow(
        "CONNECT4",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        cols * tile_size,
        rows * tile_size,
        SDL_WINDOW_SHOWN
    ); // SDL_WINDOW_BORDERLESS //SDL_WINDOW_SHOWN
    if (!game->win)
    {
        ft_putstr_fd("Error creating SDL window.\n", STDERR_FILENO);
        SDL_Quit();
        return FALSE;
    }
    game->ren = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //0
    if (game->ren == NULL)
    {
        SDL_DestroyWindow(game->win);
        ft_putstr_fd("SDL_CreateRenderer Error\n", STDERR_FILENO);
        SDL_Quit();
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
    free(game);
}

int calcTileSize(int rows, int cols)
{
    (void)rows;
    int tile_size = 50;
    float scale;
    if (rows > 30)
        return (-1);
    if (cols < 60 && rows < 30)
        scale = 0.60;
    if (cols < 55 && rows < 23)
        scale = 0.7;
    if (cols < 46 && rows < 26)
        scale = 0.8;
    if (cols < 39 && rows < 19)
        scale = 1;
    if (cols < 30 && rows < 15)
        scale = 1.3;
    if (cols < 20 && rows < 10)
        scale = 2;
    return (round(tile_size * scale));
}
