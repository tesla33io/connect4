#include "../../inc/colors.h"

// Initialize the array with ANSI escape codes
const char *color_codes[COLOR_COUNT] = {
    "\033[93m", // Yellow
    "\033[91m", // Red
    "\033[92m", // Green
    "\033[94m", // Blue
    "\033[95m", // Magenta
    "\033[96m", // Cyan
    "\033[97m", // White
    "\033[90m",  // Gray
    "\033[0m"   // Reset
};
