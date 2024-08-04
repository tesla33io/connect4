#ifndef BONUS_SDL2_H
# define BONUS_SDL2_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2/SDL_render.h>
#include "connect_four.h"

# define ANIMATION_SPEED 1
# define MARGINE 0

typedef struct s_gameVisual
{
    SDL_Window* win;
    SDL_Renderer *ren;
	u_int32_t	*colorBuf;
    int         isGameRunning;
}   t_gameVisual;

typedef struct s_rgba
{
    int r;
    int g;
    int b;
    int a;
}   t_rgba;

void    processInput(t_gameVisual *gameVis, t_game *game);
int     executeUserTurnVisual(t_game *game, t_gameVisual *gameVis, int x, int y);
void    executeBotTurnVisual(t_game *game, t_gameVisual *gameVis);
void    setUserInputVisual(t_game *game, int row, int col);
void    render(t_gameVisual *gameVis, t_game *game);

#endif //BONUS_SDL2_H