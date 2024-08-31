#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

void DrawRectangle(SDL_Renderer* renderer, int32_t x, int32_t y, int32_t width, int32_t height);
void DrawCircleBorder(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

void    render(t_gameVisual *gameVis, t_game *game)
{
    SDL_SetRenderDrawColor(gameVis->ren, 255, 255, 255, 1);
    SDL_RenderClear(gameVis->ren);

    drawGrid(game, gameVis->ren);

    SDL_RenderPresent(gameVis->ren);
}

void drawGrid(t_game *game, SDL_Renderer* renderer)
{
    t_rgba  rgba;
    int rowsMax = game->rows;
    int colsMax = game->cols;
    int tile_size = game->tile_size;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
    for (int r = 0; r < rowsMax ; r++)
    {
        for (int c = 0; c < colsMax; c++)
        {
            DrawRectangle(renderer, c * tile_size, (rowsMax - 1 - r) * tile_size, 
            tile_size, tile_size);

            if (r != game->last_checker_row || c != game->last_checker_col)
                rgba = getRgba(game->bp1, game->bmask, r, c);
            else
                rgba = getRgbaEmpty();
            drawChecker(renderer, r, c, rowsMax, tile_size, rgba);
        }
    }
}

void    drawAnimatedChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], t_game *game, t_gameVisual *gameVis, int row, int col)
{
    t_rgba  rgba = getRgba(bp, bmask, row, col);
    float tile_size = game->tile_size;
    int rowsMax = game->rows;
    float     centreX = col * tile_size + (tile_size / 2);
    float     centreY = (rowsMax - 1 - row ) * tile_size + (tile_size / 2);
    float     startCentreY = 0;

    while (startCentreY <= centreY)
    {
        SDL_SetRenderDrawColor(gameVis->ren, 255, 255, 255, 1);
        SDL_RenderClear(gameVis->ren);
        drawGrid(game, gameVis->ren);
        DrawCircle(gameVis->ren, centreX, startCentreY, tile_size / 3, rgba);
        SDL_RenderPresent(gameVis->ren);
        startCentreY += ANIMATION_STEP;
        SDL_Delay(5);
    }
}

t_rgba getRgbaEmpty(void)
{
    t_rgba  rgba;

    rgba.r = 255;
    rgba.g = 255;
    rgba.b = 255;
    rgba.a = 1;
    return (rgba);
}


t_rgba getRgba(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], int row, int col)
{
    t_rgba  rgba;

    if (bp[row] & (1UL << col)) // green
    {
        rgba.r = 0;
        rgba.g = 160;
        rgba.b = 133;
        rgba.a = 100;
    }
    else if ((bmask[row] & (1UL << col)) && !(bp[row] & (1UL << col))) // red
    {
        rgba.r = 207;
        rgba.g = 0;
        rgba.b = 0;
        rgba.a = 1;
    }
    else
        return (getRgbaEmpty());
    return (rgba);
}

void drawChecker(SDL_Renderer* renderer, int row, int col, int rowsMax, int tile_size, t_rgba rgba)
{
    int     centreX = col * tile_size + (tile_size / 2);
    int     centreY = (rowsMax - 1 - row ) * tile_size + (tile_size / 2);

    DrawCircle(renderer, centreX, centreY, tile_size / 3, rgba);
    for (int i = 0; i < 4; i++)
        DrawCircleBorder(renderer, centreX - 1 + i, centreY - 1 + i, tile_size / 3);
}

void DrawRectangle(SDL_Renderer* renderer, int32_t x, int32_t y, int32_t width, int32_t height)
{
    SDL_SetRenderDrawColor(renderer, 242, 239, 239, 10);
    SDL_Rect backgroundRect = {x - MARGINE, y, width - MARGINE, height};
    SDL_RenderFillRect(renderer, &backgroundRect);
}

void DrawCircleBorder(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        float intensityBottomRight = (float)(radius + x) / radius;

        SDL_SetRenderDrawColor(renderer, (int)(120 * intensityBottomRight), (int)(120 * intensityBottomRight), (int)(255 * intensityBottomRight), 255);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);

        SDL_SetRenderDrawColor(renderer, (int)(120 * intensityBottomRight), (int)(120 * intensityBottomRight), (int)(255 * intensityBottomRight), 255);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, t_rgba rgba)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int r = rgba.r;
                int g = rgba.g;
                int b = rgba.b;
                SDL_SetRenderDrawColor(renderer, r, g, b, rgba.a);
                SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
            }
        }
    }
}
