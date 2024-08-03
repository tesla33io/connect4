/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 19:20:00 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* int	main(int ac, char *av[])
{
	srand(time(NULL));
	(void)ac;
	(void)av;
	uint64_t	bp1[MAX_SIZE], bp2[MAX_SIZE] = {0};
	t_TreeNode	*node = tree_new(bp1, bp2, 1, -1);
	t_Settings	as;
	as.dificulty = 5;
	as.wi = 7;
	as.he = 6;
	sim_rand_game(node, &as);
	return (0);
} */

int	sim_rand_game(t_TreeNode *parent, t_Settings *as)
{
	if (!parent || !as)
		return (on_crash_code(INVALID_FUNC_ARGS, -1, __FILE__, __LINE__));
	t_TreeNode	sim_node = *parent;
	for (int i = 0; i < as->dificulty; ++i)
		sim_node.children[i] = NULL;

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
		printBitBoard(sim_node.mask, sim_node.bp1, as->he, as->wi);
		ft_putstr_fd("-- -- -- -- --\n", 1);
	}
	return (0);
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
