#include "../../inc/connect_four.h"

void    initGame(t_game *game)
{
    ft_memset(game->bp1, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bp2, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bmask, 0, MAX_SIZE * sizeof(uint64_t));
    game->winner = FALSE;
    game->scale = 1;
}

int validateInput(int size, char **args, t_game *game)
{
    if (size < 3 || size > 4)
        return (ft_putendl_fd("Error:\nUsage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDERR_FILENO), 1);
    int rows = ft_atoi(args[1]);
    int cols = ft_atoi(args[2]);
    int visual;
    visual = (size == 4) ? ft_atoi(args[3]) : 0;
    if (rows < MIN_ROWS || cols < MIN_COLS)
        return (ft_putendl_fd("Error:\nUsage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDERR_FILENO), 2);
    game->rows = rows;
    game->cols = cols;
    game->visual = visual;
    return (0);
}

void    displayUserMsg(void)
{
    write(STDOUT_FILENO, COLOR_GREEN, ft_strlen(COLOR_GREEN));
    write(STDOUT_FILENO, "Y O U R  T U R N : ", 20);
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
}
