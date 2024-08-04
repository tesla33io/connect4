#include "../inc/connect_four.h"
#include "../inc/bonus_sdl2.h"
#include "../inc/get_next_line.h"

int main(int ac, char **av)
{
    t_game  game;

    if (ac == 1)
        return (ft_putendl_fd("Usage:\t./connect4 <rows (min 6)> <columns (min 7)>", STDOUT_FILENO), 0);
    if (validateInput(ac, av, &game) != 0)
        return (-1);
    srand(time(NULL));
    game.turn = rand() % 2;
    if (game.visual == 1)
        return (runGameVisual(&game));
    initGame(&game);
    if (launchGame(&game) == -1)
        return (-1);
    return (0);
}

int    launchGame(t_game *game)
{
    while (1)
    {
        printBoard(game);
        printBitBoard(game->bmask, game->bp1, game->rows, game->cols);
        if (game->turn % 2 == 0)
        {
            if (usersTurn(game) == -1)
                return (-1);
            if (isWinner(game->bp1, game->rows, game->cols))
            {
                return (printBoard(game), ft_putendl_fd("\tUSER THE WINNER!", 1), 1);
            }
        }
        else
        {
            botTurn(game);
            if (isWinner(game->bp2, game->rows, game->cols))
            {
                return (printBoard(game), ft_putendl_fd("\tBOT THE WINNER!", 1), 1);
            }
        }
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
        displayUserMsg();
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
