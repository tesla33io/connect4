###########################
###### MAIN SETTINGS ######
###########################

# Compiler to be used
CC				:= cc

# Compiler flags
CFLAGS			:= -Wall -Werror -Wextra -O3 -g

# Libraries to be linked (if any)
LIBS			= -L $(LFT_PATH) -lft -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lm
#L/opt/homebrew/bin/sdl2-config
# LIBS			= -L $(LFT_PATH) -lft -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 
#L/opt/homebrew/bin/sdl2-config
# Include directories
INCLUDES		:= -Iinc/

# Target executable
TARGET			:= connect4

# Source files directory
SRC_DIR			:= src/

# Source files
SRC_FILES		+= main.c  
SRC_FILES		+= tui/board_utils.c  
SRC_FILES		+= tui/game_utils.c  
SRC_FILES		+= tui/printBoard.c  
SRC_FILES		+= tui/gameState.c  
SRC_FILES		+= algo/algo.c
SRC_FILES		+= algo/tree.c
SRC_FILES		+= algo/utils.c
SRC_FILES		+= algo/winner_state.c
SRC_FILES		+= gnl/get_next_line.c
SRC_FILES		+= gnl/get_next_line_utils.c

# bonus related files
SRC_FILES		+= bonus/run_game_visual.c
SRC_FILES		+= bonus/process_input.c
SRC_FILES		+= bonus/execute_turns.c
SRC_FILES		+= bonus/render_board.c


# Object files directory
OBJ_DIR			:= obj/

# Object files
OBJ_FILES		:= $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_FILES))

# Dependency files directory
DEP_DIR			:= dep/

# Dependency files
DEPENDS			:= $(patsubst %.o, $(DEP_DIR)%.d, $(OBJ_FILES))
-include $(DEPENDS)


############################
###### SHELL COMMANDS ######
############################

RM				:= /bin/rm -f
MKDIR			:= /bin/mkdir -p
TOUCH			:= /bin/touch


#############################
###### LOCAL LIBRARIES ######
#############################

LFT_PATH		:= lib/libft
LFT_BIN			:=$(LFT_PATH)/libft.a

############################
###### DEBUG SETTINGS ######
############################

ifeq ($(DEBUG), 1)
	CFLAGS		+= -g3 -O0
endif

################################
###### TARGET COMPILATION ######
################################

.DEFAULT_GOAL	:= all

all: $(TARGET) ## Build this project

# Compilation rule for object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o, %.d, $@) $(INCLUDES) -c $< -o $@

# Rule for linking the target executable
$(TARGET): $(OBJ_FILES) $(LFT_BIN)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(INCLUDES) $(LIBS)
	-@echo -n "🚀 $(MAGENTA)" && ls -lah $(TARGET) && echo -n "$(RESET)"

#-lSDL2 $(sdl2-config --cflags --libs)

####################################
###### LOCAL LIBS COMPILATION ######
####################################

$(LFT_BIN):
	@make -C $(LFT_PATH)

##############################
###### ADDITIONAL RULES ######
##############################

clean: ## Clean objects and dependencies
	@make -C $(LFT_PATH) clean
	$(RM) $(OBJ_FILES)
	$(RM) -r $(OBJ_DIR)
	$(RM) $(DEPENDS)
	$(RM) -r $(DEP_DIR)

fclean: clean ## Restore project to initial state
	@make -C $(LFT_PATH) fclean
	$(RM) $(TARGET)

re: fclean all ## Rebuild project

help: ## Show help info
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "$(CYAN)%-30s$(RESET) %s\n", $$1, $$2}'

.PHONY: all re clean fclean help


####################
###### COLORS ######
####################
# Color codes
RESET		:= \033[0m
BOLD		:= \033[1m
UNDERLINE	:= \033[4m

# Regular colors
BLACK		:= \033[30m
RED			:= \033[31m
GREEN		:= \033[32m
YELLOW		:= \033[33m
BLUE		:= \033[34m
MAGENTA		:= \033[35m
CYAN		:= \033[36m
WHITE		:= \033[37m

# Background colors
BG_BLACK	:= \033[40m
BG_RED		:= \033[41m
BG_GREEN	:= \033[42m
BG_YELLOW	:= \033[43m
BG_BLUE		:= \033[44m
BG_MAGENTA	:= \033[45m
BG_CYAN		:= \033[46m
BG_WHITE	:= \033[47m
