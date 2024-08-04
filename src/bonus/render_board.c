#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

void drawGrid(t_game *game, SDL_Renderer* renderer, int rowsMax, int colsMax, int scale);
void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int scale);
void animateChecker(SDL_Renderer* renderer, const int startX, const int startY, int endX, int endY);
void Draw3DRectangle(SDL_Renderer* renderer, int32_t x, int32_t y, int32_t width, int32_t height);
void DrawShadedCircleBorder(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
void DrawShadedCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, t_rgba rgba);

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
    SDL_SetRenderDrawColor(renderer, 224, 224, 224, 255);
    for (int r = 0; r < rowsMax ; r++)
    {
        for (int c = 0; c < colsMax; c++)
        {
            // SDL_Rect rect = { c * TILE_SIZE(scale), (rowsMax - 1 - r) * TILE_SIZE(scale), 
            // TILE_SIZE(scale) - MARGINE, TILE_SIZE(scale) - MARGINE};
            // SDL_SetRenderDrawColor(renderer, 222, 184, 135, 200);
            // SDL_RenderFillRect(renderer, &rect);
            Draw3DRectangle(renderer, c * TILE_SIZE(scale), (rowsMax - 1 - r) * TILE_SIZE(scale), 
            TILE_SIZE(scale) - MARGINE, TILE_SIZE(scale) - MARGINE);
            drawChecker(game->bp1, game->bmask, renderer, r, c, rowsMax, scale);
        }
    }
}

void drawChecker(uint64_t bp[MAX_SIZE], uint64_t bmask[MAX_SIZE], SDL_Renderer* renderer, int row, int col, int rowsMax, int scale)
{
    (void)scale;
    (void)bp;
    (void)bmask;
    t_rgba  rgba;

    // SDL_Rect rect = { 
    //     col * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4), 
    //     (rowsMax - 1 - row ) * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4), 
    //     TILE_SIZE(scale) / 2, 
    //     TILE_SIZE(scale) / 2
    // };
    if (bp[row] & (1UL << col))
    {
        rgba.r = 120;
        rgba.g = 187;
        rgba.b = 88;
        rgba.a = 255;
    }
    else if ((bmask[row] & (1UL << col)) && !(bp[row] & (1UL << col)))
    {
        rgba.r = 255;
        rgba.g = 29;
        rgba.b = 18;
        rgba.a = 255;
    }
    else
    {
        rgba.r = 255;
        rgba.g = 248;
        rgba.b = 220;
        rgba.a = 255;
    }
        // SDL_SetRenderDrawColor(renderer, 120, 187, 88, 255);
        // SDL_SetRenderDrawColor(renderer, 255, 29, 18, 255);
        // SDL_SetRenderDrawColor(renderer, 255, 248, 220, 255);
    // SDL_RenderFillRect(renderer, &rect);

    DrawShadedCircle(renderer, (col * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4)), ((rowsMax - 1 - row ) * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4)), TILE_SIZE(scale) / 4, rgba);
    for (int i = 0; i < 5; i++)
        DrawShadedCircleBorder(renderer, (col * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4)) - 1 + i, ((rowsMax - 1 - row ) * TILE_SIZE(scale) + (TILE_SIZE(scale) / 4)) - 1 + i, TILE_SIZE(scale) / 4);
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
        // Calculate intensity for shading effect
        // float intensityTopLeft = (float)(radius - x) / radius;
        float intensityBottomRight = (float)(radius + x) / radius;

        // Top-left and bottom-right quadrants (darker)
        SDL_SetRenderDrawColor(renderer, (int)(120 * intensityBottomRight), (int)(120 * intensityBottomRight), (int)(255 * intensityBottomRight), 255);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);

        // Top-right and bottom-left quadrants (lighter) // 120 120 255
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