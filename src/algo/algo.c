/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 13:05:27 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"

#include <stdint.h>
#include <stdio.h>

/* int	main(int ac, char *av[])
{
	(void)ac;
	(void)av;
	uint64_t	bp1[MAX_SIZE], bp2[MAX_SIZE] = {0};
	t_TreeNode	*node = tree_new(bp1, bp2, 2, -1);
	node->bp1[0] = 15;
	printf("Win: %d\n", check_terminal_state(node));
	return (0);
} */

int	sim_rand_game(t_TreeNode *parent)
{
	t_TreeNode	*game_node = tree_new(parent->bp1, parent->bp2,
		parent->player_to_move, parent->last_move_col);
	(void)game_node;
	return (0);
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
