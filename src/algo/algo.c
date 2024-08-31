/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:13:11 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/31 16:29:52 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"
#include "../../inc/connect_four.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* int	main(int ac, char *av[])
{
	srand(time(NULL));
	(void)ac;
	(void)av;
	t_Settings	as;
	as.wi = 10;
	as.he = 10;
	as.dificulty = 5;
	as.depth = 3;
	uint64_t	bp1[MAX_SIZE], bp2[MAX_SIZE] = {0};
	clear_board(bp1, MAX_SIZE);
	clear_board(bp2, MAX_SIZE);
	t_TreeNode	*node = tree_new(bp1, bp2, 1, as.dificulty);
	node->bp1[0] = 1ULL << 3;
	printf("Suggested move: %d\n", build_tree(node, &as));
	gc_free_gc(0);
	return (0);
}
*/

int	calc_ai_turn(uint64_t *bp1, uint64_t *bp2, uint8_t player, t_game *g)
{
	t_Settings	as;
	as.wi = g->cols;
	as.he = g->rows;
	as.dificulty = 5;
	as.depth = 3;
	// clear_board(bp1, MAX_SIZE);
	// clear_board(bp2, MAX_SIZE);
	t_TreeNode	*node = tree_new(bp1, bp2, player, as.dificulty);
	int	sug = build_tree(node, &as);
	gc_free_gc(0);
	return (sug);
}

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
	priority->head = NULL;
	priority->size = 0;

	uint64_t	nnode = 0;
	uint8_t		pm[as->dificulty];
	uint8_t		n_pm = 0;

	// Create first five random next positions
	for (int c = 0; c < as->dificulty; ++c)
	{

		uint8_t	rollout = 0;
		t_TreeNode	*child = tree_new(root->bp1, root->bp2,
				3 - root->player_to_move, as->dificulty);
		root->children[c] = child;
		child->parent = root;
		nnode++;

		// Find valid moves
		uint8_t	valid_moves[as->dificulty];
		uint8_t	n_valid_moves = 0;
		for (uint8_t col = 0; col < as->wi; ++col)
		{
			if (is_valid_move(child, col, as->dificulty)
					&& !i_in(pm, col, as->dificulty))
				valid_moves[n_valid_moves++] = col;
		}
		if (n_valid_moves > 0)
		{
			uint8_t	move = valid_moves[rand() % n_valid_moves];
			child->move_made = move;
			apply_move(child, move, child->player_to_move);
			pm[n_pm++] = move;
			rollout = simulate(child, as);
			if (rollout == root->player_to_move)
			{
				root->wins++;
				child->wins++;
			}
			else if (rollout == 3 - root->player_to_move)
			{
				root->wins--;
				child->wins--;
			}
			root->vis++;
			child->vis++;

			double	exploi = ((double) rollout == root->player_to_move ? 1:0 / child->vis);
			double	explor  = EXPLOR_CONST * ft_sqrt(ft_ln((double) root->vis) / child->vis);
			child->score = exploi + explor;

			deque_emplace_back(priority, (void *) child);
		}
	}
	while (nnode < (5*5*5*5))
	{
		// printf("nnode:%ld\n", nnode);
		uint8_t		played_moves[as->dificulty];
		uint8_t		n_played_moves = 0;
		t_deque_node	*to_explore = deque_pop_front(priority);
		if (!to_explore)
			break ;
		t_TreeNode		*cur = (t_TreeNode *) to_explore->data;
		gc_free_ptr((void **) &to_explore);

		for (int c = 0; c < as->dificulty; ++c)
		{

			uint8_t	rollout = 0;
			t_TreeNode	*child = tree_new(cur->bp1, cur->bp2,
					3 - cur->player_to_move, as->dificulty);
			child->parent = cur;
			cur->children[c] = child;
			nnode++;

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
				child->move_made = move;
				apply_move(child, move, child->player_to_move);
				played_moves[n_played_moves++] = move;
				rollout = simulate(child, as);
				if (rollout == cur->player_to_move)
					child->wins++;
				else if (rollout == 3 - cur->player_to_move)
					child->wins--;
				child->vis++;

				double	exploi = ((double) rollout == cur->player_to_move ? 1:0 / child->vis);
				double	explor  = EXPLOR_CONST * ft_sqrt(ft_ln((double) cur->vis) / child->vis);
				child->score = exploi + explor;

				deque_emplace_back(priority, (void *) child);
			}
		}
		backpropagate(cur, as);
	}
	double		best_score = -9999999;
	t_TreeNode	*best_node = NULL;
	for (int i = 0; i < as->dificulty; ++i)
	{
		if (root->children[i]->score > best_score)
		{
			best_score = root->children[i]->score;
			best_node = root->children[i];
		}
		// printf("[%d] %f\n", i, root->children[i]->score);
		// printf("[%d] w:%d v:%d\n\n", i, root->children[i]->wins, root->children[i]->vis);
	}
	return (best_node->move_made);
}

