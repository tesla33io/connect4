#include "../inc/connect_four.h"
#include "../inc/bonus_sdl2.h"
#include <fcntl.h>

int main(int ac, char **av)
{
    t_game  game;

    initGame(&game);
    if (validateInput(ac, av, &game) != 0)
        return (-1);
    srand(time(NULL));
    if (game.visual == TRUE && game.rows < 30)
        return (runGameVisual(&game));
    if (launchGame(&game) == -1)
        return (-1);
    return (0);
}

int    launchGame(t_game *game)
{
    while (1)
    {
        printBoard(game);
        if (game->turn % 2 == 0)
        {
            if (usersTurn(game) == -1)
                return (-1);
            if (isWinner(game->bp1, game->rows, game->cols))
                return (ft_putendl_fd("/n\tYOU ARE THE WINNER!", 1), printBoard(game), userWinner(), 1);
        }
        else
        {
            botTurn(game);
            if (isWinner(game->bp2, game->rows, game->cols))
                return (ft_putendl_fd("/n\tBOT THE WINNER!", 1), printBoard(game), botWinner(), 1);
        }
        if (game->turn >= (game->cols * game->rows))
            return (printBoard(game), drawGame(), 1);
    }
    return (0);
}

int    usersTurn(t_game *game)
{
    char *str = NULL;
    int col;
    while (1)
    {
        write(STDOUT_FILENO, "\n* Press 'q' to quit the game\n\n", 30);
        displayUserMsg();
        str = get_next_line(STDIN_FILENO);
        if (!str)
            return (-1);
        if (!ft_strncmp(str, "q", 1) || !ft_strncmp(str, "exit", 4))
        {
            free(str);
            str = NULL;
            return (-1);
        }
        col = ft_atoi(str) - 1;
        free(str);
        str = NULL;
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
    return (0);
}

void    botTurn(t_game *game)
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
