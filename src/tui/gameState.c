#include "../../inc/connect_four.h"

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
    write(STDOUT_FILENO, color_codes[COLOR_GRAY], ft_strlen(color_codes[COLOR_GRAY]));
    write(STDOUT_FILENO, title, ft_strlen(title));
    write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
    // write(STDOUT_FILENO, "P R E S S  \n", 13);
    // write(STDOUT_FILENO, color_codes[COLOR_GREEN], ft_strlen(color_codes[COLOR_GREEN]));
    // write(STDOUT_FILENO, "\tE N T E R", 11);
    // write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
    // write(STDOUT_FILENO, "  T O  C O N T I N U E\n", 24);
    // write(STDOUT_FILENO, color_codes[COLOR_YELLOW], ft_strlen(color_codes[COLOR_YELLOW]));
    // write(STDOUT_FILENO, "\t'Q'", 5);
    // write(STDOUT_FILENO, color_codes[COLOR_RESET], ft_strlen(color_codes[COLOR_RESET]));
    // write(STDOUT_FILENO, "  T O  E X I T\n", 15);
}
