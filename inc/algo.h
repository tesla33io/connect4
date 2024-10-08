/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:26:40 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 20:07:09 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "./connect_four.h"
# include <stdint.h>

/* Can be allocated on stack without (score, wins, sims, parent, last_move_col)
 * up to 200000 elements 
 *
 * Can be allocated on stack with all those params up to 100000 elements */
typedef struct	s_TreeNode {
	uint64_t			*bp1;
	uint64_t			*bp2;
	uint64_t			*mask;
	double				score; // not sure if it's gonna be used
	int					wins;
	int					vis;
	struct s_TreeNode	*parent;
	struct s_TreeNode	**children;
	int					num_children;
	int					player_to_move;
	uint8_t				move_made;
}				t_TreeNode;

typedef struct	s_AlgoSettings {
	uint8_t		dificulty;	// Number of simulations per node
	uint8_t		wi;			// width
	uint8_t		he;			// height
	uint8_t		depth;		// depth of tree
}				t_Settings;

# define MEMALLOC_FAIL "memory allocation failed"
# define INVALID_FUNC_ARGS "invalid function arguments"

# define EULER_CONST 2.718281828459045235
# define TAYLOR_ITERATIONS 20
# define EXPLOR_CONST 1.414213562
# define FABS(x) ((x) > 0 ? (x) : -(x))

/* Algo (alog.c) */

int				calc_ai_turn(uint64_t *bp1, uint64_t *bp2, uint8_t player,
	t_game *g);

int				build_tree(t_TreeNode *root, t_Settings *as);
int				simulate(t_TreeNode *parent, t_Settings *as);
void			backpropagate(t_TreeNode *parent, t_Settings *as);
void			apply_move(t_TreeNode *node, int col, int player);
int				check_winner(uint64_t *bp, int player, int rmax, int cmax);
int				check_terminal_state(t_TreeNode *node, t_Settings *as);

/* Tree (tree.c) */

t_TreeNode		*tree_new(uint64_t sbp1[MAX_SIZE], uint64_t sbp2m[MAX_SIZE],
	int player, int nc);

/* Utils (utils.c) */

int				on_crash_code(char *msg, int code, char *file, int line);
void			*on_crash_null(char *msg, char *file, int line);

void			copy_board(uint64_t *src, uint64_t *dest, uint8_t max);
void			clear_board(uint64_t *b, uint8_t max);
int				fill_mask(uint64_t *mask, uint64_t *b1, uint64_t *b2, uint8_t rmax,
	uint8_t cmax);
int				is_valid_move(t_TreeNode *node, uint8_t col, uint8_t dificulty);

uint8_t			i_in(uint8_t *arr, uint8_t i, uint8_t max);
double			ft_sqrt(double x);
double			ft_ln(double x);

#endif /* ALGO_H */
