/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:26:40 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/03 15:01:12 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "./connect_four.h"
# include <stdint.h>

typedef struct	s_TreeNode {
	uint64_t			bp1[MAX_SIZE];
	uint64_t			bp2[MAX_SIZE];
	uint64_t			mask[MAX_SIZE];
	int					score; // not sure if it's gonna be used
	int					wins;
	int					sims;
	struct s_TreeNode	*parent;
	struct s_TreeNode	**children;
	int					num_children;
	int					player_to_move;
	int					last_move_col;
}				t_TreeNode;

typedef struct	s_AlgoSettings {
	uint8_t		dificulty;	// Number of simulations per node
	uint8_t		wi;			// width
	uint8_t		he;			// height
}				t_Settings;

# define MEMALLOC_FAIL "memory allocation failed"
# define INVALID_FUNC_ARGS "invalid function arguments"

# define EULER_CONST 2.718281828459045235
# define TAYLOR_ITERATIONS 20
# define FABS(x) ((x) > 0 ? (x) : -(x))

/* Algo (alog.c) */

int				sim_rand_game(t_TreeNode *parent, t_Settings *as);
void			apply_move(t_TreeNode *node, int col, int player);
int				check_winner(uint64_t bp[MAX_SIZE], int player);
int				check_terminal_state(t_TreeNode *node);

/* Tree (tree.c) */

t_TreeNode		*tree_new(uint64_t sbp1[MAX_SIZE], uint64_t sbp2m[MAX_SIZE],
	int player, int lmc);

/* Utils (utils.c) */

int				on_crash_code(char *msg, int code, char *file, int line);
void			*on_crash_null(char *msg, char *file, int line);

void			copy_board_row(uint64_t src[MAX_SIZE], uint64_t dest[MAX_SIZE]);
int				is_valid_move(t_TreeNode *node, uint8_t col, uint8_t dificulty);

double			ft_sqrt(double x);
double			ft_ln(double x);

#endif /* ALGO_H */
