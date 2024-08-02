#include "../../inc/connect_four.h"

void    freeMemory(t_game *game)
{
    if (game->steps)
        free(game->steps);
    if (game->board)
    {
        for (int i = 0; i < game->rows; i++)
            free(game->board[i]);
        free(game->board);
    }
}

int allocateMemory(t_game *game)
{
    int size = game->cols * game->rows;
    game->steps = ft_calloc(size, sizeof(int));
    if (game->steps == NULL)
        return (ft_putendl_fd("malloc: bad allocation", STDERR_FILENO), 1);
    game->board = (int **)ft_calloc(game->rows, sizeof(int *));
    if (game->board == NULL)
        return (ft_putendl_fd("malloc: bad allocation", STDERR_FILENO), 2);
    for (int i = 0; i < game->rows; i++)
    {
        game->board[i] = (int *)malloc(game->cols * sizeof(int));
        if (game->board[i] == NULL)
        {
            ft_putendl_fd("malloc: bad allocation", STDERR_FILENO);
            for (int j = 0; j < i; j++) {
                free(game->board[j]);
            }
            free(game->board);
            return (3);
        }
    }
    return (0);
}
