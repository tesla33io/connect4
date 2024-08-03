/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 19:21:52 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> /* DELETE */

/* int	main(int ac, char *av[])
{
	srand(time(NULL));
	(void)ac;
	(void)av;
	uint64_t	bp1[MAX_SIZE], bp2[MAX_SIZE] = {0};
	clear_board(bp1, MAX_SIZE);
	clear_board(bp2, MAX_SIZE);
	t_TreeNode	*node = tree_new(bp1, bp2, 1, -1);
	node->bp1[0] = 1ULL << 3;
	t_Settings	as;
	as.wi = 10;
	as.he = 10;
	as.dificulty = 5 % as.wi;
	as.depth = 3;
	build_tree(node, &as);
	return (0);
}
*/

int	build_tree(t_TreeNode *root, t_Settings *as)
{
	// used to store prev nodes to be able to go back
	t_list	*stack = ft_lstnew((void*) root);
	if (!stack)
		return (on_crash_code(MEMALLOC_FAIL, -1, __FILE_NAME__, __LINE__));
	// priority queue, store nodes to visit depending on their score
	t_deque	*priority = gc_malloc(sizeof(*priority));
	if (!priority)
		return (on_crash_code(MEMALLOC_FAIL, -1, __FILE_NAME__, __LINE__));
	t_TreeNode	*cur = root;
	int			total_N = 0;
	while (1)
	{
		printf("Root [%p]\n", (void *) cur);
		fill_mask(cur->mask, cur->bp1, cur->bp2, MAX_SIZE, MAX_SIZE);
		printBitBoard(cur->mask, cur->bp1, as->he, as->wi);
		uint8_t	played_moves[as->dificulty];
		uint8_t	n_played_moves = 0;
		uint8_t	rollout = 0;
		for (int c = 0; c < as->dificulty; ++c)
		{
			t_TreeNode	*child = tree_new(cur->bp1, cur->bp2,
					3 - cur->player_to_move, -1);

			// Find valid moves
			uint8_t	valid_moves[as->dificulty];
			uint8_t	n_valid_moves = 0;
			for (uint8_t col = 0; col < as->wi; ++col)
			{
				if (is_valid_move(child, col, as->dificulty)
					&& !i_in(played_moves, col, as->dificulty))
					valid_moves[n_valid_moves++] = col;
			}
			if (n_valid_moves > 0)
			{
				uint8_t	move = valid_moves[rand() % n_valid_moves];
				apply_move(child, move, child->player_to_move);
				played_moves[n_played_moves++] = move;
				rollout = sim_rand_game(child, as);
				if (rollout == cur->player_to_move)
					(cur->wins++, child->wins++);
				else if (rollout == 3 - cur->player_to_move)
					(cur->wins--, child->wins--);
				cur->vis++;
				child->vis++;
			}
			printf("Child [%d] [%p]\n", c, (void *) child);
			fill_mask(child->mask, child->bp1, child->bp2, MAX_SIZE, MAX_SIZE);
			printBitBoard(child->mask, child->bp1, as->he, as->wi);
		}
		total_N += cur->vis;
		printf("========\nUTC\n========\n");
		printf("w=%d n=%d N=%d c=%f\n",
				cur->wins, cur->vis, total_N, ft_sqrt(2));
		printf("%f\n",
				(
				 ((double) cur->wins/cur->vis)
				 +
				 ft_sqrt(2)
				 *
				 ft_sqrt(
					 log((double) total_N)/cur->vis
					 )
				)
			  );
		break ;
	}
	return (0);
}

int	sim_rand_game(t_TreeNode *parent, t_Settings *as)
{
	if (!parent || !as)
		return (on_crash_code(INVALID_FUNC_ARGS, -1, __FILE_NAME__, __LINE__));
	t_TreeNode	sim_node = *parent;
//	for (int i = 0; i < as->dificulty; ++i)
//		sim_node.children[i] = NULL;

	int	result = 0;
	// Play random game
	while (1)
	{
		if ((result = check_terminal_state(&sim_node)) != 0)
		{
			ft_putnbr_lft_fd(result, 1);
			ft_putendl_fd("", 1);
			break ;
		}
		// Find valid moves
		uint8_t	valid_moves[as->dificulty];
		uint8_t	n_valid_moves = 0;
		for (uint8_t col = 0; col < as->wi; ++col)
		{
			if (is_valid_move(&sim_node, col, as->dificulty))
				valid_moves[n_valid_moves++] = col;
		}
		if (n_valid_moves > 0)
		{
			uint8_t	move = valid_moves[rand() % n_valid_moves];
			apply_move(&sim_node, move, sim_node.player_to_move);
			sim_node.player_to_move = 3 - sim_node.player_to_move;
		}
	}
	return (result);
}

void	apply_move(t_TreeNode *node, int col, int player)
{
	for (int row = 0; row < MAX_SIZE; row++)
	{
		if (!(node->mask[row] & (1ULL << col)))
		{
			node->mask[row] |= (1ULL << col);
			if (player == 1)
				node->bp1[row] |= (1ULL << col);
			else
				node->bp2[row] |= (1ULL << col);
			break;
		}
	}
}

int	check_winner(uint64_t bp[MAX_SIZE], int player)
{
	// Horizontal check
	for (int row = 0; row < MAX_SIZE; row++) {
		for (int col = 0; col < MAX_SIZE - 3; col++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row] & (1ULL << (col + 1))) &&
				(bp[row] & (1ULL << (col + 2))) &&
				(bp[row] & (1ULL << (col + 3)))) {
				return (player);
			}
		}
	}
	// Vertical check
	for (int col = 0; col < MAX_SIZE; col++) {
		for (int row = 0; row < MAX_SIZE - 3; row++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row + 1] & (1ULL << col)) &&
				(bp[row + 2] & (1ULL << col)) &&
				(bp[row + 3] & (1ULL << col))) {
				return (player);
			}
		}
	}
	// Diagonal (positive slope) check
	for (int row = 0; row < MAX_SIZE - 3; row++) {
		for (int col = 0; col < MAX_SIZE - 3; col++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row + 1] & (1ULL << (col + 1))) &&
				(bp[row + 2] & (1ULL << (col + 2))) &&
				(bp[row + 3] & (1ULL << (col + 3)))) {
				return (player);
			}
		}
	}
	// Diagonal (negative slope) check
	for (int row = 3; row < MAX_SIZE; row++) {
		for (int col = 0; col < MAX_SIZE - 3; col++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row - 1] & (1ULL << (col + 1))) &&
				(bp[row - 2] & (1ULL << (col + 2))) &&
				(bp[row - 3] & (1ULL << (col + 3)))) {
				return (player);
			}
		}
	}
	return (0);
}

int	check_terminal_state(t_TreeNode *node)
{
	int winner = check_winner(node->bp1, 1);
	if (winner)
		return (winner);
	winner = check_winner(node->bp2, 2);
	if (winner)
		return (winner);
	// Check for draw (if the top row is full)
	for (int col = 0; col < MAX_SIZE; col++)
	{
		if (!(node->mask[MAX_SIZE - 1] & (1ULL << col)))
			return (0); // Game is not over
	}
	return (3); // Draw
}
