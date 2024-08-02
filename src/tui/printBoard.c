#include "../../inc/connect_four.h"

void    ft_printarr(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ft_putnbr_lft_fd(arr[i][j], STDOUT_FILENO);
            write (STDOUT_FILENO, " ", 1);
        }
    }
    write(STDOUT_FILENO, "\n", 1);
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
void    printBoard(t_game *game)
{
    char *spaces = "          ";
    char *topBorder = "  |¯¯¯¯¯¯|";
    char *emptyBorder = "  |      |";
    char *circleTop = "/¯¯\\";
    char *circleBottom = "\\__/";
    char *bottomBorder = "  |______|";
    char *leftBorder = "  | ";
    char *rightBorder = " |";
    const char *title = 
        "\n"
        "   ██████╗ ██████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗   ███████╗ ██████╗ ██╗   ██╗██████╗ \n"
        "  ██╔════╝██╔═══██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝   ██╔════╝██╔═══██╗██║   ██║██╔══██╗\n"
        "  ██║     ██║   ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║      █████╗  ██║   ██║██║   ██║██████╔╝\n"
        "  ██║     ██║   ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║      ██╔══╝  ██║   ██║██║   ██║██╔══██╗\n"
        "  ╚██████╗╚██████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║      ██║     ╚██████╔╝╚██████╔╝██║  ██║\n"
        "   ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝      ╚═╝      ╚═════╝  ╚═════╝ ╚═╝  ╚═╝"
        "\n";
    // print title
    write(STDOUT_FILENO, color_codes[COLOR_BLUE], ft_strlen(color_codes[COLOR_BLUE]));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
    // print board
    for (int i = 0; i < game->rows; i++)
    {
        write(STDOUT_FILENO, color_codes[COLOR_GRAY], ft_strlen(color_codes[COLOR_GRAY]));
        for (int k = 0; k < game->cols; k++)
        {
            write(STDOUT_FILENO, spaces, ft_strlen(spaces));
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
        {
            write(STDOUT_FILENO, topBorder, ft_strlen(topBorder));
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
        {
            if (game->board[i][k] == 0 || game->board[i][k] == 1)
            {
                write(STDOUT_FILENO, leftBorder, ft_strlen(leftBorder));
                write(STDOUT_FILENO, color_codes[game->board[i][k]], ft_strlen(color_codes[game->board[i][k]]));
                write(STDOUT_FILENO, circleTop, ft_strlen(circleTop));
                write(STDOUT_FILENO, color_codes[COLOR_GRAY], ft_strlen(color_codes[COLOR_GRAY]));
                write(STDOUT_FILENO, rightBorder, ft_strlen(rightBorder));
            }
            else
                write(STDOUT_FILENO, emptyBorder, ft_strlen(emptyBorder));
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
        {
            if (game->board[i][k] != -1)
            {
                write(STDOUT_FILENO, leftBorder, ft_strlen(leftBorder));
                write(STDOUT_FILENO, color_codes[game->board[i][k]], ft_strlen(color_codes[game->board[i][k]]));
                write(STDOUT_FILENO, circleBottom, ft_strlen(circleBottom));
                write(STDOUT_FILENO, color_codes[COLOR_GRAY], ft_strlen(color_codes[COLOR_GRAY]));
                write(STDOUT_FILENO, rightBorder, ft_strlen(rightBorder));
            }
            else
                write(STDOUT_FILENO, emptyBorder, ft_strlen(emptyBorder));
        }
        write(STDOUT_FILENO, "\n", 1);
        for (int k = 0; k < game->cols; k++)
            write(STDOUT_FILENO, bottomBorder, ft_strlen(bottomBorder));
        write(STDOUT_FILENO, "\n", 1);
        write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
    }
    write(STDOUT_FILENO, "\n", 1);
    printTurn_n_pos(game);
}
