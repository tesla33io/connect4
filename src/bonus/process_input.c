#include "../../inc/bonus_sdl2.h"
#include "../../inc/connect_four.h"

void processInput(t_gameVisual *gameVis, t_game *game)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameVis->isGameRunning = FALSE;
            return;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                gameVis->isGameRunning = FALSE;
                return;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (game->turn % 2 == 0 && game->winner == FALSE)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (executeUserTurnVisual(game, x, y) != 0)
                    return;
            }
        }
    }
}
