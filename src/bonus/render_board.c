#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

void drawGrid(t_game *game, SDL_Renderer* renderer, int rowsMax, int colsMax, int scale);
void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int scale);
void animateChecker(SDL_Renderer* renderer, const int startX, const int startY, int endX, int endY);

void    render(t_gameVisual *gameVis, t_game *game)
{
    int scale = game->scale;
    SDL_SetRenderDrawColor(gameVis->ren, 255, 255, 255, 105);
    SDL_RenderClear(gameVis->ren);

    drawGrid(game, gameVis->ren, game->rows, game->cols, scale);

    SDL_RenderPresent(gameVis->ren);
}

void drawGrid(t_game *game, SDL_Renderer* renderer, int rowsMax, int colsMax, int scale)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int r = 0; r < rowsMax ; r++)
    {
        for (int c = 0; c < colsMax; c++)
        {
            SDL_Rect rect = { c * TILE_SIZE(scale), (rowsMax - 1 - r) * TILE_SIZE(scale), 
            TILE_SIZE(scale) - MARGINE, TILE_SIZE(scale) - MARGINE};
            SDL_SetRenderDrawColor(renderer, 222, 184, 135, 200);
            SDL_RenderFillRect(renderer, &rect);
            drawChecker(game->bp1, game->bmask, renderer, r, c, rowsMax, scale);
        }
    }
}

void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int scale)
{
    SDL_Rect rect = { 
        col * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4), 
        (rowsMax - 1 - row ) * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4), 
        TILE_SIZE(scale) / 2, 
        TILE_SIZE(scale) / 2
    };
    if (bp[row] & (1UL << col))
    {
        SDL_SetRenderDrawColor(renderer, 120, 187, 88, 255);
    }
    else if ((bmask[row] & (1UL << col)) && !(bp[row] & (1UL << col)))
        SDL_SetRenderDrawColor(renderer, 255, 29, 18, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 248, 220, 255);
    SDL_RenderFillRect(renderer, &rect);
}

/* 
void animateChecker(SDL_Renderer* renderer,  const int startX, const int startY, int endX, int endY)
{
    static int currentX = startX;
    static int currentY = startY;
    static int moving = TRUE;

    if (moving) {
        if (currentX < endX) {
            currentX += ANIMATION_SPEED;
        } else if (currentX > endX) {
            currentX -= ANIMATION_SPEED;
        }

        if (currentY < endY) {
            currentY += ANIMATION_SPEED;
        } else if (currentY > endY) {
            currentY -= ANIMATION_SPEED;
        }

        if (currentX == endX * TILE_SIZE(1) && currentY == endY * TILE_SIZE(1)) {
            moving = FALSE;
        }
    }

    drawChecker(renderer, currentX / TILE_SIZE(1), currentY / TILE_SIZE(1));
}
 */