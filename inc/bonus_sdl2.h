#ifndef BONUS_SDL2_H
# define BONUS_SDL2_H

# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_timer.h>
# include <SDL2/SDL_render.h>
# include "connect_four.h"

# define ANIMATION_STEP 30
# define MARGINE 1

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
void    setUserInputVisual(t_game *game, t_gameVisual *gameVis, int row, int col);
void    render(t_gameVisual *gameVis, t_game *game);
t_rgba  getRgba(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], int row, int col);
t_rgba  getRgbaEmpty(void);
void    drawChecker(SDL_Renderer* renderer, int row, int col, int rowsMax, int tile_size, t_rgba rgba);
void    DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, t_rgba rgba);
void    drawGrid(t_game *game, SDL_Renderer* renderer);
void    drawAnimatedChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], t_game *game, t_gameVisual *gameVis, int row, int col);

#endif //BONUS_SDL2_H