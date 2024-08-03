#include "../../inc/connect_four.h"

void           printTurn_n_pos(t_game *game);
static void    displayeTitle();

void    printBoard(t_game *game)
{
    char *spaces = "          ";
    char *topBorder = "  |¯¯¯¯¯¯|";
    char *emptyBorder = "  |      |";
    char *circleTop = "/¯¯\\";
    char *circleBottom = "\\__/";
    // char *circleTopWin = "/¯/\\";
    // char *circleBtmWin = "\\/_/";
    char *bottomBorder = "  |______|";
    char *leftBorder = "  | ";
    char *rightBorder = " |";

    displayeTitle();

    // display board
    for (int i = game->rows - 1; i >= 0; i--)
    {
        write(STDOUT_FILENO, COLOR_GRAY, ft_strlen(COLOR_GRAY));
        for (int k = 0; k < game->cols; k++)
            write(STDOUT_FILENO, spaces, ft_strlen(spaces));
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
            write(STDOUT_FILENO, topBorder, ft_strlen(topBorder));
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
        {
            if (!(game->bp1[i] & (1UL << k)) && !(game->bmask[i] & (1UL << k)))
                write(STDOUT_FILENO, emptyBorder, ft_strlen(emptyBorder));
            else
            {
                write(STDOUT_FILENO, leftBorder, ft_strlen(leftBorder));
                if (game->bp1[i] & (1UL << k))
                    write(STDOUT_FILENO, COLOR_GREEN, ft_strlen(COLOR_GREEN));
                else
                    write(STDOUT_FILENO, COLOR_RED, ft_strlen(COLOR_RED));
                write(STDOUT_FILENO, circleTop, ft_strlen(circleTop));
                write(STDOUT_FILENO, COLOR_GRAY, ft_strlen(COLOR_GRAY));
                write(STDOUT_FILENO, rightBorder, ft_strlen(rightBorder));
            }
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
        {
            if (!(game->bp1[i] & (1UL << k)) && !(game->bmask[i] & (1UL << k)))
                write(STDOUT_FILENO, emptyBorder, ft_strlen(emptyBorder));
            else
            {
                write(STDOUT_FILENO, leftBorder, ft_strlen(leftBorder));
                if (game->bp1[i] & (1UL << k))
                    write(STDOUT_FILENO, COLOR_GREEN, ft_strlen(COLOR_GREEN));
                else
                    write(STDOUT_FILENO, COLOR_RED, ft_strlen(COLOR_RED));
                write(STDOUT_FILENO, circleBottom, ft_strlen(circleBottom));
                write(STDOUT_FILENO, COLOR_GRAY, ft_strlen(COLOR_GRAY));
                write(STDOUT_FILENO, rightBorder, ft_strlen(rightBorder));
            }
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
            write(STDOUT_FILENO, bottomBorder, ft_strlen(bottomBorder));
        write(STDOUT_FILENO, "\n", 1);
        write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
    }
    write(STDOUT_FILENO, "\n", 1);
    // printTurn_n_pos(game);
}

void    printBitBoard(uint64_t bmask[MAX_SIZE], uint64_t bp[MAX_SIZE], int rowMax, int colMax)
{
    for (int r = rowMax - 1; r >= 0; r--)
    {
        for (int c = 0; c < colMax; c++)
        {
            if (bp[r] & (1UL << c))
                ft_putstr_fd("X ", 1);
            else if ((bmask[r] & (1UL << c)) && !(bp[r] & (1UL << c)))
                ft_putstr_fd("O ", 1);
            else
                ft_putstr_fd(". ", 1);
        }
        ft_putstr_fd("\n", 1);
    }
}

static void    displayeTitle()
{
    const char *title = 
        "\n"
        "   ██████╗ ██████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗   ██╗  ██╗\n"
        "  ██╔════╝██╔═══██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝   ██║  ██║\n"
        "  ██║     ██║   ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║      ███████║\n"
        "  ██║     ██║   ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║      ╚════██║\n"
        "  ╚██████╗╚██████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║           ██║\n"
        "   ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝           ╚═╝"
        "\n";

    // print title
    write(STDOUT_FILENO, COLOR_BLUE, ft_strlen(COLOR_BLUE));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
}

void    printTurn_n_pos(t_game *game)
{
    for (int i = 0; i < game->rows * game->cols; i++)
    {
        ft_putnbr_lft_fd(game->steps[i], STDOUT_FILENO);
        write (STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
    ft_putnbr_lft_fd(game->turn, STDOUT_FILENO);
    write(STDOUT_FILENO, "\n", 1);

    ft_putstr_fd("User: ", STDOUT_FILENO);
    for (int j = 0; j < game->turn; j++)
    {
        if ((j % 2) == 0 && game->steps[j])
        {
            ft_putnbr_lft_fd(game->steps[j], STDOUT_FILENO);
            write(STDOUT_FILENO, " ", 1);
        }
    }
    write(STDOUT_FILENO, "\n", 1);
    ft_putstr_fd("Robot: ", STDOUT_FILENO);
    for (int j = 0; j < game->turn; j++)
    {
        if ((j % 2) != 0 && game->steps[j])
        {
            ft_putnbr_lft_fd(game->steps[j], STDOUT_FILENO);
            write(STDOUT_FILENO, " ", 1);
        }
    }
    write (STDOUT_FILENO, "\n\n", 2);
}
