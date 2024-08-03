/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:24:23 by astavrop          #+#    #+#             */
/*   Updated: 2024/08/03 14:48:25 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../../inc/algo.h"
#include <stdint.h>

int	on_crash_code(char *msg, int code, char *file, int line)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_lft_fd(line, 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(msg, 2);
	gc_free_gc(0);
	return (code);
}

void	*on_crash_null(char *msg, char *file, int line)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_lft_fd(line, 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(msg, 2);
	gc_free_gc(0);
	return (NULL);
}

void	copy_board_row(uint64_t src[MAX_SIZE], uint64_t dest[MAX_SIZE])
{
	for (int i = 0; i < MAX_SIZE; ++i)
		dest[i] = src[i];
}

int is_valid_move(t_TreeNode *node, uint8_t col, uint8_t dificulty)
{
	return !(node->mask[dificulty - 1] & (1ULL << col));
}

double ft_sqrt(double x)
{
	// for 0 and 1, the square roots are themselves
	if (x < 2)
		return (x);
	// considering the equation values
	double y = x;
	double z = (y + (x / y)) / 2;
	// as we want to get upto 3 decimal digits, the absolute
	// difference should not exceed 0.001
	while (FABS(y - z) >= 0.001)
	{
		y = z;
		z = (y + (x / y)) / 2;
	}
	return (z);
}

double ft_ln(double x)
{
	// Trap illegal values
	if (x <= 0)
		return (0.0/0.0);  // NaN
	// Confine x to a sensible range
	int power_adjust = 0;
	while (x > 1.0)
	{
		x /= EULER_CONST;
		power_adjust++;
	}
	while (x < .25)
	{
		x *= EULER_CONST;
		power_adjust--;
	}
	// Now use the Taylor series to calculate the logarithm
	x -= 1.0;
	double t = 0.0, s = 1.0, z = x;
	for (int k=1; k<=TAYLOR_ITERATIONS; k++)
	{
		t += z * s / k;
		z *= x;
		s = -s;
	}
	// Combine the result with the power_adjust value and return
	return (t + power_adjust);
}
