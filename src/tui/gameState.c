#include "../../inc/connect_four.h"

void    theWinner();
void    drawGame()
{
    const char *title = 
        "\n"
    "   ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██╗   ██╗███████╗██████╗ \n"
    "  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝   ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n"
    "  ██║  ███╗███████║██╔████╔██║█████╗     ██║   ██║██║   ██║█████╗  ██████╔╝\n"
    "  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝     ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n"
    "  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n"
    "   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n"
    "\n";
    write(STDOUT_FILENO, COLOR_GRAY, ft_strlen(COLOR_GRAY));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
}

void    userWinner()
{
    const char *title = 
    "\n"
    "\t██╗   ██╗ ██████╗ ██╗   ██╗     █████╗ ██████╗ ███████╗\n"
    "\t╚██╗ ██╔╝██╔═══██╗██║   ██║    ██╔══██╗██╔══██╗██╔════╝\n"
    "\t ╚████╔╝ ██║   ██║██║   ██║    ███████║██████╔╝█████╗\n"
    "\t  ╚██╔╝  ██║   ██║██║   ██║    ██╔══██║██╔══██╗██╔══╝\n"
    "\t   ██║   ╚██████╔╝╚██████╔╝    ██║  ██║██║  ██║███████╗\n"
    "\t   ╚═╝    ╚═════╝  ╚═════╝     ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝\n";
    write(STDOUT_FILENO, COLOR_MAGENTA, ft_strlen(COLOR_MAGENTA));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
    theWinner();
}


void    botWinner()
{
    const char *title = 
    "\n"
    "\t\t██████╗  ██████╗ ████████╗  \n"
    "\t\t██╔══██╗██╔═══██╗╚══██╔══╝  \n"
    "\t\t██████╔╝██║   ██║   ██║     \n"
    "\t\t██╔══██╗██║   ██║   ██║     \n"
    "\t\t██████╔╝╚██████╔╝   ██║     \n"
    "\t\t╚═════╝  ╚═════╝    ╚═╝     \n";
    write(STDOUT_FILENO, COLOR_MAGENTA, ft_strlen(COLOR_MAGENTA));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
    theWinner();
}

void    theWinner()
{
    const char *title = 
    "\n"
    "████████╗██╗  ██╗███████╗    ██╗    ██╗██╗███╗   ██╗███╗   ██╗███████╗██████╗ ██╗\n"
    "╚══██╔══╝██║  ██║██╔════╝    ██║    ██║██║████╗  ██║████╗  ██║██╔════╝██╔══██╗██║\n"
    "   ██║   ███████║█████╗      ██║ █╗ ██║██║██╔██╗ ██║██╔██╗ ██║█████╗  ██████╔╝██║\n"
    "   ██║   ██╔══██║██╔══╝      ██║███╗██║██║██║╚██╗██║██║╚██╗██║██╔══╝  ██╔══██╗╚═╝\n"
    "   ██║   ██║  ██║███████╗    ╚███╔███╔╝██║██║ ╚████║██║ ╚████║███████╗██║  ██║██╗\n"
    "   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚═╝\n";                                                                                                         

    write(STDOUT_FILENO, COLOR_MAGENTA, ft_strlen(COLOR_MAGENTA));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, COLOR_RESET, ft_strlen(COLOR_RESET));
}