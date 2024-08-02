#include "../inc/connect_four.h"

/* int main(int ac, char **av)
{
    t_game  game;

    if (ac == 1)
        return (ft_putendl_fd("Usage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDOUT_FILENO), 0);
    if (validateInput(ac, av, &game) != 0)
        return (-1);
    srand(time(NULL));
    game.turn = rand() % 2;
    initGame(&game);
    if (launchGame(&game) == -1)
        return (-1);
    return (0);
} */

int    launchGame(t_game *game)
{
    while (1)
    {
        test();
        printBoard(game);
        printBitBoard(game->bmask, game->bp1, game->rows, game->cols);
        if (game->turn % 2 == 0)
        {
            if (usersTurn(game) == -1)
                return (-1);
        }
        else
            robotsTurn(game);
        if (game->turn >= (game->cols * game->rows))
            return (printBoard(game), drawGame(), 1);
    }
    return (0);
}

int    usersTurn(t_game *game)
{
    char str[100];
    int col;
    while (1)
    {
        write(STDOUT_FILENO, "* Press 'q' to quit the game\n\n", 30);
        write(STDOUT_FILENO, COLOR_GREEN, ft_strlen(COLOR_GREEN));
        write(STDOUT_FILENO, "Y O U R  T U R N : ", 20);
        write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
        if (read(STDIN_FILENO, str, 100) > 0)
        {
            if (!ft_strncmp(str, "q", 1) || !ft_strncmp(str, "exit", 4))
                return (-1);
            col = ft_atoi(str) - 1;
            if (col < 0 || col >= game->cols)
                continue;
            int row = getOpenedRowFromCol(game->bmask, col, game->cols, game->rows);
            if (row == -1)
                continue;
            setChecker(game->bp1, game->rows, row, col);
            setChecker(game->bmask, game->rows, row, col);
            game->steps[game->turn] = col + 1;
            game->turn += 1;
            return (0);
        }
    }
    return (0);
}

void    robotsTurn(t_game *game)
{
    while (1)
    {
        int col = rand() % game->cols;
        if (col < 0 || col > game->cols)
            continue;
        int row = getOpenedRowFromCol(game->bmask, col, game->cols, game->rows);
        if (row == -1)
            continue;
        if (!isValidPosition(game->bmask, row, col))
            continue;
        setChecker(game->bp2, game->rows, row, col);
        setChecker(game->bmask, game->rows, row, col);
        game->steps[game->turn] = col + 1;
        game->turn += 1;
        return;
    }
}
