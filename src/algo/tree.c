/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:05:32 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/04 18:22:14 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"
#include <stdio.h>
#include <stdint.h>

t_TreeNode	*tree_new(uint64_t sbp1[MAX_SIZE], uint64_t sbp2[MAX_SIZE],
	int player, int nc)
{
	t_TreeNode	*new_node = NULL;

	if (!sbp1 || !sbp2)
		return (on_crash_null(INVALID_FUNC_ARGS, __FILE__, __LINE__));

	new_node = gc_malloc(sizeof(*new_node));
	if (!new_node)
		return (on_crash_null(MEMALLOC_FAIL, __FILE__, __LINE__));
	new_node->bp1 = gc_malloc(sizeof(uint64_t) * MAX_SIZE);
	if (!new_node->bp1)
		return (on_crash_null(MEMALLOC_FAIL, __FILE__, __LINE__));
	new_node->bp2 = gc_malloc(sizeof(uint64_t) * MAX_SIZE);
	if (!new_node->bp2)
		return (on_crash_null(MEMALLOC_FAIL, __FILE__, __LINE__));
	new_node->mask = gc_malloc(sizeof(uint64_t) * MAX_SIZE);
	if (!new_node->mask)
		return (on_crash_null(MEMALLOC_FAIL, __FILE__, __LINE__));
	copy_board(sbp1, new_node->bp1, MAX_SIZE);
	copy_board(sbp2, new_node->bp2, MAX_SIZE);
	fill_mask(new_node->mask, new_node->bp1, new_node->bp2, MAX_SIZE, MAX_SIZE);

	new_node->score = 0;
	new_node->wins = 0;
	new_node->vis = 0;
	new_node->parent = NULL;
	new_node->children = gc_malloc(sizeof(t_TreeNode) * nc);
	new_node->num_children = 0;
	new_node->player_to_move = player;
//	new_node->last_move_col = lmc;
	return (new_node);
}

int	tree_insert_child(t_TreeNode *parent, t_TreeNode *child)
{
	if (!parent || !child)
		return (on_crash_code(INVALID_FUNC_ARGS, -1, __FILE__, __LINE__));
	if (parent->children == NULL)
	{
		parent->children = gc_malloc(sizeof(t_TreeNode *) * MAX_SIZE);
		if (!parent->children)
			return (on_crash_code(MEMALLOC_FAIL, -1, __FILE__, __LINE__));
	}
	int	i = 0;
	while (parent->children[i] && i < MAX_SIZE)
		i++;
	parent->children[i] = child;
	child->parent = parent;
	parent->num_children++;
	return (0);
}
