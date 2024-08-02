#include "../inc/connect_four.h"

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

void    usersTurn(t_game *game)
{
    (void)game;
    char str[100];
    int col;
    while (1)
    {
        write(STDOUT_FILENO, "* Press 'q' to quit the game\n\n", 30);
        write(STDOUT_FILENO, color_codes[COLOR_GREEN], ft_strlen(color_codes[COLOR_GREEN]));
        write(STDOUT_FILENO, "Y O U R  T U R N : ", 20);
        write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
        if (read(STDIN_FILENO, str, 100) > 0)
        {
            if (!ft_strncmp(str, "q", 1) || !ft_strncmp(str, "exit", 4))
            {
               freeMemory(game);
                exit(-1);
            }
            col = ft_atoi(str);
            if (col <= 0 || col > game->cols)
                continue;
            int row = getOpenRowFromCol(game->board, col - 1, game->cols, game->rows);
            if (row == -1)
                continue;
            setChecker(game->board, row, col - 1, 0);
            game->steps[game->turn] = col;
            game->turn += 1;
            return;
        }
    }
}

void    robotsTurn(t_game *game)
{
    while (1)
    {
        int col = rand() % game->cols;
        if (col < 0 || col > game->cols)
            continue;
        int row = getOpenRowFromCol(game->board, col, game->cols, game->rows);
        if (row == -1)
            continue;
        if (!isValidPosition(game->board, row, col))
            continue;
        setChecker(game->board, row, col, 1);
        game->steps[game->turn] = col + 1;
        game->turn += 1;
        return;
    }
}

void    launchGame(t_game *game)
{
    while (1)
    {
        printBoard(game);
        if (game->turn % 2 == 0)
            usersTurn(game);
        else
            robotsTurn(game);
        if (game->turn >= (game->cols * game->rows))
            return (printBoard(game), drawGame(), freeMemory(game));
    }
}

int main(int ac, char **av)
{
    t_game  game;

    if (ac == 1)
        return (ft_putendl_fd("Usage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDOUT_FILENO), 0);
    if (validateInput(ac, av, &game) != 0)
        return (-1);
    srand(time(NULL));
    if (allocateMemory(&game) != 0)
        return (-1);
    game.turn = rand() % 2;
    initBoard(&game);
    launchGame(&game);
    return (0);
}
