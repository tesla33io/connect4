#ifndef BONUS_SDL2_H
# define BONUS_SDL2_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
// #include <SDL_ttf.h>
// #include <SDL2/SDL_ttf.h> 
#include "connect_four.h"


# define TILE_SIZE 100
# define WINDOW_WIDTH(col) (col * TILE_SIZE)
# define WINDOW_HEIGHT(row) (row * TILE_SIZE)
# define TRUE 1
# define FALSE 0


typedef struct s_gameVisual
{
    SDL_Window* win;
    SDL_Renderer *ren;
    int         isGameRunning;
}   t_gameVisual;

void processInput(t_gameVisual *gameVis, t_game *game);

#endif //BONUS_SDL2_H