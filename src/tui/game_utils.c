#include "../../inc/connect_four.h"

void    usageMsg();

void    initGame(t_game *game)
{
    ft_memset(game->bp1, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bp2, 0, MAX_SIZE * sizeof(uint64_t));
    ft_memset(game->bmask, 0, MAX_SIZE * sizeof(uint64_t));
    game->winner = FALSE;
    game->rows = 0;
    game->cols = 0;
    game->visual = FALSE;
    game->turn = rand() % 2;
    game->last_checker_row = -1;
    game->last_checker_col = -1;
}

int validateInput(int size, char **args, t_game *game)
{
    if (size < 3 || size > 4)
        return (usageMsg(), 1);
    for (int i = 1; i < size && args[i]; i++)
    {
        if (!ft_strncmp(args[i], "-g", 2) || !ft_strncmp(args[i], "g", 1))
        {
            game->visual = TRUE;
        }
        else if (!ft_strncmp(args[i], "-t", 2) || !ft_strncmp(args[i], "g", 1))
        {
            game->visual = FALSE;
        }
        else
        {
            int nbr = ft_atoi(args[i]);
            if (!nbr || nbr > MAX_SIZE)
                return (usageMsg(), 1);
            if (!game->rows)
            {
                if (nbr < MIN_ROWS)
                    return (usageMsg(), 1);
                game->rows = nbr;
            }
            else if (!game->cols)
            {
                if (nbr < MIN_COLS)
                    return (usageMsg(), 1);
                game->cols = nbr;
            }
        }
    }
    if (!game->rows || !game->cols)
        return (usageMsg(), 1);
    return (0);
}

void    usageMsg()
{
    ft_putstr_fd("Usage:", STDERR_FILENO);
    ft_putstr_fd("./connect4 <rows> <columns> <-t or -g>\n\n", STDERR_FILENO);
    ft_putstr_fd("\trows      -> min 6, max 60\n", STDERR_FILENO);
    ft_putstr_fd("\tcolumns   -> min 7, max 60\n", STDERR_FILENO);
    ft_putstr_fd("\t-t        -> terminal ui\n", STDERR_FILENO);
    ft_putstr_fd("\t-g        -> graphical ui | row max 29\n", STDERR_FILENO);
}

void    displayUserMsg(void)
{
    write(STDOUT_FILENO, COLOR_GREEN, ft_strlen(COLOR_GREEN));
    write(STDOUT_FILENO, "Y O U R  T U R N : ", 20);
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
}