void	backpropagate(t_TreeNode *parent, t_Settings *as)
{
	double		best_score = -9999999;
	t_TreeNode	*best_node = NULL;
	t_TreeNode	*child = NULL;
	for (int c = 0; c < as->dificulty; ++c)
	{
		child = parent->children[c];
		parent->wins += child->wins;
		parent->vis += child->vis;
	//	double	score = (((double) child->wins / child->vis)
	//		+ EXPLOR_CONST * ft_sqrt(ft_ln(parent->vis) / child->vis));
		double	score = (double) child->wins / child->vis;
		if (score > best_score)
		{
			best_score = score;
			best_node = child;
		}
	}
	if (best_node)
		parent->score = best_score;
	if (parent->parent)
		backpropagate(parent->parent, as);
}

int	simulate(t_TreeNode *parent, t_Settings *as)
{
	if (!parent || !as)
		return (on_crash_code(INVALID_FUNC_ARGS, -1, __FILE_NAME__, __LINE__));
	t_TreeNode	sim_node = *parent;

	int	result1 = 0;
	int	result2 = 0;
	int	i = 0;
	// Play random game
	while (i + 1)
	{
		// printf("%d\n", i);
		if ((result1 = isWinner(sim_node.bp1, as->he, as->wi)) == 1
			|| (result2 = isWinner(sim_node.bp2, as->he, as->wi) == 1))//check_terminal_state(&sim_node, as)) != 0)
			break ;
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
		else
			break ;
	}
	return (result1 == 1 ? 1 : 2);
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

int	check_winner(uint64_t *bp, int player, int rmax, int cmax)
{
	// Horizontal check
	for (int row = 0; row < rmax; row++) {
		for (int col = 0; col < cmax - 3; col++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row] & (1ULL << (col + 1))) &&
				(bp[row] & (1ULL << (col + 2))) &&
				(bp[row] & (1ULL << (col + 3)))) {
				return (player);
			}
		}
	}
	// Vertical check
	for (int col = 0; col < cmax; col++) {
		for (int row = 0; row < rmax - 3; row++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row + 1] & (1ULL << col)) &&
				(bp[row + 2] & (1ULL << col)) &&
				(bp[row + 3] & (1ULL << col))) {
				return (player);
			}
		}
	}
	// Diagonal (positive slope) check
	for (int row = 0; row < rmax - 3; row++) {
		for (int col = 0; col < cmax - 3; col++) {
			if ((bp[row] & (1ULL << col)) &&
				(bp[row + 1] & (1ULL << (col + 1))) &&
				(bp[row + 2] & (1ULL << (col + 2))) &&
				(bp[row + 3] & (1ULL << (col + 3)))) {
				return (player);
			}
		}
	}
	// Diagonal (negative slope) check
	for (int row = 3; row < rmax; row++) {
		for (int col = 0; col < cmax - 3; col++) {
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

int	check_terminal_state(t_TreeNode *node, t_Settings *as)
{
	int winner = check_winner(node->bp1, 1, as->he, as->wi);
	if (winner)
		return (winner);
	winner = check_winner(node->bp2, 2, as->he, as->wi);
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
