#ifndef COLORS_H
#define COLORS_H

// Define an enum for color names
typedef enum {
    COLOR_YELLOW, // "\033[93m"
    COLOR_RED,    // "\033[91m"
    COLOR_GREEN,  // "\033[92m"
    COLOR_BLUE,   // "\033[94m"
    COLOR_MAGENTA,// "\033[95m"
    COLOR_CYAN,   // "\033[96m"
    COLOR_WHITE,  // "\033[97m"
    COLOR_GRAY,   // "\033[90m"
    COLOR_RESET,  // "\033[0m"
    COLOR_COUNT   // Total number of colors
} Color;

// Array of ANSI color escape codes
extern const char *color_codes[COLOR_COUNT];

#endif // COLORS_H
