#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

void drawGrid(t_game *game, SDL_Renderer* renderer);
void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int tile_size);
void Draw3DRectangle(SDL_Renderer* renderer, int32_t x, int32_t y, int32_t width, int32_t height);
void DrawShadedCircleBorder(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void DrawShadedCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, t_rgba rgba);

void animateChecker(SDL_Renderer* renderer, uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], 
int startRow, int startCol, int endRow, int endCol, int rowsMax, int tile_size, t_rgba rgba)
{
    float currentX = startCol * tile_size + (tile_size / 2);
    float currentY = (rowsMax - 1 - startRow) * tile_size + (tile_size / 2);
    float targetX = endCol * tile_size + (tile_size / 2);
    float targetY = (rowsMax - 1 - endRow) * tile_size + (tile_size / 2);

    float deltaX = targetX - currentX;
    float deltaY = targetY - currentY;
    float stepX = deltaX / 100.0;
    float stepY = deltaY / 100.0;

    for (int i = 0; i < 100; ++i) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        float currentPosX = currentX + stepX * i;
        float currentPosY = currentY + stepY * i;

        DrawShadedCircle(renderer, currentPosX, currentPosY, tile_size / 3, rgba);
        for (int j = 0; j < 5; j++) {
            DrawShadedCircleBorder(renderer, currentPosX - 1 + j, currentPosY - 1 + j, tile_size / 3);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(20); // Control the speed of the animation
    }

    // Draw the final position
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawChecker(bp, bmask, renderer, endRow, endCol, rowsMax, tile_size);
    SDL_RenderPresent(renderer);
}

void    render(t_gameVisual *gameVis, t_game *game)
{
    SDL_SetRenderDrawColor(gameVis->ren, 255, 255, 255, 105);
    SDL_RenderClear(gameVis->ren);

    drawGrid(game, gameVis->ren);

    SDL_RenderPresent(gameVis->ren);
}

void drawGrid(t_game *game, SDL_Renderer* renderer)
{
    int rowsMax = game->rows;
    int colsMax = game->cols;
    int tile_size = game->tile_size;
    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
    for (int r = 0; r < rowsMax ; r++)
    {
        for (int c = 0; c < colsMax; c++)
        {
            Draw3DRectangle(renderer, c * tile_size, (rowsMax - 1 - r) * tile_size, 
            tile_size - MARGINE, tile_size - MARGINE);
            drawChecker(game->bp1, game->bmask, renderer, r, c, rowsMax, tile_size);
        }
    }
}

void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int tile_size)
{
    t_rgba  rgba;

    if (bp[row] & (1UL << col)) // green
    {
        rgba.r = 22;
        rgba.g = 160;
        rgba.b = 133;
        rgba.a = 100;
    }
    else if ((bmask[row] & (1UL << col)) && !(bp[row] & (1UL << col))) // red
    {
        rgba.r = 207;
        rgba.g = 0;
        rgba.b = 15;
        rgba.a = 1;
    }
    else
    {
        rgba.r = 255;
        rgba.g = 248;
        rgba.b = 220;
        rgba.a = 1;
    }
    int centreX = col * tile_size + (tile_size / 2);
    int centreY = (rowsMax - 1 - row ) * tile_size + (tile_size / 2);
    DrawShadedCircle(renderer, centreX, centreY, tile_size / 3, rgba);
    for (int i = 0; i < 5; i++)
        DrawShadedCircleBorder(renderer, centreX - 1 + i, centreY - 1 + i, tile_size / 3);
}

void Draw3DRectangle(SDL_Renderer* renderer, int32_t x, int32_t y, int32_t width, int32_t height)
{
    for (int32_t i = 0; i < height; ++i)
    {
        // float intensity = 1.0f - (float)i / height;
        float intensity = 1;
        SDL_SetRenderDrawColor(renderer, (int)(242 * intensity), (int)(239 * intensity), (int)(239 * intensity), 10);
        SDL_RenderDrawLine(renderer, x, y + i, x + width, y + i);
    }
}

void DrawShadedCircleBorder(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
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

void DrawShadedCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, t_rgba rgba)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                // Calculate the distance from the center
                // float distance = sqrtf(x * x + y * y);
                // float intensity = 1.0f - (distance / radius);
                float intensity = 1;

                // Calculate color based on intensity
                int r = (int)(rgba.r * intensity);
                int g = (int)(rgba.g * intensity);
                int b = (int)(rgba.b * intensity);

                // Draw the point
                SDL_SetRenderDrawColor(renderer, r, g, b, rgba.a);
                SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
            }
        }
    }

}


