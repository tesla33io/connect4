#ifndef BONUS_SDL2_H
# define BONUS_SDL2_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
// #include <SDL_ttf.h>
// #include <SDL2/SDL_ttf.h> 
#include "connect_four.h"

# define TILE_SIZE(n) (80 * n)
# define ANIMATION_SPEED 1
# define MARGINE 1
# define WINDOW_WIDTH(col, n) (col * TILE_SIZE(n))
# define WINDOW_HEIGHT(row, n) (row * TILE_SIZE(n))

typedef struct s_gameVisual
{
    SDL_Window* win;
    SDL_Renderer *ren;
	u_int32_t	*colorBuf;
    int         isGameRunning;
}   t_gameVisual;

void    processInput(t_gameVisual *gameVis, t_game *game);
int     executeUserTurnVisual(t_game *game, int x, int y);
void     executeBotTurnVisual(t_game *game);
void    setUserInputVisual(t_game *game, int row, int col);
int    initGameVis(t_gameVisual *dataVis, int rows, int cols);
void    render(t_gameVisual *gameVis, t_game *game);

#endif //BONUS_SDL2_H