#include "../../inc/connect_four.h"

void    initGame(t_game *game)
{
    ft_memset(game->bp1, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bp2, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bmask, 0, MAX_SIZE * sizeof(uint64_t));
}

int validateInput(int size, char **args, t_game *game)
{
    if (size != 3)
        return (ft_putendl_fd("Error:\nUsage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDERR_FILENO), 1);
    int rows = ft_atoi(args[1]);
    int cols = ft_atoi(args[2]);
    if (rows < 6 || cols < 7)
        return (ft_putendl_fd("Error:\nUsage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDERR_FILENO), 2);
    game->rows = rows;
    game->cols = cols;
    return (0);
}
